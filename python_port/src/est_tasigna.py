from __future__ import annotations

from dataclasses import dataclass
from typing import ClassVar


@dataclass
class SEstTAsigna:
    """
    Mapeo best-effort para TAsigna.ct1 (192 bytes por registro).
    No existe header Est*.h, pero se extraen los campos básicos visibles (código, nombre, alias).
    El resto se conserva en bruto en raw para no perder información.
    """

    SIZE: ClassVar[int] = 192
    cod: bytes
    nombre: bytes
    alias: bytes
    raw: bytes

    @classmethod
    def from_bytes(cls, data: bytes) -> "SEstTAsigna":
        if len(data) != cls.SIZE:
            raise ValueError(f"Expected {cls.SIZE} bytes, got {len(data)}")
        cod = data[0:7].split(b"\x00", 1)[0]
        nombre = data[7:40].split(b"\x00", 1)[0]
        alias = data[80:96].split(b"\x00", 1)[0]
        return cls(cod=cod, nombre=nombre, alias=alias, raw=data)

    def to_bytes(self) -> bytes:
        return bytes(self.raw)
