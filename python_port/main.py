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


if __name__ == "__main__":
    main()
