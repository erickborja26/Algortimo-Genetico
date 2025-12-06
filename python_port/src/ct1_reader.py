from __future__ import annotations

from pathlib import Path
from typing import Iterator, Type, TypeVar

T = TypeVar("T")


def iter_records(path: str | Path, cls: Type[T]) -> Iterator[T]:
    """
    Yield records of type cls from a fixed-width binary file.
    cls must expose SIZE and from_bytes().
    """
    size = getattr(cls, "SIZE", None)
    if size is None:
        raise ValueError(f"{cls} must define SIZE")
    path = Path(path)
    with path.open("rb") as fh:
        while True:
            chunk = fh.read(size)
            if not chunk:
                break
            if len(chunk) != size:
                # Ignora residuo incompleto (observado en TCHoras.ct1)
                break
            yield cls.from_bytes(chunk)


def load_all(path: str | Path, cls: Type[T]) -> list[T]:
    return list(iter_records(path, cls))
