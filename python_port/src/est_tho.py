from __future__ import annotations

from dataclasses import dataclass
from typing import ClassVar

from .layout_utils import FieldDef, build_layout_ops, build_record, parse_record


LAYOUT: list[FieldDef] = [
    ("m_szcthora", "bytes", 1),
    ("m_szdthora", "bytes", 12),
    ("m_szlibre1", "bytes", 3),
]
_, SIZE = build_layout_ops(LAYOUT)


@dataclass
class SEstTHo:
    SIZE: ClassVar[int] = SIZE
    m_szcthora: bytes
    m_szdthora: bytes
    m_szlibre1: bytes

    @classmethod
    def from_bytes(cls, data: bytes) -> "SEstTHo":
        values = parse_record(data, LAYOUT, SIZE)
        return cls(**values)

    def to_bytes(self) -> bytes:
        return build_record(self.__dict__, LAYOUT, SIZE)
