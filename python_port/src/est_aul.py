from __future__ import annotations

from dataclasses import dataclass
from typing import ClassVar

from .layout_utils import FieldDef, build_layout_ops, build_record, parse_record


LAYOUT: list[FieldDef] = [
    ("m_szcodaul", "bytes", 3),
    ("m_szctaasi", "bytes", 4),
    ("m_sznivaul", "bytes", 11),
    ("m_szlibre1", "bytes", 14),
]
_, SIZE = build_layout_ops(LAYOUT)


@dataclass
class SEstAul:
    SIZE: ClassVar[int] = SIZE
    m_szcodaul: bytes
    m_szctaasi: bytes
    m_sznivaul: bytes
    m_szlibre1: bytes

    @classmethod
    def from_bytes(cls, data: bytes) -> "SEstAul":
        values = parse_record(data, LAYOUT, SIZE)
        return cls(**values)

    def to_bytes(self) -> bytes:
        return build_record(self.__dict__, LAYOUT, SIZE)
