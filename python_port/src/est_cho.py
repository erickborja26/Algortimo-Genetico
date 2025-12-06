from __future__ import annotations

from dataclasses import dataclass
from typing import ClassVar

from .layout_utils import FieldDef, build_layout_ops, build_record, parse_record


LAYOUT: list[FieldDef] = [
    ("m_szcodcur", "bytes", 4),
    ("m_szcthora", "bytes", 1),
    ("m_szlibre2", "bytes", 1),
    ("m_szctaula", "bytes", 4),
    ("m_sznumhor", "bytes", 1),
    ("m_szlibre1", "bytes", 21),
]
_, SIZE = build_layout_ops(LAYOUT)


@dataclass
class SEstCHo:
    SIZE: ClassVar[int] = SIZE
    m_szcodcur: bytes
    m_szcthora: bytes
    m_szlibre2: bytes
    m_szctaula: bytes
    m_sznumhor: bytes
    m_szlibre1: bytes

    @classmethod
    def from_bytes(cls, data: bytes) -> "SEstCHo":
        values = parse_record(data, LAYOUT, SIZE)
        return cls(**values)

    def to_bytes(self) -> bytes:
        return build_record(self.__dict__, LAYOUT, SIZE)
