from __future__ import annotations

from dataclasses import dataclass
from typing import ClassVar

from .layout_utils import FieldDef, build_layout_ops, build_record, parse_record


LAYOUT: list[FieldDef] = [
    ("m_szcoddoc", "bytes", 4),
    ("m_szctdisp", "bytes", 1),
    ("m_szlibre2", "bytes", 1),
    ("m_szapdoce", "bytes", 16),
    ("m_szamdoce", "bytes", 16),
    ("m_sznomdoc", "bytes", 16),
    ("m_szlibre1", "bytes", 10),
]
_, SIZE = build_layout_ops(LAYOUT)


@dataclass
class SEstDoc:
    SIZE: ClassVar[int] = SIZE
    m_szcoddoc: bytes
    m_szctdisp: bytes
    m_szlibre2: bytes
    m_szapdoce: bytes
    m_szamdoce: bytes
    m_sznomdoc: bytes
    m_szlibre1: bytes

    @classmethod
    def from_bytes(cls, data: bytes) -> "SEstDoc":
        values = parse_record(data, LAYOUT, SIZE)
        return cls(**values)

    def to_bytes(self) -> bytes:
        return build_record(self.__dict__, LAYOUT, SIZE)
