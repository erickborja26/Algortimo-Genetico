from __future__ import annotations

from dataclasses import dataclass
from typing import ClassVar

from .layout_utils import FieldDef, build_layout_ops, build_record, parse_record


LAYOUT: list[FieldDef] = [
    ("m_szcodcur", "bytes", 4),
    ("m_szcodgru", "bytes", 4),
    ("m_szcoddoc", "bytes", 4),
    ("m_szcodaul", "bytes", 3),
    ("m_sznumdia", "bytes", 1),
    ("m_szhorini", "bytes", 6),
    ("m_szhorfin", "bytes", 6),
    ("m_szlibre1", "bytes", 20),
]
_, SIZE = build_layout_ops(LAYOUT)


@dataclass
class SEstHor:
    SIZE: ClassVar[int] = SIZE
    m_szcodcur: bytes
    m_szcodgru: bytes
    m_szcoddoc: bytes
    m_szcodaul: bytes
    m_sznumdia: bytes
    m_szhorini: bytes
    m_szhorfin: bytes
    m_szlibre1: bytes

    @classmethod
    def from_bytes(cls, data: bytes) -> "SEstHor":
        values = parse_record(data, LAYOUT, SIZE)
        return cls(**values)

    def to_bytes(self) -> bytes:
        return build_record(self.__dict__, LAYOUT, SIZE)
