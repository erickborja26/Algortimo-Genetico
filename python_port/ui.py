from __future__ import annotations

import tkinter as tk
from tkinter import ttk, messagebox
import pathlib

from src.state import GlobalState
from src.logic import LisACaLogic
from src.data_loader import load_ct1_directory


class FrontendApp(ttk.Frame):
    def __init__(self, master: tk.Tk, base_dir: str | pathlib.Path = "AsiHor") -> None:
        super().__init__(master)
        self.master = master
        self.base_dir = pathlib.Path(base_dir)
        self.state = None
        self.logic = None

        self.penalidades_list = None
        self.poblacion_list = None
        self.horarios_tree = None
        self.horario_final_tree = None
        self.aula_var = tk.StringVar()
        self.nb = None

        self._build_ui()
        self._load_data()

    def _build_ui(self) -> None:
        self.master.title("Horarios - Port Python")
        self.master.geometry("900x600")
        self.nb = ttk.Notebook(self)
        self.nb.pack(fill=tk.BOTH, expand=True)

        # Tab penalidades
        tab_pen = ttk.Frame(self.nb)
        self.nb.add(tab_pen, text="Penalidades")
        self.penalidades_list = tk.Listbox(tab_pen, font=("Courier New", 10))
        self.penalidades_list.pack(fill=tk.BOTH, expand=True, padx=6, pady=6)

        # Tab población
        tab_pop = ttk.Frame(self.nb)
        self.nb.add(tab_pop, text="Población")
        self.poblacion_list = tk.Listbox(tab_pop, font=("Courier New", 10))
        self.poblacion_list.pack(fill=tk.BOTH, expand=True, padx=6, pady=6)

        # Tab horarios
        tab_hor = ttk.Frame(self.nb)
        self.nb.add(tab_hor, text="Horarios (Aula)")
        top_bar = ttk.Frame(tab_hor)
        top_bar.pack(fill=tk.X, padx=6, pady=4)
        ttk.Label(top_bar, text="Aula:").pack(side=tk.LEFT)
        self.aula_combo = ttk.Combobox(top_bar, textvariable=self.aula_var, state="readonly", width=10)
        self.aula_combo.pack(side=tk.LEFT, padx=4)
        self.aula_combo.bind("<<ComboboxSelected>>", lambda e: self._refresh_horarios())

        dias = ["Hora", "Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado"]
        self.horarios_tree = ttk.Treeview(tab_hor, columns=dias[1:], show="headings", height=17)
        self.horarios_tree.heading("#0", text=dias[0])
        self.horarios_tree.column("#0", width=100, anchor=tk.W, stretch=False)
        for dia in dias[1:]:
            self.horarios_tree.heading(dia, text=dia)
            self.horarios_tree.column(dia, width=100, anchor=tk.CENTER)
        self.horarios_tree.pack(fill=tk.BOTH, expand=True, padx=6, pady=6)

        # Tab datos iniciales
        tab_datos = ttk.Frame(self.nb)
        self.nb.add(tab_datos, text="Datos Iniciales")
        self.pestana_datos_iniciales = PestanaDatosIniciales(tab_datos, self.base_dir, app_ref=self)
        self.pestana_datos_iniciales.pack(fill=tk.BOTH, expand=True)

        # Tab horario inicial
        tab_horario_inicial = ttk.Frame(self.nb)
        self.nb.add(tab_horario_inicial, text="Horario Inicial")
        frame_superior = ttk.LabelFrame(tab_horario_inicial, text="Asignaciones Iniciales")
        frame_superior.pack(fill=tk.BOTH, expand=True, padx=10, pady=5)
        self.tree_horario_inicial = ttk.Treeview(frame_superior, columns=("Curso", "Docente", "Aula", "Día", "Hora"), show="headings", height=15)
        self.tree_horario_inicial.heading("Curso", text="Curso")
        self.tree_horario_inicial.heading("Docente", text="Docente")
        self.tree_horario_inicial.heading("Aula", text="Aula")
        self.tree_horario_inicial.heading("Día", text="Día")
        self.tree_horario_inicial.heading("Hora", text="Hora")
        self.tree_horario_inicial.column("Curso", width=80, anchor=tk.CENTER)
        self.tree_horario_inicial.column("Docente", width=120, anchor=tk.W)
        self.tree_horario_inicial.column("Aula", width=80, anchor=tk.CENTER)
        self.tree_horario_inicial.column("Día", width=100, anchor=tk.CENTER)
        self.tree_horario_inicial.column("Hora", width=100, anchor=tk.CENTER)
        self.tree_horario_inicial.pack(fill=tk.BOTH, expand=True)
        self.tree_horario_inicial.tag_configure("odd", background="#ffffcc")
        self.tree_horario_inicial.tag_configure("even", background="#ffffe6")

        # Botonera
        btn_bar = ttk.Frame(self)
        btn_bar.pack(fill=tk.X, pady=6)
        ttk.Button(btn_bar, text="Recalcular penalidades", command=self._calc_penalidades).pack(side=tk.LEFT, padx=4)
        ttk.Button(btn_bar, text="Ejecutar GA (rápido)", command=self._run_ga).pack(side=tk.LEFT, padx=4)
        ttk.Button(btn_bar, text="Salir", command=self.master.destroy).pack(side=tk.RIGHT, padx=4)

        self.pack(fill=tk.BOTH, expand=True)

    def _load_data(self) -> None:
        if not self.base_dir.exists():
            messagebox.showerror("Error", f"No se encuentra la carpeta {self.base_dir}")
            return
        self.state = GlobalState.load(self.base_dir)
        self.logic = LisACaLogic(self.state)
        # Intenta cargar ocupación desde LSolHor si existe
        self.logic.load_from_lsolhor()
        # Aula combo
        aulas = [_trim(a.m_szcodaul) for a in self.logic.aulas] or ["A1"]
        self.aula_combo["values"] = aulas
        if aulas:
            self.aula_combo.current(0)
        self._calc_penalidades()
        self._refresh_horarios()
        self._refresh_horario_final()

    def _calc_penalidades(self) -> None:
        if not self.logic:
            return
        pen = self.logic.calc_penalties()
        self.penalidades_list.delete(0, tk.END)
        for line in pen["pen_ciclo"]:
            self.penalidades_list.insert(tk.END, line)
        # resumen población
        pop = self.logic.generar_poblacion()
        self.poblacion_list.delete(0, tk.END)
        for line in pop["poblacion"][:200]:
            self.poblacion_list.insert(tk.END, line)
        # refresca horarios
        self._refresh_horarios()
        self._refresh_horario_final()

    def _run_ga(self) -> None:
        if not self.logic:
            return
        res = self.logic.run_ga(generaciones=1, pob_size=8, mut_prob=0.2)
        messagebox.showinfo("GA", f"Mejor fitness: {res.get('mejor_fitness')}\nPenalidad: {res.get('total_penalidad')}")
        self._calc_penalidades()

    def _refresh_horarios(self) -> None:
        if not self.logic or not self.horarios_tree:
            return
        aula_sel = self.aula_var.get()
        aula_idx = 0
        for i, a in enumerate(self.logic.aulas):
            if _trim(a.m_szcodaul) == aula_sel:
                aula_idx = i
                break
        # Limpiar
        for item in self.horarios_tree.get_children():
            self.horarios_tree.delete(item)

        horas = [
            "08:00 - 09:00", "09:00 - 10:00", "10:00 - 11:00", "11:00 - 12:00", "12:00 - 13:00",
            "13:00 - 14:00", "14:00 - 15:00", "15:00 - 16:00", "16:00 - 17:00", "17:00 - 18:00",
            "18:00 - 19:00", "19:00 - 20:00", "20:00 - 21:00", "21:00 - 22:00"
        ]
        dias = ["Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado"]

        for hora_idx, hora_label in enumerate(horas):
            values = []
            for dia_idx in range(6):
                tag = self.logic.hda_aulas[aula_idx][dia_idx][hora_idx]
                values.append(tag if tag != "D" else "")
            self.horarios_tree.insert("", tk.END, values=values, text=hora_label)

    def _refresh_horario_final(self) -> None:
        """Llena la tabla 'Horario final' con el mismo formato que imprime main.py."""
        if not self.logic or not self.horario_final_tree:
            return
        # Limpiar
        for item in self.horario_final_tree.get_children():
            self.horario_final_tree.delete(item)

        dias = ["Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado"]
        rows = []
        for aula_idx, dias_aula in enumerate(self.logic.hda_aulas):
            aula_nombre = _trim(self.logic.aulas[aula_idx].m_szcodaul)
            for dia_idx, horas in enumerate(dias_aula):
                for hora_idx, etiqueta in enumerate(horas):
                    if etiqueta != "D":
                        curso = etiqueta[:3].strip()
                        docente = etiqueta[3:6].strip()
                        grupo = etiqueta[6:].strip()
                        hora = f"{hora_idx + 8:02}:00"
                        rows.append((curso, grupo, docente, dias[dia_idx], hora, aula_nombre, dia_idx, hora_idx, aula_idx))

        # Ordenar por dia, hora y aula para que quede coherente
        rows.sort(key=lambda r: (r[6], r[7], r[8]))
        for curso, grupo, docente, dia, hora, aula, _, _, _ in rows:
            self.horario_final_tree.insert("", tk.END, values=(curso, grupo, docente, dia, hora, aula))


