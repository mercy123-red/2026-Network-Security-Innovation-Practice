#!/usr/bin/env python3
"""Bitcoin testnet experiment: byte parser and a minimal legacy P2PKH wallet.

Only Python's standard library is used.  The wallet is intentionally limited to
testnet legacy P2PKH so the serialization and signature algorithm stay visible.
"""

from __future__ import annotations

import argparse
import hashlib
import hmac
import json
import secrets
import struct
import sys
import urllib.error
import urllib.request
from dataclasses import dataclass, asdict
from datetime import datetime, timezone
from pathlib import Path

API = "https://blockstream.info/testnet/api"
SAT = 100_000_000
P = 0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFC2F
N = 0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEBAAEDCE6AF48A03BBFD25E8CD0364141
G = (0x79BE667EF9DCBBAC55A06295CE870B07029BFCDB2DCE28D959F2815B16F81798,
     0x483ADA7726A3C4655DA4FBFC0E1108A8FD17B448A68554199C47D08FFB10D4B8)
B58 = "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz"


def sha256(data: bytes) -> bytes:
    return hashlib.sha256(data).digest()


def hash256(data: bytes) -> bytes:
    return sha256(sha256(data))


def hash160(data: bytes) -> bytes:
    return hashlib.new("ripemd160", sha256(data)).digest()


def b58check_encode(payload: bytes) -> str:
    raw = payload + hash256(payload)[:4]
    n = int.from_bytes(raw, "big")
    out = ""
    while n:
        n, r = divmod(n, 58)
        out = B58[r] + out
    return "1" * (len(raw) - len(raw.lstrip(b"\0"))) + (out or "")


