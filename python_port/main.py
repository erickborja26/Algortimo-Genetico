from __future__ import annotations

import pathlib
import sys

from src.state import GlobalState
from src.logic import LisACaLogic


def main() -> None:
    base = pathlib.Path("AsiHor")
    if not base.exists():
        print("Carpeta AsiHor no encontrada")
        sys.exit(1)
    state = GlobalState.load(base)
    logic = LisACaLogic(state)
    # Carga ocupación desde la solución textual generada por el exe original.
    logic.load_from_lsolhor()

    # Ejecuta cálculo de penalidades (versión portada de OnCalpen).
    penalidades = logic.calc_penalties()
    print("Penalidades por ciclo (primeros 10):")
    for line in penalidades["pen_ciclo"][:10]:
        print(" ", line)

    # Demo de generación de población (parcial de OnGnpobl).
    poblacion = logic.generar_poblacion()
    print("\nResumen población (fitness):")
    for line in poblacion["poblacion"][:10]:
        print(" ", line)

    # Corre GA simplificado para proponer una nueva asignación.
    ga_res = logic.run_ga(generaciones=1, pob_size=5, mut_prob=0.2)
    print("\nGA result:", ga_res)

    # Llamar a la función para imprimir el horario final
    imprimir_horario_final(logic)


def imprimir_horario_final(logic):
    """
    Imprime una tabla con las columnas: CURSO, GRUPO, DOCENTE, DIA, HORA, AULA.
    Recorre las matrices hda_aulas y hda_aulas2.
    """
    dias = ["Lunes", "Martes", "Miércoles", "Jueves", "Viernes", "Sábado"]

    print("\nHorario Final:")
    print(f"{'CURSO':<10}{'GRUPO':<10}{'DOCENTE':<10}{'DIA':<10}{'HORA':<10}{'AULA':<10}")
    print("-" * 60)

    for aula_idx, dias_aula in enumerate(logic.hda_aulas):
        aula_nombre = logic.aulas[aula_idx].m_szcodaul.decode('latin1').strip()
        for dia_idx, horas in enumerate(dias_aula):
            for hora_idx, etiqueta in enumerate(horas):
                if etiqueta != "D":
                    curso = etiqueta[:3].strip()
                    docente = etiqueta[3:6].strip()
                    grupo = etiqueta[6:].strip()
                    hora = f"{hora_idx + 8:02}:00"
                    dia = dias[dia_idx]
                    print(f"{curso:<10}{grupo:<10}{docente:<10}{dia:<10}{hora:<10}{aula_nombre:<10}")


if __name__ == "__main__":
    main()
