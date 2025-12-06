from __future__ import annotations

from dataclasses import dataclass
from typing import ClassVar, List

from .layout_utils import FieldDef, build_layout_ops, build_record, parse_record


LAYOUT: list[FieldDef] = [
    ("m_sznummat", "bytes", 7),
    ("m_szcodniv", "bytes", 1),
    ("m_szcodgra", "bytes", 1),
    ("m_szsecalu", "bytes", 1),
    ("m_nztipalu", "short", 1),
    ("m_szapalum", "bytes", 21),
    ("m_szamalum", "bytes", 21),
    ("m_szasiexo", "bytes", 7),
    ("m_szfaalum", "bytes", 9),
    ("m_szsaperi", "bytes", 10),
    ("m_szlibre2", "bytes", 2),
    ("m_szsexalu", "bytes", 1),
    ("m_szcodalu", "bytes", 7),
    ("m_szcodmod", "bytes", 15),
    ("m_szfnalum", "bytes", 11),
    ("m_szlnalum", "bytes", 31),
    ("m_szfecmat", "bytes", 9),
    ("m_szcsalum", "bytes", 3),
    ("m_szfiasec", "bytes", 27),
    ("m_szccalum", "bytes", 2),
    ("m_szficalu", "bytes", 18),
    ("m_szfralum", "bytes", 9),
    ("m_sznomalu", "bytes", 31),
    ("m_szccpag1", "bytes", 1),
    ("m_nzimpcp1", "short", 1),
    ("m_szlibre3", "bytes", 3),
    ("m_nzscfalu", "short", 1),
    ("m_nzncfalu", "short", 1),
    ("m_nzuasecc", "short", 1),
    ("m_nztppalu", "short_array", 10),
    ("m_szlibre4", "bytes", 3),
    ("m_szdiralu", "bytes", 48),
    ("m_szdisalu", "bytes", 7),
    ("m_sztfalum", "bytes", 11),
    ("m_sztmalum", "bytes", 11),
    ("m_szfmalum", "bytes", 11),
    ("m_szcpalum", "bytes", 31),
    ("m_sztpalum", "bytes", 1),
    ("m_szcomalu", "bytes", 51),
    ("m_szcomdos", "bytes", 31),
    ("m_szcodcpr", "bytes", 8),
    ("m_szncproc", "bytes", 31),
    ("m_szcodcat", "bytes", 1),
    ("m_szFIDato", "bytes", 9),
    ("m_szestmat", "bytes", 1),
    ("m_sznapalu", "bytes", 10),
    ("m_szpspalu", "bytes", 10),
    ("m_szlibre5", "bytes", 3),
    ("m_szaematr", "bytes", 5),
    ("m_nzicdocu", "bytes", 1),
    ("m_nzied001", "bytes", 1),
    ("m_nzied002", "bytes", 1),
    ("m_nzied003", "bytes", 1),
    ("m_nzied004", "bytes", 1),
    ("m_nzied005", "bytes", 1),
    ("m_nzied006", "bytes", 1),
    ("m_szlibre1", "bytes", 38),
]
_, SIZE = build_layout_ops(LAYOUT)


@dataclass
class SEstMat:
    SIZE: ClassVar[int] = SIZE
    m_sznummat: bytes
    m_szcodniv: bytes
    m_szcodgra: bytes
    m_szsecalu: bytes
    m_nztipalu: int
    m_szapalum: bytes
    m_szamalum: bytes
    m_szasiexo: bytes
    m_szfaalum: bytes
    m_szsaperi: bytes
    m_szlibre2: bytes
    m_szsexalu: bytes
    m_szcodalu: bytes
    m_szcodmod: bytes
    m_szfnalum: bytes
    m_szlnalum: bytes
    m_szfecmat: bytes
    m_szcsalum: bytes
    m_szfiasec: bytes
    m_szccalum: bytes
    m_szficalu: bytes
    m_szfralum: bytes
    m_sznomalu: bytes
    m_szccpag1: bytes
    m_nzimpcp1: int
    m_szlibre3: bytes
    m_nzscfalu: int
    m_nzncfalu: int
    m_nzuasecc: int
    m_nztppalu: List[int]
    m_szlibre4: bytes
    m_szdiralu: bytes
    m_szdisalu: bytes
    m_sztfalum: bytes
    m_sztmalum: bytes
    m_szfmalum: bytes
    m_szcpalum: bytes
    m_sztpalum: bytes
    m_szcomalu: bytes
    m_szcomdos: bytes
    m_szcodcpr: bytes
    m_szncproc: bytes
    m_szcodcat: bytes
    m_szFIDato: bytes
    m_szestmat: bytes
    m_sznapalu: bytes
    m_szpspalu: bytes
    m_szlibre5: bytes
    m_szaematr: bytes
    m_nzicdocu: bytes
    m_nzied001: bytes
    m_nzied002: bytes
    m_nzied003: bytes
    m_nzied004: bytes
    m_nzied005: bytes
    m_nzied006: bytes
    m_szlibre1: bytes

    @classmethod
    def from_bytes(cls, data: bytes) -> "SEstMat":
        values = parse_record(data, LAYOUT, SIZE)
        return cls(**values)

    def to_bytes(self) -> bytes:
        return build_record(self.__dict__, LAYOUT, SIZE)
