# 交易逐字节解析

- 总大小：226 bytes
- txid：`b37774146e93f345ea7532475e1a00209ffd913cabe031231435c4096518acd4`
- SegWit：False

## 字段

| 偏移 | 字节数 | 字段 | 原始字节（线缆序） | 解释值 |
|---:|---:|---|---|---|
| 0 | 4 | `tx.version` | `01000000` | 1 |
| 4 | 1 | `tx.input_count` | `01` | 1 |
| 5 | 32 | `vin[0].prev_txid` | `8dbdd46b31da99da11fc073e0d3e20c4bae5f12c78e16c00fe81e69f5a23657f` | 7f65235a9fe681fe006ce1782cf1e5bac4203e0d3e07fc11da99da316bd4bd8d |
| 37 | 4 | `vin[0].vout` | `00000000` | 0 |
| 41 | 1 | `vin[0].scriptSig_length` | `6b` | 107 |
| 42 | 107 | `vin[0].scriptSig` | `483045022100baa0b9639871f2334a2529c24ecbcc9a2c71b1faa3efc8fc1ca3ca0ed19bda8d022079331125ae3f8a95454beda3ed32a5426b5359d24490751d86db8126603bde2d0121038b870bb3832f0bf2f38341ca8878bc9a894c97df81079255d63db29e5df46550` | 3045022100baa0b9639871f2334a2529c24ecbcc9a2c71b1faa3efc8fc1ca3ca0ed19bda8d022079331125ae3f8a95454beda3ed32a5426b5359d24490751d86db8126603bde2d01 038b870bb3832f0bf2f38341ca8878bc9a894c97df81079255d63db29e5df46550 |
| 149 | 4 | `vin[0].sequence` | `ffffffff` | 4294967295 |
| 153 | 1 | `tx.output_count` | `02` | 2 |
| 154 | 8 | `vout[0].value` | `e803000000000000` | 1000 |
| 162 | 1 | `vout[0].scriptPubKey_length` | `19` | 25 |
| 163 | 25 | `vout[0].scriptPubKey` | `76a914e78a00b2e2d66e64404f677126b10b57afd8636288ac` | OP_DUP OP_HASH160 e78a00b2e2d66e64404f677126b10b57afd86362 OP_EQUALVERIFY OP_CHECKSIG |
| 188 | 8 | `vout[1].value` | `943c0f0000000000` | 998548 |
| 196 | 1 | `vout[1].scriptPubKey_length` | `19` | 25 |
| 197 | 25 | `vout[1].scriptPubKey` | `76a914731e4ab4c2186bf8d89d75ec7a2ad315feb2301b88ac` | OP_DUP OP_HASH160 731e4ab4c2186bf8d89d75ec7a2ad315feb2301b OP_EQUALVERIFY OP_CHECKSIG |
| 222 | 4 | `tx.locktime` | `00000000` | 0 |

> 偏移从 0 开始；多字节整数按比特币协议使用小端序。
