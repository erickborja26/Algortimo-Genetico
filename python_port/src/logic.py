from __future__ import annotations

import math
import random
from dataclasses import dataclass, field
from typing import Dict, List, Tuple, Optional
from pathlib import Path
import re

from . import SEstAul, SEstCDA, SEstCDo, SEstCHo, SEstCur, SEstDoc, SEstPAd, SEstTAu, SEstTHo
from .state import GlobalState


def _trim(bs: bytes) -> str:
    return bs.decode("cp1252", errors="ignore").rstrip("\x00 ").strip()


@dataclass
class LisACaLogic:
    state: GlobalState
    # Datos cargados desde los .ct1
    tipos_aula: List[SEstTAu] = field(default_factory=list)
    aulas: List[SEstAul] = field(default_factory=list)
    docentes: List[SEstDoc] = field(default_factory=list)
    cursos: List[SEstCur] = field(default_factory=list)
    cursos_hora: List[SEstCHo] = field(default_factory=list)
    cursos_docente: List[SEstCDo] = field(default_factory=list)
    config: Optional[SEstPAd] = None

    # Arreglos de disponibilidad/ocupación (equivalentes a sArrHDA*)
    hda_aulas: List[List[List[str]]] = field(default_factory=list)   # [aula][dia][hora] -> etiqueta o "D"
    hda_aulas2: List[List[List[str]]] = field(default_factory=list)
    hda_docentes: List[List[List[str]]] = field(default_factory=list)  # [doc][dia][hora] -> "D"/"A"
    hda_ciclos: List[List[List[str]]] = field(default_factory=list)    # [ciclo][dia][hora] -> etiqueta o "D"

    # Penalidades por curso-docente
    pen_ciclo: List[int] = field(default_factory=list)
    pen_aula: List[int] = field(default_factory=list)
    pen_docente: List[int] = field(default_factory=list)
    
    # Sub-poblaciones (clasificación por ciclo/horas)
    sub_poblaciones: Dict[int, List[int]] = field(default_factory=dict)

    def __post_init__(self) -> None:
        self._load_basics()
        self._init_disponibilidad()
        # DESHABILITADO TEMPORALMENTE para debug - causa bucles infinitos
        # self._clasificar_subpoblaciones()
        # Inicializar sub_poblaciones vacío como fallback
        self.sub_poblaciones = {i: [] for i in range(15)}

    def _load_basics(self) -> None:
        """Replica CarDatTAu, CarDesAul, CarDocent, CarCursos, CarDesCHo, CarDesCDo usando GlobalState."""
        data = self.state.data
        self.tipos_aula = list(data.get("TTAula.ct1", []))
        self.aulas = list(data.get("TAulas.ct1", []))
        self.docentes = list(data.get("TDocent.ct1", []))
        self.cursos = list(data.get("TCursos.ct1", []))
        # Atributos de horas por curso (TCHoras.ct1)
        self.cursos_hora = list(data.get("TCHoras.ct1", []))
        # Cursos-Docentes: usamos TCDocen.ct1 (la estructura correcta de 32 bytes)
        # y anexamos TAsiPro.ct1 si existe (asignaciones adicionales)
        self.cursos_docente = list(data.get("TCDocen.ct1", []))
        if "TAsiPro.ct1" in data:
            self.cursos_docente.extend(data["TAsiPro.ct1"])
        # Carga configuración global (TParAdm.ct1)
        config_data = data.get("TParAdm.ct1", [])
        if config_data:
            self.config = config_data[0]
        
        # FILTRADO CRÍTICO: Eliminar registros vacíos (llenos de \x00 del binario)
        # que causaban penalidades astronómicas por falsos positivos en startswith("")
        self.cursos_docente = [x for x in self.cursos_docente if _trim(x.m_szcodcur)]
        self.docentes = [x for x in self.docentes if _trim(x.m_szcoddoc)]
        self.cursos = [x for x in self.cursos if _trim(x.m_szcodcur)]
        self.aulas = [x for x in self.aulas if _trim(x.m_szcodaul)]
        self.cursos_hora = [x for x in self.cursos_hora if _trim(x.m_szcodcur)]

    def _init_disponibilidad(self) -> None:
        """Inicializa estructuras de disponibilidad en 'D' (Disponible), emulando las tablas 4D del C++."""
        num_aulas = max(1, len(self.aulas))
        num_doc = max(1, len(self.docentes))
        # Aulas: [aula][dia(6)][hora(18)]
        self.hda_aulas = [[["D" for _ in range(18)] for _ in range(6)] for _ in range(num_aulas)]
        self.hda_aulas2 = [[["D" for _ in range(18)] for _ in range(6)] for _ in range(num_aulas)]
        # Docentes
        self.hda_docentes = [[["D" for _ in range(18)] for _ in range(6)] for _ in range(num_doc)]
        # Ciclos (hasta 10)
        self.hda_ciclos = [[["D" for _ in range(18)] for _ in range(6)] for _ in range(10)]
        # Penalidades
        total_cd = max(1, len(self.cursos_docente))
        self.pen_ciclo = [0 for _ in range(total_cd)]
        self.pen_aula = [0 for _ in range(total_cd)]
        self.pen_docente = [0 for _ in range(total_cd)]

    def _clasificar_subpoblaciones(self) -> None:
        """
        Clasifica los indices de cursos-docentes en 15 sub-poblaciones (0-14)
        basandose en el Ciclo del curso y las Horas semanales.
        
        NOTA: Dado que los datos en TProfes.ct1/TAsiPro.ct1 no contienen la información
        esperada de cursos, esta clasificación se basa en los cursos que aparecen en
        TCHoras.ct1 (que solo tiene 65 cursos únicos con información de horario).
        
        Reglas:
        - Procesa cursos de TCHoras que tengan tipo de aula empezando con "A" (Teoría).
        - Turnos (base):
          * Mañana (base=0): Ciclos 0-3 (I-IV)
          * Tarde (base=5): Ciclos 4-6 (V-VII)
          * Noche (base=10): Ciclos >= 7 (VIII-X)
        - Offset por horas (suma total):
          * 6 horas -> offset=0
          * 5 horas -> offset=1
          * 4 horas -> offset=2
          * 3 horas -> offset=3
          * 2 horas -> offset=4
        - sub_poblacion = base + offset (rango 0-14)
        """
        # Inicializar 15 sub-poblaciones
        self.sub_poblaciones = {i: [] for i in range(15)}
        
        # Construir un mapa de cursos a sus horas totales de teoría (tipo A)
        cursos_horas_teoria = {}
        for ch in self.cursos_hora:
            tipo_aula = _trim(ch.m_szctaula)
            # Solo contar si empieza con "A" (Teoría)
            if not tipo_aula.startswith("A"):
                continue
            
            codcur = _trim(ch.m_szcodcur)
            num_horas_str = _trim(ch.m_sznumhor)
            try:
                num_horas = int(num_horas_str)
            except (ValueError, AttributeError):
                num_horas = 0
            
            # Sumar horas por curso
            if codcur not in cursos_horas_teoria:
                cursos_horas_teoria[codcur] = 0
            cursos_horas_teoria[codcur] += num_horas
        
        # Procesar cada curso-docente
        for idx_cd, cd in enumerate(self.cursos_docente):
            codcur = _trim(cd.m_szcodcur)
            
            # Solo procesar si tiene horas de teoría
            if codcur not in cursos_horas_teoria:
                continue
            
            num_horas = cursos_horas_teoria[codcur]
            
            # Obtener ciclo del curso
            ciclo = self._ciclo_from_curso(codcur)
            
            # Determinar base según turno (ciclo)
            if ciclo <= 3:
                base = 0  # Mañana (I-IV)
            elif ciclo <= 6:
                base = 5  # Tarde (V-VII)
            else:
                base = 10  # Noche (VIII-X)
            
            # Determinar offset según horas
            if num_horas == 6:
                offset = 0
            elif num_horas == 5:
                offset = 1
            elif num_horas == 4:
                offset = 2
            elif num_horas == 3:
                offset = 3
            elif num_horas == 2:
                offset = 4
            else:
                offset = 0
            
            # Calcular índice de sub-población
            sub_pob_idx = base + offset
            
            # Asegurar que esté dentro del rango 0-14
            if 0 <= sub_pob_idx <= 14:
                self.sub_poblaciones[sub_pob_idx].append(idx_cd)

    def etiqueta_cd(self, idx_cd: int) -> str:
        """Devuelve etiqueta 'CUR DOC GRU' de 9 chars igual que el código C."""
        cd = self.cursos_docente[idx_cd]
        return f"{_trim(cd.m_szcodcur):<3}{_trim(cd.m_szcoddoc):<3}{_trim(cd.m_szcodgru):<3}"

    def _ciclo_from_curso(self, codcur: str) -> int:
        for cur in self.cursos:
            if _trim(cur.m_szcodcur) == codcur:
                cic = _trim(cur.m_szciccur)
                if len(cic) >= 2 and cic[0].isdigit() and cic[1].isdigit():
                    val = int(cic[:2]) - 1
                    return val if 0 <= val < 10 else 0
        return 0

    def _idx_doc(self, coddoc: str) -> int:
        for i, doc in enumerate(self.docentes):
            if _trim(doc.m_szcoddoc) == coddoc:
                return i
        return -1

    def _idx_aula(self, codaul: str) -> int:
        for i, a in enumerate(self.aulas):
            if _trim(a.m_szcodaul) == codaul:
                return i
        return -1

    # --------------------------- Asignación y penalidades --------------------------- #

    def asignar_slot(self, aula_idx: int, dia: int, hora: int, cd_idx: int, lista: int = 1) -> None:
        """Marca la asignación de un curso-docente-grupo en aula/día/hora y sugiere ciclo/docente."""
        tag = self.etiqueta_cd(cd_idx)
        if lista == 1:
            self.hda_aulas[aula_idx][dia][hora] = tag
        else:
            self.hda_aulas2[aula_idx][dia][hora] = tag
        cd = self.cursos_docente[cd_idx]
        coddoc = _trim(cd.m_szcoddoc)
        doc_idx = self._idx_doc(coddoc)
        if doc_idx >= 0:
            self.hda_docentes[doc_idx][dia][hora] = "A"
        ciclo = self._ciclo_from_curso(_trim(cd.m_szcodcur))
        self.hda_ciclos[ciclo][dia][hora] = _trim(cd.m_szcodcur)

    def calc_penalties(self) -> Dict[str, List[str]]:
        """
        Traduce la lógica central de OnCalpen - OPTIMIZADO CON PESOS DE TESIS.
        Una única pasada sobre los slots con caché de ciclos y docentes.
        Penalidades ponderadas según documento de tesis:
        - Ciclo: factor 5
        - Aula: factor 4
        - Docente: factor 2
        """
        # Reinicia contadores
        num_cd = len(self.cursos_docente)
        self.pen_ciclo = [0] * num_cd
        self.pen_aula = [0] * num_cd
        self.pen_docente = [0] * num_cd

        # PRECACHEA: ciclos y docentes
        ciclo_cache = {}
        doc_idx_cache = {}
        
        for cur in self.cursos:
            codcur = _trim(cur.m_szcodcur)
            if not codcur:  # Medida de seguridad: saltar registros vacíos
                continue
            cic = _trim(cur.m_szciccur)
            if len(cic) >= 2 and cic[0].isdigit() and cic[1].isdigit():
                val = int(cic[:2]) - 1
                ciclo_cache[codcur] = val if 0 <= val < 10 else 0
            else:
                ciclo_cache[codcur] = 0
        
        for i, doc in enumerate(self.docentes):
            coddoc = _trim(doc.m_szcoddoc)
            if not coddoc:  # Medida de seguridad: saltar registros vacíos
                continue
            doc_idx_cache[coddoc] = i

        # CONSTRUCCIÓN DEL MAPA: tag_9chars -> (idx_cd, ciclo, doc_idx)
        tag_to_info = {}
        for idx_cd, cd in enumerate(self.cursos_docente):
            codcur = _trim(cd.m_szcodcur)
            if not codcur:  # Medida de seguridad: saltar registros vacíos
                continue
            coddoc = _trim(cd.m_szcoddoc)
            codgru = _trim(cd.m_szcodgru)
            ciclo = ciclo_cache.get(codcur, 0)
            doc_idx = doc_idx_cache.get(coddoc, -1)
            tag = f"{codcur[:3]}{coddoc[0:3]}{codgru[0:3]}"
            tag_to_info[tag] = (idx_cd, ciclo, doc_idx)

        # ÚNICA PASADA SOBRE SLOTS
        slot_to_cds = {}  # (ciclo, dia, hora) -> [idx_cd, ...]
        aula_slot_to_cds = {}  # (aula_idx, dia, hora) -> [idx_cd, ...]
        doc_slot_to_cds = {}  # (doc_idx, dia, hora) -> [idx_cd, ...]
        
        for aula_idx in range(len(self.hda_aulas)):
            for dia in range(6):
                for hora in range(18):
                    tags = []
                    tag = self.hda_aulas[aula_idx][dia][hora]
                    tag2 = self.hda_aulas2[aula_idx][dia][hora]
                    if tag != "D" and len(tag) >= 9:
                        tags.append(tag)
                    if tag2 != "D" and len(tag2) >= 9:
                        tags.append(tag2)
                    
                    for tag in tags:
                        if tag in tag_to_info:
                            idx_cd, ciclo, doc_idx = tag_to_info[tag]
                            
                            # Ciclo
                            key_cic = (ciclo, dia, hora)
                            if key_cic not in slot_to_cds:
                                slot_to_cds[key_cic] = []
                            slot_to_cds[key_cic].append(idx_cd)
                            
                            # Aula
                            key_aul = (aula_idx, dia, hora)
                            if key_aul not in aula_slot_to_cds:
                                aula_slot_to_cds[key_aul] = []
                            aula_slot_to_cds[key_aul].append(idx_cd)
                            
                            # Docente
                            if doc_idx >= 0:
                                key_doc = (doc_idx, dia, hora)
                                if key_doc not in doc_slot_to_cds:
                                    doc_slot_to_cds[key_doc] = []
                                doc_slot_to_cds[key_doc].append(idx_cd)
        
        # APLICAR PENALIDADES CON PESOS DE TESIS
        # Factor 5 para penalidad de ciclo
        for cd_list in slot_to_cds.values():
            if len(cd_list) > 1:
                penalty = (len(cd_list) - 1) * 5
                for idx_cd in cd_list:
                    self.pen_ciclo[idx_cd] += penalty
        
        # Factor 4 para penalidad de aula
        for cd_list in aula_slot_to_cds.values():
            if len(cd_list) > 1:
                penalty = (len(cd_list) - 1) * 4
                for idx_cd in cd_list:
                    self.pen_aula[idx_cd] += penalty
        
        # Factor 2 para penalidad de docente
        for cd_list in doc_slot_to_cds.values():
            if len(cd_list) > 1:
                penalty = (len(cd_list) - 1) * 2
                for idx_cd in cd_list:
                    self.pen_docente[idx_cd] += penalty

        # Salidas legibles
        lines_pen_cic = []
        lines_pen_aul = []
        lines_pen_doc = []
        for idx_cd, cd in enumerate(self.cursos_docente):
            cur = _trim(cd.m_szcodcur)
            gru = _trim(cd.m_szcodgru)
            doc = _trim(cd.m_szcoddoc)
            lines_pen_cic.append(f"{cur} {gru} {doc} PEN_CIC={self.pen_ciclo[idx_cd]}")
            lines_pen_aul.append(f"{cur} {gru} {doc} PEN_AUL={self.pen_aula[idx_cd]}")
            lines_pen_doc.append(f"{cur} {gru} {doc} PEN_DOC={self.pen_docente[idx_cd]}")

        return {
            "pen_ciclo": lines_pen_cic,
            "pen_aula": lines_pen_aul,
            "pen_docente": lines_pen_doc,
        }

    # --------------------------- Población / genética simplificada --------------------------- #

    def fitness(self, idx_cd: int) -> float:
        """Función de aptitud equivalente a 1/(penalidad_total+1)."""
        total_pen = self.pen_ciclo[idx_cd] + self.pen_aula[idx_cd] + self.pen_docente[idx_cd]
        return 1.0 / (total_pen + 1.0)

    def seleccion_ruleta(self, pesos: List[float]) -> int:
        total = sum(pesos)
        if total <= 0:
            return 0
        r = random.random() * total
        acc = 0.0
        for i, w in enumerate(pesos):
            acc += w
            if r <= acc:
                return i
        return len(pesos) - 1

    def generar_poblacion(self) -> Dict[str, List[str]]:
        """
        Traducción simplificada de OnGnpobl:
        - Usa penalidades actuales para construir probabilidades.
        - Devuelve strings que representan selección de padres/hijos.
        No ejecuta cruce/mutación completa; sirve como base para completar la portación.
        """
        resumen = []
        fitness_vals = [self.fitness(i) for i in range(len(self.cursos_docente))]
        for i, fit in enumerate(fitness_vals):
            resumen.append(f"{self.etiqueta_cd(i)} FIT={fit:.4f} PEN={1/fit -1:.0f}")
        # Selecciona dos padres por ruleta
        if len(fitness_vals) >= 2:
            p1 = self.seleccion_ruleta(fitness_vals)
            p2 = p1
            while p2 == p1:
                p2 = self.seleccion_ruleta(fitness_vals)
            resumen.append(f"Padre1={self.etiqueta_cd(p1)} Padre2={self.etiqueta_cd(p2)}")
        return {"poblacion": resumen}

    # --------------------------- GA: individuos, cruce, mutación --------------------------- #

    def _current_individual(self) -> List[Tuple[int, int, int, int, int]]:
        """
        Extrae el individuo actual a partir de hda_aulas/hda_aulas2.
        Retorna lista de genes: (cd_idx, aula_idx, dia, hora, lista_id).
        """
        genes = []
        for aula_idx in range(len(self.aulas)):
            for dia in range(6):
                for hora in range(18):
                    tag = self.hda_aulas[aula_idx][dia][hora]
                    if tag != "D":
                        cd_idx = self._tag_to_cd_idx(tag)
                        if cd_idx is not None:
                            genes.append((cd_idx, aula_idx, dia, hora, 1))
                    tag2 = self.hda_aulas2[aula_idx][dia][hora]
                    if tag2 != "D":
                        cd_idx = self._tag_to_cd_idx(tag2)
                        if cd_idx is not None:
                            genes.append((cd_idx, aula_idx, dia, hora, 2))
        return genes

    def _tag_to_cd_idx(self, tag: str) -> Optional[int]:
        for idx, cd in enumerate(self.cursos_docente):
            if tag.startswith(_trim(cd.m_szcodcur)) and tag[3:6] == _trim(cd.m_szcoddoc) and tag[6:9] == _trim(cd.m_szcodgru):
                return idx
        return None

    def _apply_individual(self, genes: List[Tuple[int, int, int, int, int]]) -> None:
        """Aplica un individuo a las tablas hda*, limpiando primero."""
        self._init_disponibilidad()
        for cd_idx, aula_idx, dia, hora, lista_id in genes:
            if aula_idx < 0 or aula_idx >= len(self.aulas):
                continue
            if dia < 0 or dia >= 6 or hora < 0 or hora >= 18:
                continue
            self.asignar_slot(aula_idx, dia, hora, cd_idx, lista=lista_id)

    def _fitness_individual(self, genes: List[Tuple[int, int, int, int, int]]) -> float:
        """Calcula fitness de un individuo construyendo tablas temporales y penalidades."""
        # Guarda estado actual
        orig_aulas = self.hda_aulas
        orig_aulas2 = self.hda_aulas2
        orig_doc = self.hda_docentes
        orig_cic = self.hda_ciclos
        orig_pen_c = self.pen_ciclo
        orig_pen_a = self.pen_aula
        orig_pen_d = self.pen_docente
        try:
            self._apply_individual(genes)
            self.calc_penalties()
            # Penalidad total = suma penalidades; fitness = 1/(1+pen)
            total_pen = sum(self.pen_ciclo) + sum(self.pen_aula) + sum(self.pen_docente)
            return 1.0 / (1.0 + total_pen)
        finally:
            # Restaura
            self.hda_aulas = orig_aulas
            self.hda_aulas2 = orig_aulas2
            self.hda_docentes = orig_doc
            self.hda_ciclos = orig_cic
            self.pen_ciclo = orig_pen_c
            self.pen_aula = orig_pen_a
            self.pen_docente = orig_pen_d

    def _crossover(self, p1: List[Tuple[int, int, int, int, int]], p2: List[Tuple[int, int, int, int, int]]) -> List[Tuple[int, int, int, int, int]]:
        """Crossover uniforme: mezcla genes sin duplicar el mismo curso-docente."""
        child = []
        seen_cd = set()
        for g1, g2 in zip(p1, p2):
            pick = g1 if random.random() < 0.5 else g2
            if pick[0] in seen_cd:
                other = g2 if pick is g1 else g1
                pick = other
            if pick[0] in seen_cd:
                continue
            seen_cd.add(pick[0])
            child.append(pick)
        # Añade genes restantes de padres si falta alguno
        for g in p1 + p2:
            if g[0] not in seen_cd:
                child.append(g)
                seen_cd.add(g[0])
        return child

    def _mutate(self, genes: List[Tuple[int, int, int, int, int]], prob: float) -> List[Tuple[int, int, int, int, int]]:
        mutated = []
        for cd_idx, aula_idx, dia, hora, lista_id in genes:
            if random.random() < prob:
                aula_idx = random.randrange(len(self.aulas)) if self.aulas else aula_idx
                dia = random.randrange(6)
                hora = random.randrange(18)
                lista_id = 1
            mutated.append((cd_idx, aula_idx, dia, hora, lista_id))
        return mutated

    def _hours_for_course(self, codcur: str) -> int:
        """Horas requeridas para un curso según TCHoras (m_sznumhor)."""
        total = 0
        for ch in self.cursos_hora:
            if _trim(ch.m_szcodcur) == codcur:
                try:
                    total += int(_trim(ch.m_sznumhor) or "0")
                except ValueError:
                    total += 1
        return max(total, 1)

    def _aulas_for_type(self, ctaula: str) -> List[int]:
        """Devuelve índices de aulas compatibles con tipo de aula (m_szctaasi)."""
        res = []
        for idx, a in enumerate(self.aulas):
            if _trim(a.m_szctaasi) == ctaula or not ctaula.strip():
                res.append(idx)
        if not res:
            res = list(range(len(self.aulas)))
        return res

    def _generate_random_individual(self) -> List[Tuple[int, int, int, int, int]]:
        """
        Construye un individuo aleatorio respetando número de horas por curso
        y evitando choques de aula/docente durante la generación.
        """
        genes: List[Tuple[int, int, int, int, int]] = []
        occ_aula = set()
        occ_doc = set()
        for idx_cd, cd in enumerate(self.cursos_docente):
            codcur = _trim(cd.m_szcodcur)
            coddoc = _trim(cd.m_szcoddoc)
            doc_idx = self._idx_doc(coddoc)
            horas = self._hours_for_course(codcur)
            # aula preferida por tipo
            ctaula = ""
            for ch in self.cursos_hora:
                if _trim(ch.m_szcodcur) == codcur:
                    ctaula = _trim(ch.m_szctaula)
                    break
            aulas_posibles = self._aulas_for_type(ctaula)
            for _ in range(horas):
                for _attempt in range(50):
                    aula_idx = random.choice(aulas_posibles) if aulas_posibles else 0
                    dia = random.randrange(6)
                    hora = random.randrange(18)
                    if (aula_idx, dia, hora) in occ_aula:
                        continue
                    if doc_idx >= 0 and (doc_idx, dia, hora) in occ_doc:
                        continue
                    occ_aula.add((aula_idx, dia, hora))
                    if doc_idx >= 0:
                        occ_doc.add((doc_idx, dia, hora))
                    genes.append((idx_cd, aula_idx, dia, hora, 1))
                    break
        return genes

    def run_ga(self, generaciones: int = 5, pob_size: int = 10, mut_prob: float = 0.1) -> Dict[str, str]:
        """
        GA simplificado:
        - Individuo: lista de asignaciones (cd_idx, aula, dia, hora, lista).
        - Población inicial: padre base (ocupación actual) + clones mutados.
        - Selección: ruleta por fitness.
        - Crossover + mutación por generación.
        - Al final aplica el mejor individuo y recalcula penalidades.
        Devuelve resumen y aplica cambios sobre hda_*.
        """
        base = self._current_individual()
        if not base:
            base = self._generate_random_individual()
        if not base:
            return {"status": "sin_asignaciones"}
        poblacion = [base]
        # Inicializa población mutando o generando variantes aleatorias
        for i in range(pob_size - 1):
            if i % 2 == 0:
                poblacion.append(self._mutate(base, prob=0.3))
            else:
                poblacion.append(self._generate_random_individual())

        best = base
        best_fit = self._fitness_individual(best)

        for _ in range(generaciones):
            fits = [self._fitness_individual(ind) for ind in poblacion]
            # Guarda mejor
            for ind, fit in zip(poblacion, fits):
                if fit > best_fit:
                    best_fit = fit
                    best = ind
            # Nueva población
            nueva = []
            for _ in range(pob_size // 2):
                p1 = poblacion[self.seleccion_ruleta(fits)]
                p2 = poblacion[self.seleccion_ruleta(fits)]
                hijo = self._crossover(p1, p2)
                hijo = self._mutate(hijo, mut_prob)
                nueva.extend([p1, hijo])
            poblacion = nueva[:pob_size]

        # Aplica mejor individuo encontrado
        self._apply_individual(best)
        self.calc_penalties()
        return {
            "mejor_fitness": f"{best_fit:.4f}",
            "total_penalidad": str(sum(self.pen_ciclo) + sum(self.pen_aula) + sum(self.pen_docente)),
            "genes": str(len(best)),
        }

    # --------------------------- Carga desde solución textual --------------------------- #

    def load_from_lsolhor(self, path: str | Path = "AsiHor/LSolHor.txt") -> None:
        """
        Parsea LSolHor.txt y llena la matriz hda_aulas con etiquetas formateadas.
        Formato esperado:
        Ciclo Cod_Curso Nombre_Curso ... Cod_Docente Nombre_Docente ... Aula Día HH:MM HH:MM
        """
        p = Path(path)
        if not p.exists():
            return

        text = p.read_text(encoding="latin1", errors="ignore")

        dia_map = {
            "Lunes": 0,
            "Martes": 1,
            "Mierco": 2,
            "Jueves": 3,
            "Vierne": 4,
            "Sabado": 5,
            "Sábado": 5,
        }

        hora_pattern = re.compile(r"^(\d{2}):(\d{2})$")
        doc_pattern = re.compile(r"(D\d+)")

        for line in text.splitlines():
            line = line.strip()
            if not line:
                continue

            tokens = line.split()
            if len(tokens) < 8:
                continue

            try:
                hora_fin_str = tokens[-1]
                if not hora_pattern.match(hora_fin_str):
                    continue
                hh_fin, mm_fin = map(int, hora_fin_str.split(":"))
                end_min = hh_fin * 60 + mm_fin

                hora_ini_str = tokens[-2]
                if not hora_pattern.match(hora_ini_str):
                    continue
                hh_ini, mm_ini = map(int, hora_ini_str.split(":"))
                start_min = hh_ini * 60 + mm_ini

                dia_str = tokens[-3]
                if dia_str not in dia_map:
                    continue
                dia_idx = dia_map[dia_str]

                aula_cod = tokens[-4]
                cod_cur = tokens[1]

                doc_match = doc_pattern.search(line)
                if not doc_match:
                    continue
                cod_doc = doc_match.group(1)

                cd_idx = self._find_curso_docente(cod_cur, cod_doc, aula_cod)
                aula_idx = self._idx_aula(aula_cod)

                if cd_idx < 0 or aula_idx < 0:
                    continue

                for h in range(start_min // 60, end_min // 60):
                    if h < 18:
                        self.asignar_slot(aula_idx, dia_idx, h, cd_idx, lista=1)

            except (IndexError, ValueError, AttributeError):
                continue

    def _find_curso_docente(self, cod_cur: str, cod_doc: str, cod_gru: str) -> int:
        """
        Busca en cursos_docente por coincidencia de curso, docente y grupo.
        Si no encuentra grupo, relaja a (curso, docente).
        """
        for idx, cd in enumerate(self.cursos_docente):
            if _trim(cd.m_szcodcur) == cod_cur and _trim(cd.m_szcoddoc) == cod_doc and _trim(cd.m_szcodgru) == cod_gru:
                return idx
        for idx, cd in enumerate(self.cursos_docente):
            if _trim(cd.m_szcodcur) == cod_cur and _trim(cd.m_szcoddoc) == cod_doc:
                return idx
        return -1