class PestanaDatosIniciales(ttk.Frame):
    def __init__(self, parent, base_dir, app_ref=None):
        super().__init__(parent)
        self.base_dir = base_dir
        self.app_ref = app_ref
        self._build_ui()
        self._load_data()

    def _build_ui(self):
        # Botón de acción
        toolbar = ttk.Frame(self)
        toolbar.pack(fill=tk.X, padx=5, pady=5)
        ttk.Button(toolbar, text="Generar Horario Inicial", command=self._generar_horario_inicial).pack(side=tk.LEFT)

        # Sección Superior
        frame_superior = ttk.LabelFrame(self, text="Datos Iniciales")
        frame_superior.pack(fill=tk.BOTH, expand=True, padx=10, pady=5)

        # Lista de Docentes
        frame_docentes = ttk.Frame(frame_superior)
        frame_docentes.pack(side=tk.LEFT, fill=tk.BOTH, expand=True, padx=5)
        ttk.Label(frame_docentes, text="Lista de Docentes").pack()
        self.tree_docentes = ttk.Treeview(frame_docentes, columns=("ID", "Nombre", "Carga"), show="headings", height=10)
        self.tree_docentes.heading("ID", text="ID")
        self.tree_docentes.heading("Nombre", text="Nombre")
        self.tree_docentes.heading("Carga", text="Carga")
        self.tree_docentes.column("ID", width=50, anchor=tk.CENTER)
        self.tree_docentes.column("Nombre", width=150, anchor=tk.W)
        self.tree_docentes.column("Carga", width=100, anchor=tk.CENTER)
        self.tree_docentes.pack(fill=tk.BOTH, expand=True)
        self.tree_docentes.tag_configure("odd", background="#ffffcc")
        self.tree_docentes.tag_configure("even", background="#ffffe6")

        # Lista de Aulas
        frame_aulas = ttk.Frame(frame_superior)
        frame_aulas.pack(side=tk.LEFT, fill=tk.BOTH, expand=True, padx=5)
        ttk.Label(frame_aulas, text="Lista de Aulas").pack()
        self.tree_aulas = ttk.Treeview(frame_aulas, columns=("ID", "Tipo", "Descripción", "Ubicación"), show="headings", height=10)
        self.tree_aulas.heading("ID", text="ID")
        self.tree_aulas.heading("Tipo", text="Tipo")
        self.tree_aulas.heading("Descripción", text="Descripción")
        self.tree_aulas.heading("Ubicación", text="Ubicación")
        self.tree_aulas.column("ID", width=50, anchor=tk.CENTER)
        self.tree_aulas.column("Tipo", width=100, anchor=tk.W)
        self.tree_aulas.column("Descripción", width=150, anchor=tk.W)
        self.tree_aulas.column("Ubicación", width=100, anchor=tk.W)
        self.tree_aulas.pack(fill=tk.BOTH, expand=True)
        self.tree_aulas.tag_configure("odd", background="#ffffcc")
        self.tree_aulas.tag_configure("even", background="#ffffe6")

        # Sección Media
        frame_media = ttk.LabelFrame(self, text="Lista de Cursos y Horas")
        frame_media.pack(fill=tk.BOTH, expand=True, padx=10, pady=5)
        self.tree_cursos = ttk.Treeview(frame_media, columns=("Cod", "Nombre", "Horas", "Tipo", "Aula Pref", "Desc", "Ciclo"), show="headings", height=10)
        self.tree_cursos.heading("Cod", text="Cod")
        self.tree_cursos.heading("Nombre", text="Nombre")
        self.tree_cursos.heading("Horas", text="Horas")
        self.tree_cursos.heading("Tipo", text="Tipo")
        self.tree_cursos.heading("Aula Pref", text="Aula Pref")
        self.tree_cursos.heading("Desc", text="Desc")
        self.tree_cursos.heading("Ciclo", text="Ciclo")
        self.tree_cursos.column("Cod", width=50, anchor=tk.CENTER)
        self.tree_cursos.column("Nombre", width=150, anchor=tk.W)
        self.tree_cursos.column("Horas", width=50, anchor=tk.CENTER)
        self.tree_cursos.column("Tipo", width=100, anchor=tk.W)
        self.tree_cursos.column("Aula Pref", width=100, anchor=tk.W)
        self.tree_cursos.column("Desc", width=150, anchor=tk.W)
        self.tree_cursos.column("Ciclo", width=50, anchor=tk.CENTER)
        self.tree_cursos.pack(fill=tk.BOTH, expand=True)
        self.tree_cursos.tag_configure("odd", background="#ffffcc")
        self.tree_cursos.tag_configure("even", background="#ffffe6")

        # Sección Inferior
        frame_inferior = ttk.LabelFrame(self, text="Lista de Cursos y Docentes")
        frame_inferior.pack(fill=tk.BOTH, expand=True, padx=10, pady=5)

        self.tree_cursos_docentes = ttk.Treeview(frame_inferior, columns=("Curso", "Docente"), show="headings", height=5)
        self.tree_cursos_docentes.heading("Curso", text="Curso")
        self.tree_cursos_docentes.heading("Docente", text="Docente")
        self.tree_cursos_docentes.column("Curso", width=150, anchor=tk.W)
        self.tree_cursos_docentes.column("Docente", width=150, anchor=tk.W)
        self.tree_cursos_docentes.pack(fill=tk.BOTH, expand=True)
        self.tree_cursos_docentes.tag_configure("odd", background="#ffffcc")
        self.tree_cursos_docentes.tag_configure("even", background="#ffffe6")

        # Población Inicial
        self.text_poblacion = tk.Text(frame_inferior, height=10, font=("Consolas", 10), bg="#ffffcc")
        self.text_poblacion.pack(fill=tk.BOTH, expand=True, padx=5, pady=5)

    def _load_data(self):
        # Cargar datos desde archivos ct1
        data = load_ct1_directory(self.base_dir)

        # Cargar docentes
        docentes = data.get("TDocent.ct1", [])
        for i, docente in enumerate(docentes):
            tag = "odd" if i % 2 == 0 else "even"
            cod = docente.m_szcoddoc.decode("latin1", errors="ignore").strip()
            nombre = docente.m_sznomdoc.decode("latin1", errors="ignore").strip()
            apellido = docente.m_szapdoce.decode("latin1", errors="ignore").strip()
            carga = docente.m_szctdisp.decode("latin1", errors="ignore").strip()
            self.tree_docentes.insert("", tk.END, values=(cod, apellido + " " + nombre, carga), tags=(tag,))

        # Cargar aulas
        aulas = data.get("TAulas.ct1", [])
        for i, aula in enumerate(aulas):
            tag = "odd" if i % 2 == 0 else "even"
            cod = aula.m_szcodaul.decode("latin1", errors="ignore").strip()
            tipo = aula.m_szctaasi.decode("latin1", errors="ignore").strip()
            desc = aula.m_sznivaul.decode("latin1", errors="ignore").strip()
            self.tree_aulas.insert("", tk.END, values=(cod, tipo, desc, ""), tags=(tag,))

        # Crear diccionario de horas por curso
        horas_dict = {}
        horas_data = data.get("TCHoras.ct1", [])
        for h in horas_data:
            cod_cur = h.m_szcodcur.decode("latin1", errors="ignore").strip()
            num_hor = h.m_sznumhor.decode("latin1", errors="ignore").strip()
            tipo = h.m_szcthora.decode("latin1", errors="ignore").strip()
            aula = h.m_szctaula.decode("latin1", errors="ignore").strip()
            horas_dict[cod_cur] = (num_hor, tipo, aula)

        # Cargar cursos
        cursos = data.get("TCursos.ct1", [])
        for i, curso in enumerate(cursos):
            tag = "odd" if i % 2 == 0 else "even"
            cod = curso.m_szcodcur.decode("latin1", errors="ignore").strip()
            nombre = curso.m_sznomcur.decode("latin1", errors="ignore").strip()
            ciclo = curso.m_szciccur.decode("latin1", errors="ignore").strip()
            info = horas_dict.get(cod, ("", "", ""))
            horas, tipo, aula = info
            self.tree_cursos.insert("", tk.END, values=(cod, nombre, horas, tipo, aula, "", ciclo), tags=(tag,))

    def _generar_horario_inicial(self):
        # Cargar datos de los Treeviews
        docentes_items = []
        for item in self.tree_docentes.get_children():
            values = self.tree_docentes.item(item)['values']
            docentes_items.append(values)

        aulas_items = []
        for item in self.tree_aulas.get_children():
            values = self.tree_aulas.item(item)['values']
            aulas_items.append(values)

        cursos_items = []
        for item in self.tree_cursos.get_children():
            values = self.tree_cursos.item(item)['values']
            cursos_items.append(values)

        # Cargar relación de cursos-docentes desde ct1
        data = load_ct1_directory(self.base_dir)
        cursos_docentes_data = data.get("TCDocen.ct1", [])
        
        # Construir diccionario de curso -> lista de docentes
        curso_doc_dict = {}
        for cd in cursos_docentes_data:
            cod_cur = cd.m_szcodcur.decode("latin1", errors="ignore").strip()
            cod_doc = cd.m_szcoddoc.decode("latin1", errors="ignore").strip()
            cod_gru = cd.m_szcodgru.decode("latin1", errors="ignore").strip()
            if cod_cur not in curso_doc_dict:
                curso_doc_dict[cod_cur] = []
            curso_doc_dict[cod_cur].append((cod_doc, cod_gru))

        # Generar población inicial basada en datos reales
        dias = ["Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado"]
        horas = ["08:00", "09:00", "10:00", "11:00", "12:00", "13:00", "14:00", "15:00", "16:00", "17:00"]
        
        asignaciones = []
        poblacion_text = []
        hora_idx = 0
        dia_idx = 0
        
        # Generar asignaciones para cada curso y cada docente asignado
        for i, curso in enumerate(cursos_items):
            cod_curso = curso[0] if curso else f"C{i:02d}"
            
            # Obtener docentes asignados a este curso
            docentes_curso = curso_doc_dict.get(cod_curso, [])
            
            if not docentes_curso and docentes_items:
                # Si no hay docentes en TCDocen, asignar uno por defecto
                docentes_curso = [(docentes_items[i % len(docentes_items)][0], f"{i:02d}S")]
            
            # Generar una asignación por cada docente del curso
            for doc_cod, grupo_cod in docentes_curso:
                # Obtener nombre del docente
                docente_nombre = ""
                for doc in docentes_items:
                    if doc[0] == doc_cod:
                        docente_nombre = doc[1]
                        break
                
                if not docente_nombre:
                    docente_nombre = f"Docente {doc_cod}"
                
                # Asignar aula
                aula = aulas_items[len(asignaciones) % len(aulas_items)][0] if aulas_items else "A1"
                dia = dias[dia_idx % len(dias)]
                hora = horas[hora_idx % len(horas)]
                
                asignaciones.append((cod_curso, docente_nombre, aula, dia, hora))
                poblacion_text.append(f"{cod_curso} {grupo_cod} {aula}")
                
                # Rotar hora y día
                hora_idx += 1
                if hora_idx >= len(horas):
                    hora_idx = 0
                    dia_idx += 1
        
        # Actualizar texto de población inicial
        self.text_poblacion.delete(1.0, tk.END)
        self.text_poblacion.insert(tk.END, "\n".join(poblacion_text))

        # Poblar la tabla de asignaciones
        for item in self.tree_cursos_docentes.get_children():
            self.tree_cursos_docentes.delete(item)
        
        for i, asignacion in enumerate(asignaciones):
            tag = "odd" if i % 2 == 0 else "even"
            self.tree_cursos_docentes.insert("", tk.END, values=asignacion, tags=(tag,))

        # Si existe referencia a la app principal, actualizar la pestaña de horario inicial
        if self.app_ref and hasattr(self.app_ref, 'tree_horario_inicial'):
            # Limpiar tabla de horario inicial
            for item in self.app_ref.tree_horario_inicial.get_children():
                self.app_ref.tree_horario_inicial.delete(item)
            
            # Llenar tabla de horario inicial
            for i, asignacion in enumerate(asignaciones):
                tag = "odd" if i % 2 == 0 else "even"
                self.app_ref.tree_horario_inicial.insert("", tk.END, values=asignacion, tags=(tag,))
            
            # Cambiar a la pestaña de horario inicial
            if hasattr(self.app_ref, 'nb'):
                self.app_ref.nb.select(4)  # Índice de la pestaña "Horario Inicial"


def _trim(bs: bytes) -> str:
    return bs.decode("latin1", errors="ignore").rstrip("\x00 ").strip()


def launch_ui() -> None:
    root = tk.Tk()
    FrontendApp(root)
    root.mainloop()


if __name__ == "__main__":
    launch_ui()
