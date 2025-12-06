"""
Helpers for working with the fixed-width binary records used by the legacy C structs.
The layout preserves the original field order and default VC++ alignment (chars = 1, shorts = 2).
"""
from __future__ import annotations

from dataclasses import fields
import struct
from typing import Iterable, List, Sequence, Tuple

FieldDef = Tuple[str, str, int]  # (name, kind, size/count)
LayoutOp = Tuple[str, str | None, str | None, int]  # (op, name, kind, size)


def _alignment_for(kind: str) -> int:
    return 1 if kind == "bytes" else 2


def _field_size(kind: str, size: int) -> int:
    if kind == "bytes":
        return size
    if kind == "short":
        return 2
    if kind == "short_array":
        return 2 * size
    raise ValueError(f"Unknown kind {kind}")


def build_layout_ops(layout: Sequence[FieldDef]) -> Tuple[List[LayoutOp], int]:
    """
    Translates field definitions into operations (pads + fields) with VC++-style alignment.
    Returns (ops, total_size).
    """
    ops: List[LayoutOp] = []
    offset = 0
    max_align = 1
    for name, kind, size in layout:
        align = _alignment_for(kind)
        max_align = max(max_align, align)
        pad = (align - (offset % align)) % align
        if pad:
            ops.append(("pad", None, None, pad))
            offset += pad
        ops.append(("field", name, kind, size))
        offset += _field_size(kind, size)
    final_pad = (max_align - (offset % max_align)) % max_align
    if final_pad:
        ops.append(("pad", None, None, final_pad))
        offset += final_pad
    return ops, offset


def parse_record(data: bytes, layout: Sequence[FieldDef], expected_size: int) -> dict:
    ops, total = build_layout_ops(layout)
    if len(data) != total:
        raise ValueError(f"Expected {total} bytes, got {len(data)}")
    if total != expected_size:
        raise ValueError(f"Layout total {total} does not match expected size {expected_size}")
    offset = 0
    out: dict = {}
    for op, name, kind, size in ops:
        if op == "pad":
            offset += size
            continue
        if kind == "bytes":
            out[name] = data[offset : offset + size]
            offset += size
        elif kind == "short":
            out[name] = struct.unpack("<h", data[offset : offset + 2])[0]
            offset += 2
        elif kind == "short_array":
            count = size
            out[name] = list(struct.unpack(f"<{count}h", data[offset : offset + 2 * count]))
            offset += 2 * count
        else:
            raise ValueError(f"Unsupported kind {kind}")
    return out


def build_record(values: dict, layout: Sequence[FieldDef], expected_size: int) -> bytes:
    ops, total = build_layout_ops(layout)
    if total != expected_size:
        raise ValueError(f"Layout total {total} does not match expected size {expected_size}")
    parts: List[bytes] = []
    for op, name, kind, size in ops:
        if op == "pad":
            parts.append(b"\x00" * size)
            continue
        if kind == "bytes":
            raw = values[name]
            if isinstance(raw, str):
                raw = raw.encode("latin1")
            if len(raw) > size:
                raise ValueError(f"Field {name} longer than {size} bytes")
            parts.append(raw.ljust(size, b"\x00"))
        elif kind == "short":
            parts.append(struct.pack("<h", int(values[name])))
        elif kind == "short_array":
            arr = values[name]
            if len(arr) != size:
                raise ValueError(f"Field {name} requires {size} short values")
            parts.append(struct.pack(f"<{size}h", *[int(v) for v in arr]))
        else:
            raise ValueError(f"Unsupported kind {kind}")
    data = b"".join(parts)
    if len(data) != expected_size:
        raise ValueError(f"Built {len(data)} bytes, expected {expected_size}")
    return data