def b58check_decode(text: str) -> bytes:
    n = 0
    for c in text:
        if c not in B58:
            raise ValueError(f"Base58 非法字符: {c!r}")
        n = n * 58 + B58.index(c)
    raw = n.to_bytes((n.bit_length() + 7) // 8, "big") if n else b""
    raw = b"\0" * (len(text) - len(text.lstrip("1"))) + raw
    if len(raw) < 5 or hash256(raw[:-4])[:4] != raw[-4:]:
        raise ValueError("Base58Check 校验和错误")
    return raw[:-4]


def inv(x: int, m: int = P) -> int:
    return pow(x, m - 2, m)


def point_add(a, b):
    if a is None:
        return b
    if b is None:
        return a
    x1, y1 = a
    x2, y2 = b
    if x1 == x2 and (y1 != y2 or y1 == 0):
        return None
    if a == b:
        slope = (3 * x1 * x1) * inv(2 * y1) % P
    else:
        slope = (y2 - y1) * inv((x2 - x1) % P) % P
    x3 = (slope * slope - x1 - x2) % P
    return x3, (slope * (x1 - x3) - y1) % P


def point_mul(k: int, point=G):
    result = None
    addend = point
    while k:
        if k & 1:
            result = point_add(result, addend)
        addend = point_add(addend, addend)
        k >>= 1
    return result


def public_key(secret: int, compressed: bool = True) -> bytes:
    x, y = point_mul(secret)
    if compressed:
        return bytes([2 + (y & 1)]) + x.to_bytes(32, "big")
    return b"\x04" + x.to_bytes(32, "big") + y.to_bytes(32, "big")


def secret_to_wif(secret: int, compressed: bool = True) -> str:
    return b58check_encode(b"\xef" + secret.to_bytes(32, "big") + (b"\x01" if compressed else b""))


def wif_to_secret(wif: str) -> tuple[int, bool]:
    payload = b58check_decode(wif)
    if payload[0] != 0xEF or len(payload) not in (33, 34):
        raise ValueError("只接受 Bitcoin testnet WIF")
    compressed = len(payload) == 34 and payload[-1] == 1
    if len(payload) == 34 and not compressed:
        raise ValueError("WIF 压缩标记错误")
    secret = int.from_bytes(payload[1:33], "big")
    if not 1 <= secret < N:
        raise ValueError("私钥范围错误")
    return secret, compressed


def p2pkh_address(pubkey: bytes) -> str:
    return b58check_encode(b"\x6f" + hash160(pubkey))


def address_hash160(address: str) -> bytes:
    payload = b58check_decode(address)
    if len(payload) != 21 or payload[0] != 0x6F:
        raise ValueError("本实验只支持 testnet legacy P2PKH 地址（m 或 n 开头）")
    return payload[1:]


def p2pkh_script(h160: bytes) -> bytes:
    return b"\x76\xa9\x14" + h160 + b"\x88\xac"


def encode_varint(n: int) -> bytes:
    if n < 0xFD:
        return bytes([n])
    if n <= 0xFFFF:
        return b"\xfd" + struct.pack("<H", n)
    if n <= 0xFFFFFFFF:
        return b"\xfe" + struct.pack("<I", n)
    return b"\xff" + struct.pack("<Q", n)


def push(data: bytes) -> bytes:
    if len(data) < 0x4C:
        return bytes([len(data)]) + data
    if len(data) <= 0xFF:
        return b"\x4c" + bytes([len(data)]) + data
    raise ValueError("本实验不支持大于 255 字节的脚本压栈")


def rfc6979_k(secret: int, digest: bytes) -> int:
    x = secret.to_bytes(32, "big")
    v, k = b"\x01" * 32, b"\x00" * 32
    k = hmac.new(k, v + b"\x00" + x + digest, hashlib.sha256).digest()
    v = hmac.new(k, v, hashlib.sha256).digest()
    k = hmac.new(k, v + b"\x01" + x + digest, hashlib.sha256).digest()
    v = hmac.new(k, v, hashlib.sha256).digest()
    while True:
        v = hmac.new(k, v, hashlib.sha256).digest()
        candidate = int.from_bytes(v, "big")
        if 1 <= candidate < N:
            return candidate
        k = hmac.new(k, v + b"\x00", hashlib.sha256).digest()
        v = hmac.new(k, v, hashlib.sha256).digest()


def der_signature(secret: int, digest: bytes) -> bytes:
    z = int.from_bytes(digest, "big")
    while True:
        k = rfc6979_k(secret, digest)
        r = point_mul(k)[0] % N
        if r:
            s = inv(k, N) * (z + r * secret) % N
            if s:
                s = min(s, N - s)
                break
    def der_int(n: int) -> bytes:
        b = n.to_bytes((n.bit_length() + 7) // 8, "big")
        if b[0] & 0x80:
            b = b"\x00" + b
        return b"\x02" + bytes([len(b)]) + b
    body = der_int(r) + der_int(s)
    return b"\x30" + bytes([len(body)]) + body


@dataclass
class Field:
    offset: int
    size: int
    name: str
    raw_hex: str
    value: object
    note: str = ""


class Reader:
    def __init__(self, data: bytes, base: int = 0):
        self.data, self.pos, self.base = data, 0, base
        self.fields: list[Field] = []

    def take(self, n: int, name: str, value=None, note="") -> bytes:
        if n < 0 or self.pos + n > len(self.data):
            raise ValueError(f"数据在 {self.base + self.pos} 偏移处提前结束（需要 {n} 字节）")
        start = self.pos
        raw = self.data[start:start+n]
        self.pos += n
        shown = raw.hex() if value is None else value
        self.fields.append(Field(self.base + start, n, name, raw.hex(), shown, note))
        return raw

    def u32(self, name: str, note="") -> int:
        start = self.pos
        raw = self.take(4, name, note=note)
        value = struct.unpack("<I", raw)[0]
        self.fields[-1].value = value
        return value

    def u64(self, name: str, note="") -> int:
        raw = self.take(8, name, note=note)
        value = struct.unpack("<Q", raw)[0]
        self.fields[-1].value = value
        return value

    def varint(self, name: str) -> int:
        start = self.pos
        first = self.take(1, name + ".prefix")[0]
        sizes = {0xFD: 2, 0xFE: 4, 0xFF: 8}
        if first < 0xFD:
            self.fields[-1].name = name
            self.fields[-1].value = first
            return first
        n = sizes[first]
        tail = self.take(n, name + ".value")
        value = int.from_bytes(tail, "little")
        self.fields[-2].value = f"0x{first:02x}（后续 {n} 字节）"
        self.fields[-1].value = value
        return value


def script_asm(script: bytes) -> str:
    names = {0x00: "OP_0", 0x76: "OP_DUP", 0xA9: "OP_HASH160", 0x87: "OP_EQUAL",
             0x88: "OP_EQUALVERIFY", 0xAC: "OP_CHECKSIG"}
    out, i = [], 0
    while i < len(script):
        op = script[i]
        i += 1
        if 1 <= op <= 75 and i + op <= len(script):
            out.append(script[i:i+op].hex())
            i += op
        else:
            out.append(names.get(op, f"OP_0x{op:02x}"))
    return " ".join(out)


def parse_transaction(data: bytes, base: int = 0) -> dict:
    r = Reader(data, base)
    version = r.u32("tx.version", "交易版本，小端序")
    segwit = len(data) >= 6 and data[4:6] == b"\x00\x01"
    if segwit:
        r.take(1, "tx.marker", 0, "SegWit marker")
        r.take(1, "tx.flag", 1, "SegWit flag")
    vin_count = r.varint("tx.input_count")
    inputs = []
    for i in range(vin_count):
        prev = r.take(32, f"vin[{i}].prev_txid")
        r.fields[-1].value = prev[::-1].hex()
        index = r.u32(f"vin[{i}].vout")
        slen = r.varint(f"vin[{i}].scriptSig_length")
        script = r.take(slen, f"vin[{i}].scriptSig")
        r.fields[-1].value = script_asm(script)
        seq = r.u32(f"vin[{i}].sequence")
        inputs.append({"prev_txid": prev[::-1].hex(), "vout": index,
                       "scriptSig": script.hex(), "sequence": seq})
    vout_count = r.varint("tx.output_count")
    outputs = []
    for i in range(vout_count):
        value = r.u64(f"vout[{i}].value", "单位：satoshi")
        plen = r.varint(f"vout[{i}].scriptPubKey_length")
        script = r.take(plen, f"vout[{i}].scriptPubKey")
        r.fields[-1].value = script_asm(script)
        outputs.append({"value_sat": value, "scriptPubKey": script.hex(), "asm": script_asm(script)})
    witnesses = []
    if segwit:
        for i in range(vin_count):
            count = r.varint(f"witness[{i}].item_count")
            stack = []
            for j in range(count):
                size = r.varint(f"witness[{i}][{j}].length")
                item = r.take(size, f"witness[{i}][{j}].data")
                stack.append(item.hex())
            witnesses.append(stack)
    locktime = r.u32("tx.locktime")
    if r.pos != len(data):
        raise ValueError(f"交易末尾还有 {len(data)-r.pos} 个未解析字节")
    if segwit:
        stripped = struct.pack("<I", version) + encode_varint(vin_count)
        for item in inputs:
            s = bytes.fromhex(item["scriptSig"])
            stripped += bytes.fromhex(item["prev_txid"])[::-1] + struct.pack("<I", item["vout"])
            stripped += encode_varint(len(s)) + s + struct.pack("<I", item["sequence"])
        stripped += encode_varint(vout_count)
        for item in outputs:
            s = bytes.fromhex(item["scriptPubKey"])
            stripped += struct.pack("<Q", item["value_sat"]) + encode_varint(len(s)) + s
        stripped += struct.pack("<I", locktime)
    else:
        stripped = data
    return {"txid": hash256(stripped)[::-1].hex(), "wtxid": hash256(data)[::-1].hex(),
            "size": len(data), "version": version, "segwit": segwit, "inputs": inputs,
            "outputs": outputs, "witnesses": witnesses, "locktime": locktime,
            "fields": [asdict(f) for f in r.fields]}


def transaction_length(data: bytes, start: int) -> int:
    """Determine a serialized transaction length by parsing from a block cursor."""
    r = Reader(data[start:])
    r.u32("version")
    segwit = r.data[4:6] == b"\x00\x01"
    if segwit:
        r.take(2, "marker_flag")
    vin = r.varint("vin")
    for _ in range(vin):
        r.take(36, "outpoint")
        r.take(r.varint("script_length"), "script")
        r.take(4, "sequence")
    vout = r.varint("vout")
    for _ in range(vout):
        r.take(8, "value")
        r.take(r.varint("script_length"), "script")
    if segwit:
        for _ in range(vin):
            for _ in range(r.varint("items")):
                r.take(r.varint("item_length"), "item")
    r.take(4, "locktime")
    return r.pos


def merkle_root(txids: list[str]) -> str:
    level = [bytes.fromhex(x)[::-1] for x in txids]
    if not level:
        raise ValueError("区块不能没有交易")
    while len(level) > 1:
        if len(level) & 1:
            level.append(level[-1])
        level = [hash256(level[i] + level[i+1]) for i in range(0, len(level), 2)]
    return level[0][::-1].hex()


def compact_target(bits: int) -> int:
    """Expand Bitcoin's nBits compact target representation."""
    exponent, coefficient = bits >> 24, bits & 0x007FFFFF
    return coefficient << (8 * (exponent - 3)) if exponent >= 3 else coefficient >> (8 * (3 - exponent))


def parse_block(data: bytes) -> dict:
    if len(data) < 81:
        raise ValueError("区块数据不足 81 字节")
    r = Reader(data)
    version = r.u32("block.version")
    prev = r.take(32, "block.previous_hash")
    r.fields[-1].value = prev[::-1].hex()
    mr = r.take(32, "block.merkle_root")
    r.fields[-1].value = mr[::-1].hex()
    timestamp = r.u32("block.timestamp")
    r.fields[-1].value = f"{timestamp} ({datetime.fromtimestamp(timestamp, timezone.utc).isoformat()})"
    bits = r.u32("block.bits")
    nonce = r.u32("block.nonce")
    count = r.varint("block.transaction_count")
    header_fields = [asdict(f) for f in r.fields]
    transactions = []
    for i in range(count):
        length = transaction_length(data, r.pos)
        tx_start = r.pos
        raw = r.take(length, f"block.tx[{i}].raw", note="详细字段见 transactions")
        tx = parse_transaction(raw, tx_start)
        transactions.append(tx)
    if r.pos != len(data):
        raise ValueError(f"区块末尾还有 {len(data)-r.pos} 个未解析字节")
    computed = merkle_root([t["txid"] for t in transactions])
    expected = mr[::-1].hex()
    digest = hash256(data[:80])
    target = compact_target(bits)
    return {"block_hash": digest[::-1].hex(), "size": len(data),
            "version": version, "previous_hash": prev[::-1].hex(), "merkle_root": expected,
            "computed_merkle_root": computed, "merkle_valid": computed == expected,
            "timestamp": timestamp, "bits": f"{bits:08x}", "nonce": nonce,
            "target": f"{target:064x}", "pow_valid": int.from_bytes(digest, "little") <= target,
            "transaction_count": count, "header_fields": header_fields,
            "transactions": transactions}


def api_get(path: str, binary: bool = False):
    req = urllib.request.Request(API + path, headers={"User-Agent": "bitcoin-lab/1.0"})
    try:
        with urllib.request.urlopen(req, timeout=30) as response:
            data = response.read()
    except urllib.error.HTTPError as e:
        raise RuntimeError(f"Blockstream API HTTP {e.code}: {e.read().decode(errors='replace')}") from e
    except urllib.error.URLError as e:
        raise RuntimeError(f"网络请求失败: {e.reason}") from e
    return data if binary else data.decode().strip()


def api_post(path: str, body: str) -> str:
    req = urllib.request.Request(API + path, data=body.encode(), method="POST",
                                 headers={"Content-Type": "text/plain", "User-Agent": "bitcoin-lab/1.0"})
    try:
        with urllib.request.urlopen(req, timeout=30) as response:
            return response.read().decode().strip()
    except urllib.error.HTTPError as e:
        raise RuntimeError(f"广播失败 HTTP {e.code}: {e.read().decode(errors='replace')}") from e


def load_hex(value: str | None, file: str | None) -> bytes:
    text = Path(file).read_text(encoding="utf-8") if file else value
    if not text:
        raise ValueError("必须提供 --hex 或 --file")
    return bytes.fromhex("".join(text.split()))


def markdown_report(kind: str, parsed: dict) -> str:
    title = "完整区块逐字节解析" if kind == "block" else "交易逐字节解析"
    lines = [f"# {title}", "", f"- 总大小：{parsed['size']} bytes"]
    if kind == "block":
        lines += [f"- 区块哈希：`{parsed['block_hash']}`", f"- 交易数：{parsed['transaction_count']}",
                  f"- Merkle Root 校验：{'通过' if parsed['merkle_valid'] else '失败'}",
                  f"- PoW 目标校验：{'通过' if parsed['pow_valid'] else '失败'}",
                  f"- 难度目标：`{parsed['target']}`", "", "## 区块头", "",
                  "| 偏移 | 字节数 | 字段 | 原始字节（线缆序） | 解释值 |", "|---:|---:|---|---|---|"]
        fields = parsed["header_fields"]
    else:
        lines += [f"- txid：`{parsed['txid']}`", f"- SegWit：{parsed['segwit']}", "", "## 字段", "",
                  "| 偏移 | 字节数 | 字段 | 原始字节（线缆序） | 解释值 |", "|---:|---:|---|---|---|"]
        fields = parsed["fields"]
    for f in fields:
        raw = f["raw_hex"] or "（空）"
        val = str(f["value"]).replace("|", "\\|")
        lines.append(f"| {f['offset']} | {f['size']} | `{f['name']}` | `{raw}` | {val} |")
    if kind == "block":
        for i, tx in enumerate(parsed["transactions"]):
            lines += ["", f"## 交易 {i}: `{tx['txid']}`", "",
                      "| 偏移 | 字节数 | 字段 | 原始字节（线缆序） | 解释值 |", "|---:|---:|---|---|---|"]
            for f in tx["fields"]:
                raw = f["raw_hex"] or "（空）"
                val = str(f["value"]).replace("|", "\\|")
                lines.append(f"| {f['offset']} | {f['size']} | `{f['name']}` | `{raw}` | {val} |")
    lines += ["", "> 偏移从 0 开始；多字节整数按比特币协议使用小端序。", ""]
    return "\n".join(lines)


def serialize_tx(inputs: list[dict], outputs: list[tuple[int, bytes]], scripts: list[bytes] | None = None) -> bytes:
    result = struct.pack("<I", 1) + encode_varint(len(inputs))
    for i, item in enumerate(inputs):
        script = scripts[i] if scripts is not None else item.get("script_sig", b"")
        result += bytes.fromhex(item["txid"])[::-1] + struct.pack("<I", item["vout"])
        result += encode_varint(len(script)) + script + struct.pack("<I", 0xFFFFFFFF)
    result += encode_varint(len(outputs))
    for value, script in outputs:
        result += struct.pack("<Q", value) + encode_varint(len(script)) + script
    return result + struct.pack("<I", 0)


def build_signed_transaction(wif: str, destination: str, amount: int, fee_rate: int) -> tuple[bytes, dict]:
    secret, compressed = wif_to_secret(wif)
    pub = public_key(secret, compressed)
    source = p2pkh_address(pub)
    source_script = p2pkh_script(hash160(pub))
    dest_script = p2pkh_script(address_hash160(destination))
    utxos = json.loads(api_get(f"/address/{source}/utxo"))
    utxos.sort(key=lambda x: (not bool(x["status"].get("confirmed")), x["value"]))
    selected, total = [], 0
    for u in utxos:
        selected.append({"txid": u["txid"], "vout": u["vout"], "value": u["value"]})
        total += u["value"]
        estimated_fee = (10 + 148 * len(selected) + 34 * 2) * fee_rate
        if total >= amount + estimated_fee:
            break
    else:
        raise ValueError(f"余额不足：地址 {source} 仅有 {total} sat，目标金额 {amount} sat")
    fee = (10 + 148 * len(selected) + 34 * 2) * fee_rate
    change = total - amount - fee
    outputs = [(amount, dest_script)]
    if change >= 546:
        outputs.append((change, source_script))
    else:
        fee += max(change, 0)
        change = 0
    signed_scripts = []
    for i in range(len(selected)):
        scripts = [source_script if j == i else b"" for j in range(len(selected))]
        preimage = serialize_tx(selected, outputs, scripts) + struct.pack("<I", 1)
        signature = der_signature(secret, hash256(preimage)) + b"\x01"
        signed_scripts.append(push(signature) + push(pub))
    for item, script in zip(selected, signed_scripts):
        item["script_sig"] = script
    raw = serialize_tx(selected, outputs)
    actual_fee = total - sum(v for v, _ in outputs)
    summary_inputs = [{"txid": item["txid"], "vout": item["vout"], "value": item["value"]}
                      for item in selected]
    return raw, {"source": source, "destination": destination, "amount_sat": amount,
                 "change_sat": change, "fee_sat": actual_fee, "inputs": summary_inputs,
                 "txid": hash256(raw)[::-1].hex(), "size": len(raw)}


def cmd_wallet(args):
    secret = secrets.randbelow(N - 1) + 1
    wif = secret_to_wif(secret)
    address = p2pkh_address(public_key(secret))
    payload = {"network": "bitcoin-testnet", "type": "legacy-p2pkh", "address": address, "wif": wif}
    if args.output:
        path = Path(args.output)
        if path.exists() and not args.force:
            raise FileExistsError(f"{path} 已存在；如需覆盖请加 --force")
        path.write_text(json.dumps(payload, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
        print(f"钱包已保存到 {path}。请勿提交或发送此文件。\n测试网地址: {address}")
    else:
        print(json.dumps(payload, ensure_ascii=False, indent=2))


def cmd_parse(args, kind: str):
    if getattr(args, "txid", None):
        data = bytes.fromhex(api_get(f"/tx/{args.txid}/hex"))
    elif getattr(args, "block_hash", None):
        block_hash = api_get("/blocks/tip/hash") if args.block_hash == "tip" else args.block_hash
        data = api_get(f"/block/{block_hash}/raw", binary=True)
    else:
        data = load_hex(args.hex, args.file)
    parsed = parse_block(data) if kind == "block" else parse_transaction(data)
    text = markdown_report(kind, parsed) if args.format == "markdown" else json.dumps(parsed, ensure_ascii=False, indent=2)
    if args.output:
        Path(args.output).write_text(text + ("" if text.endswith("\n") else "\n"), encoding="utf-8")
        print(f"解析完成：{args.output}")
    else:
        print(text)


def cmd_send(args):
    wallet = json.loads(Path(args.wallet).read_text(encoding="utf-8"))
    raw, summary = build_signed_transaction(wallet["wif"], args.to, args.amount, args.fee_rate)
    print(json.dumps(summary, ensure_ascii=False, indent=2))
    print(f"raw transaction:\n{raw.hex()}")
    if args.broadcast:
        if args.confirm != "I_UNDERSTAND_TESTNET":
            raise ValueError("广播时还需加入 --confirm I_UNDERSTAND_TESTNET")
        result = api_post("/tx", raw.hex())
        print(f"广播成功，txid: {result}")
    else:
        print("未广播（dry-run）。确认无误后添加 --broadcast --confirm I_UNDERSTAND_TESTNET")


def build_cli() -> argparse.ArgumentParser:
    p = argparse.ArgumentParser(description="Bitcoin testnet 交易与区块逐字节实验")
    sub = p.add_subparsers(dest="command", required=True)
    w = sub.add_parser("wallet", help="生成仅用于测试网的 legacy P2PKH 钱包")
    w.add_argument("--output", help="钱包 JSON 文件路径")
    w.add_argument("--force", action="store_true", help="覆盖已有文件")
    w.set_defaults(func=cmd_wallet)
    for name, kind in (("parse-tx", "tx"), ("parse-block", "block")):
        q = sub.add_parser(name, help=f"解析{'交易' if kind == 'tx' else '完整区块'}")
        source = q.add_mutually_exclusive_group(required=True)
        source.add_argument("--hex", help="原始十六进制")
        source.add_argument("--file", help="含原始十六进制的文本文件")
        if kind == "tx":
            source.add_argument("--txid", help="从 Blockstream testnet API 获取")
        else:
            source.add_argument("--block-hash", help="从 API 获取；可写 tip 表示最新区块")
        q.add_argument("--format", choices=("markdown", "json"), default="markdown")
        q.add_argument("--output", help="输出报告文件")
        q.set_defaults(func=lambda a, k=kind: cmd_parse(a, k))
    s = sub.add_parser("send", help="构造、签名并可选广播测试网 P2PKH 交易")
    s.add_argument("--wallet", required=True, help="wallet 命令生成的 JSON")
    s.add_argument("--to", required=True, help="目标 testnet legacy P2PKH 地址")
    s.add_argument("--amount", type=int, required=True, help="发送金额，单位 sat")
    s.add_argument("--fee-rate", type=int, default=2, help="费率 sat/vB（默认 2）")
    s.add_argument("--broadcast", action="store_true", help="实际广播；默认只构造")
    s.add_argument("--confirm", help="广播确认短语")
    s.set_defaults(func=cmd_send)
    return p


def main() -> int:
    try:
        args = build_cli().parse_args()
        if getattr(args, "amount", 1) <= 0 or getattr(args, "fee_rate", 1) <= 0:
            raise ValueError("amount 和 fee-rate 必须为正整数")
        args.func(args)
        return 0
    except (ValueError, RuntimeError, OSError, json.JSONDecodeError) as e:
        print(f"错误: {e}", file=sys.stderr)
        return 1


if __name__ == "__main__":
    raise SystemExit(main())
