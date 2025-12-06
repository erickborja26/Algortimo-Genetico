from __future__ import annotations

from dataclasses import dataclass
from typing import ClassVar

from .layout_utils import FieldDef, build_layout_ops, build_record, parse_record


LAYOUT: list[FieldDef] = [
    ("m_szannpro", "bytes", 5),
    ("m_szfecini", "bytes", 9),
    ("m_szfecter", "bytes", 9),
    ("m_nznumpe1", "short", 1),
    ("m_sznompe1", "bytes", 144),
    ("m_sznteva1", "bytes", 16),
    ("m_szfiper1", "bytes", 81),
    ("m_szlibre2", "bytes", 9),
    ("m_szftper1", "bytes", 81),
    ("m_szlibre3", "bytes", 9),
    ("m_szestpe1", "bytes", 10),
    ("m_sznompe2", "bytes", 144),
    ("m_sznteva2", "bytes", 16),
    ("m_szfiper2", "bytes", 81),
    ("m_szlibre4", "bytes", 2),
    ("m_sziamora", "bytes", 1),
    ("m_szitmora", "bytes", 1),
    ("m_szicpcpr", "bytes", 1),
    ("m_sziracal", "bytes", 1),
    ("m_sznccper", "bytes", 1),
    ("m_sznmcper", "bytes", 1),
    ("m_szippfas", "bytes", 1),
    ("m_szftper2", "bytes", 81),
    ("m_nzlibnot", "short", 1),
    ("m_nzcibnot", "short", 1),
    ("m_nzlibpag", "short", 1),
    ("m_nzcibpag", "short", 1),
    ("m_szestpe2", "bytes", 10),
    ("m_nznumcuo", "short", 1),
    ("m_szestpad", "bytes", 1),
    ("m_szFIDato", "bytes", 9),
    ("m_sztipev1", "bytes", 1),
    ("m_sztipev2", "bytes", 1),
    ("m_nznumpe2", "short", 1),
    ("m_nznmalum", "short", 1),
    ("m_szitpcca", "bytes", 1),
    ("m_szgiapli", "bytes", 1),
    ("m_szicpppo", "bytes", 1),
    ("m_szigpmdi", "bytes", 1),
    ("m_szlisval", "bytes", 20),
    ("m_sziipmes", "bytes", 1),
    ("m_sznmp001", "bytes", 1),
    ("m_sznmp002", "bytes", 1),
    ("m_sznmp003", "bytes", 1),
    ("m_sznmp004", "bytes", 1),
    ("m_szindpsm", "bytes", 1),
    ("m_szindimp", "bytes", 1),
    ("m_szindexp", "bytes", 1),
    ("m_szindidm", "bytes", 1),
    ("m_szindpdm", "bytes", 1),
    ("m_szinddcp", "bytes", 1),
    ("m_szncaper", "bytes", 1),
    ("m_szipappp", "bytes", 1),
    ("m_sziomppl", "bytes", 1),
    ("m_szctdsol", "bytes", 36),
    ("m_szipbanc", "bytes", 1),
    ("m_sziipuni", "bytes", 1),
    ("m_szippatr", "bytes", 1),
    ("m_szlibre1", "bytes", 5),
]
_, SIZE = build_layout_ops(LAYOUT)


@dataclass
class SEstPAd:
    SIZE: ClassVar[int] = SIZE
    m_szannpro: bytes
    m_szfecini: bytes
    m_szfecter: bytes
    m_nznumpe1: int
    m_sznompe1: bytes
    m_sznteva1: bytes
    m_szfiper1: bytes
    m_szlibre2: bytes
    m_szftper1: bytes
    m_szlibre3: bytes
    m_szestpe1: bytes
    m_sznompe2: bytes
    m_sznteva2: bytes
    m_szfiper2: bytes
    m_szlibre4: bytes
    m_sziamora: bytes
    m_szitmora: bytes
    m_szicpcpr: bytes
    m_sziracal: bytes
    m_sznccper: bytes
    m_sznmcper: bytes
    m_szippfas: bytes
    m_szftper2: bytes
    m_nzlibnot: int
    m_nzcibnot: int
    m_nzlibpag: int
    m_nzcibpag: int
    m_szestpe2: bytes
    m_nznumcuo: int
    m_szestpad: bytes
    m_szFIDato: bytes
    m_sztipev1: bytes
    m_sztipev2: bytes
    m_nznumpe2: int
    m_nznmalum: int
    m_szitpcca: bytes
    m_szgiapli: bytes
    m_szicpppo: bytes
    m_szigpmdi: bytes
    m_szlisval: bytes
    m_sziipmes: bytes
    m_sznmp001: bytes
    m_sznmp002: bytes
    m_sznmp003: bytes
    m_sznmp004: bytes
    m_szindpsm: bytes
    m_szindimp: bytes
    m_szindexp: bytes
    m_szindidm: bytes
    m_szindpdm: bytes
    m_szinddcp: bytes
    m_szncaper: bytes
    m_szipappp: bytes
    m_sziomppl: bytes
    m_szctdsol: bytes
    m_szipbanc: bytes
    m_sziipuni: bytes
    m_szippatr: bytes
    m_szlibre1: bytes

    @classmethod
    def from_bytes(cls, data: bytes) -> "SEstPAd":
        values = parse_record(data, LAYOUT, SIZE)
        return cls(**values)

    def to_bytes(self) -> bytes:
        return build_record(self.__dict__, LAYOUT, SIZE)
