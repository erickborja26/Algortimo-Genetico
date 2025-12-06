from __future__ import annotations

from dataclasses import dataclass, field
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
)
from .ct1_reader import iter_records
from .data_loader import CT1_MAP


@dataclass
class GlobalState:
    base_dir: Path
    data: Dict[str, List] = field(default_factory=dict)

    @classmethod
    def load(cls, base_dir: str | Path) -> "GlobalState":
        base = Path(base_dir)
        data: Dict[str, List] = {}
        for fname, cls_struct in CT1_MAP.items():
            path = base / fname
            if not path.exists():
                continue
            records = list(iter_records(path, cls_struct))
            data[fname] = records
        return cls(base_dir=base, data=data)

    def get(self, fname: str):
        return self.data.get(fname, [])

    def save(self, out_dir: str | Path | None = None) -> None:
        """
        Escribe todos los .ct1 cargados a disco, usando to_bytes() de cada registro.
        out_dir: carpeta destino (por defecto sobrescribe base_dir).
        """
        target = Path(out_dir) if out_dir else self.base_dir
        target.mkdir(parents=True, exist_ok=True)
        for fname, records in self.data.items():
            cls_struct: Type | None = CT1_MAP.get(fname)
            if cls_struct is None or not records:
                continue
            size = cls_struct.SIZE
            path = target / fname
            with path.open("wb") as fh:
                for rec in records:
                    blob = rec.to_bytes()
                    if len(blob) != size:
                        raise ValueError(f"{fname}: record size {len(blob)} != expected {size}")
                    fh.write(blob)
