from __future__ import annotations

from dataclasses import dataclass
from typing import ClassVar, List

from .layout_utils import FieldDef, build_layout_ops, build_record, parse_record


LAYOUT: list[FieldDef] = [
    ("m_szcodniv", "bytes", 1),
    ("m_szcodgra", "bytes", 1),
    ("m_szcodsec", "bytes", 1),
    ("m_szcodalu", "bytes", 7),
    ("m_szcodasi", "bytes", 7),
    ("m_nzcalifi", "short_array", 21),
    ("m_nzpromed", "short", 1),
    ("m_szestcal", "bytes", 1),
    ("m_szlibre1", "bytes", 16),
]
_, SIZE = build_layout_ops(LAYOUT)


@dataclass
class SEstCDA:
    SIZE: ClassVar[int] = SIZE
    m_szcodniv: bytes
    m_szcodgra: bytes
    m_szcodsec: bytes
    m_szcodalu: bytes
    m_szcodasi: bytes
    m_nzcalifi: List[int]
    m_nzpromed: int
    m_szestcal: bytes
    m_szlibre1: bytes

    @classmethod
    def from_bytes(cls, data: bytes) -> "SEstCDA":
        values = parse_record(data, LAYOUT, SIZE)
        return cls(**values)

    def to_bytes(self) -> bytes:
        return build_record(self.__dict__, LAYOUT, SIZE)
