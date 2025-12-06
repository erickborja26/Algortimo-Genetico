from __future__ import annotations

from dataclasses import dataclass
from typing import ClassVar

from .layout_utils import FieldDef, build_layout_ops, build_record, parse_record


LAYOUT: list[FieldDef] = [
    ("m_szcodalu", "bytes", 7),
    ("m_szcodmod", "bytes", 15),
    ("m_szapalum", "bytes", 21),
    ("m_szamalum", "bytes", 21),
    ("m_sznomalu", "bytes", 31),
    ("m_szfnalum", "bytes", 11),
    ("m_szsexalu", "bytes", 1),
    ("m_sztipsan", "bytes", 3),
    ("m_szsegesc", "bytes", 1),
    ("m_szdiralu", "bytes", 48),
    ("m_szdisalu", "bytes", 7),
    ("m_sztfalum", "bytes", 11),
    ("m_sztmalum", "bytes", 11),
    ("m_szcomalu", "bytes", 51),
    ("m_szestalu", "bytes", 1),
    ("m_szFIDato", "bytes", 9),
    ("m_szlnalum", "bytes", 31),
    ("m_szcodcat", "bytes", 1),
    ("m_szcodniv", "bytes", 1),
    ("m_szcodgra", "bytes", 1),
    ("m_szcodsec", "bytes", 1),
    ("m_szarcima", "bytes", 16),
    ("m_szlenmat", "bytes", 1),
    ("m_szaumatr", "bytes", 5),
    ("m_szlibre1", "bytes", 94),
]
_, SIZE = build_layout_ops(LAYOUT)


@dataclass
class SEstAlu:
    SIZE: ClassVar[int] = SIZE
    m_szcodalu: bytes
    m_szcodmod: bytes
    m_szapalum: bytes
    m_szamalum: bytes
    m_sznomalu: bytes
    m_szfnalum: bytes
    m_szsexalu: bytes
    m_sztipsan: bytes
    m_szsegesc: bytes
    m_szdiralu: bytes
    m_szdisalu: bytes
    m_sztfalum: bytes
    m_sztmalum: bytes
    m_szcomalu: bytes
    m_szestalu: bytes
    m_szFIDato: bytes
    m_szlnalum: bytes
    m_szcodcat: bytes
    m_szcodniv: bytes
    m_szcodgra: bytes
    m_szcodsec: bytes
    m_szarcima: bytes
    m_szlenmat: bytes
    m_szaumatr: bytes
    m_szlibre1: bytes

    @classmethod
    def from_bytes(cls, data: bytes) -> "SEstAlu":
        values = parse_record(data, LAYOUT, SIZE)
        return cls(**values)

    def to_bytes(self) -> bytes:
        return build_record(self.__dict__, LAYOUT, SIZE)
