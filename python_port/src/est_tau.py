from __future__ import annotations

from dataclasses import dataclass
from typing import ClassVar

from .layout_utils import FieldDef, build_layout_ops, build_record, parse_record


LAYOUT: list[FieldDef] = [
    ("m_szctaula", "bytes", 4),
    ("m_szdtaula", "bytes", 32),
    ("m_szcapaul", "bytes", 3),
    ("m_szlibre1", "bytes", 9),
]
_, SIZE = build_layout_ops(LAYOUT)


@dataclass
class SEstTAu:
    SIZE: ClassVar[int] = SIZE
    m_szctaula: bytes
    m_szdtaula: bytes
    m_szcapaul: bytes
    m_szlibre1: bytes

    @classmethod
    def from_bytes(cls, data: bytes) -> "SEstTAu":
        values = parse_record(data, LAYOUT, SIZE)
        return cls(**values)

    def to_bytes(self) -> bytes:
        return build_record(self.__dict__, LAYOUT, SIZE)
