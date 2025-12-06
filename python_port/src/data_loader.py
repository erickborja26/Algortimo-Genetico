from __future__ import annotations

from pathlib import Path
from typing import Dict, List, Type

from . import (
    SEstAul,
    SEstCDA,
    SEstCDo,
    SEstCHo,
    SEstCur,
    SEstDoc,
    SEstHor,
    SEstPAd,
    SEstTAu,
    SEstTHo,
    SEstTAsigna,
    iter_records,
)

# Mapea cada archivo .ct1 a la estructura correspondiente conocida.
CT1_MAP: dict[str, Type] = {
    "TAulas.ct1": SEstAul,
    "TTAula.ct1": SEstTAu,
    "TTHora.ct1": SEstTHo,
    "TCDocen.ct1": SEstDoc,
    "TDocent.ct1": SEstDoc,  # alias observado en carpeta
    "TCursos.ct1": SEstCur,
    "TCHoras.ct1": SEstCHo,
    "TCDAlum.ct1": SEstCDA,
    "TParAdm.ct1": SEstPAd,
    "TProfes.ct1": SEstCDo,
    "TAsiPro.ct1": SEstCDo,  # usa misma estructura de 32 bytes
    "TAsigna.ct1": SEstTAsigna,  # mapeo best-effort (192 bytes, sin header)
}


def load_ct1_directory(base_dir: str | Path) -> Dict[str, List]:
    """
    Carga todos los .ct1 mapeados en CT1_MAP desde base_dir.
    Devuelve un dict {nombre_archivo: [registros]}.
    Ignora restos incompletos al final del archivo y avisa por consola.
    """
    base = Path(base_dir)
    out: Dict[str, List] = {}
    for fname, cls in CT1_MAP.items():
        path = base / fname
        if not path.exists():
            continue
        size = getattr(cls, "SIZE")
        length = path.stat().st_size
        full_records = length // size
        remainder = length % size
        if remainder:
            print(f"[warn] {fname}: length {length} leaves remainder {remainder} for size {size}, trailing bytes will be ignored")
        records = []
        with path.open("rb") as fh:
            for _ in range(full_records):
                chunk = fh.read(size)
                if not chunk:
                    break
                records.append(cls.from_bytes(chunk))
        out[fname] = records
    return out
