from __future__ import annotations

from dataclasses import dataclass
from typing import ClassVar

from .layout_utils import FieldDef, build_layout_ops, build_record, parse_record


LAYOUT: list[FieldDef] = [
    ("m_szcodcur", "bytes", 4),
    ("m_sznomcur", "bytes", 33),
    ("m_szciccur", "bytes", 3),
    ("m_szlibre1", "bytes", 8),
]
_, SIZE = build_layout_ops(LAYOUT)


@dataclass
class SEstCur:
    SIZE: ClassVar[int] = SIZE
    m_szcodcur: bytes
    m_sznomcur: bytes
    m_szciccur: bytes
    m_szlibre1: bytes

    @classmethod
    def from_bytes(cls, data: bytes) -> "SEstCur":
        values = parse_record(data, LAYOUT, SIZE)
        return cls(**values)

    def to_bytes(self) -> bytes:
        return build_record(self.__dict__, LAYOUT, SIZE)
