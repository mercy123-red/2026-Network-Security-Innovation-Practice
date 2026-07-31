# 完整区块逐字节解析

- 总大小：22528 bytes
- 区块哈希：`0000000010fd16f5549e20575522b15d77ee98305f5fd0454d85ddf18a4f666b`
- 交易数：87
- Merkle Root 校验：通过
- PoW 目标校验：通过
- 难度目标：`00000000ffff0000000000000000000000000000000000000000000000000000`

## 区块头

| 偏移 | 字节数 | 字段 | 原始字节（线缆序） | 解释值 |
|---:|---:|---|---|---|
| 0 | 4 | `block.version` | `04000020` | 536870916 |
| 4 | 32 | `block.previous_hash` | `3ac82d91c1bf03add9b56482f5a51ecbd1a7db30a79eae311a7f013d00000000` | 000000003d017f1a31ae9ea730dba7d1cb1ea5f58264b5d9ad03bfc1912dc83a |
| 36 | 32 | `block.merkle_root` | `3c99959b60a56ccd5685c377f2c809aad6039d24013378d4fcc0b0ade7c2d824` | 24d8c2e7adb0c0fcd4783301249d03d6aa09c8f277c38556cd6ca5609b95993c |
| 68 | 4 | `block.timestamp` | `11d25d6a` | 1784533521 (2026-07-20T07:45:21+00:00) |
| 72 | 4 | `block.bits` | `ffff001d` | 486604799 |
| 76 | 4 | `block.nonce` | `13e34ccd` | 3444368147 |
| 80 | 1 | `block.transaction_count` | `57` | 87 |

## 交易 0: `8351caf5353b822659e7d8d342f5d36b756d906a71ccbb038c7772bdf6d8cb7f`

| 偏移 | 字节数 | 字段 | 原始字节（线缆序） | 解释值 |
|---:|---:|---|---|---|
| 81 | 4 | `tx.version` | `02000000` | 2 |
| 85 | 1 | `tx.marker` | `00` | 0 |
| 86 | 1 | `tx.flag` | `01` | 1 |
| 87 | 1 | `tx.input_count` | `01` | 1 |
| 88 | 32 | `vin[0].prev_txid` | `0000000000000000000000000000000000000000000000000000000000000000` | 0000000000000000000000000000000000000000000000000000000000000000 |
| 120 | 4 | `vin[0].vout` | `ffffffff` | 4294967295 |
| 124 | 1 | `vin[0].scriptSig_length` | `29` | 41 |
| 125 | 41 | `vin[0].scriptSig` | `03c8724d0411d25d6a2f53424943727970746f2e636f6d20506f6f6c2f0200354d0100000000000000` | c8724d 11d25d6a OP_0x2f OP_0x53 OP_0x42 OP_0x49 OP_0x43 OP_0x72 OP_0x79 OP_0x70 OP_0x74 OP_0x6f OP_0x2e OP_0x63 OP_0x6f OP_0x6d OP_0x20 OP_0x50 OP_0x6f OP_0x6f OP_0x6c OP_0x2f 0035 OP_0x4d 00 OP_0 OP_0 OP_0 OP_0 OP_0 OP_0 |
| 166 | 4 | `vin[0].sequence` | `ffffffff` | 4294967295 |
| 170 | 1 | `tx.output_count` | `02` | 2 |
| 171 | 8 | `vout[0].value` | `8375000000000000` | 30083 |
| 179 | 1 | `vout[0].scriptPubKey_length` | `16` | 22 |
| 180 | 22 | `vout[0].scriptPubKey` | `00140e289c4c6030afc3fef48b94bf4ebdf5a12e67a9` | OP_0 0e289c4c6030afc3fef48b94bf4ebdf5a12e67a9 |
| 202 | 8 | `vout[1].value` | `0000000000000000` | 0 |
| 210 | 1 | `vout[1].scriptPubKey_length` | `26` | 38 |
| 211 | 38 | `vout[1].scriptPubKey` | `6a24aa21a9ed0caaf1745474885099c0aafc531de95b2a2df23eac750e59dae1dbb87758875f` | OP_0x6a aa21a9ed0caaf1745474885099c0aafc531de95b2a2df23eac750e59dae1dbb87758875f |
| 249 | 1 | `witness[0].item_count` | `01` | 1 |
| 250 | 1 | `witness[0][0].length` | `20` | 32 |
| 251 | 32 | `witness[0][0].data` | `0000000000000000000000000000000000000000000000000000000000000000` | 0000000000000000000000000000000000000000000000000000000000000000 |
| 283 | 4 | `tx.locktime` | `00000000` | 0 |

## 交易 1: `c9b541c15d0c4a11b704f9a887633dc7eee32051839e3ce27a6da16e2d6bc0c2`

| 偏移 | 字节数 | 字段 | 原始字节（线缆序） | 解释值 |
|---:|---:|---|---|---|
| 287 | 4 | `tx.version` | `01000000` | 1 |
| 291 | 1 | `tx.marker` | `00` | 0 |
| 292 | 1 | `tx.flag` | `01` | 1 |
| 293 | 1 | `tx.input_count` | `02` | 2 |
| 294 | 32 | `vin[0].prev_txid` | `48490002fd1825980f5a35de18d85426777a5b764d19f00dd012b5a5f7495298` | 985249f7a5b512d00df0194d765b7a772654d818de355a0f982518fd02004948 |
| 326 | 4 | `vin[0].vout` | `00000000` | 0 |
| 330 | 1 | `vin[0].scriptSig_length` | `00` | 0 |
| 331 | 0 | `vin[0].scriptSig` | `（空）` |  |
| 331 | 4 | `vin[0].sequence` | `ffffffff` | 4294967295 |
| 335 | 32 | `vin[1].prev_txid` | `8c55836efeea483872b68e6371f8d0bcc8c851a037207ec632640522d5ebfd4a` | 4afdebd522056432c67e2037a051c8c8bcd0f871638eb6723848eafe6e83558c |
| 367 | 4 | `vin[1].vout` | `00000000` | 0 |
| 371 | 1 | `vin[1].scriptSig_length` | `00` | 0 |
| 372 | 0 | `vin[1].scriptSig` | `（空）` |  |
| 372 | 4 | `vin[1].sequence` | `ffffffff` | 4294967295 |
| 376 | 1 | `tx.output_count` | `02` | 2 |
| 377 | 8 | `vout[0].value` | `dd45000000000000` | 17885 |
| 385 | 1 | `vout[0].scriptPubKey_length` | `16` | 22 |
| 386 | 22 | `vout[0].scriptPubKey` | `00144d4c2edad38bfeff9336f7b86d7c53af5de9277a` | OP_0 4d4c2edad38bfeff9336f7b86d7c53af5de9277a |
| 408 | 8 | `vout[1].value` | `0795000000000000` | 38151 |
| 416 | 1 | `vout[1].scriptPubKey_length` | `16` | 22 |
| 417 | 22 | `vout[1].scriptPubKey` | `00144d4c2edad38bfeff9336f7b86d7c53af5de9277a` | OP_0 4d4c2edad38bfeff9336f7b86d7c53af5de9277a |
| 439 | 1 | `witness[0].item_count` | `02` | 2 |
| 440 | 1 | `witness[0][0].length` | `47` | 71 |
| 441 | 71 | `witness[0][0].data` | `304402202fcd72ab4021eaf80711e4a0318ca779282e7e2290d4f57e3cae0a73e05815a202205d2b90a697c2015be8e98c52a0366963cdc48844cc5a418fe3b04b0a58de3c1101` | 304402202fcd72ab4021eaf80711e4a0318ca779282e7e2290d4f57e3cae0a73e05815a202205d2b90a697c2015be8e98c52a0366963cdc48844cc5a418fe3b04b0a58de3c1101 |
| 512 | 1 | `witness[0][1].length` | `21` | 33 |
| 513 | 33 | `witness[0][1].data` | `03598c8f56f3ca1600af22b19ab85de1fa1df9e387940be18a0192a08004d4b974` | 03598c8f56f3ca1600af22b19ab85de1fa1df9e387940be18a0192a08004d4b974 |
| 546 | 1 | `witness[1].item_count` | `02` | 2 |
| 547 | 1 | `witness[1][0].length` | `47` | 71 |
| 548 | 71 | `witness[1][0].data` | `3044022069d0a73bb512355085d9266a7587548858038e7870cb8f5f7398af0b988b8cd902205e0a0ae468e3f52754342717985df7f3a4a2a2038642539baf84bf378b1223a101` | 3044022069d0a73bb512355085d9266a7587548858038e7870cb8f5f7398af0b988b8cd902205e0a0ae468e3f52754342717985df7f3a4a2a2038642539baf84bf378b1223a101 |
| 619 | 1 | `witness[1][1].length` | `21` | 33 |
| 620 | 33 | `witness[1][1].data` | `03598c8f56f3ca1600af22b19ab85de1fa1df9e387940be18a0192a08004d4b974` | 03598c8f56f3ca1600af22b19ab85de1fa1df9e387940be18a0192a08004d4b974 |
| 653 | 4 | `tx.locktime` | `00000000` | 0 |

## 交易 2: `db9489c7a223f31c6c942415cde8d43266ff26f39125035e2c868a86e1beef1e`

| 偏移 | 字节数 | 字段 | 原始字节（线缆序） | 解释值 |
|---:|---:|---|---|---|
| 657 | 4 | `tx.version` | `01000000` | 1 |
| 661 | 1 | `tx.marker` | `00` | 0 |
| 662 | 1 | `tx.flag` | `01` | 1 |
| 663 | 1 | `tx.input_count` | `01` | 1 |
| 664 | 32 | `vin[0].prev_txid` | `48490002fd1825980f5a35de18d85426777a5b764d19f00dd012b5a5f7495298` | 985249f7a5b512d00df0194d765b7a772654d818de355a0f982518fd02004948 |
| 696 | 4 | `vin[0].vout` | `01000000` | 1 |
| 700 | 1 | `vin[0].scriptSig_length` | `17` | 23 |
| 701 | 23 | `vin[0].scriptSig` | `1600148455371d11306bab13d4bb6e4bcbb757c08018f0` | 00148455371d11306bab13d4bb6e4bcbb757c08018f0 |
| 724 | 4 | `vin[0].sequence` | `ffffffff` | 4294967295 |
| 728 | 1 | `tx.output_count` | `02` | 2 |
| 729 | 8 | `vout[0].value` | `8b20000000000000` | 8331 |
| 737 | 1 | `vout[0].scriptPubKey_length` | `16` | 22 |
| 738 | 22 | `vout[0].scriptPubKey` | `00144d4c2edad38bfeff9336f7b86d7c53af5de9277a` | OP_0 4d4c2edad38bfeff9336f7b86d7c53af5de9277a |
| 760 | 8 | `vout[1].value` | `0869490000000000` | 4811016 |
| 768 | 1 | `vout[1].scriptPubKey_length` | `17` | 23 |
| 769 | 23 | `vout[1].scriptPubKey` | `a9146ccec94e3312e1d9b3bf5b7b6b74a8d4515295ba87` | OP_HASH160 6ccec94e3312e1d9b3bf5b7b6b74a8d4515295ba OP_EQUAL |
| 792 | 1 | `witness[0].item_count` | `02` | 2 |
| 793 | 1 | `witness[0][0].length` | `48` | 72 |
| 794 | 72 | `witness[0][0].data` | `3045022100c88f291f998bad9b5ee96cc7ca04298e98758ffb32ff659f7f3337e9cfd899ac022005833195fbf47860c53a5726792e57ada83a740f50296f92ae57cdb2fb857ab801` | 3045022100c88f291f998bad9b5ee96cc7ca04298e98758ffb32ff659f7f3337e9cfd899ac022005833195fbf47860c53a5726792e57ada83a740f50296f92ae57cdb2fb857ab801 |
| 866 | 1 | `witness[0][1].length` | `21` | 33 |
| 867 | 33 | `witness[0][1].data` | `0366a43f0f65b0961c89c186ec7263e6dd811305f62255d8b0a8a814907586cd4d` | 0366a43f0f65b0961c89c186ec7263e6dd811305f62255d8b0a8a814907586cd4d |
| 900 | 4 | `tx.locktime` | `00000000` | 0 |

## 交易 3: `2374d9192e4794338b6949ea14df935881cf3e0ae89f1117983f9f1721ef980e`

| 偏移 | 字节数 | 字段 | 原始字节（线缆序） | 解释值 |
|---:|---:|---|---|---|
| 904 | 4 | `tx.version` | `02000000` | 2 |
| 908 | 1 | `tx.marker` | `00` | 0 |
| 909 | 1 | `tx.flag` | `01` | 1 |
| 910 | 1 | `tx.input_count` | `01` | 1 |
| 911 | 32 | `vin[0].prev_txid` | `d76f845063542f2974a42744337248abaa694dfa9e5567871b9b5d96ddc37459` | 5974c3dd965d9b1b8767559efa4d69aaab4872334427a474292f546350846fd7 |
| 943 | 4 | `vin[0].vout` | `01000000` | 1 |
| 947 | 1 | `vin[0].scriptSig_length` | `00` | 0 |
| 948 | 0 | `vin[0].scriptSig` | `（空）` |  |
| 948 | 4 | `vin[0].sequence` | `ffffffff` | 4294967295 |
| 952 | 1 | `tx.output_count` | `02` | 2 |
| 953 | 8 | `vout[0].value` | `e803000000000000` | 1000 |
| 961 | 1 | `vout[0].scriptPubKey_length` | `16` | 22 |
| 962 | 22 | `vout[0].scriptPubKey` | `00148704b9c722f825fe9369c30cbf6f3bd3a620e8a1` | OP_0 8704b9c722f825fe9369c30cbf6f3bd3a620e8a1 |
| 984 | 8 | `vout[1].value` | `5448024f02000000` | 9915484244 |
| 992 | 1 | `vout[1].scriptPubKey_length` | `16` | 22 |
| 993 | 22 | `vout[1].scriptPubKey` | `0014c40c786f442cc00d629b4945f8fad7a18127e4ef` | OP_0 c40c786f442cc00d629b4945f8fad7a18127e4ef |
| 1015 | 1 | `witness[0].item_count` | `02` | 2 |
| 1016 | 1 | `witness[0][0].length` | `47` | 71 |
| 1017 | 71 | `witness[0][0].data` | `3044022044f9d4e5d42fff60cd2ee140cc8744a118d2dd0c8c71ef7a1749a94e961d91f9022074607427a0322f7a6901ca9801b679d9ceab01c5e02a675e2c78662eb86259e901` | 3044022044f9d4e5d42fff60cd2ee140cc8744a118d2dd0c8c71ef7a1749a94e961d91f9022074607427a0322f7a6901ca9801b679d9ceab01c5e02a675e2c78662eb86259e901 |
| 1088 | 1 | `witness[0][1].length` | `21` | 33 |
| 1089 | 33 | `witness[0][1].data` | `0398fd582cebb4fdd213ae22a4981b2c74194ae751e29c0fbf7579bb26000907b3` | 0398fd582cebb4fdd213ae22a4981b2c74194ae751e29c0fbf7579bb26000907b3 |
| 1122 | 4 | `tx.locktime` | `00000000` | 0 |

## 交易 4: `2c9d08d7ab13894174ec1a166657504f630f8166ad4cbfc5b0c64e7c38db08cf`

| 偏移 | 字节数 | 字段 | 原始字节（线缆序） | 解释值 |
|---:|---:|---|---|---|
| 1126 | 4 | `tx.version` | `01000000` | 1 |
| 1130 | 1 | `tx.marker` | `00` | 0 |
| 1131 | 1 | `tx.flag` | `01` | 1 |
| 1132 | 1 | `tx.input_count` | `01` | 1 |
| 1133 | 32 | `vin[0].prev_txid` | `3d9ca6557487774c792635978e03422094402c4b3f1d23bad124a497bd1d5c9f` | 9f5c1dbd97a424d1ba231d3f4b2c40942042038e973526794c77877455a69c3d |
| 1165 | 4 | `vin[0].vout` | `01000000` | 1 |
| 1169 | 1 | `vin[0].scriptSig_length` | `00` | 0 |
| 1170 | 0 | `vin[0].scriptSig` | `（空）` |  |
| 1170 | 4 | `vin[0].sequence` | `ffffffff` | 4294967295 |
| 1174 | 1 | `tx.output_count` | `02` | 2 |
| 1175 | 8 | `vout[0].value` | `1027000000000000` | 10000 |
| 1183 | 1 | `vout[0].scriptPubKey_length` | `16` | 22 |
| 1184 | 22 | `vout[0].scriptPubKey` | `0014494b2c93cd8903bb0eb6292ff312251631d9f27b` | OP_0 494b2c93cd8903bb0eb6292ff312251631d9f27b |
| 1206 | 8 | `vout[1].value` | `24f5003b00000000` | 989918500 |
| 1214 | 1 | `vout[1].scriptPubKey_length` | `16` | 22 |
| 1215 | 22 | `vout[1].scriptPubKey` | `00149a5efca33f974de7148916562cf6ec02e432bf0f` | OP_0 9a5efca33f974de7148916562cf6ec02e432bf0f |
| 1237 | 1 | `witness[0].item_count` | `02` | 2 |
| 1238 | 1 | `witness[0][0].length` | `48` | 72 |
| 1239 | 72 | `witness[0][0].data` | `3045022100ca59e63cc906577d040f297386aa3fe53939bae5b24a17f0e04bc4251077c947022008e704c334ae9414014ef693933df352aa7e4c37917d3b0e6227ab80de5176fc01` | 3045022100ca59e63cc906577d040f297386aa3fe53939bae5b24a17f0e04bc4251077c947022008e704c334ae9414014ef693933df352aa7e4c37917d3b0e6227ab80de5176fc01 |
| 1311 | 1 | `witness[0][1].length` | `21` | 33 |
| 1312 | 33 | `witness[0][1].data` | `03d674e0b8096497868402595f6cd78c85137d8a717cc35081346fb55430a554a3` | 03d674e0b8096497868402595f6cd78c85137d8a717cc35081346fb55430a554a3 |
| 1345 | 4 | `tx.locktime` | `00000000` | 0 |

## 交易 5: `db7aa362a12ee7d2ecfcd63141cf6b60871f39c7a359068c53ffb3dbca444693`

| 偏移 | 字节数 | 字段 | 原始字节（线缆序） | 解释值 |
|---:|---:|---|---|---|
| 1349 | 4 | `tx.version` | `02000000` | 2 |
| 1353 | 1 | `tx.input_count` | `01` | 1 |
| 1354 | 32 | `vin[0].prev_txid` | `fba794eeee88743bc758b848e571cd5aaf2daee08f977c6170a1bb973346123f` | 3f12463397bba170617c978fe0ae2daf5acd71e548b858c73b7488eeee94a7fb |
| 1386 | 4 | `vin[0].vout` | `01000000` | 1 |
| 1390 | 1 | `vin[0].scriptSig_length` | `6a` | 106 |
| 1391 | 106 | `vin[0].scriptSig` | `47304402206b6ec83e3744ad766eb10d78eef554b34b60776a419a8fbaa6ed210ed12f322002204eb174faaad59d647fca1e33d2140d00143123acbee2c590719a3d1ddfe2edd80121038c9afdff475fb3558c72929580b3d1c1db15139b0782e28c5ba069706fb17861` | 304402206b6ec83e3744ad766eb10d78eef554b34b60776a419a8fbaa6ed210ed12f322002204eb174faaad59d647fca1e33d2140d00143123acbee2c590719a3d1ddfe2edd801 038c9afdff475fb3558c72929580b3d1c1db15139b0782e28c5ba069706fb17861 |
| 1497 | 4 | `vin[0].sequence` | `fdffffff` | 4294967293 |
| 1501 | 1 | `tx.output_count` | `02` | 2 |
| 1502 | 8 | `vout[0].value` | `542b000000000000` | 11092 |
| 1510 | 1 | `vout[0].scriptPubKey_length` | `19` | 25 |
| 1511 | 25 | `vout[0].scriptPubKey` | `76a914a9cd5d353d35e41ca934c1fe82710b2697a7bb0488ac` | OP_DUP OP_HASH160 a9cd5d353d35e41ca934c1fe82710b2697a7bb04 OP_EQUALVERIFY OP_CHECKSIG |
| 1536 | 8 | `vout[1].value` | `4882000000000000` | 33352 |
| 1544 | 1 | `vout[1].scriptPubKey_length` | `19` | 25 |
| 1545 | 25 | `vout[1].scriptPubKey` | `76a914726d9133156d67f6c7d27ab273209bdbc0b750a188ac` | OP_DUP OP_HASH160 726d9133156d67f6c7d27ab273209bdbc0b750a1 OP_EQUALVERIFY OP_CHECKSIG |
| 1570 | 4 | `tx.locktime` | `00000000` | 0 |

## 交易 6: `fc2073d7ec0cf8bc0f81bb47fc097c8e8bf9edf8173292cf409d3e7d01e59b85`

| 偏移 | 字节数 | 字段 | 原始字节（线缆序） | 解释值 |
|---:|---:|---|---|---|
| 1574 | 4 | `tx.version` | `02000000` | 2 |
| 1578 | 1 | `tx.marker` | `00` | 0 |
| 1579 | 1 | `tx.flag` | `01` | 1 |
| 1580 | 1 | `tx.input_count` | `01` | 1 |
| 1581 | 32 | `vin[0].prev_txid` | `6c051d80cec5eb9deb1370cf859f086cba9a2b5cb80b3e17e662fc8520f7477e` | 7e47f72085fc62e6173e0bb85c2b9aba6c089f85cf7013eb9debc5ce801d056c |
| 1613 | 4 | `vin[0].vout` | `01000000` | 1 |
| 1617 | 1 | `vin[0].scriptSig_length` | `00` | 0 |
| 1618 | 0 | `vin[0].scriptSig` | `（空）` |  |
| 1618 | 4 | `vin[0].sequence` | `ffffffff` | 4294967295 |
| 1622 | 1 | `tx.output_count` | `02` | 2 |
| 1623 | 8 | `vout[0].value` | `401f000000000000` | 8000 |
| 1631 | 1 | `vout[0].scriptPubKey_length` | `16` | 22 |
| 1632 | 22 | `vout[0].scriptPubKey` | `00147e00225f756855e4479d3a9789c264bad9afc60a` | OP_0 7e00225f756855e4479d3a9789c264bad9afc60a |
| 1654 | 8 | `vout[1].value` | `3726000000000000` | 9783 |
| 1662 | 1 | `vout[1].scriptPubKey_length` | `16` | 22 |
| 1663 | 22 | `vout[1].scriptPubKey` | `0014d59acb0c18e36056a20e53f0ecb80c658c2da318` | OP_0 d59acb0c18e36056a20e53f0ecb80c658c2da318 |
| 1685 | 1 | `witness[0].item_count` | `02` | 2 |
| 1686 | 1 | `witness[0][0].length` | `47` | 71 |
| 1687 | 71 | `witness[0][0].data` | `30440220282270ea8ce431ac68efebd0efce3a85fd90e38f0979fb95f15b55bda3452b9402206cf6e7baf741fd7433e6fbcc9b8b2dbfc6646606d85679683e04c962e1d6636401` | 30440220282270ea8ce431ac68efebd0efce3a85fd90e38f0979fb95f15b55bda3452b9402206cf6e7baf741fd7433e6fbcc9b8b2dbfc6646606d85679683e04c962e1d6636401 |
| 1758 | 1 | `witness[0][1].length` | `21` | 33 |
| 1759 | 33 | `witness[0][1].data` | `038c95ca9f6d39294c51e198b56d97fba2c0a9de924cdcd930b8a14fc876b45731` | 038c95ca9f6d39294c51e198b56d97fba2c0a9de924cdcd930b8a14fc876b45731 |
| 1792 | 4 | `tx.locktime` | `00000000` | 0 |

## 交易 7: `8b116a1e6c5c0ac42d262ebaa72f7c9eee2e11c47890cdb823c7ca08aeb89e25`

| 偏移 | 字节数 | 字段 | 原始字节（线缆序） | 解释值 |
|---:|---:|---|---|---|
| 1796 | 4 | `tx.version` | `01000000` | 1 |
| 1800 | 1 | `tx.marker` | `00` | 0 |
| 1801 | 1 | `tx.flag` | `01` | 1 |
| 1802 | 1 | `tx.input_count` | `02` | 2 |
| 1803 | 32 | `vin[0].prev_txid` | `51637914b75d57a6a25f64ee140a43feab36bf9067edcbd207aad37d478a980f` | 0f988a477dd3aa07d2cbed6790bf36abfe430a14ee645fa2a6575db714796351 |
| 1835 | 4 | `vin[0].vout` | `00000000` | 0 |
| 1839 | 1 | `vin[0].scriptSig_length` | `00` | 0 |
| 1840 | 0 | `vin[0].scriptSig` | `（空）` |  |
| 1840 | 4 | `vin[0].sequence` | `ffffffff` | 4294967295 |
| 1844 | 32 | `vin[1].prev_txid` | `e004212c43e9fa851df0e3bd2798abf4e0cdc0a064b7902a2e7320a7d1d077a7` | a777d0d1a720732e2a90b764a0c0cde0f4ab9827bde3f01d85fae9432c2104e0 |
| 1876 | 4 | `vin[1].vout` | `01000000` | 1 |
| 1880 | 1 | `vin[1].scriptSig_length` | `00` | 0 |
| 1881 | 0 | `vin[1].scriptSig` | `（空）` |  |
| 1881 | 4 | `vin[1].sequence` | `ffffffff` | 4294967295 |
| 1885 | 1 | `tx.output_count` | `02` | 2 |
| 1886 | 8 | `vout[0].value` | `e803000000000000` | 1000 |
| 1894 | 1 | `vout[0].scriptPubKey_length` | `16` | 22 |
| 1895 | 22 | `vout[0].scriptPubKey` | `0014ee71bdc5434659207d5934046ce0b7d921f0c9a5` | OP_0 ee71bdc5434659207d5934046ce0b7d921f0c9a5 |
| 1917 | 8 | `vout[1].value` | `2c02000000000000` | 556 |
| 1925 | 1 | `vout[1].scriptPubKey_length` | `22` | 34 |
| 1926 | 34 | `vout[1].scriptPubKey` | `5120b2c04b16995f85fbb9f44de95fd0d95f7371d4a8b4525fbd2e7d215da3325bf6` | OP_0x51 b2c04b16995f85fbb9f44de95fd0d95f7371d4a8b4525fbd2e7d215da3325bf6 |
| 1960 | 1 | `witness[0].item_count` | `02` | 2 |
| 1961 | 1 | `witness[0][0].length` | `47` | 71 |
| 1962 | 71 | `witness[0][0].data` | `3044022026d0dbde78fb2c2fdda86d627e7846d1f4c5533506b940b3df9fb88eabde0a7702201b2c2a5a97eb0228290502afa05d243c789bc9d860379dea91a34576265d3b8201` | 3044022026d0dbde78fb2c2fdda86d627e7846d1f4c5533506b940b3df9fb88eabde0a7702201b2c2a5a97eb0228290502afa05d243c789bc9d860379dea91a34576265d3b8201 |
| 2033 | 1 | `witness[0][1].length` | `21` | 33 |
| 2034 | 33 | `witness[0][1].data` | `02e651baca2351d946467aca04a522ab3878a33d3e017f8e1350415fc1dd0d7453` | 02e651baca2351d946467aca04a522ab3878a33d3e017f8e1350415fc1dd0d7453 |
| 2067 | 1 | `witness[1].item_count` | `02` | 2 |
| 2068 | 1 | `witness[1][0].length` | `47` | 71 |
| 2069 | 71 | `witness[1][0].data` | `3044022074e5c0926b187ff0dedd4e28d68e2c21273d2b1318daefa9401a78c948de19c60220312fcfd6b626c2d3b3a6cee6ebb30d141cda4d1c57528caa065b6dfd823bac7701` | 3044022074e5c0926b187ff0dedd4e28d68e2c21273d2b1318daefa9401a78c948de19c60220312fcfd6b626c2d3b3a6cee6ebb30d141cda4d1c57528caa065b6dfd823bac7701 |
| 2140 | 1 | `witness[1][1].length` | `21` | 33 |
| 2141 | 33 | `witness[1][1].data` | `031dc7d1e192eac790363a71aeef562a20b16b162acef02785fc7734023d094922` | 031dc7d1e192eac790363a71aeef562a20b16b162acef02785fc7734023d094922 |
| 2174 | 4 | `tx.locktime` | `00000000` | 0 |

## 交易 8: `9f037cc383ebe0de3079b220f8e0b3709016f99a838200d9df36cab573b1b17c`

| 偏移 | 字节数 | 字段 | 原始字节（线缆序） | 解释值 |
|---:|---:|---|---|---|
| 2178 | 4 | `tx.version` | `01000000` | 1 |
| 2182 | 1 | `tx.marker` | `00` | 0 |
| 2183 | 1 | `tx.flag` | `01` | 1 |
| 2184 | 1 | `tx.input_count` | `02` | 2 |
| 2185 | 32 | `vin[0].prev_txid` | `d5f2b8934e7c7e0e7ce47d53b73567a8d5acb2295613949429bf2621fa8dc218` | 18c28dfa2126bf299494135629b2acd5a86735b7537de47c0e7e7c4e93b8f2d5 |
| 2217 | 4 | `vin[0].vout` | `01000000` | 1 |
| 2221 | 1 | `vin[0].scriptSig_length` | `00` | 0 |
| 2222 | 0 | `vin[0].scriptSig` | `（空）` |  |
| 2222 | 4 | `vin[0].sequence` | `ffffffff` | 4294967295 |
| 2226 | 32 | `vin[1].prev_txid` | `d81589603bd7fbed21ada6627fe17422ce701b36279576070c2c13598254eb76` | 76eb548259132c0c07769527361b70ce2274e17f62a6ad21edfbd73b608915d8 |
| 2258 | 4 | `vin[1].vout` | `01000000` | 1 |
| 2262 | 1 | `vin[1].scriptSig_length` | `00` | 0 |
| 2263 | 0 | `vin[1].scriptSig` | `（空）` |  |
| 2263 | 4 | `vin[1].sequence` | `ffffffff` | 4294967295 |
| 2267 | 1 | `tx.output_count` | `02` | 2 |
| 2268 | 8 | `vout[0].value` | `5a2c390000000000` | 3746906 |
| 2276 | 1 | `vout[0].scriptPubKey_length` | `22` | 34 |
| 2277 | 34 | `vout[0].scriptPubKey` | `5120bc4ce7b5624b54a1c9648aa9b8acaab66b905af3c752f85e00a0054adbdcf7ac` | OP_0x51 bc4ce7b5624b54a1c9648aa9b8acaab66b905af3c752f85e00a0054adbdcf7ac |
| 2311 | 8 | `vout[1].value` | `e803000000000000` | 1000 |
| 2319 | 1 | `vout[1].scriptPubKey_length` | `16` | 22 |
| 2320 | 22 | `vout[1].scriptPubKey` | `0014ee71bdc5434659207d5934046ce0b7d921f0c9a5` | OP_0 ee71bdc5434659207d5934046ce0b7d921f0c9a5 |
| 2342 | 1 | `witness[0].item_count` | `01` | 1 |
| 2343 | 1 | `witness[0][0].length` | `40` | 64 |
| 2344 | 64 | `witness[0][0].data` | `1993cc2416c3f1d5e7aa1dee7f592399320e47096cc3a3f3864b505012d94515c15dc7a208c1b932c617ca9e67c71366c0e9f82c7a1b88cf7373cb0794e2b2f5` | 1993cc2416c3f1d5e7aa1dee7f592399320e47096cc3a3f3864b505012d94515c15dc7a208c1b932c617ca9e67c71366c0e9f82c7a1b88cf7373cb0794e2b2f5 |
| 2408 | 1 | `witness[1].item_count` | `01` | 1 |
| 2409 | 1 | `witness[1][0].length` | `40` | 64 |
| 2410 | 64 | `witness[1][0].data` | `6ee9893f78aba12ac48afdeaec76786cf2203ad36cbd30dffc542566ce6630894024b2c67a4486533558bf0bdc5b7d66798d9f5575581e9e2a38d859e97cbcbc` | 6ee9893f78aba12ac48afdeaec76786cf2203ad36cbd30dffc542566ce6630894024b2c67a4486533558bf0bdc5b7d66798d9f5575581e9e2a38d859e97cbcbc |
| 2474 | 4 | `tx.locktime` | `00000000` | 0 |

## 交易 9: `fdba73993f2262e4bee5aaa2eb46af1d34693ec3fbd9fa002810055a779c87dc`

| 偏移 | 字节数 | 字段 | 原始字节（线缆序） | 解释值 |
|---:|---:|---|---|---|
| 2478 | 4 | `tx.version` | `01000000` | 1 |
| 2482 | 1 | `tx.marker` | `00` | 0 |
| 2483 | 1 | `tx.flag` | `01` | 1 |
| 2484 | 1 | `tx.input_count` | `02` | 2 |
| 2485 | 32 | `vin[0].prev_txid` | `cb34e5abace36ed1ac34f3679bb1bd92d7bd924a6f4a015f0a0e87466f3a67d5` | d5673a6f46870e0a5f014a6f4a92bdd792bdb19b67f334acd16ee3acabe534cb |
| 2517 | 4 | `vin[0].vout` | `00000000` | 0 |
| 2521 | 1 | `vin[0].scriptSig_length` | `00` | 0 |
| 2522 | 0 | `vin[0].scriptSig` | `（空）` |  |
| 2522 | 4 | `vin[0].sequence` | `ffffffff` | 4294967295 |
| 2526 | 32 | `vin[1].prev_txid` | `678f4fe7b045cc9330763fc2185d8bde96cf47e998846b35c9eb475345387497` | 977438455347ebc9356b8498e947cf96de8b5d18c23f763093cc45b0e74f8f67 |
| 2558 | 4 | `vin[1].vout` | `00000000` | 0 |
| 2562 | 1 | `vin[1].scriptSig_length` | `00` | 0 |
| 2563 | 0 | `vin[1].scriptSig` | `（空）` |  |
| 2563 | 4 | `vin[1].sequence` | `ffffffff` | 4294967295 |
| 2567 | 1 | `tx.output_count` | `02` | 2 |
| 2568 | 8 | `vout[0].value` | `2c02000000000000` | 556 |
| 2576 | 1 | `vout[0].scriptPubKey_length` | `22` | 34 |
| 2577 | 34 | `vout[0].scriptPubKey` | `51206d952f91645f6b9bcf58094f3da32c337e905885df8050c2847567430c7a2610` | OP_0x51 6d952f91645f6b9bcf58094f3da32c337e905885df8050c2847567430c7a2610 |
| 2611 | 8 | `vout[1].value` | `e803000000000000` | 1000 |
| 2619 | 1 | `vout[1].scriptPubKey_length` | `16` | 22 |
| 2620 | 22 | `vout[1].scriptPubKey` | `0014a3ed95cec518a08473570131635588c92bfb5180` | OP_0 a3ed95cec518a08473570131635588c92bfb5180 |
| 2642 | 1 | `witness[0].item_count` | `02` | 2 |
| 2643 | 1 | `witness[0][0].length` | `48` | 72 |
| 2644 | 72 | `witness[0][0].data` | `3045022100bc1c5e761fe8b47baa85f47da67cfcb8a595a4b9c29fa73553f76ede58c3b29b022070c1daa28fa2cc651ab9484d3e0507793010678fb3d14bd31f9a97a14ca8315401` | 3045022100bc1c5e761fe8b47baa85f47da67cfcb8a595a4b9c29fa73553f76ede58c3b29b022070c1daa28fa2cc651ab9484d3e0507793010678fb3d14bd31f9a97a14ca8315401 |
| 2716 | 1 | `witness[0][1].length` | `21` | 33 |
| 2717 | 33 | `witness[0][1].data` | `032b992310ee8373057f256f4bba7b59f321285116a7b2c6ad8877412cbf50c0d6` | 032b992310ee8373057f256f4bba7b59f321285116a7b2c6ad8877412cbf50c0d6 |
| 2750 | 1 | `witness[1].item_count` | `02` | 2 |
| 2751 | 1 | `witness[1][0].length` | `47` | 71 |
| 2752 | 71 | `witness[1][0].data` | `304402202ef69c711fa2e67088d72c8afd3b99f736ce8494af19dc03b4684fe3f8982bc0022025550b708cbad94e004bddedc52cc2e2f483f410b2ac0e5de73412351e78d87401` | 304402202ef69c711fa2e67088d72c8afd3b99f736ce8494af19dc03b4684fe3f8982bc0022025550b708cbad94e004bddedc52cc2e2f483f410b2ac0e5de73412351e78d87401 |
| 2823 | 1 | `witness[1][1].length` | `21` | 33 |
| 2824 | 33 | `witness[1][1].data` | `02df616f941da474cc893068c88e970d4cd3d4181c28fab5a5db41349027b34e04` | 02df616f941da474cc893068c88e970d4cd3d4181c28fab5a5db41349027b34e04 |
| 2857 | 4 | `tx.locktime` | `00000000` | 0 |

## 交易 10: `2313c6341e756dc07bf8aaf32b36cc5afc269aa56eee2754315cbb20b7af4f03`

| 偏移 | 字节数 | 字段 | 原始字节（线缆序） | 解释值 |
|---:|---:|---|---|---|
| 2861 | 4 | `tx.version` | `01000000` | 1 |
| 2865 | 1 | `tx.input_count` | `01` | 1 |
| 2866 | 32 | `vin[0].prev_txid` | `02738d04dc303772f1d774bc9a687c7f931485d3a80238bcddf382a9db0effc4` | c4ff0edba982f3ddbc3802a8d38514937f7c689abc74d7f1723730dc048d7302 |
| 2898 | 4 | `vin[0].vout` | `09000000` | 9 |
| 2902 | 1 | `vin[0].scriptSig_length` | `6a` | 106 |
| 2903 | 106 | `vin[0].scriptSig` | `47304402205f28a999301610d9bcaeb04b053d7392405aabe4d2f5b3ed196ef0841fd7aac2022038b283cf8a4a4d724a69cb0703b99ad9a5343fb3bf83b21cbe0ec91150a7d84d012103bf8b55d9987647e53088fe90e86c3e855636d9845ad73dce0d6ce7127f2b451c` | 304402205f28a999301610d9bcaeb04b053d7392405aabe4d2f5b3ed196ef0841fd7aac2022038b283cf8a4a4d724a69cb0703b99ad9a5343fb3bf83b21cbe0ec91150a7d84d01 03bf8b55d9987647e53088fe90e86c3e855636d9845ad73dce0d6ce7127f2b451c |
| 3009 | 4 | `vin[0].sequence` | `ffffffff` | 4294967295 |
| 3013 | 1 | `tx.output_count` | `0a` | 10 |
| 3014 | 8 | `vout[0].value` | `2202000000000000` | 546 |
| 3022 | 1 | `vout[0].scriptPubKey_length` | `19` | 25 |
| 3023 | 25 | `vout[0].scriptPubKey` | `76a9145349472f38382f494a2f5034503258554363426a88ac` | OP_DUP OP_HASH160 5349472f38382f494a2f5034503258554363426a OP_EQUALVERIFY OP_CHECKSIG |
| 3048 | 8 | `vout[1].value` | `2202000000000000` | 546 |
| 3056 | 1 | `vout[1].scriptPubKey_length` | `19` | 25 |
| 3057 | 25 | `vout[1].scriptPubKey` | `76a9146343584a676c625478485378637177563251386288ac` | OP_DUP OP_HASH160 6343584a676c6254784853786371775632513862 OP_EQUALVERIFY OP_CHECKSIG |
| 3082 | 8 | `vout[2].value` | `2202000000000000` | 546 |
| 3090 | 1 | `vout[2].scriptPubKey_length` | `19` | 25 |
| 3091 | 25 | `vout[2].scriptPubKey` | `76a9144767744c65737350336f4956515237503946724788ac` | OP_DUP OP_HASH160 4767744c65737350336f49565152375039467247 OP_EQUALVERIFY OP_CHECKSIG |
| 3116 | 8 | `vout[3].value` | `2202000000000000` | 546 |
| 3124 | 1 | `vout[3].scriptPubKey_length` | `19` | 25 |
| 3125 | 25 | `vout[3].scriptPubKey` | `76a9146370562f445838363469756435796e4936642f7788ac` | OP_DUP OP_HASH160 6370562f445838363469756435796e4936642f77 OP_EQUALVERIFY OP_CHECKSIG |
| 3150 | 8 | `vout[4].value` | `2202000000000000` | 546 |
| 3158 | 1 | `vout[4].scriptPubKey_length` | `19` | 25 |
| 3159 | 25 | `vout[4].scriptPubKey` | `76a914487269677778302b785761456d383d2f32372f2388ac` | OP_DUP OP_HASH160 487269677778302b785761456d383d2f32372f23 OP_EQUALVERIFY OP_CHECKSIG |
| 3184 | 8 | `vout[5].value` | `2202000000000000` | 546 |
| 3192 | 1 | `vout[5].scriptPubKey_length` | `19` | 25 |
| 3193 | 25 | `vout[5].scriptPubKey` | `76a9144254432d5553442036343130352e30303c3c2d3888ac` | OP_DUP OP_HASH160 4254432d5553442036343130352e30303c3c2d38 OP_EQUALVERIFY OP_CHECKSIG |
| 3218 | 8 | `vout[6].value` | `2202000000000000` | 546 |
| 3226 | 1 | `vout[6].scriptPubKey_length` | `19` | 25 |
| 3227 | 25 | `vout[6].scriptPubKey` | `76a914393033323e3e232323232323232323232323232388ac` | OP_DUP OP_HASH160 393033323e3e2323232323232323232323232323 OP_EQUALVERIFY OP_CHECKSIG |
| 3252 | 8 | `vout[7].value` | `2202000000000000` | 546 |
| 3260 | 1 | `vout[7].scriptPubKey_length` | `19` | 25 |
| 3261 | 25 | `vout[7].scriptPubKey` | `76a9144254432d5553442323232323232323232323232388ac` | OP_DUP OP_HASH160 4254432d55534423232323232323232323232323 OP_EQUALVERIFY OP_CHECKSIG |
| 3286 | 8 | `vout[8].value` | `2202000000000000` | 546 |
| 3294 | 1 | `vout[8].scriptPubKey_length` | `19` | 25 |
| 3295 | 25 | `vout[8].scriptPubKey` | `76a914b15dc77858baa905544219b3ca386029aefb476988ac` | OP_DUP OP_HASH160 b15dc77858baa905544219b3ca386029aefb4769 OP_EQUALVERIFY OP_CHECKSIG |
| 3320 | 8 | `vout[9].value` | `82ad9a0200000000` | 43691394 |
| 3328 | 1 | `vout[9].scriptPubKey_length` | `19` | 25 |
| 3329 | 25 | `vout[9].scriptPubKey` | `76a914b07f4f84f182121de9d36d835afae41ad0eb122888ac` | OP_DUP OP_HASH160 b07f4f84f182121de9d36d835afae41ad0eb1228 OP_EQUALVERIFY OP_CHECKSIG |
| 3354 | 4 | `tx.locktime` | `00000000` | 0 |

## 交易 11: `7ea8354d1f201100b06a826537ac6d7241bf46dd1b408087e7779b549875a723`

| 偏移 | 字节数 | 字段 | 原始字节（线缆序） | 解释值 |
|---:|---:|---|---|---|
| 3358 | 4 | `tx.version` | `01000000` | 1 |
| 3362 | 1 | `tx.input_count` | `01` | 1 |
| 3363 | 32 | `vin[0].prev_txid` | `cc20b33f18a9d24dff1f2a7b5d1a7726822768f829fe64d444301ae51bde2ee0` | e02ede1be51a3044d464fe29f868278226771a5d7b2a1fff4dd2a9183fb320cc |
| 3395 | 4 | `vin[0].vout` | `09000000` | 9 |
| 3399 | 1 | `vin[0].scriptSig_length` | `6a` | 106 |
| 3400 | 106 | `vin[0].scriptSig` | `47304402204c3a31942b8e0de2ce5c274fd19e938241e8ad8f33ae1c381158a9df51b3a45a022023b038e94d24d09487e06c7877ca57541bda521cd15d81f78dca500e4afc49880121025af096a487c2001f5af58368bb7c2cc93c11a2112e6adbb02e9e10ea0bb1366a` | 304402204c3a31942b8e0de2ce5c274fd19e938241e8ad8f33ae1c381158a9df51b3a45a022023b038e94d24d09487e06c7877ca57541bda521cd15d81f78dca500e4afc498801 025af096a487c2001f5af58368bb7c2cc93c11a2112e6adbb02e9e10ea0bb1366a |
| 3506 | 4 | `vin[0].sequence` | `ffffffff` | 4294967295 |
| 3510 | 1 | `tx.output_count` | `0a` | 10 |
| 3511 | 8 | `vout[0].value` | `2202000000000000` | 546 |
| 3519 | 1 | `vout[0].scriptPubKey_length` | `19` | 25 |
| 3520 | 25 | `vout[0].scriptPubKey` | `76a9145349473f38383f48786c6c70384a486a6f54614a88ac` | OP_DUP OP_HASH160 5349473f38383f48786c6c70384a486a6f54614a OP_EQUALVERIFY OP_CHECKSIG |
| 3545 | 8 | `vout[1].value` | `2202000000000000` | 546 |
| 3553 | 1 | `vout[1].scriptPubKey_length` | `19` | 25 |
| 3554 | 25 | `vout[1].scriptPubKey` | `76a91453573366357a774b58733356753470494455776288ac` | OP_DUP OP_HASH160 53573366357a774b587333567534704944557762 OP_EQUALVERIFY OP_CHECKSIG |
| 3579 | 8 | `vout[2].value` | `2202000000000000` | 546 |
| 3587 | 1 | `vout[2].scriptPubKey_length` | `19` | 25 |
| 3588 | 25 | `vout[2].scriptPubKey` | `76a9147164486f706f33506e4c67666475784f467a433188ac` | OP_DUP OP_HASH160 7164486f706f33506e4c67666475784f467a4331 OP_EQUALVERIFY OP_CHECKSIG |
| 3613 | 8 | `vout[3].value` | `2202000000000000` | 546 |
| 3621 | 1 | `vout[3].scriptPubKey_length` | `19` | 25 |
| 3622 | 25 | `vout[3].scriptPubKey` | `76a91432424b3273524f6e615055454f346a4d7042453588ac` | OP_DUP OP_HASH160 32424b3273524f6e615055454f346a4d70424535 OP_EQUALVERIFY OP_CHECKSIG |
| 3647 | 8 | `vout[4].value` | `2202000000000000` | 546 |
| 3655 | 1 | `vout[4].scriptPubKey_length` | `19` | 25 |
| 3656 | 25 | `vout[4].scriptPubKey` | `76a9146f4e71512b78435a303553466c673d3f32333f2388ac` | OP_DUP OP_HASH160 6f4e71512b78435a303553466c673d3f32333f23 OP_EQUALVERIFY OP_CHECKSIG |
| 3681 | 8 | `vout[5].value` | `2202000000000000` | 546 |
| 3689 | 1 | `vout[5].scriptPubKey_length` | `19` | 25 |
| 3690 | 25 | `vout[5].scriptPubKey` | `76a914444f472d55534420302e30373c3c2d373033313988ac` | OP_DUP OP_HASH160 444f472d55534420302e30373c3c2d3730333139 OP_EQUALVERIFY OP_CHECKSIG |
| 3715 | 8 | `vout[6].value` | `2202000000000000` | 546 |
| 3723 | 1 | `vout[6].scriptPubKey_length` | `19` | 25 |
| 3724 | 25 | `vout[6].scriptPubKey` | `76a9143e3e23232323232323232323232323232323232388ac` | OP_DUP OP_HASH160 3e3e232323232323232323232323232323232323 OP_EQUALVERIFY OP_CHECKSIG |
| 3749 | 8 | `vout[7].value` | `2202000000000000` | 546 |
| 3757 | 1 | `vout[7].scriptPubKey_length` | `19` | 25 |
| 3758 | 25 | `vout[7].scriptPubKey` | `76a914444f472d5553442323232323232323232323232388ac` | OP_DUP OP_HASH160 444f472d55534423232323232323232323232323 OP_EQUALVERIFY OP_CHECKSIG |
| 3783 | 8 | `vout[8].value` | `2202000000000000` | 546 |
| 3791 | 1 | `vout[8].scriptPubKey_length` | `19` | 25 |
| 3792 | 25 | `vout[8].scriptPubKey` | `76a914e157c674eab2ebc885979ac56c8c820f440412a788ac` | OP_DUP OP_HASH160 e157c674eab2ebc885979ac56c8c820f440412a7 OP_EQUALVERIFY OP_CHECKSIG |
| 3817 | 8 | `vout[9].value` | `96c507a901000000` | 7130826134 |
| 3825 | 1 | `vout[9].scriptPubKey_length` | `19` | 25 |
| 3826 | 25 | `vout[9].scriptPubKey` | `76a91489649cfdbbc9889f12f73b16e56291103e443cfd88ac` | OP_DUP OP_HASH160 89649cfdbbc9889f12f73b16e56291103e443cfd OP_EQUALVERIFY OP_CHECKSIG |
| 3851 | 4 | `tx.locktime` | `00000000` | 0 |

## 交易 12: `2e304effa5bf3cd162dd275933db842116b961f2c76ab1bb2cc8b911d27b5d15`

| 偏移 | 字节数 | 字段 | 原始字节（线缆序） | 解释值 |
|---:|---:|---|---|---|
| 3855 | 4 | `tx.version` | `01000000` | 1 |
| 3859 | 1 | `tx.input_count` | `01` | 1 |
| 3860 | 32 | `vin[0].prev_txid` | `7953b9b713d2c3b71aeac0c91cea15c1e91a19be431b94511515348476907e3b` | 3b7e90768434151551941b43be191ae9c115ea1cc9c0ea1ab7c3d213b7b95379 |
| 3892 | 4 | `vin[0].vout` | `09000000` | 9 |
| 3896 | 1 | `vin[0].scriptSig_length` | `6b` | 107 |
| 3897 | 107 | `vin[0].scriptSig` | `483045022100cf1e5ac4f829772ee17546c6676796d4c634ef515f27ede484770483341cfd1c02204d18644af60f5f6ec08a33a26ed7e05e722dad95d5837d9c770b99cb502f273901210200a796485f64ea00df49cc540f6d64842e6737ad854aa9de2fe744b125af1453` | 3045022100cf1e5ac4f829772ee17546c6676796d4c634ef515f27ede484770483341cfd1c02204d18644af60f5f6ec08a33a26ed7e05e722dad95d5837d9c770b99cb502f273901 0200a796485f64ea00df49cc540f6d64842e6737ad854aa9de2fe744b125af1453 |
| 4004 | 4 | `vin[0].sequence` | `ffffffff` | 4294967295 |
| 4008 | 1 | `tx.output_count` | `0a` | 10 |
| 4009 | 8 | `vout[0].value` | `2202000000000000` | 546 |
| 4017 | 1 | `vout[0].scriptPubKey_length` | `19` | 25 |
| 4018 | 25 | `vout[0].scriptPubKey` | `76a9145349473f38383f487a506468424d51355078777888ac` | OP_DUP OP_HASH160 5349473f38383f487a506468424d513550787778 OP_EQUALVERIFY OP_CHECKSIG |
| 4043 | 8 | `vout[1].value` | `2202000000000000` | 546 |
| 4051 | 1 | `vout[1].scriptPubKey_length` | `19` | 25 |
| 4052 | 25 | `vout[1].scriptPubKey` | `76a914414e7568775530356d33434b6b734935736a734c88ac` | OP_DUP OP_HASH160 414e7568775530356d33434b6b734935736a734c OP_EQUALVERIFY OP_CHECKSIG |
| 4077 | 8 | `vout[2].value` | `2202000000000000` | 546 |
| 4085 | 1 | `vout[2].scriptPubKey_length` | `19` | 25 |
| 4086 | 25 | `vout[2].scriptPubKey` | `76a9144e497953794136416d447857576a4c7a376f533188ac` | OP_DUP OP_HASH160 4e497953794136416d447857576a4c7a376f5331 OP_EQUALVERIFY OP_CHECKSIG |
| 4111 | 8 | `vout[3].value` | `2202000000000000` | 546 |
| 4119 | 1 | `vout[3].scriptPubKey_length` | `19` | 25 |
| 4120 | 25 | `vout[3].scriptPubKey` | `76a914724a52574d3973564e79554c47554f33394f616688ac` | OP_DUP OP_HASH160 724a52574d3973564e79554c47554f33394f6166 OP_EQUALVERIFY OP_CHECKSIG |
| 4145 | 8 | `vout[4].value` | `2202000000000000` | 546 |
| 4153 | 1 | `vout[4].scriptPubKey_length` | `19` | 25 |
| 4154 | 25 | `vout[4].scriptPubKey` | `76a914457a4b62674348547134506b474d3d3f32373f2388ac` | OP_DUP OP_HASH160 457a4b62674348547134506b474d3d3f32373f23 OP_EQUALVERIFY OP_CHECKSIG |
| 4179 | 8 | `vout[5].value` | `2202000000000000` | 546 |
| 4187 | 1 | `vout[5].scriptPubKey_length` | `19` | 25 |
| 4188 | 25 | `vout[5].scriptPubKey` | `76a9144254432d5553442036343031352e30303c3c2d3788ac` | OP_DUP OP_HASH160 4254432d5553442036343031352e30303c3c2d37 OP_EQUALVERIFY OP_CHECKSIG |
| 4213 | 8 | `vout[6].value` | `2202000000000000` | 546 |
| 4221 | 1 | `vout[6].scriptPubKey_length` | `19` | 25 |
| 4222 | 25 | `vout[6].scriptPubKey` | `76a914303132343e3e232323232323232323232323232388ac` | OP_DUP OP_HASH160 303132343e3e2323232323232323232323232323 OP_EQUALVERIFY OP_CHECKSIG |
| 4247 | 8 | `vout[7].value` | `2202000000000000` | 546 |
| 4255 | 1 | `vout[7].scriptPubKey_length` | `19` | 25 |
| 4256 | 25 | `vout[7].scriptPubKey` | `76a9144254432d5553442323232323232323232323232388ac` | OP_DUP OP_HASH160 4254432d55534423232323232323232323232323 OP_EQUALVERIFY OP_CHECKSIG |
| 4281 | 8 | `vout[8].value` | `2202000000000000` | 546 |
| 4289 | 1 | `vout[8].scriptPubKey_length` | `19` | 25 |
| 4290 | 25 | `vout[8].scriptPubKey` | `76a9142045dc100bfb96bdeba4af5a2d520b28c899937a88ac` | OP_DUP OP_HASH160 2045dc100bfb96bdeba4af5a2d520b28c899937a OP_EQUALVERIFY OP_CHECKSIG |
| 4315 | 8 | `vout[9].value` | `3efdf73a00000000` | 989330750 |
| 4323 | 1 | `vout[9].scriptPubKey_length` | `19` | 25 |
| 4324 | 25 | `vout[9].scriptPubKey` | `76a914d9f9d8bd152be115821f9e83fd00fffe40c35b4588ac` | OP_DUP OP_HASH160 d9f9d8bd152be115821f9e83fd00fffe40c35b45 OP_EQUALVERIFY OP_CHECKSIG |
| 4349 | 4 | `tx.locktime` | `00000000` | 0 |

## 交易 13: `f92ef2cb47bc1b1a719383a9818ee03f057664a2088b740be22d89d83b31cb9e`

| 偏移 | 字节数 | 字段 | 原始字节（线缆序） | 解释值 |
|---:|---:|---|---|---|
| 4353 | 4 | `tx.version` | `01000000` | 1 |
| 4357 | 1 | `tx.input_count` | `01` | 1 |
| 4358 | 32 | `vin[0].prev_txid` | `bf39a85cf1dfd5c0f3079250f5197b3ea507af3edabfaf0693005d0fa1965e69` | 695e96a10f5d009306afbfda3eaf07a53e7b19f5509207f3c0d5dff15ca839bf |
| 4390 | 4 | `vin[0].vout` | `09000000` | 9 |
| 4394 | 1 | `vin[0].scriptSig_length` | `6b` | 107 |
| 4395 | 107 | `vin[0].scriptSig` | `483045022100b2c5949c3f95d77791effdceb80d986e9221bbdc1a8fe70c30fcd76fb7feffa602206d6b0d4788109fb683475ada9a54d522c862ec6e4677d7416fc4a4f573df7042012102a3cc1abdabf26ef59ea063eae269294a64c2333067a5f410e5d4fdff6393c74c` | 3045022100b2c5949c3f95d77791effdceb80d986e9221bbdc1a8fe70c30fcd76fb7feffa602206d6b0d4788109fb683475ada9a54d522c862ec6e4677d7416fc4a4f573df704201 02a3cc1abdabf26ef59ea063eae269294a64c2333067a5f410e5d4fdff6393c74c |
| 4502 | 4 | `vin[0].sequence` | `ffffffff` | 4294967295 |
| 4506 | 1 | `tx.output_count` | `0a` | 10 |
| 4507 | 8 | `vout[0].value` | `2202000000000000` | 546 |
| 4515 | 1 | `vout[0].scriptPubKey_length` | `19` | 25 |
| 4516 | 25 | `vout[0].scriptPubKey` | `76a91453494722383822483646594439765476504b416e88ac` | OP_DUP OP_HASH160 53494722383822483646594439765476504b416e OP_EQUALVERIFY OP_CHECKSIG |
| 4541 | 8 | `vout[1].value` | `2202000000000000` | 546 |
| 4549 | 1 | `vout[1].scriptPubKey_length` | `19` | 25 |
| 4550 | 25 | `vout[1].scriptPubKey` | `76a9144d534b6a7853415659657461566f4a6c3869364388ac` | OP_DUP OP_HASH160 4d534b6a7853415659657461566f4a6c38693643 OP_EQUALVERIFY OP_CHECKSIG |
| 4575 | 8 | `vout[2].value` | `2202000000000000` | 546 |
| 4583 | 1 | `vout[2].scriptPubKey_length` | `19` | 25 |
| 4584 | 25 | `vout[2].scriptPubKey` | `76a9147244364e46492f682b5756615477595a3949574888ac` | OP_DUP OP_HASH160 7244364e46492f682b5756615477595a39495748 OP_EQUALVERIFY OP_CHECKSIG |
| 4609 | 8 | `vout[3].value` | `2202000000000000` | 546 |
| 4617 | 1 | `vout[3].scriptPubKey_length` | `19` | 25 |
| 4618 | 25 | `vout[3].scriptPubKey` | `76a914646475655241416f7956644f5164546d5636614788ac` | OP_DUP OP_HASH160 646475655241416f7956644f5164546d56366147 OP_EQUALVERIFY OP_CHECKSIG |
| 4643 | 8 | `vout[4].value` | `2202000000000000` | 546 |
| 4651 | 1 | `vout[4].scriptPubKey_length` | `19` | 25 |
| 4652 | 25 | `vout[4].scriptPubKey` | `76a914366552323555457a6f2f6e2b50773d223236222388ac` | OP_DUP OP_HASH160 366552323555457a6f2f6e2b50773d2232362223 OP_EQUALVERIFY OP_CHECKSIG |
| 4677 | 8 | `vout[5].value` | `2202000000000000` | 546 |
| 4685 | 1 | `vout[5].scriptPubKey_length` | `19` | 25 |
| 4686 | 25 | `vout[5].scriptPubKey` | `76a9144554482d55534420313835352e30373c3c2d383088ac` | OP_DUP OP_HASH160 4554482d55534420313835352e30373c3c2d3830 OP_EQUALVERIFY OP_CHECKSIG |
| 4711 | 8 | `vout[6].value` | `2202000000000000` | 546 |
| 4719 | 1 | `vout[6].scriptPubKey_length` | `19` | 25 |
| 4720 | 25 | `vout[6].scriptPubKey` | `76a9143939383e3e23232323232323232323232323232388ac` | OP_DUP OP_HASH160 3939383e3e232323232323232323232323232323 OP_EQUALVERIFY OP_CHECKSIG |
| 4745 | 8 | `vout[7].value` | `2202000000000000` | 546 |
| 4753 | 1 | `vout[7].scriptPubKey_length` | `19` | 25 |
| 4754 | 25 | `vout[7].scriptPubKey` | `76a9144554482d5553442323232323232323232323232388ac` | OP_DUP OP_HASH160 4554482d55534423232323232323232323232323 OP_EQUALVERIFY OP_CHECKSIG |
| 4779 | 8 | `vout[8].value` | `2202000000000000` | 546 |
| 4787 | 1 | `vout[8].scriptPubKey_length` | `19` | 25 |
| 4788 | 25 | `vout[8].scriptPubKey` | `76a9140b8375854320536a1ba2c041248cb54293f3dd2988ac` | OP_DUP OP_HASH160 0b8375854320536a1ba2c041248cb54293f3dd29 OP_EQUALVERIFY OP_CHECKSIG |
| 4813 | 8 | `vout[9].value` | `8843741d00000000` | 494158728 |
| 4821 | 1 | `vout[9].scriptPubKey_length` | `19` | 25 |
| 4822 | 25 | `vout[9].scriptPubKey` | `76a91475fdbe41ec7b4092dce5eaea2409b1c75a54061188ac` | OP_DUP OP_HASH160 75fdbe41ec7b4092dce5eaea2409b1c75a540611 OP_EQUALVERIFY OP_CHECKSIG |
| 4847 | 4 | `tx.locktime` | `00000000` | 0 |

## 交易 14: `b37774146e93f345ea7532475e1a00209ffd913cabe031231435c4096518acd4`

| 偏移 | 字节数 | 字段 | 原始字节（线缆序） | 解释值 |
|---:|---:|---|---|---|
| 4851 | 4 | `tx.version` | `01000000` | 1 |
| 4855 | 1 | `tx.input_count` | `01` | 1 |
| 4856 | 32 | `vin[0].prev_txid` | `8dbdd46b31da99da11fc073e0d3e20c4bae5f12c78e16c00fe81e69f5a23657f` | 7f65235a9fe681fe006ce1782cf1e5bac4203e0d3e07fc11da99da316bd4bd8d |
| 4888 | 4 | `vin[0].vout` | `00000000` | 0 |
| 4892 | 1 | `vin[0].scriptSig_length` | `6b` | 107 |
| 4893 | 107 | `vin[0].scriptSig` | `483045022100baa0b9639871f2334a2529c24ecbcc9a2c71b1faa3efc8fc1ca3ca0ed19bda8d022079331125ae3f8a95454beda3ed32a5426b5359d24490751d86db8126603bde2d0121038b870bb3832f0bf2f38341ca8878bc9a894c97df81079255d63db29e5df46550` | 3045022100baa0b9639871f2334a2529c24ecbcc9a2c71b1faa3efc8fc1ca3ca0ed19bda8d022079331125ae3f8a95454beda3ed32a5426b5359d24490751d86db8126603bde2d01 038b870bb3832f0bf2f38341ca8878bc9a894c97df81079255d63db29e5df46550 |
| 5000 | 4 | `vin[0].sequence` | `ffffffff` | 4294967295 |
| 5004 | 1 | `tx.output_count` | `02` | 2 |
| 5005 | 8 | `vout[0].value` | `e803000000000000` | 1000 |
| 5013 | 1 | `vout[0].scriptPubKey_length` | `19` | 25 |
| 5014 | 25 | `vout[0].scriptPubKey` | `76a914e78a00b2e2d66e64404f677126b10b57afd8636288ac` | OP_DUP OP_HASH160 e78a00b2e2d66e64404f677126b10b57afd86362 OP_EQUALVERIFY OP_CHECKSIG |
| 5039 | 8 | `vout[1].value` | `943c0f0000000000` | 998548 |
| 5047 | 1 | `vout[1].scriptPubKey_length` | `19` | 25 |
| 5048 | 25 | `vout[1].scriptPubKey` | `76a914731e4ab4c2186bf8d89d75ec7a2ad315feb2301b88ac` | OP_DUP OP_HASH160 731e4ab4c2186bf8d89d75ec7a2ad315feb2301b OP_EQUALVERIFY OP_CHECKSIG |
| 5073 | 4 | `tx.locktime` | `00000000` | 0 |

## 交易 15: `94fca0fd6971efb4de9edc61cc095891d789e797759342205f8341ede9fa93e7`

| 偏移 | 字节数 | 字段 | 原始字节（线缆序） | 解释值 |
|---:|---:|---|---|---|
| 5077 | 4 | `tx.version` | `01000000` | 1 |
| 5081 | 1 | `tx.input_count` | `01` | 1 |
| 5082 | 32 | `vin[0].prev_txid` | `be85322789640b98459cef6b442196a7717355b205cc880fc229755632df2721` | 2127df32567529c20f88cc05b2557371a79621446bef9c45980b6489273285be |
| 5114 | 4 | `vin[0].vout` | `19000000` | 25 |
| 5118 | 1 | `vin[0].scriptSig_length` | `6b` | 107 |
| 5119 | 107 | `vin[0].scriptSig` | `483045022100ddcac63fa99c534cbd28b9cc9e38a34bf8c3acc4fef4c0323d5e24c8b9e40763022079dfc1543c7b78a11364e732e78943f23c00f4739046444686261777fc06e98e01210278d5e9f044f664db82f59ffd3e06ddc29cb28f77f3d899cc6726babb2b92b055` | 3045022100ddcac63fa99c534cbd28b9cc9e38a34bf8c3acc4fef4c0323d5e24c8b9e40763022079dfc1543c7b78a11364e732e78943f23c00f4739046444686261777fc06e98e01 0278d5e9f044f664db82f59ffd3e06ddc29cb28f77f3d899cc6726babb2b92b055 |
| 5226 | 4 | `vin[0].sequence` | `ffffffff` | 4294967295 |
| 5230 | 1 | `tx.output_count` | `1a` | 26 |
| 5231 | 8 | `vout[0].value` | `2202000000000000` | 546 |
| 5239 | 1 | `vout[0].scriptPubKey_length` | `19` | 25 |
| 5240 | 25 | `vout[0].scriptPubKey` | `76a9145349473a38383a494d4a66793871586d3067475188ac` | OP_DUP OP_HASH160 5349473a38383a494d4a66793871586d30674751 OP_EQUALVERIFY OP_CHECKSIG |
| 5265 | 8 | `vout[1].value` | `2202000000000000` | 546 |
| 5273 | 1 | `vout[1].scriptPubKey_length` | `19` | 25 |
| 5274 | 25 | `vout[1].scriptPubKey` | `76a9142b6c6132696c4c7346746d466d6f706e4f56555688ac` | OP_DUP OP_HASH160 2b6c6132696c4c7346746d466d6f706e4f565556 OP_EQUALVERIFY OP_CHECKSIG |
| 5299 | 8 | `vout[2].value` | `2202000000000000` | 546 |
| 5307 | 1 | `vout[2].scriptPubKey_length` | `19` | 25 |
| 5308 | 25 | `vout[2].scriptPubKey` | `76a9147769554a69477634534278457a5547706448544288ac` | OP_DUP OP_HASH160 7769554a69477634534278457a55477064485442 OP_EQUALVERIFY OP_CHECKSIG |
| 5333 | 8 | `vout[3].value` | `2202000000000000` | 546 |
| 5341 | 1 | `vout[3].scriptPubKey_length` | `19` | 25 |
| 5342 | 25 | `vout[3].scriptPubKey` | `76a91448787233526839424a676963717778326b4c4d3088ac` | OP_DUP OP_HASH160 48787233526839424a676963717778326b4c4d30 OP_EQUALVERIFY OP_CHECKSIG |
| 5367 | 8 | `vout[4].value` | `2202000000000000` | 546 |
| 5375 | 1 | `vout[4].scriptPubKey_length` | `19` | 25 |
| 5376 | 25 | `vout[4].scriptPubKey` | `76a91468567876776c7a78704a6b6c34343d3a3334383a88ac` | OP_DUP OP_HASH160 68567876776c7a78704a6b6c34343d3a3334383a OP_EQUALVERIFY OP_CHECKSIG |
| 5401 | 8 | `vout[5].value` | `2202000000000000` | 546 |
| 5409 | 1 | `vout[5].scriptPubKey_length` | `19` | 25 |
| 5410 | 25 | `vout[5].scriptPubKey` | `76a9145b20736b6f6d726120636f6c6c656374696f6e2088ac` | OP_DUP OP_HASH160 5b20736b6f6d726120636f6c6c656374696f6e20 OP_EQUALVERIFY OP_CHECKSIG |
| 5435 | 8 | `vout[6].value` | `2202000000000000` | 546 |
| 5443 | 1 | `vout[6].scriptPubKey_length` | `19` | 25 |
| 5444 | 25 | `vout[6].scriptPubKey` | `76a91461726368697665205d0a0a4172746973743a204188ac` | OP_DUP OP_HASH160 61726368697665205d0a0a4172746973743a2041 OP_EQUALVERIFY OP_CHECKSIG |
| 5469 | 8 | `vout[7].value` | `2202000000000000` | 546 |
| 5477 | 1 | `vout[7].scriptPubKey_length` | `19` | 25 |
| 5478 | 25 | `vout[7].scriptPubKey` | `76a914726c656e204d616c7462790a0a4920616d20686588ac` | OP_DUP OP_HASH160 726c656e204d616c7462790a0a4920616d206865 OP_EQUALVERIFY OP_CHECKSIG |
| 5503 | 8 | `vout[8].value` | `2202000000000000` | 546 |
| 5511 | 1 | `vout[8].scriptPubKey_length` | `19` | 25 |
| 5512 | 25 | `vout[8].scriptPubKey` | `76a9147265206c697374656e696e67207761766573206688ac` | OP_DUP OP_HASH160 7265206c697374656e696e672077617665732066 OP_EQUALVERIFY OP_CHECKSIG |
| 5537 | 8 | `vout[9].value` | `2202000000000000` | 546 |
| 5545 | 1 | `vout[9].scriptPubKey_length` | `19` | 25 |
| 5546 | 25 | `vout[9].scriptPubKey` | `76a914726f6d20657665727920646972656374696f6e0a88ac` | OP_DUP OP_HASH160 726f6d20657665727920646972656374696f6e0a OP_EQUALVERIFY OP_CHECKSIG |
| 5571 | 8 | `vout[10].value` | `2202000000000000` | 546 |
| 5579 | 1 | `vout[10].scriptPubKey_length` | `19` | 25 |
| 5580 | 25 | `vout[10].scriptPubKey` | `76a9140a61726c656e206d616c7462790a0a4d696e746588ac` | OP_DUP OP_HASH160 0a61726c656e206d616c7462790a0a4d696e7465 OP_EQUALVERIFY OP_CHECKSIG |
| 5605 | 8 | `vout[11].value` | `2202000000000000` | 546 |
| 5613 | 1 | `vout[11].scriptPubKey_length` | `19` | 25 |
| 5614 | 25 | `vout[11].scriptPubKey` | `76a9146420646174653a20323032332d30322d3234543188ac` | OP_DUP OP_HASH160 6420646174653a20323032332d30322d32345431 OP_EQUALVERIFY OP_CHECKSIG |
| 5639 | 8 | `vout[12].value` | `2202000000000000` | 546 |
| 5647 | 1 | `vout[12].scriptPubKey_length` | `19` | 25 |
| 5648 | 25 | `vout[12].scriptPubKey` | `76a914333a35363a32392b30303a30300a0a566965772088ac` | OP_DUP OP_HASH160 333a35363a32392b30303a30300a0a5669657720 OP_EQUALVERIFY OP_CHECKSIG |
| 5673 | 8 | `vout[13].value` | `2202000000000000` | 546 |
| 5681 | 1 | `vout[13].scriptPubKey_length` | `19` | 25 |
| 5682 | 25 | `vout[13].scriptPubKey` | `76a9146f6e206f626a6b743a0a3c3c68747470733a2f2f88ac` | OP_DUP OP_HASH160 6f6e206f626a6b743a0a3c3c68747470733a2f2f OP_EQUALVERIFY OP_CHECKSIG |
| 5707 | 8 | `vout[14].value` | `2202000000000000` | 546 |
| 5715 | 1 | `vout[14].scriptPubKey_length` | `19` | 25 |
| 5716 | 25 | `vout[14].scriptPubKey` | `76a9146f626a6b742e636f6d2f746f6b656e732f4b543188ac` | OP_DUP OP_HASH160 6f626a6b742e636f6d2f746f6b656e732f4b5431 OP_EQUALVERIFY OP_CHECKSIG |
| 5741 | 8 | `vout[15].value` | `2202000000000000` | 546 |
| 5749 | 1 | `vout[15].scriptPubKey_length` | `19` | 25 |
| 5750 | 25 | `vout[15].scriptPubKey` | `76a914524a3650626a48707763334d3572773573324e6288ac` | OP_DUP OP_HASH160 524a3650626a48707763334d3572773573324e62 OP_EQUALVERIFY OP_CHECKSIG |
| 5775 | 8 | `vout[16].value` | `2202000000000000` | 546 |
| 5783 | 1 | `vout[16].scriptPubKey_length` | `19` | 25 |
| 5784 | 25 | `vout[16].scriptPubKey` | `76a9146d656677627577626478746f6e2f38313332383188ac` | OP_DUP OP_HASH160 6d656677627577626478746f6e2f383133323831 OP_EQUALVERIFY OP_CHECKSIG |
| 5809 | 8 | `vout[17].value` | `2202000000000000` | 546 |
| 5817 | 1 | `vout[17].scriptPubKey_length` | `19` | 25 |
| 5818 | 25 | `vout[17].scriptPubKey` | `76a9143e3e0a0a23e28e9be28e9d2828e29795e280bfe288ac` | OP_DUP OP_HASH160 3e3e0a0a23e28e9be28e9d2828e29795e280bfe2 OP_EQUALVERIFY OP_CHECKSIG |
| 5843 | 8 | `vout[18].value` | `2202000000000000` | 546 |
| 5851 | 1 | `vout[18].scriptPubKey_length` | `19` | 25 |
| 5852 | 25 | `vout[18].scriptPubKey` | `76a91497952929e28ea0e28e9e3c3c495046533a516d5788ac` | OP_DUP OP_HASH160 97952929e28ea0e28e9e3c3c495046533a516d57 OP_EQUALVERIFY OP_CHECKSIG |
| 5877 | 8 | `vout[19].value` | `2202000000000000` | 546 |
| 5885 | 1 | `vout[19].scriptPubKey_length` | `19` | 25 |
| 5886 | 25 | `vout[19].scriptPubKey` | `76a914554c5a61564b385a5375486f5a417455764e437288ac` | OP_DUP OP_HASH160 554c5a61564b385a5375486f5a417455764e4372 OP_EQUALVERIFY OP_CHECKSIG |
| 5911 | 8 | `vout[20].value` | `2202000000000000` | 546 |
| 5919 | 1 | `vout[20].scriptPubKey_length` | `19` | 25 |
| 5920 | 25 | `vout[20].scriptPubKey` | `76a9144169483279576e694a76416362345273516b707888ac` | OP_DUP OP_HASH160 4169483279576e694a76416362345273516b7078 OP_EQUALVERIFY OP_CHECKSIG |
| 5945 | 8 | `vout[21].value` | `2202000000000000` | 546 |
| 5953 | 1 | `vout[21].scriptPubKey_length` | `19` | 25 |
| 5954 | 25 | `vout[21].scriptPubKey` | `76a9143567632f61727469666163742e706e673e3e3c3c88ac` | OP_DUP OP_HASH160 3567632f61727469666163742e706e673e3e3c3c OP_EQUALVERIFY OP_CHECKSIG |
| 5979 | 8 | `vout[22].value` | `2202000000000000` | 546 |
| 5987 | 1 | `vout[22].scriptPubKey_length` | `19` | 25 |
| 5988 | 25 | `vout[22].scriptPubKey` | `76a9142d32373230373e3e23232323232323232323232388ac` | OP_DUP OP_HASH160 2d32373230373e3e232323232323232323232323 OP_EQUALVERIFY OP_CHECKSIG |
| 6013 | 8 | `vout[23].value` | `2202000000000000` | 546 |
| 6021 | 1 | `vout[23].scriptPubKey_length` | `19` | 25 |
| 6022 | 25 | `vout[23].scriptPubKey` | `76a914e28e9be28e9d2828e29795e280bfe297952929e288ac` | OP_DUP OP_HASH160 e28e9be28e9d2828e29795e280bfe297952929e2 OP_EQUALVERIFY OP_CHECKSIG |
| 6047 | 8 | `vout[24].value` | `2202000000000000` | 546 |
| 6055 | 1 | `vout[24].scriptPubKey_length` | `19` | 25 |
| 6056 | 25 | `vout[24].scriptPubKey` | `76a914765951f67f32b91d8bddc5f073b07722305b6b4d88ac` | OP_DUP OP_HASH160 765951f67f32b91d8bddc5f073b07722305b6b4d OP_EQUALVERIFY OP_CHECKSIG |
| 6081 | 8 | `vout[25].value` | `b6347e3400000000` | 880686262 |
| 6089 | 1 | `vout[25].scriptPubKey_length` | `19` | 25 |
| 6090 | 25 | `vout[25].scriptPubKey` | `76a914c0ce6a08d34f54b136fed2ecbf2bdda418f52d2a88ac` | OP_DUP OP_HASH160 c0ce6a08d34f54b136fed2ecbf2bdda418f52d2a OP_EQUALVERIFY OP_CHECKSIG |
| 6115 | 4 | `tx.locktime` | `00000000` | 0 |

## 交易 16: `dc76b1836d298884223ada26d920395bf52efe0a1bbffb549fb27a77b96ecd03`

| 偏移 | 字节数 | 字段 | 原始字节（线缆序） | 解释值 |
|---:|---:|---|---|---|
| 6119 | 4 | `tx.version` | `01000000` | 1 |
| 6123 | 1 | `tx.marker` | `00` | 0 |
| 6124 | 1 | `tx.flag` | `01` | 1 |
| 6125 | 1 | `tx.input_count` | `01` | 1 |
| 6126 | 32 | `vin[0].prev_txid` | `f31c4b86b15b11d842a2ffca071ab7828d8fecc185b00cd19ed62cc423286be3` | e36b2823c42cd69ed10cb085c1ec8f8d82b71a07caffa242d8115bb1864b1cf3 |
| 6158 | 4 | `vin[0].vout` | `01000000` | 1 |
| 6162 | 1 | `vin[0].scriptSig_length` | `00` | 0 |
| 6163 | 0 | `vin[0].scriptSig` | `（空）` |  |
| 6163 | 4 | `vin[0].sequence` | `ffffffff` | 4294967295 |
| 6167 | 1 | `tx.output_count` | `02` | 2 |
| 6168 | 8 | `vout[0].value` | `e803000000000000` | 1000 |
| 6176 | 1 | `vout[0].scriptPubKey_length` | `16` | 22 |
| 6177 | 22 | `vout[0].scriptPubKey` | `0014b0feeac2312d429d569da17b462144a5b9d0d90c` | OP_0 b0feeac2312d429d569da17b462144a5b9d0d90c |
| 6199 | 8 | `vout[1].value` | `0c7d010000000000` | 97548 |
| 6207 | 1 | `vout[1].scriptPubKey_length` | `16` | 22 |
| 6208 | 22 | `vout[1].scriptPubKey` | `00148aa3a74793710ebf620cb1779ce55bfd38860687` | OP_0 8aa3a74793710ebf620cb1779ce55bfd38860687 |
| 6230 | 1 | `witness[0].item_count` | `02` | 2 |
| 6231 | 1 | `witness[0][0].length` | `47` | 71 |
| 6232 | 71 | `witness[0][0].data` | `304402205d1ab73c24692f66fd34ba92b643e1576f58353a7663f8591447eb106b46371d0220055e012e95ca528eac1a5edc2e63e26a1b8770f9974c217e0d6326c80a91a70801` | 304402205d1ab73c24692f66fd34ba92b643e1576f58353a7663f8591447eb106b46371d0220055e012e95ca528eac1a5edc2e63e26a1b8770f9974c217e0d6326c80a91a70801 |
| 6303 | 1 | `witness[0][1].length` | `21` | 33 |
| 6304 | 33 | `witness[0][1].data` | `02254215e408029a4967347ced81f782a5898a952eb926bb60e1052f5d2a53a824` | 02254215e408029a4967347ced81f782a5898a952eb926bb60e1052f5d2a53a824 |
| 6337 | 4 | `tx.locktime` | `00000000` | 0 |

## 交易 17: `bec157d5c9ba5697177de0e9cc581e35a6d101385c41e74d93b300a210699f08`

| 偏移 | 字节数 | 字段 | 原始字节（线缆序） | 解释值 |
|---:|---:|---|---|---|
| 6341 | 4 | `tx.version` | `01000000` | 1 |
| 6345 | 1 | `tx.marker` | `00` | 0 |
| 6346 | 1 | `tx.flag` | `01` | 1 |
| 6347 | 1 | `tx.input_count` | `01` | 1 |
| 6348 | 32 | `vin[0].prev_txid` | `2532f59a00f0ada2f33e6238b8a561b1e21aeb760a91e1ede6283c00d509544c` | 4c5409d5003c28e6ede1910a76eb1ae2b161a5b838623ef3a2adf0009af53225 |
| 6380 | 4 | `vin[0].vout` | `01000000` | 1 |
| 6384 | 1 | `vin[0].scriptSig_length` | `00` | 0 |
| 6385 | 0 | `vin[0].scriptSig` | `（空）` |  |
| 6385 | 4 | `vin[0].sequence` | `ffffffff` | 4294967295 |
| 6389 | 1 | `tx.output_count` | `02` | 2 |
| 6390 | 8 | `vout[0].value` | `e803000000000000` | 1000 |
| 6398 | 1 | `vout[0].scriptPubKey_length` | `16` | 22 |
| 6399 | 22 | `vout[0].scriptPubKey` | `0014b0feeac2312d429d569da17b462144a5b9d0d90c` | OP_0 b0feeac2312d429d569da17b462144a5b9d0d90c |
| 6421 | 8 | `vout[1].value` | `0c7d010000000000` | 97548 |
| 6429 | 1 | `vout[1].scriptPubKey_length` | `16` | 22 |
| 6430 | 22 | `vout[1].scriptPubKey` | `00148aa3a74793710ebf620cb1779ce55bfd38860687` | OP_0 8aa3a74793710ebf620cb1779ce55bfd38860687 |
| 6452 | 1 | `witness[0].item_count` | `02` | 2 |
| 6453 | 1 | `witness[0][0].length` | `47` | 71 |
| 6454 | 71 | `witness[0][0].data` | `3044022041aa6a7b70126572441ddc83b6cbe41f24a170dfc8fa52e482c363874284eaf40220064a801e85d0083856cfc8015c55d21bbb76ddca57d40a338107d1ad418e9d8d01` | 3044022041aa6a7b70126572441ddc83b6cbe41f24a170dfc8fa52e482c363874284eaf40220064a801e85d0083856cfc8015c55d21bbb76ddca57d40a338107d1ad418e9d8d01 |
| 6525 | 1 | `witness[0][1].length` | `21` | 33 |
| 6526 | 33 | `witness[0][1].data` | `02254215e408029a4967347ced81f782a5898a952eb926bb60e1052f5d2a53a824` | 02254215e408029a4967347ced81f782a5898a952eb926bb60e1052f5d2a53a824 |
| 6559 | 4 | `tx.locktime` | `00000000` | 0 |

## 交易 18: `7ce80550ba76d1bc2e5ada57e241d45eef3e05949fc567437cf456411eff2d09`

| 偏移 | 字节数 | 字段 | 原始字节（线缆序） | 解释值 |
|---:|---:|---|---|---|
| 6563 | 4 | `tx.version` | `01000000` | 1 |
| 6567 | 1 | `tx.marker` | `00` | 0 |
| 6568 | 1 | `tx.flag` | `01` | 1 |
| 6569 | 1 | `tx.input_count` | `01` | 1 |
| 6570 | 32 | `vin[0].prev_txid` | `71242ce83c3f1dbf2ae6524da3cb8b0e4f664180a0e85de0d1dd03937804c3c1` | c1c304789303ddd1e05de8a08041664f0e8bcba34d52e62abf1d3f3ce82c2471 |
| 6602 | 4 | `vin[0].vout` | `01000000` | 1 |
| 6606 | 1 | `vin[0].scriptSig_length` | `00` | 0 |
| 6607 | 0 | `vin[0].scriptSig` | `（空）` |  |
| 6607 | 4 | `vin[0].sequence` | `ffffffff` | 4294967295 |
| 6611 | 1 | `tx.output_count` | `02` | 2 |
| 6612 | 8 | `vout[0].value` | `e803000000000000` | 1000 |
| 6620 | 1 | `vout[0].scriptPubKey_length` | `16` | 22 |
| 6621 | 22 | `vout[0].scriptPubKey` | `0014b0feeac2312d429d569da17b462144a5b9d0d90c` | OP_0 b0feeac2312d429d569da17b462144a5b9d0d90c |
| 6643 | 8 | `vout[1].value` | `0c7d010000000000` | 97548 |
| 6651 | 1 | `vout[1].scriptPubKey_length` | `16` | 22 |
| 6652 | 22 | `vout[1].scriptPubKey` | `00148aa3a74793710ebf620cb1779ce55bfd38860687` | OP_0 8aa3a74793710ebf620cb1779ce55bfd38860687 |
| 6674 | 1 | `witness[0].item_count` | `02` | 2 |
| 6675 | 1 | `witness[0][0].length` | `47` | 71 |
| 6676 | 71 | `witness[0][0].data` | `3044022045d9db3c90a77e4d28a8e0f4ea26a82ce03e1cfb6cd1337e27b4c9475ac92e73022054d65a8a1f3344906c771c66f397de953bc9550f6dffbac6ebeb573c763ddb1d01` | 3044022045d9db3c90a77e4d28a8e0f4ea26a82ce03e1cfb6cd1337e27b4c9475ac92e73022054d65a8a1f3344906c771c66f397de953bc9550f6dffbac6ebeb573c763ddb1d01 |
| 6747 | 1 | `witness[0][1].length` | `21` | 33 |
| 6748 | 33 | `witness[0][1].data` | `02254215e408029a4967347ced81f782a5898a952eb926bb60e1052f5d2a53a824` | 02254215e408029a4967347ced81f782a5898a952eb926bb60e1052f5d2a53a824 |
| 6781 | 4 | `tx.locktime` | `00000000` | 0 |

## 交易 19: `d9b030510f184db77f41e430abe1001c417da9087ec549cf2d4e119d32ac3d0c`

| 偏移 | 字节数 | 字段 | 原始字节（线缆序） | 解释值 |
|---:|---:|---|---|---|
| 6785 | 4 | `tx.version` | `01000000` | 1 |
| 6789 | 1 | `tx.marker` | `00` | 0 |
| 6790 | 1 | `tx.flag` | `01` | 1 |
| 6791 | 1 | `tx.input_count` | `01` | 1 |
| 6792 | 32 | `vin[0].prev_txid` | `509dcfa42f61b0f62286266150678ccf87400ee4b44ab072a9f976ef55bbb7fb` | fbb7bb55ef76f9a972b04ab4e40e4087cf8c675061268622f6b0612fa4cf9d50 |
| 6824 | 4 | `vin[0].vout` | `01000000` | 1 |
| 6828 | 1 | `vin[0].scriptSig_length` | `00` | 0 |
| 6829 | 0 | `vin[0].scriptSig` | `（空）` |  |
| 6829 | 4 | `vin[0].sequence` | `ffffffff` | 4294967295 |
| 6833 | 1 | `tx.output_count` | `02` | 2 |
| 6834 | 8 | `vout[0].value` | `e803000000000000` | 1000 |
| 6842 | 1 | `vout[0].scriptPubKey_length` | `16` | 22 |
| 6843 | 22 | `vout[0].scriptPubKey` | `0014b0feeac2312d429d569da17b462144a5b9d0d90c` | OP_0 b0feeac2312d429d569da17b462144a5b9d0d90c |
| 6865 | 8 | `vout[1].value` | `0c7d010000000000` | 97548 |
| 6873 | 1 | `vout[1].scriptPubKey_length` | `16` | 22 |
| 6874 | 22 | `vout[1].scriptPubKey` | `00148aa3a74793710ebf620cb1779ce55bfd38860687` | OP_0 8aa3a74793710ebf620cb1779ce55bfd38860687 |
| 6896 | 1 | `witness[0].item_count` | `02` | 2 |
| 6897 | 1 | `witness[0][0].length` | `47` | 71 |
| 6898 | 71 | `witness[0][0].data` | `3044022006d1033e8245cf365a997b6636bb467bfa931019ea44e2c0acaf7e434350f84a02207d32182d457768c767243bc005df3bee663cb0b148d4781dd0e1c03552112f4501` | 3044022006d1033e8245cf365a997b6636bb467bfa931019ea44e2c0acaf7e434350f84a02207d32182d457768c767243bc005df3bee663cb0b148d4781dd0e1c03552112f4501 |
| 6969 | 1 | `witness[0][1].length` | `21` | 33 |
| 6970 | 33 | `witness[0][1].data` | `02254215e408029a4967347ced81f782a5898a952eb926bb60e1052f5d2a53a824` | 02254215e408029a4967347ced81f782a5898a952eb926bb60e1052f5d2a53a824 |
| 7003 | 4 | `tx.locktime` | `00000000` | 0 |

## 交易 20: `8fdd256636dad9f527f040299dbe028e3c216ca2ec8bd4272af14e79cd1e3c13`

| 偏移 | 字节数 | 字段 | 原始字节（线缆序） | 解释值 |
|---:|---:|---|---|---|
| 7007 | 4 | `tx.version` | `01000000` | 1 |
| 7011 | 1 | `tx.marker` | `00` | 0 |
| 7012 | 1 | `tx.flag` | `01` | 1 |
| 7013 | 1 | `tx.input_count` | `01` | 1 |
| 7014 | 32 | `vin[0].prev_txid` | `a4e0d08303c6af532cec0058da7924a2e12d6f58696f15c47c76369aaf86ecc3` | c3ec86af9a36767cc4156f69586f2de1a22479da5800ec2c53afc60383d0e0a4 |
| 7046 | 4 | `vin[0].vout` | `01000000` | 1 |
| 7050 | 1 | `vin[0].scriptSig_length` | `00` | 0 |
| 7051 | 0 | `vin[0].scriptSig` | `（空）` |  |
| 7051 | 4 | `vin[0].sequence` | `ffffffff` | 4294967295 |
| 7055 | 1 | `tx.output_count` | `02` | 2 |
| 7056 | 8 | `vout[0].value` | `e803000000000000` | 1000 |
| 7064 | 1 | `vout[0].scriptPubKey_length` | `16` | 22 |
| 7065 | 22 | `vout[0].scriptPubKey` | `0014b0feeac2312d429d569da17b462144a5b9d0d90c` | OP_0 b0feeac2312d429d569da17b462144a5b9d0d90c |
| 7087 | 8 | `vout[1].value` | `0c7d010000000000` | 97548 |
| 7095 | 1 | `vout[1].scriptPubKey_length` | `16` | 22 |
| 7096 | 22 | `vout[1].scriptPubKey` | `00148aa3a74793710ebf620cb1779ce55bfd38860687` | OP_0 8aa3a74793710ebf620cb1779ce55bfd38860687 |
| 7118 | 1 | `witness[0].item_count` | `02` | 2 |
| 7119 | 1 | `witness[0][0].length` | `47` | 71 |
| 7120 | 71 | `witness[0][0].data` | `304402202ca5bab236b4a5c6737a063e9b9c304df83a6f3ea2d546ef493ad30d65f2d5620220212a62cb550ea607392426eb1e6e3d7360394e07cd8d2b7d19c1b6b128c5f30301` | 304402202ca5bab236b4a5c6737a063e9b9c304df83a6f3ea2d546ef493ad30d65f2d5620220212a62cb550ea607392426eb1e6e3d7360394e07cd8d2b7d19c1b6b128c5f30301 |
| 7191 | 1 | `witness[0][1].length` | `21` | 33 |
| 7192 | 33 | `witness[0][1].data` | `02254215e408029a4967347ced81f782a5898a952eb926bb60e1052f5d2a53a824` | 02254215e408029a4967347ced81f782a5898a952eb926bb60e1052f5d2a53a824 |
| 7225 | 4 | `tx.locktime` | `00000000` | 0 |

## 交易 21: `78f2106c311e233291059876e27f0e4d5540312e3c16af7bb423b76bb22e771a`

| 偏移 | 字节数 | 字段 | 原始字节（线缆序） | 解释值 |
|---:|---:|---|---|---|
| 7229 | 4 | `tx.version` | `01000000` | 1 |
| 7233 | 1 | `tx.marker` | `00` | 0 |
| 7234 | 1 | `tx.flag` | `01` | 1 |
| 7235 | 1 | `tx.input_count` | `01` | 1 |
| 7236 | 32 | `vin[0].prev_txid` | `c93484ac7ae8825759067390301a585845cb7ea69350874b9fa7fde5e08e02c3` | c3028ee0e5fda79f4b875093a67ecb4558581a30907306595782e87aac8434c9 |
| 7268 | 4 | `vin[0].vout` | `01000000` | 1 |
| 7272 | 1 | `vin[0].scriptSig_length` | `00` | 0 |
| 7273 | 0 | `vin[0].scriptSig` | `（空）` |  |
| 7273 | 4 | `vin[0].sequence` | `ffffffff` | 4294967295 |
| 7277 | 1 | `tx.output_count` | `02` | 2 |
| 7278 | 8 | `vout[0].value` | `e803000000000000` | 1000 |
| 7286 | 1 | `vout[0].scriptPubKey_length` | `16` | 22 |
| 7287 | 22 | `vout[0].scriptPubKey` | `0014b0feeac2312d429d569da17b462144a5b9d0d90c` | OP_0 b0feeac2312d429d569da17b462144a5b9d0d90c |
| 7309 | 8 | `vout[1].value` | `0c7d010000000000` | 97548 |
| 7317 | 1 | `vout[1].scriptPubKey_length` | `16` | 22 |
| 7318 | 22 | `vout[1].scriptPubKey` | `00148aa3a74793710ebf620cb1779ce55bfd38860687` | OP_0 8aa3a74793710ebf620cb1779ce55bfd38860687 |
| 7340 | 1 | `witness[0].item_count` | `02` | 2 |
| 7341 | 1 | `witness[0][0].length` | `47` | 71 |
| 7342 | 71 | `witness[0][0].data` | `3044022067c8d871aafdd274d6c66b95037ed19d563c91e1d99e8d0645e41dccc3fc5bd6022031f8602cb76c10be0625761a1a2990fd46d20d66a744214da77541dffbf60ae601` | 3044022067c8d871aafdd274d6c66b95037ed19d563c91e1d99e8d0645e41dccc3fc5bd6022031f8602cb76c10be0625761a1a2990fd46d20d66a744214da77541dffbf60ae601 |
| 7413 | 1 | `witness[0][1].length` | `21` | 33 |
| 7414 | 33 | `witness[0][1].data` | `02254215e408029a4967347ced81f782a5898a952eb926bb60e1052f5d2a53a824` | 02254215e408029a4967347ced81f782a5898a952eb926bb60e1052f5d2a53a824 |
| 7447 | 4 | `tx.locktime` | `00000000` | 0 |

## 交易 22: `c7d1da9d303152e700742352298428ab5bb2ec92a0c1dfcc9bfa58036da9ad1a`

| 偏移 | 字节数 | 字段 | 原始字节（线缆序） | 解释值 |
|---:|---:|---|---|---|
| 7451 | 4 | `tx.version` | `01000000` | 1 |
| 7455 | 1 | `tx.marker` | `00` | 0 |
| 7456 | 1 | `tx.flag` | `01` | 1 |
| 7457 | 1 | `tx.input_count` | `01` | 1 |
| 7458 | 32 | `vin[0].prev_txid` | `6242eb549843d737e67271b22753df739f766794b8c840420789925f2cfd60f1` | f160fd2c5f9289074240c8b89467769f73df5327b27172e637d7439854eb4262 |
| 7490 | 4 | `vin[0].vout` | `01000000` | 1 |
| 7494 | 1 | `vin[0].scriptSig_length` | `00` | 0 |
| 7495 | 0 | `vin[0].scriptSig` | `（空）` |  |
| 7495 | 4 | `vin[0].sequence` | `ffffffff` | 4294967295 |
| 7499 | 1 | `tx.output_count` | `02` | 2 |
| 7500 | 8 | `vout[0].value` | `e803000000000000` | 1000 |
| 7508 | 1 | `vout[0].scriptPubKey_length` | `16` | 22 |
| 7509 | 22 | `vout[0].scriptPubKey` | `0014b0feeac2312d429d569da17b462144a5b9d0d90c` | OP_0 b0feeac2312d429d569da17b462144a5b9d0d90c |
| 7531 | 8 | `vout[1].value` | `0c7d010000000000` | 97548 |
| 7539 | 1 | `vout[1].scriptPubKey_length` | `16` | 22 |
| 7540 | 22 | `vout[1].scriptPubKey` | `00148aa3a74793710ebf620cb1779ce55bfd38860687` | OP_0 8aa3a74793710ebf620cb1779ce55bfd38860687 |
| 7562 | 1 | `witness[0].item_count` | `02` | 2 |
| 7563 | 1 | `witness[0][0].length` | `48` | 72 |
| 7564 | 72 | `witness[0][0].data` | `30450221009acea539ee721032878cc016912e05db68560d41df619b7c281d9e084ab708e5022027486062c6cdab123a6412f6a7a7241913c5ce246f9d03f59489895e50902ec901` | 30450221009acea539ee721032878cc016912e05db68560d41df619b7c281d9e084ab708e5022027486062c6cdab123a6412f6a7a7241913c5ce246f9d03f59489895e50902ec901 |
| 7636 | 1 | `witness[0][1].length` | `21` | 33 |
| 7637 | 33 | `witness[0][1].data` | `02254215e408029a4967347ced81f782a5898a952eb926bb60e1052f5d2a53a824` | 02254215e408029a4967347ced81f782a5898a952eb926bb60e1052f5d2a53a824 |
| 7670 | 4 | `tx.locktime` | `00000000` | 0 |

## 交易 23: `dd648ea05aab131aa08ccfcef9aca363f3dedb1e8324ce20d593904f42f3251f`

| 偏移 | 字节数 | 字段 | 原始字节（线缆序） | 解释值 |
|---:|---:|---|---|---|
| 7674 | 4 | `tx.version` | `01000000` | 1 |
| 7678 | 1 | `tx.marker` | `00` | 0 |
| 7679 | 1 | `tx.flag` | `01` | 1 |
| 7680 | 1 | `tx.input_count` | `01` | 1 |
| 7681 | 32 | `vin[0].prev_txid` | `dce5d34c0719d699ec55afcf9f31e0e8191f6e31f8b1039ca1068305fa5e69bd` | bd695efa058306a19c03b1f8316e1f19e8e0319fcfaf55ec99d619074cd3e5dc |
| 7713 | 4 | `vin[0].vout` | `01000000` | 1 |
| 7717 | 1 | `vin[0].scriptSig_length` | `00` | 0 |
| 7718 | 0 | `vin[0].scriptSig` | `（空）` |  |
| 7718 | 4 | `vin[0].sequence` | `ffffffff` | 4294967295 |
| 7722 | 1 | `tx.output_count` | `02` | 2 |
| 7723 | 8 | `vout[0].value` | `e803000000000000` | 1000 |
| 7731 | 1 | `vout[0].scriptPubKey_length` | `16` | 22 |
| 7732 | 22 | `vout[0].scriptPubKey` | `0014b0feeac2312d429d569da17b462144a5b9d0d90c` | OP_0 b0feeac2312d429d569da17b462144a5b9d0d90c |
| 7754 | 8 | `vout[1].value` | `889a010000000000` | 105096 |
| 7762 | 1 | `vout[1].scriptPubKey_length` | `16` | 22 |
| 7763 | 22 | `vout[1].scriptPubKey` | `00148aa3a74793710ebf620cb1779ce55bfd38860687` | OP_0 8aa3a74793710ebf620cb1779ce55bfd38860687 |
| 7785 | 1 | `witness[0].item_count` | `02` | 2 |
| 7786 | 1 | `witness[0][0].length` | `47` | 71 |
| 7787 | 71 | `witness[0][0].data` | `304402201bf3f1b3a090e8453acc039d75ecffd1f05881e853685507b8e2e21c27b3153b02205e57a31b86e67618d794caaec9922758863c928f9f0f1999f668b4e1f655550b01` | 304402201bf3f1b3a090e8453acc039d75ecffd1f05881e853685507b8e2e21c27b3153b02205e57a31b86e67618d794caaec9922758863c928f9f0f1999f668b4e1f655550b01 |
| 7858 | 1 | `witness[0][1].length` | `21` | 33 |
| 7859 | 33 | `witness[0][1].data` | `02254215e408029a4967347ced81f782a5898a952eb926bb60e1052f5d2a53a824` | 02254215e408029a4967347ced81f782a5898a952eb926bb60e1052f5d2a53a824 |
| 7892 | 4 | `tx.locktime` | `00000000` | 0 |

## 交易 24: `cfee3e0c956def63af21106f68e7a17a5f55fa83e7fc28ba72a7cda73355e71f`

| 偏移 | 字节数 | 字段 | 原始字节（线缆序） | 解释值 |
|---:|---:|---|---|---|
| 7896 | 4 | `tx.version` | `01000000` | 1 |
| 7900 | 1 | `tx.marker` | `00` | 0 |
| 7901 | 1 | `tx.flag` | `01` | 1 |
| 7902 | 1 | `tx.input_count` | `01` | 1 |
| 7903 | 32 | `vin[0].prev_txid` | `c530ea60f357b968c0580b3e8172242ec5a9eb2dc76ec8d286ae80fc69772b11` | 112b7769fc80ae86d2c86ec72deba9c52e2472813e0b58c068b957f360ea30c5 |
| 7935 | 4 | `vin[0].vout` | `01000000` | 1 |
| 7939 | 1 | `vin[0].scriptSig_length` | `00` | 0 |
| 7940 | 0 | `vin[0].scriptSig` | `（空）` |  |
| 7940 | 4 | `vin[0].sequence` | `ffffffff` | 4294967295 |
| 7944 | 1 | `tx.output_count` | `02` | 2 |
| 7945 | 8 | `vout[0].value` | `e803000000000000` | 1000 |
| 7953 | 1 | `vout[0].scriptPubKey_length` | `16` | 22 |
| 7954 | 22 | `vout[0].scriptPubKey` | `0014b0feeac2312d429d569da17b462144a5b9d0d90c` | OP_0 b0feeac2312d429d569da17b462144a5b9d0d90c |
| 7976 | 8 | `vout[1].value` | `0c7d010000000000` | 97548 |
| 7984 | 1 | `vout[1].scriptPubKey_length` | `16` | 22 |
| 7985 | 22 | `vout[1].scriptPubKey` | `00148aa3a74793710ebf620cb1779ce55bfd38860687` | OP_0 8aa3a74793710ebf620cb1779ce55bfd38860687 |
| 8007 | 1 | `witness[0].item_count` | `02` | 2 |
| 8008 | 1 | `witness[0][0].length` | `48` | 72 |
| 8009 | 72 | `witness[0][0].data` | `3045022100a13860a635a5d041c655735954698eec8bfbc82be52f29669f84190d938a04130220345e1d14b3e5b9a05d232fc847ff30a0f4ac74f45cd3ea6abda33cb3260bb66801` | 3045022100a13860a635a5d041c655735954698eec8bfbc82be52f29669f84190d938a04130220345e1d14b3e5b9a05d232fc847ff30a0f4ac74f45cd3ea6abda33cb3260bb66801 |
| 8081 | 1 | `witness[0][1].length` | `21` | 33 |
| 8082 | 33 | `witness[0][1].data` | `02254215e408029a4967347ced81f782a5898a952eb926bb60e1052f5d2a53a824` | 02254215e408029a4967347ced81f782a5898a952eb926bb60e1052f5d2a53a824 |
| 8115 | 4 | `tx.locktime` | `00000000` | 0 |

## 交易 25: `03619f9904ef2bf458fc1046cca6e7455875ab24ad081d7fa1b600acfdbc7231`

| 偏移 | 字节数 | 字段 | 原始字节（线缆序） | 解释值 |
|---:|---:|---|---|---|
| 8119 | 4 | `tx.version` | `01000000` | 1 |
| 8123 | 1 | `tx.marker` | `00` | 0 |
| 8124 | 1 | `tx.flag` | `01` | 1 |
| 8125 | 1 | `tx.input_count` | `01` | 1 |
| 8126 | 32 | `vin[0].prev_txid` | `f038cabdf2ffa067b9ea2d63633b21dd0d374202626f6d96b14c8e42a0122273` | 732212a0428e4cb1966d6f620242370ddd213b63632deab967a0fff2bdca38f0 |
| 8158 | 4 | `vin[0].vout` | `01000000` | 1 |
| 8162 | 1 | `vin[0].scriptSig_length` | `00` | 0 |
| 8163 | 0 | `vin[0].scriptSig` | `（空）` |  |
| 8163 | 4 | `vin[0].sequence` | `ffffffff` | 4294967295 |
| 8167 | 1 | `tx.output_count` | `02` | 2 |
| 8168 | 8 | `vout[0].value` | `e803000000000000` | 1000 |
| 8176 | 1 | `vout[0].scriptPubKey_length` | `16` | 22 |
| 8177 | 22 | `vout[0].scriptPubKey` | `0014b0feeac2312d429d569da17b462144a5b9d0d90c` | OP_0 b0feeac2312d429d569da17b462144a5b9d0d90c |
| 8199 | 8 | `vout[1].value` | `2821030000000000` | 205096 |
| 8207 | 1 | `vout[1].scriptPubKey_length` | `16` | 22 |
| 8208 | 22 | `vout[1].scriptPubKey` | `00148aa3a74793710ebf620cb1779ce55bfd38860687` | OP_0 8aa3a74793710ebf620cb1779ce55bfd38860687 |
| 8230 | 1 | `witness[0].item_count` | `02` | 2 |
| 8231 | 1 | `witness[0][0].length` | `47` | 71 |
| 8232 | 71 | `witness[0][0].data` | `304402200ed1c95fe54d11e9ba978c2ac3d20d2a14f964c48874c7a9f46e7ba303087707022054ac27634d43334d3292954e3436e1f78efe5fd3029e726c4f9f908e8e8fec9501` | 304402200ed1c95fe54d11e9ba978c2ac3d20d2a14f964c48874c7a9f46e7ba303087707022054ac27634d43334d3292954e3436e1f78efe5fd3029e726c4f9f908e8e8fec9501 |
| 8303 | 1 | `witness[0][1].length` | `21` | 33 |
| 8304 | 33 | `witness[0][1].data` | `02254215e408029a4967347ced81f782a5898a952eb926bb60e1052f5d2a53a824` | 02254215e408029a4967347ced81f782a5898a952eb926bb60e1052f5d2a53a824 |
| 8337 | 4 | `tx.locktime` | `00000000` | 0 |

## 交易 26: `318d41165435ba618b1967b308bca2babfb64120be2ab704551b5d022483d740`

| 偏移 | 字节数 | 字段 | 原始字节（线缆序） | 解释值 |
|---:|---:|---|---|---|
| 8341 | 4 | `tx.version` | `01000000` | 1 |
| 8345 | 1 | `tx.marker` | `00` | 0 |
| 8346 | 1 | `tx.flag` | `01` | 1 |
| 8347 | 1 | `tx.input_count` | `01` | 1 |
| 8348 | 32 | `vin[0].prev_txid` | `8877d182a27f8fee693dec9c6a48efba6af276d7fcc10a374fe4c58f5096f20e` | 0ef296508fc5e44f370ac1fcd776f26abaef486a9cec3d69ee8f7fa282d17788 |
| 8380 | 4 | `vin[0].vout` | `01000000` | 1 |
| 8384 | 1 | `vin[0].scriptSig_length` | `00` | 0 |
| 8385 | 0 | `vin[0].scriptSig` | `（空）` |  |
| 8385 | 4 | `vin[0].sequence` | `ffffffff` | 4294967295 |
| 8389 | 1 | `tx.output_count` | `02` | 2 |
| 8390 | 8 | `vout[0].value` | `e803000000000000` | 1000 |
| 8398 | 1 | `vout[0].scriptPubKey_length` | `16` | 22 |
| 8399 | 22 | `vout[0].scriptPubKey` | `0014b0feeac2312d429d569da17b462144a5b9d0d90c` | OP_0 b0feeac2312d429d569da17b462144a5b9d0d90c |
| 8421 | 8 | `vout[1].value` | `0c7d010000000000` | 97548 |
| 8429 | 1 | `vout[1].scriptPubKey_length` | `16` | 22 |
| 8430 | 22 | `vout[1].scriptPubKey` | `00148aa3a74793710ebf620cb1779ce55bfd38860687` | OP_0 8aa3a74793710ebf620cb1779ce55bfd38860687 |
| 8452 | 1 | `witness[0].item_count` | `02` | 2 |
| 8453 | 1 | `witness[0][0].length` | `48` | 72 |
| 8454 | 72 | `witness[0][0].data` | `30450221008d12587966b2436d4c9b201e331bc4ba5ddbc921e32218ad5864ec9577e06469022028fb63e4e3afea9c8d083c0273e3cd37b6ed0abf534701ba9553457b27d0ec6a01` | 30450221008d12587966b2436d4c9b201e331bc4ba5ddbc921e32218ad5864ec9577e06469022028fb63e4e3afea9c8d083c0273e3cd37b6ed0abf534701ba9553457b27d0ec6a01 |
| 8526 | 1 | `witness[0][1].length` | `21` | 33 |
| 8527 | 33 | `witness[0][1].data` | `02254215e408029a4967347ced81f782a5898a952eb926bb60e1052f5d2a53a824` | 02254215e408029a4967347ced81f782a5898a952eb926bb60e1052f5d2a53a824 |
| 8560 | 4 | `tx.locktime` | `00000000` | 0 |

## 交易 27: `eee4945127e2f9d3940017e0f2341f6aa3aec67fe141a40845d6c8309bf87b4a`

| 偏移 | 字节数 | 字段 | 原始字节（线缆序） | 解释值 |
|---:|---:|---|---|---|
| 8564 | 4 | `tx.version` | `01000000` | 1 |
| 8568 | 1 | `tx.marker` | `00` | 0 |
| 8569 | 1 | `tx.flag` | `01` | 1 |
| 8570 | 1 | `tx.input_count` | `01` | 1 |
| 8571 | 32 | `vin[0].prev_txid` | `d4c0d38f08b304ae384e3ad429bdfe1dc33240688e055ff151bfb5ce080e55e3` | e3550e08ceb5bf51f15f058e684032c31dfebd29d43a4e38ae04b3088fd3c0d4 |
| 8603 | 4 | `vin[0].vout` | `01000000` | 1 |
| 8607 | 1 | `vin[0].scriptSig_length` | `00` | 0 |
| 8608 | 0 | `vin[0].scriptSig` | `（空）` |  |
| 8608 | 4 | `vin[0].sequence` | `ffffffff` | 4294967295 |
| 8612 | 1 | `tx.output_count` | `02` | 2 |
| 8613 | 8 | `vout[0].value` | `e803000000000000` | 1000 |
| 8621 | 1 | `vout[0].scriptPubKey_length` | `16` | 22 |
| 8622 | 22 | `vout[0].scriptPubKey` | `0014b0feeac2312d429d569da17b462144a5b9d0d90c` | OP_0 b0feeac2312d429d569da17b462144a5b9d0d90c |
| 8644 | 8 | `vout[1].value` | `0c7d010000000000` | 97548 |
| 8652 | 1 | `vout[1].scriptPubKey_length` | `16` | 22 |
| 8653 | 22 | `vout[1].scriptPubKey` | `00148aa3a74793710ebf620cb1779ce55bfd38860687` | OP_0 8aa3a74793710ebf620cb1779ce55bfd38860687 |
| 8675 | 1 | `witness[0].item_count` | `02` | 2 |
| 8676 | 1 | `witness[0][0].length` | `48` | 72 |
| 8677 | 72 | `witness[0][0].data` | `30450221008f0ae0b4511c733af0549e980cb7cad1dfa8f434d8060851f5d814bd0dab188d0220682a8902c61e080be9ba22dd83193ba388cd013a321e6498264e2930a8f9bcfc01` | 30450221008f0ae0b4511c733af0549e980cb7cad1dfa8f434d8060851f5d814bd0dab188d0220682a8902c61e080be9ba22dd83193ba388cd013a321e6498264e2930a8f9bcfc01 |
| 8749 | 1 | `witness[0][1].length` | `21` | 33 |
| 8750 | 33 | `witness[0][1].data` | `02254215e408029a4967347ced81f782a5898a952eb926bb60e1052f5d2a53a824` | 02254215e408029a4967347ced81f782a5898a952eb926bb60e1052f5d2a53a824 |
| 8783 | 4 | `tx.locktime` | `00000000` | 0 |

## 交易 28: `5bbf605812fc7ce96ae6de8222e2edecefb5f7e490d36c7e40917d6bbab6194d`

| 偏移 | 字节数 | 字段 | 原始字节（线缆序） | 解释值 |
|---:|---:|---|---|---|
| 8787 | 4 | `tx.version` | `01000000` | 1 |
| 8791 | 1 | `tx.marker` | `00` | 0 |
| 8792 | 1 | `tx.flag` | `01` | 1 |
| 8793 | 1 | `tx.input_count` | `01` | 1 |
| 8794 | 32 | `vin[0].prev_txid` | `53c1ef37e9dc667ad9ff857a9639a298ef9a1072368f1fd7f230fee700189594` | 94951800e7fe30f2d71f8f3672109aef98a239967a85ffd97a66dce937efc153 |
| 8826 | 4 | `vin[0].vout` | `01000000` | 1 |
| 8830 | 1 | `vin[0].scriptSig_length` | `00` | 0 |
| 8831 | 0 | `vin[0].scriptSig` | `（空）` |  |
| 8831 | 4 | `vin[0].sequence` | `ffffffff` | 4294967295 |
| 8835 | 1 | `tx.output_count` | `02` | 2 |
| 8836 | 8 | `vout[0].value` | `e803000000000000` | 1000 |
| 8844 | 1 | `vout[0].scriptPubKey_length` | `16` | 22 |
| 8845 | 22 | `vout[0].scriptPubKey` | `0014b0feeac2312d429d569da17b462144a5b9d0d90c` | OP_0 b0feeac2312d429d569da17b462144a5b9d0d90c |
| 8867 | 8 | `vout[1].value` | `0c7d010000000000` | 97548 |
| 8875 | 1 | `vout[1].scriptPubKey_length` | `16` | 22 |
| 8876 | 22 | `vout[1].scriptPubKey` | `00148aa3a74793710ebf620cb1779ce55bfd38860687` | OP_0 8aa3a74793710ebf620cb1779ce55bfd38860687 |
| 8898 | 1 | `witness[0].item_count` | `02` | 2 |
| 8899 | 1 | `witness[0][0].length` | `48` | 72 |
| 8900 | 72 | `witness[0][0].data` | `3045022100f39d0a67bea2d1907d36c6abf4d09636f8f7b918c41baa62b7b44b17c2022f58022033df68fbbefb42f7b9ecdca31b3e573a4afd2b27cbc5e8f8cc9012e79ed87eb801` | 3045022100f39d0a67bea2d1907d36c6abf4d09636f8f7b918c41baa62b7b44b17c2022f58022033df68fbbefb42f7b9ecdca31b3e573a4afd2b27cbc5e8f8cc9012e79ed87eb801 |
| 8972 | 1 | `witness[0][1].length` | `21` | 33 |
| 8973 | 33 | `witness[0][1].data` | `02254215e408029a4967347ced81f782a5898a952eb926bb60e1052f5d2a53a824` | 02254215e408029a4967347ced81f782a5898a952eb926bb60e1052f5d2a53a824 |
| 9006 | 4 | `tx.locktime` | `00000000` | 0 |

## 交易 29: `c288e0f96ca5e6aa87ecb6ad2ff94fdeccf11b5697a33238ba4d034ca08d4b4f`

| 偏移 | 字节数 | 字段 | 原始字节（线缆序） | 解释值 |
|---:|---:|---|---|---|
| 9010 | 4 | `tx.version` | `01000000` | 1 |
| 9014 | 1 | `tx.marker` | `00` | 0 |
| 9015 | 1 | `tx.flag` | `01` | 1 |
| 9016 | 1 | `tx.input_count` | `01` | 1 |
| 9017 | 32 | `vin[0].prev_txid` | `03c1c96876809eb2291f7f37b584a5639536b85d7502e5d85d02b79f9d7c6b12` | 126b7c9d9fb7025dd8e502755db8369563a584b5377f1f29b29e807668c9c103 |
| 9049 | 4 | `vin[0].vout` | `01000000` | 1 |
| 9053 | 1 | `vin[0].scriptSig_length` | `00` | 0 |
| 9054 | 0 | `vin[0].scriptSig` | `（空）` |  |
| 9054 | 4 | `vin[0].sequence` | `ffffffff` | 4294967295 |
| 9058 | 1 | `tx.output_count` | `02` | 2 |
| 9059 | 8 | `vout[0].value` | `e803000000000000` | 1000 |
| 9067 | 1 | `vout[0].scriptPubKey_length` | `16` | 22 |
| 9068 | 22 | `vout[0].scriptPubKey` | `0014b0feeac2312d429d569da17b462144a5b9d0d90c` | OP_0 b0feeac2312d429d569da17b462144a5b9d0d90c |
| 9090 | 8 | `vout[1].value` | `0c7d010000000000` | 97548 |
| 9098 | 1 | `vout[1].scriptPubKey_length` | `16` | 22 |
| 9099 | 22 | `vout[1].scriptPubKey` | `00148aa3a74793710ebf620cb1779ce55bfd38860687` | OP_0 8aa3a74793710ebf620cb1779ce55bfd38860687 |
| 9121 | 1 | `witness[0].item_count` | `02` | 2 |
| 9122 | 1 | `witness[0][0].length` | `47` | 71 |
| 9123 | 71 | `witness[0][0].data` | `304402203fb19ce6262e9da1a90a6e45244a43693165e8d13894e9aed14f47be2101243702206cdfeab4e98b67082bc5b4a2f402b7b461bb2189d4535dbf6a8b8c44cea2c80201` | 304402203fb19ce6262e9da1a90a6e45244a43693165e8d13894e9aed14f47be2101243702206cdfeab4e98b67082bc5b4a2f402b7b461bb2189d4535dbf6a8b8c44cea2c80201 |
| 9194 | 1 | `witness[0][1].length` | `21` | 33 |
| 9195 | 33 | `witness[0][1].data` | `02254215e408029a4967347ced81f782a5898a952eb926bb60e1052f5d2a53a824` | 02254215e408029a4967347ced81f782a5898a952eb926bb60e1052f5d2a53a824 |
| 9228 | 4 | `tx.locktime` | `00000000` | 0 |

## 交易 30: `f3be173bb0a25172adccee082b3c912321c310d60605f72971df335610f41059`

| 偏移 | 字节数 | 字段 | 原始字节（线缆序） | 解释值 |
|---:|---:|---|---|---|
| 9232 | 4 | `tx.version` | `01000000` | 1 |
| 9236 | 1 | `tx.marker` | `00` | 0 |
| 9237 | 1 | `tx.flag` | `01` | 1 |
| 9238 | 1 | `tx.input_count` | `01` | 1 |
| 9239 | 32 | `vin[0].prev_txid` | `d53fcd2da94468b7833eb41a6fd82e452011bb569eed6c76d3b161408c7a7a26` | 267a7a8c4061b1d3766ced9e56bb1120452ed86f1ab43e83b76844a92dcd3fd5 |
| 9271 | 4 | `vin[0].vout` | `01000000` | 1 |
| 9275 | 1 | `vin[0].scriptSig_length` | `00` | 0 |
| 9276 | 0 | `vin[0].scriptSig` | `（空）` |  |
| 9276 | 4 | `vin[0].sequence` | `ffffffff` | 4294967295 |
| 9280 | 1 | `tx.output_count` | `02` | 2 |
| 9281 | 8 | `vout[0].value` | `e803000000000000` | 1000 |
| 9289 | 1 | `vout[0].scriptPubKey_length` | `16` | 22 |
| 9290 | 22 | `vout[0].scriptPubKey` | `0014b0feeac2312d429d569da17b462144a5b9d0d90c` | OP_0 b0feeac2312d429d569da17b462144a5b9d0d90c |
| 9312 | 8 | `vout[1].value` | `0c7d010000000000` | 97548 |
| 9320 | 1 | `vout[1].scriptPubKey_length` | `16` | 22 |
| 9321 | 22 | `vout[1].scriptPubKey` | `00148aa3a74793710ebf620cb1779ce55bfd38860687` | OP_0 8aa3a74793710ebf620cb1779ce55bfd38860687 |
| 9343 | 1 | `witness[0].item_count` | `02` | 2 |
| 9344 | 1 | `witness[0][0].length` | `48` | 72 |
| 9345 | 72 | `witness[0][0].data` | `3045022100dc91c08306c66a0e892015d1f6eabc9721607eefbe2d2f084ecc8ca2e92798850220693e23500bc226fb89ab33b45e872994c5a271b984dbe72176395a628908860e01` | 3045022100dc91c08306c66a0e892015d1f6eabc9721607eefbe2d2f084ecc8ca2e92798850220693e23500bc226fb89ab33b45e872994c5a271b984dbe72176395a628908860e01 |
| 9417 | 1 | `witness[0][1].length` | `21` | 33 |
| 9418 | 33 | `witness[0][1].data` | `02254215e408029a4967347ced81f782a5898a952eb926bb60e1052f5d2a53a824` | 02254215e408029a4967347ced81f782a5898a952eb926bb60e1052f5d2a53a824 |
| 9451 | 4 | `tx.locktime` | `00000000` | 0 |

## 交易 31: `345243ddbe6d15011a3b3a7b3e05b94ea12023426161b7a8ff52b948b7d7415a`

| 偏移 | 字节数 | 字段 | 原始字节（线缆序） | 解释值 |
|---:|---:|---|---|---|
| 9455 | 4 | `tx.version` | `01000000` | 1 |
| 9459 | 1 | `tx.marker` | `00` | 0 |
| 9460 | 1 | `tx.flag` | `01` | 1 |
| 9461 | 1 | `tx.input_count` | `01` | 1 |
| 9462 | 32 | `vin[0].prev_txid` | `a2e508302f19f74043faab83b2a0cf3c425f1afd4d37628680f2c7a2164777ff` | ff774716a2c7f2808662374dfd1a5f423ccfa0b283abfa4340f7192f3008e5a2 |
| 9494 | 4 | `vin[0].vout` | `01000000` | 1 |
| 9498 | 1 | `vin[0].scriptSig_length` | `00` | 0 |
| 9499 | 0 | `vin[0].scriptSig` | `（空）` |  |
| 9499 | 4 | `vin[0].sequence` | `ffffffff` | 4294967295 |
| 9503 | 1 | `tx.output_count` | `02` | 2 |
| 9504 | 8 | `vout[0].value` | `e803000000000000` | 1000 |
| 9512 | 1 | `vout[0].scriptPubKey_length` | `16` | 22 |
| 9513 | 22 | `vout[0].scriptPubKey` | `0014b0feeac2312d429d569da17b462144a5b9d0d90c` | OP_0 b0feeac2312d429d569da17b462144a5b9d0d90c |
| 9535 | 8 | `vout[1].value` | `186b050000000000` | 355096 |
| 9543 | 1 | `vout[1].scriptPubKey_length` | `16` | 22 |
| 9544 | 22 | `vout[1].scriptPubKey` | `00148aa3a74793710ebf620cb1779ce55bfd38860687` | OP_0 8aa3a74793710ebf620cb1779ce55bfd38860687 |
| 9566 | 1 | `witness[0].item_count` | `02` | 2 |
| 9567 | 1 | `witness[0][0].length` | `48` | 72 |
| 9568 | 72 | `witness[0][0].data` | `3045022100ae83d4f2b8736b90d0fb9450d1f54d75cb4e0b9df0d948f7c43c430c946eb4ef022030dde9cb07724d0238138cf1ad58d1928d6b8a826af91448f5f3c68f0e88ef9001` | 3045022100ae83d4f2b8736b90d0fb9450d1f54d75cb4e0b9df0d948f7c43c430c946eb4ef022030dde9cb07724d0238138cf1ad58d1928d6b8a826af91448f5f3c68f0e88ef9001 |
| 9640 | 1 | `witness[0][1].length` | `21` | 33 |
| 9641 | 33 | `witness[0][1].data` | `02254215e408029a4967347ced81f782a5898a952eb926bb60e1052f5d2a53a824` | 02254215e408029a4967347ced81f782a5898a952eb926bb60e1052f5d2a53a824 |
| 9674 | 4 | `tx.locktime` | `00000000` | 0 |

## 交易 32: `32630ec458b6434288a09a65d57e59e5afa3c995fc7f93f60bb277b6cadac85a`

| 偏移 | 字节数 | 字段 | 原始字节（线缆序） | 解释值 |
|---:|---:|---|---|---|
| 9678 | 4 | `tx.version` | `01000000` | 1 |
| 9682 | 1 | `tx.marker` | `00` | 0 |
| 9683 | 1 | `tx.flag` | `01` | 1 |
| 9684 | 1 | `tx.input_count` | `01` | 1 |
| 9685 | 32 | `vin[0].prev_txid` | `68825e0fb15786fdc544463f8735bae76d8338a07cb2b74aea50401b35e185d0` | d085e1351b4050ea4ab7b27ca038836de7ba35873f4644c5fd8657b10f5e8268 |
| 9717 | 4 | `vin[0].vout` | `01000000` | 1 |
| 9721 | 1 | `vin[0].scriptSig_length` | `00` | 0 |
| 9722 | 0 | `vin[0].scriptSig` | `（空）` |  |
| 9722 | 4 | `vin[0].sequence` | `ffffffff` | 4294967295 |
| 9726 | 1 | `tx.output_count` | `02` | 2 |
| 9727 | 8 | `vout[0].value` | `e803000000000000` | 1000 |
| 9735 | 1 | `vout[0].scriptPubKey_length` | `16` | 22 |
| 9736 | 22 | `vout[0].scriptPubKey` | `0014b0feeac2312d429d569da17b462144a5b9d0d90c` | OP_0 b0feeac2312d429d569da17b462144a5b9d0d90c |
| 9758 | 8 | `vout[1].value` | `0c7d010000000000` | 97548 |
| 9766 | 1 | `vout[1].scriptPubKey_length` | `16` | 22 |
| 9767 | 22 | `vout[1].scriptPubKey` | `00148aa3a74793710ebf620cb1779ce55bfd38860687` | OP_0 8aa3a74793710ebf620cb1779ce55bfd38860687 |
| 9789 | 1 | `witness[0].item_count` | `02` | 2 |
| 9790 | 1 | `witness[0][0].length` | `47` | 71 |
| 9791 | 71 | `witness[0][0].data` | `30440220447093a191b91e0e38d97aeff47ff3b53f993453fb8b7f4acb918f325cbacbb40220256a1af167325a7a47a92eef32e5bee3a46c3b79fca5d0dee3d225b1227585b601` | 30440220447093a191b91e0e38d97aeff47ff3b53f993453fb8b7f4acb918f325cbacbb40220256a1af167325a7a47a92eef32e5bee3a46c3b79fca5d0dee3d225b1227585b601 |
| 9862 | 1 | `witness[0][1].length` | `21` | 33 |
| 9863 | 33 | `witness[0][1].data` | `02254215e408029a4967347ced81f782a5898a952eb926bb60e1052f5d2a53a824` | 02254215e408029a4967347ced81f782a5898a952eb926bb60e1052f5d2a53a824 |
| 9896 | 4 | `tx.locktime` | `00000000` | 0 |

## 交易 33: `14c567eb1cb45c8314c2c0cc115b5680b9d00586dfa44e63aa6b626c64dee65b`

| 偏移 | 字节数 | 字段 | 原始字节（线缆序） | 解释值 |
|---:|---:|---|---|---|
| 9900 | 4 | `tx.version` | `01000000` | 1 |
| 9904 | 1 | `tx.marker` | `00` | 0 |
| 9905 | 1 | `tx.flag` | `01` | 1 |
| 9906 | 1 | `tx.input_count` | `01` | 1 |
| 9907 | 32 | `vin[0].prev_txid` | `2ef848e8ef112a2a5a2c72ed15409c434a3194faeb027d293eb4a96fed8e7c4c` | 4c7c8eed6fa9b43e297d02ebfa94314a439c4015ed722c5a2a2a11efe848f82e |
| 9939 | 4 | `vin[0].vout` | `01000000` | 1 |
| 9943 | 1 | `vin[0].scriptSig_length` | `00` | 0 |
| 9944 | 0 | `vin[0].scriptSig` | `（空）` |  |
| 9944 | 4 | `vin[0].sequence` | `ffffffff` | 4294967295 |
| 9948 | 1 | `tx.output_count` | `02` | 2 |
| 9949 | 8 | `vout[0].value` | `e803000000000000` | 1000 |
| 9957 | 1 | `vout[0].scriptPubKey_length` | `16` | 22 |
| 9958 | 22 | `vout[0].scriptPubKey` | `0014b0feeac2312d429d569da17b462144a5b9d0d90c` | OP_0 b0feeac2312d429d569da17b462144a5b9d0d90c |
| 9980 | 8 | `vout[1].value` | `7a870e0000000000` | 952186 |
| 9988 | 1 | `vout[1].scriptPubKey_length` | `16` | 22 |
| 9989 | 22 | `vout[1].scriptPubKey` | `00148aa3a74793710ebf620cb1779ce55bfd38860687` | OP_0 8aa3a74793710ebf620cb1779ce55bfd38860687 |
| 10011 | 1 | `witness[0].item_count` | `02` | 2 |
| 10012 | 1 | `witness[0][0].length` | `48` | 72 |
| 10013 | 72 | `witness[0][0].data` | `3045022100d9d1c309357bc9c7795b7098ef3551356e392af0e5a1448d7c70a7cda24cc40e02205f52f157d4be2c4ff8dd71effbca81f655a7d398ae78f2c74b96c3ff9f6c899a01` | 3045022100d9d1c309357bc9c7795b7098ef3551356e392af0e5a1448d7c70a7cda24cc40e02205f52f157d4be2c4ff8dd71effbca81f655a7d398ae78f2c74b96c3ff9f6c899a01 |
| 10085 | 1 | `witness[0][1].length` | `21` | 33 |
| 10086 | 33 | `witness[0][1].data` | `02254215e408029a4967347ced81f782a5898a952eb926bb60e1052f5d2a53a824` | 02254215e408029a4967347ced81f782a5898a952eb926bb60e1052f5d2a53a824 |
| 10119 | 4 | `tx.locktime` | `00000000` | 0 |

## 交易 34: `2c480cc419ec60a2ed92aff50fd1ed087c57db59713474ee49c97399c8a6f65b`

| 偏移 | 字节数 | 字段 | 原始字节（线缆序） | 解释值 |
|---:|---:|---|---|---|
| 10123 | 4 | `tx.version` | `01000000` | 1 |
| 10127 | 1 | `tx.marker` | `00` | 0 |
| 10128 | 1 | `tx.flag` | `01` | 1 |
| 10129 | 1 | `tx.input_count` | `01` | 1 |
| 10130 | 32 | `vin[0].prev_txid` | `3bd82d0e56e0bb5eef7d93c7e5ba142e5bede8c49a508dc4fcc2662a61f248c5` | c548f2612a66c2fcc48d509ac4e8ed5b2e14bae5c7937def5ebbe0560e2dd83b |
| 10162 | 4 | `vin[0].vout` | `01000000` | 1 |
| 10166 | 1 | `vin[0].scriptSig_length` | `00` | 0 |
| 10167 | 0 | `vin[0].scriptSig` | `（空）` |  |
| 10167 | 4 | `vin[0].sequence` | `ffffffff` | 4294967295 |
| 10171 | 1 | `tx.output_count` | `02` | 2 |
| 10172 | 8 | `vout[0].value` | `e803000000000000` | 1000 |
| 10180 | 1 | `vout[0].scriptPubKey_length` | `16` | 22 |
| 10181 | 22 | `vout[0].scriptPubKey` | `0014b0feeac2312d429d569da17b462144a5b9d0d90c` | OP_0 b0feeac2312d429d569da17b462144a5b9d0d90c |
| 10203 | 8 | `vout[1].value` | `0c7d010000000000` | 97548 |
| 10211 | 1 | `vout[1].scriptPubKey_length` | `16` | 22 |
| 10212 | 22 | `vout[1].scriptPubKey` | `00148aa3a74793710ebf620cb1779ce55bfd38860687` | OP_0 8aa3a74793710ebf620cb1779ce55bfd38860687 |
| 10234 | 1 | `witness[0].item_count` | `02` | 2 |
| 10235 | 1 | `witness[0][0].length` | `47` | 71 |
| 10236 | 71 | `witness[0][0].data` | `3044022056cb05740705e995bdd684dfdb5b88fb77667e2c4e2c0b0cd25a5a4a735addc3022028a61f19f4c5d6b6412fe43a017b7fcd4384fa9318e09ba55c6541181c67e57b01` | 3044022056cb05740705e995bdd684dfdb5b88fb77667e2c4e2c0b0cd25a5a4a735addc3022028a61f19f4c5d6b6412fe43a017b7fcd4384fa9318e09ba55c6541181c67e57b01 |
| 10307 | 1 | `witness[0][1].length` | `21` | 33 |
| 10308 | 33 | `witness[0][1].data` | `02254215e408029a4967347ced81f782a5898a952eb926bb60e1052f5d2a53a824` | 02254215e408029a4967347ced81f782a5898a952eb926bb60e1052f5d2a53a824 |
| 10341 | 4 | `tx.locktime` | `00000000` | 0 |

## 交易 35: `fa479938a840cd34c4b1e857a41c572d51e199969a84450201785041a520ec5e`

| 偏移 | 字节数 | 字段 | 原始字节（线缆序） | 解释值 |
|---:|---:|---|---|---|
| 10345 | 4 | `tx.version` | `01000000` | 1 |
| 10349 | 1 | `tx.marker` | `00` | 0 |
| 10350 | 1 | `tx.flag` | `01` | 1 |
| 10351 | 1 | `tx.input_count` | `01` | 1 |
| 10352 | 32 | `vin[0].prev_txid` | `9b8ae1709bc645addbe8764f44fe1e2729d8d2b35b499b75ecc8e9dcc7b2f413` | 13f4b2c7dce9c8ec759b495bb3d2d829271efe444f76e8dbad45c69b70e18a9b |
| 10384 | 4 | `vin[0].vout` | `01000000` | 1 |
| 10388 | 1 | `vin[0].scriptSig_length` | `00` | 0 |
| 10389 | 0 | `vin[0].scriptSig` | `（空）` |  |
| 10389 | 4 | `vin[0].sequence` | `ffffffff` | 4294967295 |
| 10393 | 1 | `tx.output_count` | `02` | 2 |
| 10394 | 8 | `vout[0].value` | `e803000000000000` | 1000 |
| 10402 | 1 | `vout[0].scriptPubKey_length` | `16` | 22 |
| 10403 | 22 | `vout[0].scriptPubKey` | `0014b0feeac2312d429d569da17b462144a5b9d0d90c` | OP_0 b0feeac2312d429d569da17b462144a5b9d0d90c |
| 10425 | 8 | `vout[1].value` | `0c7d010000000000` | 97548 |
| 10433 | 1 | `vout[1].scriptPubKey_length` | `16` | 22 |
| 10434 | 22 | `vout[1].scriptPubKey` | `00148aa3a74793710ebf620cb1779ce55bfd38860687` | OP_0 8aa3a74793710ebf620cb1779ce55bfd38860687 |
| 10456 | 1 | `witness[0].item_count` | `02` | 2 |
| 10457 | 1 | `witness[0][0].length` | `47` | 71 |
| 10458 | 71 | `witness[0][0].data` | `3044022033421ce308a16c244c23241f872c38b26f395e58ce9c9b081a5f8dc18683af03022068431feb71a116c778ac6219cefc91b8171a4c5f38151c0049b0b7929411828c01` | 3044022033421ce308a16c244c23241f872c38b26f395e58ce9c9b081a5f8dc18683af03022068431feb71a116c778ac6219cefc91b8171a4c5f38151c0049b0b7929411828c01 |
| 10529 | 1 | `witness[0][1].length` | `21` | 33 |
| 10530 | 33 | `witness[0][1].data` | `02254215e408029a4967347ced81f782a5898a952eb926bb60e1052f5d2a53a824` | 02254215e408029a4967347ced81f782a5898a952eb926bb60e1052f5d2a53a824 |
| 10563 | 4 | `tx.locktime` | `00000000` | 0 |

## 交易 36: `809a672d8639356fcf3e68b43ccd1bdb37252099d557c74363fcf25d60daf467`

| 偏移 | 字节数 | 字段 | 原始字节（线缆序） | 解释值 |
|---:|---:|---|---|---|
| 10567 | 4 | `tx.version` | `01000000` | 1 |
| 10571 | 1 | `tx.marker` | `00` | 0 |
| 10572 | 1 | `tx.flag` | `01` | 1 |
| 10573 | 1 | `tx.input_count` | `01` | 1 |
| 10574 | 32 | `vin[0].prev_txid` | `4e9c095143416e584fc17595c9deded00221e1332bf225cd5bce911b0fa25f32` | 325fa20f1b91ce5bcd25f22b33e12102d0dedec99575c14f586e414351099c4e |
| 10606 | 4 | `vin[0].vout` | `01000000` | 1 |
| 10610 | 1 | `vin[0].scriptSig_length` | `00` | 0 |
| 10611 | 0 | `vin[0].scriptSig` | `（空）` |  |
| 10611 | 4 | `vin[0].sequence` | `ffffffff` | 4294967295 |
| 10615 | 1 | `tx.output_count` | `02` | 2 |
| 10616 | 8 | `vout[0].value` | `e803000000000000` | 1000 |
| 10624 | 1 | `vout[0].scriptPubKey_length` | `16` | 22 |
| 10625 | 22 | `vout[0].scriptPubKey` | `0014b0feeac2312d429d569da17b462144a5b9d0d90c` | OP_0 b0feeac2312d429d569da17b462144a5b9d0d90c |
| 10647 | 8 | `vout[1].value` | `0c7d010000000000` | 97548 |
| 10655 | 1 | `vout[1].scriptPubKey_length` | `16` | 22 |
| 10656 | 22 | `vout[1].scriptPubKey` | `00148aa3a74793710ebf620cb1779ce55bfd38860687` | OP_0 8aa3a74793710ebf620cb1779ce55bfd38860687 |
| 10678 | 1 | `witness[0].item_count` | `02` | 2 |
| 10679 | 1 | `witness[0][0].length` | `47` | 71 |
| 10680 | 71 | `witness[0][0].data` | `304402207db512da4179207f2e630ab41f97fb9766b067944a0139da1136efb327643d85022033ac2173634c658abf80ca1c8d32137ef5ef7e97e0800543071a2f3f6787cf7301` | 304402207db512da4179207f2e630ab41f97fb9766b067944a0139da1136efb327643d85022033ac2173634c658abf80ca1c8d32137ef5ef7e97e0800543071a2f3f6787cf7301 |
| 10751 | 1 | `witness[0][1].length` | `21` | 33 |
| 10752 | 33 | `witness[0][1].data` | `02254215e408029a4967347ced81f782a5898a952eb926bb60e1052f5d2a53a824` | 02254215e408029a4967347ced81f782a5898a952eb926bb60e1052f5d2a53a824 |
| 10785 | 4 | `tx.locktime` | `00000000` | 0 |

## 交易 37: `7c2564fd7c6134730557a4b6af3e396cb53ac77156b8fd2438e6a4bd5235c277`

| 偏移 | 字节数 | 字段 | 原始字节（线缆序） | 解释值 |
|---:|---:|---|---|---|
| 10789 | 4 | `tx.version` | `01000000` | 1 |
| 10793 | 1 | `tx.marker` | `00` | 0 |
| 10794 | 1 | `tx.flag` | `01` | 1 |
| 10795 | 1 | `tx.input_count` | `01` | 1 |
| 10796 | 32 | `vin[0].prev_txid` | `3dac539445d1ee1b7182f8d38e8afc061e4da166c6778e979860da038bac1e8e` | 8e1eac8b03da6098978e77c666a14d1e06fc8a8ed3f882711beed1459453ac3d |
| 10828 | 4 | `vin[0].vout` | `01000000` | 1 |
| 10832 | 1 | `vin[0].scriptSig_length` | `00` | 0 |
| 10833 | 0 | `vin[0].scriptSig` | `（空）` |  |
| 10833 | 4 | `vin[0].sequence` | `ffffffff` | 4294967295 |
| 10837 | 1 | `tx.output_count` | `02` | 2 |
| 10838 | 8 | `vout[0].value` | `e803000000000000` | 1000 |
| 10846 | 1 | `vout[0].scriptPubKey_length` | `16` | 22 |
| 10847 | 22 | `vout[0].scriptPubKey` | `0014b0feeac2312d429d569da17b462144a5b9d0d90c` | OP_0 b0feeac2312d429d569da17b462144a5b9d0d90c |
| 10869 | 8 | `vout[1].value` | `0c7d010000000000` | 97548 |
| 10877 | 1 | `vout[1].scriptPubKey_length` | `16` | 22 |
| 10878 | 22 | `vout[1].scriptPubKey` | `00148aa3a74793710ebf620cb1779ce55bfd38860687` | OP_0 8aa3a74793710ebf620cb1779ce55bfd38860687 |
| 10900 | 1 | `witness[0].item_count` | `02` | 2 |
| 10901 | 1 | `witness[0][0].length` | `48` | 72 |
| 10902 | 72 | `witness[0][0].data` | `3045022100edc79bb91698630ba10deb59f6f2ee90bcc3d64181351494ee6962d5d0969628022053593fb98267a5501466b655871d9f30b7d57a3058ac9e3d5fc40877472881c701` | 3045022100edc79bb91698630ba10deb59f6f2ee90bcc3d64181351494ee6962d5d0969628022053593fb98267a5501466b655871d9f30b7d57a3058ac9e3d5fc40877472881c701 |
| 10974 | 1 | `witness[0][1].length` | `21` | 33 |
| 10975 | 33 | `witness[0][1].data` | `02254215e408029a4967347ced81f782a5898a952eb926bb60e1052f5d2a53a824` | 02254215e408029a4967347ced81f782a5898a952eb926bb60e1052f5d2a53a824 |
| 11008 | 4 | `tx.locktime` | `00000000` | 0 |

## 交易 38: `0b917635a0e09ff6e65c34f1fc773e15e1c31a5d2318d6c77214e755c364a87d`

| 偏移 | 字节数 | 字段 | 原始字节（线缆序） | 解释值 |
|---:|---:|---|---|---|
| 11012 | 4 | `tx.version` | `01000000` | 1 |
| 11016 | 1 | `tx.marker` | `00` | 0 |
| 11017 | 1 | `tx.flag` | `01` | 1 |
| 11018 | 1 | `tx.input_count` | `01` | 1 |
| 11019 | 32 | `vin[0].prev_txid` | `9e705c5bbe382a727656d9ba659756ae3325460a8cc9eafd0f9b6d7ce3a609e9` | e909a6e37c6d9b0ffdeac98c0a462533ae569765bad95676722a38be5b5c709e |
| 11051 | 4 | `vin[0].vout` | `01000000` | 1 |
| 11055 | 1 | `vin[0].scriptSig_length` | `00` | 0 |
| 11056 | 0 | `vin[0].scriptSig` | `（空）` |  |
| 11056 | 4 | `vin[0].sequence` | `ffffffff` | 4294967295 |
| 11060 | 1 | `tx.output_count` | `02` | 2 |
| 11061 | 8 | `vout[0].value` | `e803000000000000` | 1000 |
| 11069 | 1 | `vout[0].scriptPubKey_length` | `16` | 22 |
| 11070 | 22 | `vout[0].scriptPubKey` | `0014b0feeac2312d429d569da17b462144a5b9d0d90c` | OP_0 b0feeac2312d429d569da17b462144a5b9d0d90c |
| 11092 | 8 | `vout[1].value` | `0c7d010000000000` | 97548 |
| 11100 | 1 | `vout[1].scriptPubKey_length` | `16` | 22 |
| 11101 | 22 | `vout[1].scriptPubKey` | `00148aa3a74793710ebf620cb1779ce55bfd38860687` | OP_0 8aa3a74793710ebf620cb1779ce55bfd38860687 |
| 11123 | 1 | `witness[0].item_count` | `02` | 2 |
| 11124 | 1 | `witness[0][0].length` | `48` | 72 |
| 11125 | 72 | `witness[0][0].data` | `30450221008734c1e5749183344fc334ca3bdfebb641a6bfdd95bad84ff0f7d81240001ef502204848f1694fa5e9bf4be8bf03dbf95839a523373e65f23b5d7874cf5836d48bad01` | 30450221008734c1e5749183344fc334ca3bdfebb641a6bfdd95bad84ff0f7d81240001ef502204848f1694fa5e9bf4be8bf03dbf95839a523373e65f23b5d7874cf5836d48bad01 |
| 11197 | 1 | `witness[0][1].length` | `21` | 33 |
| 11198 | 33 | `witness[0][1].data` | `02254215e408029a4967347ced81f782a5898a952eb926bb60e1052f5d2a53a824` | 02254215e408029a4967347ced81f782a5898a952eb926bb60e1052f5d2a53a824 |
| 11231 | 4 | `tx.locktime` | `00000000` | 0 |

## 交易 39: `9f60165f91b668b2d42914cb8f7ee9b5bfb5761eed210526b858e63a1cd99980`

| 偏移 | 字节数 | 字段 | 原始字节（线缆序） | 解释值 |
|---:|---:|---|---|---|
| 11235 | 4 | `tx.version` | `01000000` | 1 |
| 11239 | 1 | `tx.marker` | `00` | 0 |
| 11240 | 1 | `tx.flag` | `01` | 1 |
| 11241 | 1 | `tx.input_count` | `01` | 1 |
| 11242 | 32 | `vin[0].prev_txid` | `1ebb9fc2667adae54b5624c341030e8540d54ba7f99b1a49e779be4d32c264d2` | d264c2324dbe79e7491a9bf9a74bd540850e0341c324564be5da7a66c29fbb1e |
| 11274 | 4 | `vin[0].vout` | `01000000` | 1 |
| 11278 | 1 | `vin[0].scriptSig_length` | `00` | 0 |
| 11279 | 0 | `vin[0].scriptSig` | `（空）` |  |
| 11279 | 4 | `vin[0].sequence` | `ffffffff` | 4294967295 |
| 11283 | 1 | `tx.output_count` | `02` | 2 |
| 11284 | 8 | `vout[0].value` | `e803000000000000` | 1000 |
| 11292 | 1 | `vout[0].scriptPubKey_length` | `16` | 22 |
| 11293 | 22 | `vout[0].scriptPubKey` | `0014b0feeac2312d429d569da17b462144a5b9d0d90c` | OP_0 b0feeac2312d429d569da17b462144a5b9d0d90c |
| 11315 | 8 | `vout[1].value` | `5896030000000000` | 235096 |
| 11323 | 1 | `vout[1].scriptPubKey_length` | `16` | 22 |
| 11324 | 22 | `vout[1].scriptPubKey` | `00148aa3a74793710ebf620cb1779ce55bfd38860687` | OP_0 8aa3a74793710ebf620cb1779ce55bfd38860687 |
| 11346 | 1 | `witness[0].item_count` | `02` | 2 |
| 11347 | 1 | `witness[0][0].length` | `47` | 71 |
| 11348 | 71 | `witness[0][0].data` | `304402205f57993c6bda4a672fb0e82a3287ead5bb567634ebdda339af7bbbd51eb6258402205643327fb388b6f965e3912448ceb0ea48ed1cbbecf77f4c9e26c57bf988b42e01` | 304402205f57993c6bda4a672fb0e82a3287ead5bb567634ebdda339af7bbbd51eb6258402205643327fb388b6f965e3912448ceb0ea48ed1cbbecf77f4c9e26c57bf988b42e01 |
| 11419 | 1 | `witness[0][1].length` | `21` | 33 |
| 11420 | 33 | `witness[0][1].data` | `02254215e408029a4967347ced81f782a5898a952eb926bb60e1052f5d2a53a824` | 02254215e408029a4967347ced81f782a5898a952eb926bb60e1052f5d2a53a824 |
| 11453 | 4 | `tx.locktime` | `00000000` | 0 |

## 交易 40: `11ee58da73320bc7147325ac2e4ca54ff2760da11ab8c8bccfe76007bc92ec8f`

| 偏移 | 字节数 | 字段 | 原始字节（线缆序） | 解释值 |
|---:|---:|---|---|---|
| 11457 | 4 | `tx.version` | `01000000` | 1 |
| 11461 | 1 | `tx.marker` | `00` | 0 |
| 11462 | 1 | `tx.flag` | `01` | 1 |
| 11463 | 1 | `tx.input_count` | `01` | 1 |
| 11464 | 32 | `vin[0].prev_txid` | `e39c496d55644aa851457479e4defb7c3fdfaaaf8c222d0143b7d0a90846db24` | 24db4608a9d0b743012d228cafaadf3f7cfbdee479744551a84a64556d499ce3 |
| 11496 | 4 | `vin[0].vout` | `01000000` | 1 |
| 11500 | 1 | `vin[0].scriptSig_length` | `00` | 0 |
| 11501 | 0 | `vin[0].scriptSig` | `（空）` |  |
| 11501 | 4 | `vin[0].sequence` | `ffffffff` | 4294967295 |
| 11505 | 1 | `tx.output_count` | `02` | 2 |
| 11506 | 8 | `vout[0].value` | `e803000000000000` | 1000 |
| 11514 | 1 | `vout[0].scriptPubKey_length` | `16` | 22 |
| 11515 | 22 | `vout[0].scriptPubKey` | `0014b0feeac2312d429d569da17b462144a5b9d0d90c` | OP_0 b0feeac2312d429d569da17b462144a5b9d0d90c |
| 11537 | 8 | `vout[1].value` | `98c1010000000000` | 115096 |
| 11545 | 1 | `vout[1].scriptPubKey_length` | `16` | 22 |
| 11546 | 22 | `vout[1].scriptPubKey` | `00148aa3a74793710ebf620cb1779ce55bfd38860687` | OP_0 8aa3a74793710ebf620cb1779ce55bfd38860687 |
| 11568 | 1 | `witness[0].item_count` | `02` | 2 |
| 11569 | 1 | `witness[0][0].length` | `48` | 72 |
| 11570 | 72 | `witness[0][0].data` | `3045022100d1734ee57cf60d8adf32eee0e8b485a85d4ea80dcb68893a53c123959d810e60022020865a6b1231bd0407bb4f5c6b6c8068866ae55298427bf1349726171ce591cd01` | 3045022100d1734ee57cf60d8adf32eee0e8b485a85d4ea80dcb68893a53c123959d810e60022020865a6b1231bd0407bb4f5c6b6c8068866ae55298427bf1349726171ce591cd01 |
| 11642 | 1 | `witness[0][1].length` | `21` | 33 |
| 11643 | 33 | `witness[0][1].data` | `02254215e408029a4967347ced81f782a5898a952eb926bb60e1052f5d2a53a824` | 02254215e408029a4967347ced81f782a5898a952eb926bb60e1052f5d2a53a824 |
| 11676 | 4 | `tx.locktime` | `00000000` | 0 |

## 交易 41: `809808bdd12d54032799bdf3bc4377baabf7a1e2f135cf5d34b5b1a1a70ba996`

| 偏移 | 字节数 | 字段 | 原始字节（线缆序） | 解释值 |
|---:|---:|---|---|---|
| 11680 | 4 | `tx.version` | `01000000` | 1 |
| 11684 | 1 | `tx.marker` | `00` | 0 |
| 11685 | 1 | `tx.flag` | `01` | 1 |
| 11686 | 1 | `tx.input_count` | `01` | 1 |
| 11687 | 32 | `vin[0].prev_txid` | `f39fd194c296270a6bc67c9e4570db5a0ccd44e0242c9c798ca3c9b9a5a21f15` | 151fa2a5b9c9a38c799c2c24e044cd0c5adb70459e7cc66b0a2796c294d19ff3 |
| 11719 | 4 | `vin[0].vout` | `01000000` | 1 |
| 11723 | 1 | `vin[0].scriptSig_length` | `00` | 0 |
| 11724 | 0 | `vin[0].scriptSig` | `（空）` |  |
| 11724 | 4 | `vin[0].sequence` | `ffffffff` | 4294967295 |
| 11728 | 1 | `tx.output_count` | `02` | 2 |
| 11729 | 8 | `vout[0].value` | `e803000000000000` | 1000 |
| 11737 | 1 | `vout[0].scriptPubKey_length` | `16` | 22 |
| 11738 | 22 | `vout[0].scriptPubKey` | `0014b0feeac2312d429d569da17b462144a5b9d0d90c` | OP_0 b0feeac2312d429d569da17b462144a5b9d0d90c |
| 11760 | 8 | `vout[1].value` | `0c7d010000000000` | 97548 |
| 11768 | 1 | `vout[1].scriptPubKey_length` | `16` | 22 |
| 11769 | 22 | `vout[1].scriptPubKey` | `00148aa3a74793710ebf620cb1779ce55bfd38860687` | OP_0 8aa3a74793710ebf620cb1779ce55bfd38860687 |
| 11791 | 1 | `witness[0].item_count` | `02` | 2 |
| 11792 | 1 | `witness[0][0].length` | `48` | 72 |
| 11793 | 72 | `witness[0][0].data` | `3045022100d1abaebe9203eff0548aed39821853c220f18513208d0693a70d93233335423602207b98016334e33eb1ba453b18e0beabc0a26eb0e8b5613b0386cc3537606d715301` | 3045022100d1abaebe9203eff0548aed39821853c220f18513208d0693a70d93233335423602207b98016334e33eb1ba453b18e0beabc0a26eb0e8b5613b0386cc3537606d715301 |
| 11865 | 1 | `witness[0][1].length` | `21` | 33 |
| 11866 | 33 | `witness[0][1].data` | `02254215e408029a4967347ced81f782a5898a952eb926bb60e1052f5d2a53a824` | 02254215e408029a4967347ced81f782a5898a952eb926bb60e1052f5d2a53a824 |
| 11899 | 4 | `tx.locktime` | `00000000` | 0 |

## 交易 42: `c5929fc73a19c29f41d87e712d3606d7d4a4155a405c9b4fb0a17514659294a2`

| 偏移 | 字节数 | 字段 | 原始字节（线缆序） | 解释值 |
|---:|---:|---|---|---|
| 11903 | 4 | `tx.version` | `01000000` | 1 |
| 11907 | 1 | `tx.marker` | `00` | 0 |
| 11908 | 1 | `tx.flag` | `01` | 1 |
| 11909 | 1 | `tx.input_count` | `01` | 1 |
| 11910 | 32 | `vin[0].prev_txid` | `346a3d9162815d76856743ff2e944957286c24d9a79d754054055b8f4e6c41c5` | c5416c4e8f5b055440759da7d9246c285749942eff436785765d8162913d6a34 |
| 11942 | 4 | `vin[0].vout` | `01000000` | 1 |
| 11946 | 1 | `vin[0].scriptSig_length` | `00` | 0 |
| 11947 | 0 | `vin[0].scriptSig` | `（空）` |  |
| 11947 | 4 | `vin[0].sequence` | `ffffffff` | 4294967295 |
| 11951 | 1 | `tx.output_count` | `02` | 2 |
| 11952 | 8 | `vout[0].value` | `e803000000000000` | 1000 |
| 11960 | 1 | `vout[0].scriptPubKey_length` | `16` | 22 |
| 11961 | 22 | `vout[0].scriptPubKey` | `0014b0feeac2312d429d569da17b462144a5b9d0d90c` | OP_0 b0feeac2312d429d569da17b462144a5b9d0d90c |
| 11983 | 8 | `vout[1].value` | `0c7d010000000000` | 97548 |
| 11991 | 1 | `vout[1].scriptPubKey_length` | `16` | 22 |
| 11992 | 22 | `vout[1].scriptPubKey` | `00148aa3a74793710ebf620cb1779ce55bfd38860687` | OP_0 8aa3a74793710ebf620cb1779ce55bfd38860687 |
| 12014 | 1 | `witness[0].item_count` | `02` | 2 |
| 12015 | 1 | `witness[0][0].length` | `48` | 72 |
| 12016 | 72 | `witness[0][0].data` | `3045022100f0aebde74af5737dfb0f264106ef543529b6636ac41a64bf40f60bc92ae5a91402205d8a3d051b7a033d06dac38bcd5a2f62bddc2d1a5ac965019f60722d277acbb101` | 3045022100f0aebde74af5737dfb0f264106ef543529b6636ac41a64bf40f60bc92ae5a91402205d8a3d051b7a033d06dac38bcd5a2f62bddc2d1a5ac965019f60722d277acbb101 |
| 12088 | 1 | `witness[0][1].length` | `21` | 33 |
| 12089 | 33 | `witness[0][1].data` | `02254215e408029a4967347ced81f782a5898a952eb926bb60e1052f5d2a53a824` | 02254215e408029a4967347ced81f782a5898a952eb926bb60e1052f5d2a53a824 |
| 12122 | 4 | `tx.locktime` | `00000000` | 0 |

## 交易 43: `9d6eea660e0e39780ca6262eaa9176d953d48cb5bff6ddb19b16b1ef77bb25b0`

| 偏移 | 字节数 | 字段 | 原始字节（线缆序） | 解释值 |
|---:|---:|---|---|---|
| 12126 | 4 | `tx.version` | `01000000` | 1 |
| 12130 | 1 | `tx.marker` | `00` | 0 |
| 12131 | 1 | `tx.flag` | `01` | 1 |
| 12132 | 1 | `tx.input_count` | `01` | 1 |
| 12133 | 32 | `vin[0].prev_txid` | `9593cfaf69e892ba8fccbe2a1411f197b2947b27d36aa7b530fc74a8c56a304b` | 4b306ac5a874fc30b5a76ad3277b94b297f111142abecc8fba92e869afcf9395 |
| 12165 | 4 | `vin[0].vout` | `01000000` | 1 |
| 12169 | 1 | `vin[0].scriptSig_length` | `00` | 0 |
| 12170 | 0 | `vin[0].scriptSig` | `（空）` |  |
| 12170 | 4 | `vin[0].sequence` | `ffffffff` | 4294967295 |
| 12174 | 1 | `tx.output_count` | `02` | 2 |
| 12175 | 8 | `vout[0].value` | `e803000000000000` | 1000 |
| 12183 | 1 | `vout[0].scriptPubKey_length` | `16` | 22 |
| 12184 | 22 | `vout[0].scriptPubKey` | `0014b0feeac2312d429d569da17b462144a5b9d0d90c` | OP_0 b0feeac2312d429d569da17b462144a5b9d0d90c |
| 12206 | 8 | `vout[1].value` | `0c7d010000000000` | 97548 |
| 12214 | 1 | `vout[1].scriptPubKey_length` | `16` | 22 |
| 12215 | 22 | `vout[1].scriptPubKey` | `00148aa3a74793710ebf620cb1779ce55bfd38860687` | OP_0 8aa3a74793710ebf620cb1779ce55bfd38860687 |
| 12237 | 1 | `witness[0].item_count` | `02` | 2 |
| 12238 | 1 | `witness[0][0].length` | `47` | 71 |
| 12239 | 71 | `witness[0][0].data` | `304402200de959129ed50b7b15b886be6543958c8174a1979c8110c5319ecced824d4d3c0220582ec3fd3aa589524ac2bf0b2c8b736b4d801e5932f172d8d0a2c1fec12010f701` | 304402200de959129ed50b7b15b886be6543958c8174a1979c8110c5319ecced824d4d3c0220582ec3fd3aa589524ac2bf0b2c8b736b4d801e5932f172d8d0a2c1fec12010f701 |
| 12310 | 1 | `witness[0][1].length` | `21` | 33 |
| 12311 | 33 | `witness[0][1].data` | `02254215e408029a4967347ced81f782a5898a952eb926bb60e1052f5d2a53a824` | 02254215e408029a4967347ced81f782a5898a952eb926bb60e1052f5d2a53a824 |
| 12344 | 4 | `tx.locktime` | `00000000` | 0 |

## 交易 44: `f71899c2ab59436c7e2197fb0eba69bdd9192a50858d9f60bdd56d0d8ba694b3`

| 偏移 | 字节数 | 字段 | 原始字节（线缆序） | 解释值 |
|---:|---:|---|---|---|
| 12348 | 4 | `tx.version` | `01000000` | 1 |
| 12352 | 1 | `tx.marker` | `00` | 0 |
| 12353 | 1 | `tx.flag` | `01` | 1 |
| 12354 | 1 | `tx.input_count` | `01` | 1 |
| 12355 | 32 | `vin[0].prev_txid` | `d1f806349dddbb97433f695aa654057eaf8c5bd4226e9737f9f35db5a3ae3cde` | de3caea3b55df3f937976e22d45b8caf7e0554a65a693f4397bbdd9d3406f8d1 |
| 12387 | 4 | `vin[0].vout` | `01000000` | 1 |
| 12391 | 1 | `vin[0].scriptSig_length` | `00` | 0 |
| 12392 | 0 | `vin[0].scriptSig` | `（空）` |  |
| 12392 | 4 | `vin[0].sequence` | `ffffffff` | 4294967295 |
| 12396 | 1 | `tx.output_count` | `02` | 2 |
| 12397 | 8 | `vout[0].value` | `e803000000000000` | 1000 |
| 12405 | 1 | `vout[0].scriptPubKey_length` | `16` | 22 |
| 12406 | 22 | `vout[0].scriptPubKey` | `0014b0feeac2312d429d569da17b462144a5b9d0d90c` | OP_0 b0feeac2312d429d569da17b462144a5b9d0d90c |
| 12428 | 8 | `vout[1].value` | `0c7d010000000000` | 97548 |
| 12436 | 1 | `vout[1].scriptPubKey_length` | `16` | 22 |
| 12437 | 22 | `vout[1].scriptPubKey` | `00148aa3a74793710ebf620cb1779ce55bfd38860687` | OP_0 8aa3a74793710ebf620cb1779ce55bfd38860687 |
| 12459 | 1 | `witness[0].item_count` | `02` | 2 |
| 12460 | 1 | `witness[0][0].length` | `47` | 71 |
| 12461 | 71 | `witness[0][0].data` | `30440220334aebb089d23a489c6d5bddd2d9f0b7a52d635fbf923eaa12ce36267452ca4a0220470cc6b19c8cbdf12f1d9be46e1938c8ce554d0cbf5835020ce0c6b42c2773e101` | 30440220334aebb089d23a489c6d5bddd2d9f0b7a52d635fbf923eaa12ce36267452ca4a0220470cc6b19c8cbdf12f1d9be46e1938c8ce554d0cbf5835020ce0c6b42c2773e101 |
| 12532 | 1 | `witness[0][1].length` | `21` | 33 |
| 12533 | 33 | `witness[0][1].data` | `02254215e408029a4967347ced81f782a5898a952eb926bb60e1052f5d2a53a824` | 02254215e408029a4967347ced81f782a5898a952eb926bb60e1052f5d2a53a824 |
| 12566 | 4 | `tx.locktime` | `00000000` | 0 |

## 交易 45: `012ab0964db6474a5c033540ea113da0e272f6f95f12e5167024c32746e59dbb`

| 偏移 | 字节数 | 字段 | 原始字节（线缆序） | 解释值 |
|---:|---:|---|---|---|
| 12570 | 4 | `tx.version` | `01000000` | 1 |
| 12574 | 1 | `tx.marker` | `00` | 0 |
| 12575 | 1 | `tx.flag` | `01` | 1 |
| 12576 | 1 | `tx.input_count` | `01` | 1 |
| 12577 | 32 | `vin[0].prev_txid` | `bf121e50a40ebd0ff7330b3eaeda693bda5e72d56229360046a8770688939664` | 649693880677a84600362962d5725eda3b69daae3e0b33f70fbd0ea4501e12bf |
| 12609 | 4 | `vin[0].vout` | `01000000` | 1 |
| 12613 | 1 | `vin[0].scriptSig_length` | `00` | 0 |
| 12614 | 0 | `vin[0].scriptSig` | `（空）` |  |
| 12614 | 4 | `vin[0].sequence` | `ffffffff` | 4294967295 |
| 12618 | 1 | `tx.output_count` | `02` | 2 |
| 12619 | 8 | `vout[0].value` | `e803000000000000` | 1000 |
| 12627 | 1 | `vout[0].scriptPubKey_length` | `16` | 22 |
| 12628 | 22 | `vout[0].scriptPubKey` | `0014b0feeac2312d429d569da17b462144a5b9d0d90c` | OP_0 b0feeac2312d429d569da17b462144a5b9d0d90c |
| 12650 | 8 | `vout[1].value` | `0c7d010000000000` | 97548 |
| 12658 | 1 | `vout[1].scriptPubKey_length` | `16` | 22 |
| 12659 | 22 | `vout[1].scriptPubKey` | `00148aa3a74793710ebf620cb1779ce55bfd38860687` | OP_0 8aa3a74793710ebf620cb1779ce55bfd38860687 |
| 12681 | 1 | `witness[0].item_count` | `02` | 2 |
| 12682 | 1 | `witness[0][0].length` | `48` | 72 |
| 12683 | 72 | `witness[0][0].data` | `3045022100ba7b917ca9bd3883d26b9fedb1e628b2375f5518e78c012d8f70f78e49c4e27602204b5639948426f5df373788bbe87283fc42ed832f081cc097f4d2d07d322742b501` | 3045022100ba7b917ca9bd3883d26b9fedb1e628b2375f5518e78c012d8f70f78e49c4e27602204b5639948426f5df373788bbe87283fc42ed832f081cc097f4d2d07d322742b501 |
| 12755 | 1 | `witness[0][1].length` | `21` | 33 |
| 12756 | 33 | `witness[0][1].data` | `02254215e408029a4967347ced81f782a5898a952eb926bb60e1052f5d2a53a824` | 02254215e408029a4967347ced81f782a5898a952eb926bb60e1052f5d2a53a824 |
| 12789 | 4 | `tx.locktime` | `00000000` | 0 |

## 交易 46: `6a0780e0b2f4a18be4c743148db6df990d17a8d6aa6dbf7a22b35312cde63dc8`

| 偏移 | 字节数 | 字段 | 原始字节（线缆序） | 解释值 |
|---:|---:|---|---|---|
| 12793 | 4 | `tx.version` | `01000000` | 1 |
| 12797 | 1 | `tx.marker` | `00` | 0 |
| 12798 | 1 | `tx.flag` | `01` | 1 |
| 12799 | 1 | `tx.input_count` | `01` | 1 |
| 12800 | 32 | `vin[0].prev_txid` | `6b26605b2978fb65d35b1d806c2e026047d688b1792c151e585bc6d96a4cd227` | 27d24c6ad9c65b581e152c79b188d64760022e6c801d5bd365fb78295b60266b |
| 12832 | 4 | `vin[0].vout` | `01000000` | 1 |
| 12836 | 1 | `vin[0].scriptSig_length` | `00` | 0 |
| 12837 | 0 | `vin[0].scriptSig` | `（空）` |  |
| 12837 | 4 | `vin[0].sequence` | `ffffffff` | 4294967295 |
| 12841 | 1 | `tx.output_count` | `02` | 2 |
| 12842 | 8 | `vout[0].value` | `e803000000000000` | 1000 |
| 12850 | 1 | `vout[0].scriptPubKey_length` | `16` | 22 |
| 12851 | 22 | `vout[0].scriptPubKey` | `0014b0feeac2312d429d569da17b462144a5b9d0d90c` | OP_0 b0feeac2312d429d569da17b462144a5b9d0d90c |
| 12873 | 8 | `vout[1].value` | `0c7d010000000000` | 97548 |
| 12881 | 1 | `vout[1].scriptPubKey_length` | `16` | 22 |
| 12882 | 22 | `vout[1].scriptPubKey` | `00148aa3a74793710ebf620cb1779ce55bfd38860687` | OP_0 8aa3a74793710ebf620cb1779ce55bfd38860687 |
| 12904 | 1 | `witness[0].item_count` | `02` | 2 |
| 12905 | 1 | `witness[0][0].length` | `47` | 71 |
| 12906 | 71 | `witness[0][0].data` | `304402206b4288e8b412001d6aba0170fd1b863425fcc544ae9b798dd12a26d0631fed3602206dcde884de1059092ba41df3c7a3b718e94b5edba03598f204f6ab39145c4d9e01` | 304402206b4288e8b412001d6aba0170fd1b863425fcc544ae9b798dd12a26d0631fed3602206dcde884de1059092ba41df3c7a3b718e94b5edba03598f204f6ab39145c4d9e01 |
| 12977 | 1 | `witness[0][1].length` | `21` | 33 |
| 12978 | 33 | `witness[0][1].data` | `02254215e408029a4967347ced81f782a5898a952eb926bb60e1052f5d2a53a824` | 02254215e408029a4967347ced81f782a5898a952eb926bb60e1052f5d2a53a824 |
| 13011 | 4 | `tx.locktime` | `00000000` | 0 |

## 交易 47: `c6af3cd55454c5b3fa3a23e4ebc0dd5555bf24cd0e85f6f8d9842e98eaff36ca`

| 偏移 | 字节数 | 字段 | 原始字节（线缆序） | 解释值 |
|---:|---:|---|---|---|
| 13015 | 4 | `tx.version` | `01000000` | 1 |
| 13019 | 1 | `tx.marker` | `00` | 0 |
| 13020 | 1 | `tx.flag` | `01` | 1 |
| 13021 | 1 | `tx.input_count` | `01` | 1 |
| 13022 | 32 | `vin[0].prev_txid` | `d6342194127bcece9d124ca047a8af6d5f127f06763f96238c92c4ed7cb1bfae` | aebfb17cedc4928c23963f76067f125f6dafa847a04c129dcece7b12942134d6 |
| 13054 | 4 | `vin[0].vout` | `01000000` | 1 |
| 13058 | 1 | `vin[0].scriptSig_length` | `00` | 0 |
| 13059 | 0 | `vin[0].scriptSig` | `（空）` |  |
| 13059 | 4 | `vin[0].sequence` | `ffffffff` | 4294967295 |
| 13063 | 1 | `tx.output_count` | `02` | 2 |
| 13064 | 8 | `vout[0].value` | `e803000000000000` | 1000 |
| 13072 | 1 | `vout[0].scriptPubKey_length` | `16` | 22 |
| 13073 | 22 | `vout[0].scriptPubKey` | `0014b0feeac2312d429d569da17b462144a5b9d0d90c` | OP_0 b0feeac2312d429d569da17b462144a5b9d0d90c |
| 13095 | 8 | `vout[1].value` | `98c1010000000000` | 115096 |
| 13103 | 1 | `vout[1].scriptPubKey_length` | `16` | 22 |
| 13104 | 22 | `vout[1].scriptPubKey` | `00148aa3a74793710ebf620cb1779ce55bfd38860687` | OP_0 8aa3a74793710ebf620cb1779ce55bfd38860687 |
| 13126 | 1 | `witness[0].item_count` | `02` | 2 |
| 13127 | 1 | `witness[0][0].length` | `48` | 72 |
| 13128 | 72 | `witness[0][0].data` | `3045022100f1dd8eaca33d676c1c47d91276a899ea741e050f2fc9842f60133df08948a76f0220515d3128b1e670d6cf6b37391350f733c55bf6af2f9eabd50475e35cf9b3251101` | 3045022100f1dd8eaca33d676c1c47d91276a899ea741e050f2fc9842f60133df08948a76f0220515d3128b1e670d6cf6b37391350f733c55bf6af2f9eabd50475e35cf9b3251101 |
| 13200 | 1 | `witness[0][1].length` | `21` | 33 |
| 13201 | 33 | `witness[0][1].data` | `02254215e408029a4967347ced81f782a5898a952eb926bb60e1052f5d2a53a824` | 02254215e408029a4967347ced81f782a5898a952eb926bb60e1052f5d2a53a824 |
| 13234 | 4 | `tx.locktime` | `00000000` | 0 |

## 交易 48: `799f88ebf7cd627e6a44033bacc6d51ab9cfeba505cf3bef86abb367314037ce`

| 偏移 | 字节数 | 字段 | 原始字节（线缆序） | 解释值 |
|---:|---:|---|---|---|
| 13238 | 4 | `tx.version` | `01000000` | 1 |
| 13242 | 1 | `tx.marker` | `00` | 0 |
| 13243 | 1 | `tx.flag` | `01` | 1 |
| 13244 | 1 | `tx.input_count` | `01` | 1 |
| 13245 | 32 | `vin[0].prev_txid` | `a4caa622c89db95baa4261c136fc602e1f01c246554c888cae91c3f14a481c93` | 931c484af1c391ae8c884c5546c2011f2e60fc36c16142aa5bb99dc822a6caa4 |
| 13277 | 4 | `vin[0].vout` | `01000000` | 1 |
| 13281 | 1 | `vin[0].scriptSig_length` | `00` | 0 |
| 13282 | 0 | `vin[0].scriptSig` | `（空）` |  |
| 13282 | 4 | `vin[0].sequence` | `ffffffff` | 4294967295 |
| 13286 | 1 | `tx.output_count` | `02` | 2 |
| 13287 | 8 | `vout[0].value` | `e803000000000000` | 1000 |
| 13295 | 1 | `vout[0].scriptPubKey_length` | `16` | 22 |
| 13296 | 22 | `vout[0].scriptPubKey` | `0014b0feeac2312d429d569da17b462144a5b9d0d90c` | OP_0 b0feeac2312d429d569da17b462144a5b9d0d90c |
| 13318 | 8 | `vout[1].value` | `0c7d010000000000` | 97548 |
| 13326 | 1 | `vout[1].scriptPubKey_length` | `16` | 22 |
| 13327 | 22 | `vout[1].scriptPubKey` | `00148aa3a74793710ebf620cb1779ce55bfd38860687` | OP_0 8aa3a74793710ebf620cb1779ce55bfd38860687 |
| 13349 | 1 | `witness[0].item_count` | `02` | 2 |
| 13350 | 1 | `witness[0][0].length` | `48` | 72 |
| 13351 | 72 | `witness[0][0].data` | `3045022100f2aafeddddd91435d27561c7a58cb4fbaa88d2629663859802810016edf6a95902203e9c0d7af29ed609122c6dd9d9c826370759c2cbb87330193e3cfaca6f3302e801` | 3045022100f2aafeddddd91435d27561c7a58cb4fbaa88d2629663859802810016edf6a95902203e9c0d7af29ed609122c6dd9d9c826370759c2cbb87330193e3cfaca6f3302e801 |
| 13423 | 1 | `witness[0][1].length` | `21` | 33 |
| 13424 | 33 | `witness[0][1].data` | `02254215e408029a4967347ced81f782a5898a952eb926bb60e1052f5d2a53a824` | 02254215e408029a4967347ced81f782a5898a952eb926bb60e1052f5d2a53a824 |
| 13457 | 4 | `tx.locktime` | `00000000` | 0 |

## 交易 49: `d917cafad619b8e2b0eeee381818e56cb39f5d5026750402cfc7c13b8398cce0`

| 偏移 | 字节数 | 字段 | 原始字节（线缆序） | 解释值 |
|---:|---:|---|---|---|
| 13461 | 4 | `tx.version` | `01000000` | 1 |
| 13465 | 1 | `tx.marker` | `00` | 0 |
| 13466 | 1 | `tx.flag` | `01` | 1 |
| 13467 | 1 | `tx.input_count` | `01` | 1 |
| 13468 | 32 | `vin[0].prev_txid` | `7cabe8babdbfce39e10f31397798aab28525f4c42e3242274e3563f6445b3b45` | 453b5b44f663354e2742322ec4f42585b2aa987739310fe139cebfbdbae8ab7c |
| 13500 | 4 | `vin[0].vout` | `01000000` | 1 |
| 13504 | 1 | `vin[0].scriptSig_length` | `00` | 0 |
| 13505 | 0 | `vin[0].scriptSig` | `（空）` |  |
| 13505 | 4 | `vin[0].sequence` | `ffffffff` | 4294967295 |
| 13509 | 1 | `tx.output_count` | `02` | 2 |
| 13510 | 8 | `vout[0].value` | `e803000000000000` | 1000 |
| 13518 | 1 | `vout[0].scriptPubKey_length` | `16` | 22 |
| 13519 | 22 | `vout[0].scriptPubKey` | `0014b0feeac2312d429d569da17b462144a5b9d0d90c` | OP_0 b0feeac2312d429d569da17b462144a5b9d0d90c |
| 13541 | 8 | `vout[1].value` | `0c7d010000000000` | 97548 |
| 13549 | 1 | `vout[1].scriptPubKey_length` | `16` | 22 |
| 13550 | 22 | `vout[1].scriptPubKey` | `00148aa3a74793710ebf620cb1779ce55bfd38860687` | OP_0 8aa3a74793710ebf620cb1779ce55bfd38860687 |
| 13572 | 1 | `witness[0].item_count` | `02` | 2 |
| 13573 | 1 | `witness[0][0].length` | `47` | 71 |
| 13574 | 71 | `witness[0][0].data` | `30440220416c8352a53233100a77d6379851c2e9aedd1f526f9fe1a42aa4e43860ec957102202ea9d08522b201092164a149fe208f4f85e588a5342b116f30e6f7a7d5885c1801` | 30440220416c8352a53233100a77d6379851c2e9aedd1f526f9fe1a42aa4e43860ec957102202ea9d08522b201092164a149fe208f4f85e588a5342b116f30e6f7a7d5885c1801 |
| 13645 | 1 | `witness[0][1].length` | `21` | 33 |
| 13646 | 33 | `witness[0][1].data` | `02254215e408029a4967347ced81f782a5898a952eb926bb60e1052f5d2a53a824` | 02254215e408029a4967347ced81f782a5898a952eb926bb60e1052f5d2a53a824 |
| 13679 | 4 | `tx.locktime` | `00000000` | 0 |

## 交易 50: `16d7bda4da6c8b0367b3814c382b719882e02f70be390d947977e8aed24b55e4`

| 偏移 | 字节数 | 字段 | 原始字节（线缆序） | 解释值 |
|---:|---:|---|---|---|
| 13683 | 4 | `tx.version` | `01000000` | 1 |
| 13687 | 1 | `tx.marker` | `00` | 0 |
| 13688 | 1 | `tx.flag` | `01` | 1 |
| 13689 | 1 | `tx.input_count` | `01` | 1 |
| 13690 | 32 | `vin[0].prev_txid` | `89d76346c6137589a98c0c8427a61afa909127654dceede64627f9a6e17e7654` | 54767ee1a6f92746e6edce4d65279190fa1aa627840c8ca9897513c64663d789 |
| 13722 | 4 | `vin[0].vout` | `01000000` | 1 |
| 13726 | 1 | `vin[0].scriptSig_length` | `00` | 0 |
| 13727 | 0 | `vin[0].scriptSig` | `（空）` |  |
| 13727 | 4 | `vin[0].sequence` | `ffffffff` | 4294967295 |
| 13731 | 1 | `tx.output_count` | `02` | 2 |
| 13732 | 8 | `vout[0].value` | `e803000000000000` | 1000 |
| 13740 | 1 | `vout[0].scriptPubKey_length` | `16` | 22 |
| 13741 | 22 | `vout[0].scriptPubKey` | `0014b0feeac2312d429d569da17b462144a5b9d0d90c` | OP_0 b0feeac2312d429d569da17b462144a5b9d0d90c |
| 13763 | 8 | `vout[1].value` | `7a870e0000000000` | 952186 |
| 13771 | 1 | `vout[1].scriptPubKey_length` | `16` | 22 |
| 13772 | 22 | `vout[1].scriptPubKey` | `00148aa3a74793710ebf620cb1779ce55bfd38860687` | OP_0 8aa3a74793710ebf620cb1779ce55bfd38860687 |
| 13794 | 1 | `witness[0].item_count` | `02` | 2 |
| 13795 | 1 | `witness[0][0].length` | `47` | 71 |
| 13796 | 71 | `witness[0][0].data` | `30440220322e3f9a2e4beb00ba4a39fec77559e3c4aaa57303e4cf441e7e3e421b58a9ab022056229e8957ff66491f54329abc38f4e344f3238d2e9cb8903e51c921ff6371e401` | 30440220322e3f9a2e4beb00ba4a39fec77559e3c4aaa57303e4cf441e7e3e421b58a9ab022056229e8957ff66491f54329abc38f4e344f3238d2e9cb8903e51c921ff6371e401 |
| 13867 | 1 | `witness[0][1].length` | `21` | 33 |
| 13868 | 33 | `witness[0][1].data` | `02254215e408029a4967347ced81f782a5898a952eb926bb60e1052f5d2a53a824` | 02254215e408029a4967347ced81f782a5898a952eb926bb60e1052f5d2a53a824 |
| 13901 | 4 | `tx.locktime` | `00000000` | 0 |

## 交易 51: `1a160bb2aa636043d91354677c1e100133732c20b25786b4f64389ed95a75fe4`

| 偏移 | 字节数 | 字段 | 原始字节（线缆序） | 解释值 |
|---:|---:|---|---|---|
| 13905 | 4 | `tx.version` | `01000000` | 1 |
| 13909 | 1 | `tx.marker` | `00` | 0 |
| 13910 | 1 | `tx.flag` | `01` | 1 |
| 13911 | 1 | `tx.input_count` | `01` | 1 |
| 13912 | 32 | `vin[0].prev_txid` | `54d9660da090baf49b710323fa0d3f0b92b1fcd20a8309e743c64a4103ed2376` | 7623ed03414ac643e709830ad2fcb1920b3f0dfa2303719bf4ba90a00d66d954 |
| 13944 | 4 | `vin[0].vout` | `01000000` | 1 |
| 13948 | 1 | `vin[0].scriptSig_length` | `00` | 0 |
| 13949 | 0 | `vin[0].scriptSig` | `（空）` |  |
| 13949 | 4 | `vin[0].sequence` | `ffffffff` | 4294967295 |
| 13953 | 1 | `tx.output_count` | `02` | 2 |
| 13954 | 8 | `vout[0].value` | `e803000000000000` | 1000 |
| 13962 | 1 | `vout[0].scriptPubKey_length` | `16` | 22 |
| 13963 | 22 | `vout[0].scriptPubKey` | `0014b0feeac2312d429d569da17b462144a5b9d0d90c` | OP_0 b0feeac2312d429d569da17b462144a5b9d0d90c |
| 13985 | 8 | `vout[1].value` | `17de010000000000` | 122391 |
| 13993 | 1 | `vout[1].scriptPubKey_length` | `16` | 22 |
| 13994 | 22 | `vout[1].scriptPubKey` | `00148aa3a74793710ebf620cb1779ce55bfd38860687` | OP_0 8aa3a74793710ebf620cb1779ce55bfd38860687 |
| 14016 | 1 | `witness[0].item_count` | `02` | 2 |
| 14017 | 1 | `witness[0][0].length` | `47` | 71 |
| 14018 | 71 | `witness[0][0].data` | `304402204f84879c61c038361af70992947f7e8a3d2c5b28d042113b9e2ce64778203fa802203df47f7eef2464834e4b6b94ef2d87eb58347e52afc13bcbe128527e91456b0f01` | 304402204f84879c61c038361af70992947f7e8a3d2c5b28d042113b9e2ce64778203fa802203df47f7eef2464834e4b6b94ef2d87eb58347e52afc13bcbe128527e91456b0f01 |
| 14089 | 1 | `witness[0][1].length` | `21` | 33 |
| 14090 | 33 | `witness[0][1].data` | `02254215e408029a4967347ced81f782a5898a952eb926bb60e1052f5d2a53a824` | 02254215e408029a4967347ced81f782a5898a952eb926bb60e1052f5d2a53a824 |
| 14123 | 4 | `tx.locktime` | `00000000` | 0 |

## 交易 52: `e59f77901417c466e25a7691560b34dd4854a2585760616cfdb607c8a31fc5e9`

| 偏移 | 字节数 | 字段 | 原始字节（线缆序） | 解释值 |
|---:|---:|---|---|---|
| 14127 | 4 | `tx.version` | `01000000` | 1 |
| 14131 | 1 | `tx.marker` | `00` | 0 |
| 14132 | 1 | `tx.flag` | `01` | 1 |
| 14133 | 1 | `tx.input_count` | `01` | 1 |
| 14134 | 32 | `vin[0].prev_txid` | `5500ea6651193d750f8e2a74e5ab78ec3f76b6551edf9a00258a430ea0b56f41` | 416fb5a00e438a25009adf1e55b6763fec78abe5742a8e0f753d195166ea0055 |
| 14166 | 4 | `vin[0].vout` | `01000000` | 1 |
| 14170 | 1 | `vin[0].scriptSig_length` | `00` | 0 |
| 14171 | 0 | `vin[0].scriptSig` | `（空）` |  |
| 14171 | 4 | `vin[0].sequence` | `ffffffff` | 4294967295 |
| 14175 | 1 | `tx.output_count` | `02` | 2 |
| 14176 | 8 | `vout[0].value` | `e803000000000000` | 1000 |
| 14184 | 1 | `vout[0].scriptPubKey_length` | `16` | 22 |
| 14185 | 22 | `vout[0].scriptPubKey` | `0014b0feeac2312d429d569da17b462144a5b9d0d90c` | OP_0 b0feeac2312d429d569da17b462144a5b9d0d90c |
| 14207 | 8 | `vout[1].value` | `04fb140000000000` | 1374980 |
| 14215 | 1 | `vout[1].scriptPubKey_length` | `16` | 22 |
| 14216 | 22 | `vout[1].scriptPubKey` | `00148aa3a74793710ebf620cb1779ce55bfd38860687` | OP_0 8aa3a74793710ebf620cb1779ce55bfd38860687 |
| 14238 | 1 | `witness[0].item_count` | `02` | 2 |
| 14239 | 1 | `witness[0][0].length` | `48` | 72 |
| 14240 | 72 | `witness[0][0].data` | `304502210089bdc03ca453a531f7227c33025ef3c13604f86f5e84e96900324f5c54c1c1d00220378d6da04bed9aa2cc3bc703dd1992eb2479b4add1239e640785fa868af8871401` | 304502210089bdc03ca453a531f7227c33025ef3c13604f86f5e84e96900324f5c54c1c1d00220378d6da04bed9aa2cc3bc703dd1992eb2479b4add1239e640785fa868af8871401 |
| 14312 | 1 | `witness[0][1].length` | `21` | 33 |
| 14313 | 33 | `witness[0][1].data` | `02254215e408029a4967347ced81f782a5898a952eb926bb60e1052f5d2a53a824` | 02254215e408029a4967347ced81f782a5898a952eb926bb60e1052f5d2a53a824 |
| 14346 | 4 | `tx.locktime` | `00000000` | 0 |

## 交易 53: `249c30ddc7156efac6f60671c94f5615887256ec3d6dac10e961d98ab22829f4`

| 偏移 | 字节数 | 字段 | 原始字节（线缆序） | 解释值 |
|---:|---:|---|---|---|
| 14350 | 4 | `tx.version` | `01000000` | 1 |
| 14354 | 1 | `tx.marker` | `00` | 0 |
| 14355 | 1 | `tx.flag` | `01` | 1 |
| 14356 | 1 | `tx.input_count` | `01` | 1 |
| 14357 | 32 | `vin[0].prev_txid` | `3e8f3cd2220b984de7159221e0a3e8c2a4bf0f7b8e57065350c86670e22b6410` | 10642be27066c8505306578e7b0fbfa4c2e8a3e0219215e74d980b22d23c8f3e |
| 14389 | 4 | `vin[0].vout` | `01000000` | 1 |
| 14393 | 1 | `vin[0].scriptSig_length` | `00` | 0 |
| 14394 | 0 | `vin[0].scriptSig` | `（空）` |  |
| 14394 | 4 | `vin[0].sequence` | `ffffffff` | 4294967295 |
| 14398 | 1 | `tx.output_count` | `02` | 2 |
| 14399 | 8 | `vout[0].value` | `e803000000000000` | 1000 |
| 14407 | 1 | `vout[0].scriptPubKey_length` | `16` | 22 |
| 14408 | 22 | `vout[0].scriptPubKey` | `0014b0feeac2312d429d569da17b462144a5b9d0d90c` | OP_0 b0feeac2312d429d569da17b462144a5b9d0d90c |
| 14430 | 8 | `vout[1].value` | `0c7d010000000000` | 97548 |
| 14438 | 1 | `vout[1].scriptPubKey_length` | `16` | 22 |
| 14439 | 22 | `vout[1].scriptPubKey` | `00148aa3a74793710ebf620cb1779ce55bfd38860687` | OP_0 8aa3a74793710ebf620cb1779ce55bfd38860687 |
| 14461 | 1 | `witness[0].item_count` | `02` | 2 |
| 14462 | 1 | `witness[0][0].length` | `48` | 72 |
| 14463 | 72 | `witness[0][0].data` | `3045022100a989757124c9e65bc7754168b843ef91a831f25915f1c1173f4e1fcd6d86b59602200cef981829f1f24b07a72f6de5e6e2ccbd37cf62d8d7c7226b3e3aa1231de43c01` | 3045022100a989757124c9e65bc7754168b843ef91a831f25915f1c1173f4e1fcd6d86b59602200cef981829f1f24b07a72f6de5e6e2ccbd37cf62d8d7c7226b3e3aa1231de43c01 |
| 14535 | 1 | `witness[0][1].length` | `21` | 33 |
| 14536 | 33 | `witness[0][1].data` | `02254215e408029a4967347ced81f782a5898a952eb926bb60e1052f5d2a53a824` | 02254215e408029a4967347ced81f782a5898a952eb926bb60e1052f5d2a53a824 |
| 14569 | 4 | `tx.locktime` | `00000000` | 0 |

## 交易 54: `c8e391d1a180554f6af380090ab55c7c39130a551f1ae8752b9997009ac3c2f4`

| 偏移 | 字节数 | 字段 | 原始字节（线缆序） | 解释值 |
|---:|---:|---|---|---|
| 14573 | 4 | `tx.version` | `01000000` | 1 |
| 14577 | 1 | `tx.marker` | `00` | 0 |
| 14578 | 1 | `tx.flag` | `01` | 1 |
| 14579 | 1 | `tx.input_count` | `01` | 1 |
| 14580 | 32 | `vin[0].prev_txid` | `428dee2f31ab6fdae1f60f4aa37618a027883d1ad9b254d6bf77e8dc12dca0f8` | f8a0dc12dce877bfd654b2d91a3d8827a01876a34a0ff6e1da6fab312fee8d42 |
| 14612 | 4 | `vin[0].vout` | `01000000` | 1 |
| 14616 | 1 | `vin[0].scriptSig_length` | `00` | 0 |
| 14617 | 0 | `vin[0].scriptSig` | `（空）` |  |
| 14617 | 4 | `vin[0].sequence` | `ffffffff` | 4294967295 |
| 14621 | 1 | `tx.output_count` | `02` | 2 |
| 14622 | 8 | `vout[0].value` | `e803000000000000` | 1000 |
| 14630 | 1 | `vout[0].scriptPubKey_length` | `16` | 22 |
| 14631 | 22 | `vout[0].scriptPubKey` | `0014b0feeac2312d429d569da17b462144a5b9d0d90c` | OP_0 b0feeac2312d429d569da17b462144a5b9d0d90c |
| 14653 | 8 | `vout[1].value` | `0c7d010000000000` | 97548 |
| 14661 | 1 | `vout[1].scriptPubKey_length` | `16` | 22 |
| 14662 | 22 | `vout[1].scriptPubKey` | `00148aa3a74793710ebf620cb1779ce55bfd38860687` | OP_0 8aa3a74793710ebf620cb1779ce55bfd38860687 |
| 14684 | 1 | `witness[0].item_count` | `02` | 2 |
| 14685 | 1 | `witness[0][0].length` | `47` | 71 |
| 14686 | 71 | `witness[0][0].data` | `304402206524fd514107cec55edefaf87d4acc17e0a2b67bec4718fdb2a99d67ba3d733b022071f99dc62f3dd3f9cfd9e3dc9bdcc6c4f146b069ee133f5b156c13c0b8565b8001` | 304402206524fd514107cec55edefaf87d4acc17e0a2b67bec4718fdb2a99d67ba3d733b022071f99dc62f3dd3f9cfd9e3dc9bdcc6c4f146b069ee133f5b156c13c0b8565b8001 |
| 14757 | 1 | `witness[0][1].length` | `21` | 33 |
| 14758 | 33 | `witness[0][1].data` | `02254215e408029a4967347ced81f782a5898a952eb926bb60e1052f5d2a53a824` | 02254215e408029a4967347ced81f782a5898a952eb926bb60e1052f5d2a53a824 |
| 14791 | 4 | `tx.locktime` | `00000000` | 0 |

## 交易 55: `5888c8afc6944344f43a418c1920d202a9a981d5dd9b3cbac1f281cd10e0ecf8`

| 偏移 | 字节数 | 字段 | 原始字节（线缆序） | 解释值 |
|---:|---:|---|---|---|
| 14795 | 4 | `tx.version` | `01000000` | 1 |
| 14799 | 1 | `tx.marker` | `00` | 0 |
| 14800 | 1 | `tx.flag` | `01` | 1 |
| 14801 | 1 | `tx.input_count` | `01` | 1 |
| 14802 | 32 | `vin[0].prev_txid` | `4469848906c477999a0be25bae08c728e5a84e480b8643e85f7ddb391ba84bda` | da4ba81b39db7d5fe843860b484ea8e528c708ae5be20b9a9977c40689846944 |
| 14834 | 4 | `vin[0].vout` | `01000000` | 1 |
| 14838 | 1 | `vin[0].scriptSig_length` | `00` | 0 |
| 14839 | 0 | `vin[0].scriptSig` | `（空）` |  |
| 14839 | 4 | `vin[0].sequence` | `ffffffff` | 4294967295 |
| 14843 | 1 | `tx.output_count` | `02` | 2 |
| 14844 | 8 | `vout[0].value` | `e803000000000000` | 1000 |
| 14852 | 1 | `vout[0].scriptPubKey_length` | `16` | 22 |
| 14853 | 22 | `vout[0].scriptPubKey` | `0014b0feeac2312d429d569da17b462144a5b9d0d90c` | OP_0 b0feeac2312d429d569da17b462144a5b9d0d90c |
| 14875 | 8 | `vout[1].value` | `0c7d010000000000` | 97548 |
| 14883 | 1 | `vout[1].scriptPubKey_length` | `16` | 22 |
| 14884 | 22 | `vout[1].scriptPubKey` | `00148aa3a74793710ebf620cb1779ce55bfd38860687` | OP_0 8aa3a74793710ebf620cb1779ce55bfd38860687 |
| 14906 | 1 | `witness[0].item_count` | `02` | 2 |
| 14907 | 1 | `witness[0][0].length` | `47` | 71 |
| 14908 | 71 | `witness[0][0].data` | `30440220469b10a89a9ac3c5047969e82782771b36a59ee02ce5de5e9edc8bb3a9412f5802206ce38b10aa42126bad1ca735e4a16c710771bef73492799ac8110089ad07a20801` | 30440220469b10a89a9ac3c5047969e82782771b36a59ee02ce5de5e9edc8bb3a9412f5802206ce38b10aa42126bad1ca735e4a16c710771bef73492799ac8110089ad07a20801 |
| 14979 | 1 | `witness[0][1].length` | `21` | 33 |
| 14980 | 33 | `witness[0][1].data` | `02254215e408029a4967347ced81f782a5898a952eb926bb60e1052f5d2a53a824` | 02254215e408029a4967347ced81f782a5898a952eb926bb60e1052f5d2a53a824 |
| 15013 | 4 | `tx.locktime` | `00000000` | 0 |

## 交易 56: `9365907e60f69a4b7030238eaa88d7acf4f999e0e785e9b4c6c555265156d3fe`

| 偏移 | 字节数 | 字段 | 原始字节（线缆序） | 解释值 |
|---:|---:|---|---|---|
| 15017 | 4 | `tx.version` | `01000000` | 1 |
| 15021 | 1 | `tx.marker` | `00` | 0 |
| 15022 | 1 | `tx.flag` | `01` | 1 |
| 15023 | 1 | `tx.input_count` | `01` | 1 |
| 15024 | 32 | `vin[0].prev_txid` | `749ffc5a6320ba3ac76f62fbab664173367524cc933427d00aa7327c894913fc` | fc1349897c32a70ad0273493cc247536734166abfb626fc73aba20635afc9f74 |
| 15056 | 4 | `vin[0].vout` | `01000000` | 1 |
| 15060 | 1 | `vin[0].scriptSig_length` | `00` | 0 |
| 15061 | 0 | `vin[0].scriptSig` | `（空）` |  |
| 15061 | 4 | `vin[0].sequence` | `ffffffff` | 4294967295 |
| 15065 | 1 | `tx.output_count` | `02` | 2 |
| 15066 | 8 | `vout[0].value` | `e803000000000000` | 1000 |
| 15074 | 1 | `vout[0].scriptPubKey_length` | `16` | 22 |
| 15075 | 22 | `vout[0].scriptPubKey` | `0014b0feeac2312d429d569da17b462144a5b9d0d90c` | OP_0 b0feeac2312d429d569da17b462144a5b9d0d90c |
| 15097 | 8 | `vout[1].value` | `0c7d010000000000` | 97548 |
| 15105 | 1 | `vout[1].scriptPubKey_length` | `16` | 22 |
| 15106 | 22 | `vout[1].scriptPubKey` | `00148aa3a74793710ebf620cb1779ce55bfd38860687` | OP_0 8aa3a74793710ebf620cb1779ce55bfd38860687 |
| 15128 | 1 | `witness[0].item_count` | `02` | 2 |
| 15129 | 1 | `witness[0][0].length` | `47` | 71 |
| 15130 | 71 | `witness[0][0].data` | `3044022072b4447ed4304fae0fcf273372928a9e5d0d1d044b05d52639fddee9aaca216f022037d59813b33c94944d35789ea03d5ebc92bf3c9366d989046fd3d14ed061e22f01` | 3044022072b4447ed4304fae0fcf273372928a9e5d0d1d044b05d52639fddee9aaca216f022037d59813b33c94944d35789ea03d5ebc92bf3c9366d989046fd3d14ed061e22f01 |
| 15201 | 1 | `witness[0][1].length` | `21` | 33 |
| 15202 | 33 | `witness[0][1].data` | `02254215e408029a4967347ced81f782a5898a952eb926bb60e1052f5d2a53a824` | 02254215e408029a4967347ced81f782a5898a952eb926bb60e1052f5d2a53a824 |
| 15235 | 4 | `tx.locktime` | `00000000` | 0 |

## 交易 57: `998055d52c50470f1af97118a40bd00f222a0559bbb25f1f3c66fb5018c6a48b`

| 偏移 | 字节数 | 字段 | 原始字节（线缆序） | 解释值 |
|---:|---:|---|---|---|
| 15239 | 4 | `tx.version` | `02000000` | 2 |
| 15243 | 1 | `tx.marker` | `00` | 0 |
| 15244 | 1 | `tx.flag` | `01` | 1 |
| 15245 | 1 | `tx.input_count` | `02` | 2 |
| 15246 | 32 | `vin[0].prev_txid` | `6c051d80cec5eb9deb1370cf859f086cba9a2b5cb80b3e17e662fc8520f7477e` | 7e47f72085fc62e6173e0bb85c2b9aba6c089f85cf7013eb9debc5ce801d056c |
| 15278 | 4 | `vin[0].vout` | `00000000` | 0 |
| 15282 | 1 | `vin[0].scriptSig_length` | `00` | 0 |
| 15283 | 0 | `vin[0].scriptSig` | `（空）` |  |
| 15283 | 4 | `vin[0].sequence` | `ffffffff` | 4294967295 |
| 15287 | 32 | `vin[1].prev_txid` | `1cd6ab497e5e50cbacc89314adb2a26e7379a61a252763fa66e22c2a2a572a0c` | 0c2a572a2a2ce266fa6327251aa679736ea2b2ad1493c8accb505e7e49abd61c |
| 15319 | 4 | `vin[1].vout` | `01000000` | 1 |
| 15323 | 1 | `vin[1].scriptSig_length` | `00` | 0 |
| 15324 | 0 | `vin[1].scriptSig` | `（空）` |  |
| 15324 | 4 | `vin[1].sequence` | `ffffffff` | 4294967295 |
| 15328 | 1 | `tx.output_count` | `02` | 2 |
| 15329 | 8 | `vout[0].value` | `1027000000000000` | 10000 |
| 15337 | 1 | `vout[0].scriptPubKey_length` | `16` | 22 |
| 15338 | 22 | `vout[0].scriptPubKey` | `0014c55d54bc31ebd82c9cbefecd7d44f5fc1d671501` | OP_0 c55d54bc31ebd82c9cbefecd7d44f5fc1d671501 |
| 15360 | 8 | `vout[1].value` | `0239a70500000000` | 94845186 |
| 15368 | 1 | `vout[1].scriptPubKey_length` | `16` | 22 |
| 15369 | 22 | `vout[1].scriptPubKey` | `00147e00225f756855e4479d3a9789c264bad9afc60a` | OP_0 7e00225f756855e4479d3a9789c264bad9afc60a |
| 15391 | 1 | `witness[0].item_count` | `02` | 2 |
| 15392 | 1 | `witness[0][0].length` | `48` | 72 |
| 15393 | 72 | `witness[0][0].data` | `30450221009d36aec214de9d9e53a5065d2e2113155c533831421466b63af3122d71e282500220462de2c26fae7f3fd10b1c47cf8610140cbccdfedec563d0a58854798c9e825901` | 30450221009d36aec214de9d9e53a5065d2e2113155c533831421466b63af3122d71e282500220462de2c26fae7f3fd10b1c47cf8610140cbccdfedec563d0a58854798c9e825901 |
| 15465 | 1 | `witness[0][1].length` | `21` | 33 |
| 15466 | 33 | `witness[0][1].data` | `03d136885b7873216c96270ae2ba95d82e51d335da6efe89484b5d13474359873a` | 03d136885b7873216c96270ae2ba95d82e51d335da6efe89484b5d13474359873a |
| 15499 | 1 | `witness[1].item_count` | `02` | 2 |
| 15500 | 1 | `witness[1][0].length` | `48` | 72 |
| 15501 | 72 | `witness[1][0].data` | `3045022100f4b55cb491aac01acbf5d787cf0109a5535503e7a9295b249dce60e6c976f1b50220013b6e68640211e38ed1dce4442e85d6e6ce8322451cd135e65bbe4c17921b6b01` | 3045022100f4b55cb491aac01acbf5d787cf0109a5535503e7a9295b249dce60e6c976f1b50220013b6e68640211e38ed1dce4442e85d6e6ce8322451cd135e65bbe4c17921b6b01 |
| 15573 | 1 | `witness[1][1].length` | `21` | 33 |
| 15574 | 33 | `witness[1][1].data` | `03d136885b7873216c96270ae2ba95d82e51d335da6efe89484b5d13474359873a` | 03d136885b7873216c96270ae2ba95d82e51d335da6efe89484b5d13474359873a |
| 15607 | 4 | `tx.locktime` | `00000000` | 0 |

## 交易 58: `585074cca724f61efb0f26c3153f224f46414dd37899200b219121c8003b2b90`

| 偏移 | 字节数 | 字段 | 原始字节（线缆序） | 解释值 |
|---:|---:|---|---|---|
| 15611 | 4 | `tx.version` | `01000000` | 1 |
| 15615 | 1 | `tx.marker` | `00` | 0 |
| 15616 | 1 | `tx.flag` | `01` | 1 |
| 15617 | 1 | `tx.input_count` | `01` | 1 |
| 15618 | 32 | `vin[0].prev_txid` | `740ad4327baea38f9a9bea4fac5758e06fb59cce93c88620e9d8b44e5bc0294d` | 4d29c05b4eb4d8e92086c893ce9cb56fe05857ac4fea9b9a8fa3ae7b32d40a74 |
| 15650 | 4 | `vin[0].vout` | `01000000` | 1 |
| 15654 | 1 | `vin[0].scriptSig_length` | `00` | 0 |
| 15655 | 0 | `vin[0].scriptSig` | `（空）` |  |
| 15655 | 4 | `vin[0].sequence` | `ffffffff` | 4294967295 |
| 15659 | 1 | `tx.output_count` | `02` | 2 |
| 15660 | 8 | `vout[0].value` | `204e000000000000` | 20000 |
| 15668 | 1 | `vout[0].scriptPubKey_length` | `16` | 22 |
| 15669 | 22 | `vout[0].scriptPubKey` | `0014c18a6d2731d584f75179d098644da98c2fb03950` | OP_0 c18a6d2731d584f75179d098644da98c2fb03950 |
| 15691 | 8 | `vout[1].value` | `ba14010000000000` | 70842 |
| 15699 | 1 | `vout[1].scriptPubKey_length` | `16` | 22 |
| 15700 | 22 | `vout[1].scriptPubKey` | `0014f1fdcf8a84c85cb8577bb6432774246877282ed7` | OP_0 f1fdcf8a84c85cb8577bb6432774246877282ed7 |
| 15722 | 1 | `witness[0].item_count` | `02` | 2 |
| 15723 | 1 | `witness[0][0].length` | `47` | 71 |
| 15724 | 71 | `witness[0][0].data` | `30440220663f0937cb975b5ffdabe9afb3f640f8dcd342573b635d9474e580f4d40b91c602202011e632738aecfd1298ac772aee9bfa4520f4b7a7894479535bfdfc10f5ecaa01` | 30440220663f0937cb975b5ffdabe9afb3f640f8dcd342573b635d9474e580f4d40b91c602202011e632738aecfd1298ac772aee9bfa4520f4b7a7894479535bfdfc10f5ecaa01 |
| 15795 | 1 | `witness[0][1].length` | `21` | 33 |
| 15796 | 33 | `witness[0][1].data` | `0304b74c1bda977f447b7c262f8b0f59becd4b21fc48b4c2df77bc87bd356bce8d` | 0304b74c1bda977f447b7c262f8b0f59becd4b21fc48b4c2df77bc87bd356bce8d |
| 15829 | 4 | `tx.locktime` | `00000000` | 0 |

## 交易 59: `b973751d5abef63ad32fcc0d3142d2b7a5a53a0ba49baf5ce7832585658c4eb9`

| 偏移 | 字节数 | 字段 | 原始字节（线缆序） | 解释值 |
|---:|---:|---|---|---|
| 15833 | 4 | `tx.version` | `01000000` | 1 |
| 15837 | 1 | `tx.marker` | `00` | 0 |
| 15838 | 1 | `tx.flag` | `01` | 1 |
| 15839 | 1 | `tx.input_count` | `01` | 1 |
| 15840 | 32 | `vin[0].prev_txid` | `f4561c48e96d149446200b4e853da9da496b50242400068e6232e06792cd579c` | 9c57cd9267e032628e06002424506b49daa93d854e0b204694146de9481c56f4 |
| 15872 | 4 | `vin[0].vout` | `01000000` | 1 |
| 15876 | 1 | `vin[0].scriptSig_length` | `00` | 0 |
| 15877 | 0 | `vin[0].scriptSig` | `（空）` |  |
| 15877 | 4 | `vin[0].sequence` | `ffffffff` | 4294967295 |
| 15881 | 1 | `tx.output_count` | `02` | 2 |
| 15882 | 8 | `vout[0].value` | `9605000000000000` | 1430 |
| 15890 | 1 | `vout[0].scriptPubKey_length` | `16` | 22 |
| 15891 | 22 | `vout[0].scriptPubKey` | `00146b3f659f2f847e60f5018a06d802bace6b06dbb7` | OP_0 6b3f659f2f847e60f5018a06d802bace6b06dbb7 |
| 15913 | 8 | `vout[1].value` | `14d9000000000000` | 55572 |
| 15921 | 1 | `vout[1].scriptPubKey_length` | `16` | 22 |
| 15922 | 22 | `vout[1].scriptPubKey` | `00147eccf4ebeab47cc675778a47de5fd115d81aa86c` | OP_0 7eccf4ebeab47cc675778a47de5fd115d81aa86c |
| 15944 | 1 | `witness[0].item_count` | `02` | 2 |
| 15945 | 1 | `witness[0][0].length` | `47` | 71 |
| 15946 | 71 | `witness[0][0].data` | `3044022004e13c8f8afbd94f4bbb39d3201ea564338f6beb66edaa2a39909dd7c65cac1902200433fdd7beec926701d3962038b67aa2eec44d396b7cf67440b43bd120b3b1f901` | 3044022004e13c8f8afbd94f4bbb39d3201ea564338f6beb66edaa2a39909dd7c65cac1902200433fdd7beec926701d3962038b67aa2eec44d396b7cf67440b43bd120b3b1f901 |
| 16017 | 1 | `witness[0][1].length` | `21` | 33 |
| 16018 | 33 | `witness[0][1].data` | `039f842347cf4da3ef9f974492c1a7f77102d9921366bb050f18c29af47924b8b0` | 039f842347cf4da3ef9f974492c1a7f77102d9921366bb050f18c29af47924b8b0 |
| 16051 | 4 | `tx.locktime` | `00000000` | 0 |

## 交易 60: `de3fe12f72e9da8c47074e80744507730e0b406633a64bf522b34485309e8b25`

| 偏移 | 字节数 | 字段 | 原始字节（线缆序） | 解释值 |
|---:|---:|---|---|---|
| 16055 | 4 | `tx.version` | `02000000` | 2 |
| 16059 | 1 | `tx.marker` | `00` | 0 |
| 16060 | 1 | `tx.flag` | `01` | 1 |
| 16061 | 1 | `tx.input_count` | `01` | 1 |
| 16062 | 32 | `vin[0].prev_txid` | `b94e8c65852583e75caf9ba40b3aa5a5b7d242310dcc2fd33af6be5a1d7573b9` | b973751d5abef63ad32fcc0d3142d2b7a5a53a0ba49baf5ce7832585658c4eb9 |
| 16094 | 4 | `vin[0].vout` | `00000000` | 0 |
| 16098 | 1 | `vin[0].scriptSig_length` | `00` | 0 |
| 16099 | 0 | `vin[0].scriptSig` | `（空）` |  |
| 16099 | 4 | `vin[0].sequence` | `ffffffff` | 4294967295 |
| 16103 | 1 | `tx.output_count` | `01` | 1 |
| 16104 | 8 | `vout[0].value` | `0705000000000000` | 1287 |
| 16112 | 1 | `vout[0].scriptPubKey_length` | `22` | 34 |
| 16113 | 34 | `vout[0].scriptPubKey` | `0020fcd6cce9ec5376ac61d37c83c3c8636c4c21a4d1e56e1dbfbdbe460887ebf7c6` | OP_0 fcd6cce9ec5376ac61d37c83c3c8636c4c21a4d1e56e1dbfbdbe460887ebf7c6 |
| 16147 | 1 | `witness[0].item_count` | `02` | 2 |
| 16148 | 1 | `witness[0][0].length` | `47` | 71 |
| 16149 | 71 | `witness[0][0].data` | `304402204fa70998c592a21108798b2c85a56c8c3ecbf23e71737b99e4f8ec9e781e5004022078ee4b44757f4e181c0e4e3b66e2b93cdcd0b6b5774f8960e76e5d1f662c8f6701` | 304402204fa70998c592a21108798b2c85a56c8c3ecbf23e71737b99e4f8ec9e781e5004022078ee4b44757f4e181c0e4e3b66e2b93cdcd0b6b5774f8960e76e5d1f662c8f6701 |
| 16220 | 1 | `witness[0][1].length` | `21` | 33 |
| 16221 | 33 | `witness[0][1].data` | `03f1b7ce8a9ffc412d48cfde0fb78279f3ec7aa7a47431e27ca7c5d0f51d90c72b` | 03f1b7ce8a9ffc412d48cfde0fb78279f3ec7aa7a47431e27ca7c5d0f51d90c72b |
| 16254 | 4 | `tx.locktime` | `00000000` | 0 |

## 交易 61: `283aa6128ca7e09f05b976f176670645b40eff9bc3a9fa3f17e643e6bd96bf01`

| 偏移 | 字节数 | 字段 | 原始字节（线缆序） | 解释值 |
|---:|---:|---|---|---|
| 16258 | 4 | `tx.version` | `02000000` | 2 |
| 16262 | 1 | `tx.marker` | `00` | 0 |
| 16263 | 1 | `tx.flag` | `01` | 1 |
| 16264 | 1 | `tx.input_count` | `01` | 1 |
| 16265 | 32 | `vin[0].prev_txid` | `94bf848370cb92bcba03392017a4614710e84d3d10378fab3ed52d18eea7eb8b` | 8beba7ee182dd53eab8f37103d4de8104761a417203903babc92cb708384bf94 |
| 16297 | 4 | `vin[0].vout` | `01000000` | 1 |
| 16301 | 1 | `vin[0].scriptSig_length` | `00` | 0 |
| 16302 | 0 | `vin[0].scriptSig` | `（空）` |  |
| 16302 | 4 | `vin[0].sequence` | `fdffffff` | 4294967293 |
| 16306 | 1 | `tx.output_count` | `02` | 2 |
| 16307 | 8 | `vout[0].value` | `088c020000000000` | 166920 |
| 16315 | 1 | `vout[0].scriptPubKey_length` | `16` | 22 |
| 16316 | 22 | `vout[0].scriptPubKey` | `0014a0a7320191a5491c5fe734d5e2179d4841741a86` | OP_0 a0a7320191a5491c5fe734d5e2179d4841741a86 |
| 16338 | 8 | `vout[1].value` | `410d643d00000000` | 1029967169 |
| 16346 | 1 | `vout[1].scriptPubKey_length` | `16` | 22 |
| 16347 | 22 | `vout[1].scriptPubKey` | `001415149d363ce26a88e4ae2d03321d28b5cb514c03` | OP_0 15149d363ce26a88e4ae2d03321d28b5cb514c03 |
| 16369 | 1 | `witness[0].item_count` | `02` | 2 |
| 16370 | 1 | `witness[0][0].length` | `47` | 71 |
| 16371 | 71 | `witness[0][0].data` | `304402202e9cf08abf4d5da5e2a4a490094317845e7702b85f35bcabd8b15f6b6179986402202bc6048505d1c104a5a196c35280dd6f59fec849f4dbf424ac6ec660e4c61e9901` | 304402202e9cf08abf4d5da5e2a4a490094317845e7702b85f35bcabd8b15f6b6179986402202bc6048505d1c104a5a196c35280dd6f59fec849f4dbf424ac6ec660e4c61e9901 |
| 16442 | 1 | `witness[0][1].length` | `21` | 33 |
| 16443 | 33 | `witness[0][1].data` | `026c010a4a0b27398df0def9d10657b2313a45e8b092a86d7916ee32344181756b` | 026c010a4a0b27398df0def9d10657b2313a45e8b092a86d7916ee32344181756b |
| 16476 | 4 | `tx.locktime` | `c7724d00` | 5075655 |

## 交易 62: `f097a19395dab64a5508d4ac05a8d1b1f6f1bbba14e2b6efd303bed769925b07`

| 偏移 | 字节数 | 字段 | 原始字节（线缆序） | 解释值 |
|---:|---:|---|---|---|
| 16480 | 4 | `tx.version` | `02000000` | 2 |
| 16484 | 1 | `tx.marker` | `00` | 0 |
| 16485 | 1 | `tx.flag` | `01` | 1 |
| 16486 | 1 | `tx.input_count` | `01` | 1 |
| 16487 | 32 | `vin[0].prev_txid` | `3facc84575d401cedda5b0998b525d5439d9eeaa40c767cddea4d984ac5a99df` | df995aac84d9a4decd67c740aaeed939545d528b99b0a5ddce01d47545c8ac3f |
| 16519 | 4 | `vin[0].vout` | `00000000` | 0 |
| 16523 | 1 | `vin[0].scriptSig_length` | `00` | 0 |
| 16524 | 0 | `vin[0].scriptSig` | `（空）` |  |
| 16524 | 4 | `vin[0].sequence` | `fdffffff` | 4294967293 |
| 16528 | 1 | `tx.output_count` | `02` | 2 |
| 16529 | 8 | `vout[0].value` | `ef19f17200000000` | 1928403439 |
| 16537 | 1 | `vout[0].scriptPubKey_length` | `16` | 22 |
| 16538 | 22 | `vout[0].scriptPubKey` | `001473ec6de8b999c309b4e8551850ed591937235312` | OP_0 73ec6de8b999c309b4e8551850ed591937235312 |
| 16560 | 8 | `vout[1].value` | `6227020000000000` | 141154 |
| 16568 | 1 | `vout[1].scriptPubKey_length` | `16` | 22 |
| 16569 | 22 | `vout[1].scriptPubKey` | `00140d8bcd9fa841c4b174aae7bb64964eefabc5ddab` | OP_0 0d8bcd9fa841c4b174aae7bb64964eefabc5ddab |
| 16591 | 1 | `witness[0].item_count` | `02` | 2 |
| 16592 | 1 | `witness[0][0].length` | `47` | 71 |
| 16593 | 71 | `witness[0][0].data` | `304402202a36c7e6daeb7ba56a56e353eca7e921870291a720384ed3d1d0c889e0747c6902200a58407011bcff62e0f1ae94ca4f2c2d0fe7e5b8adc7c1cb6fc5c2c6746118b601` | 304402202a36c7e6daeb7ba56a56e353eca7e921870291a720384ed3d1d0c889e0747c6902200a58407011bcff62e0f1ae94ca4f2c2d0fe7e5b8adc7c1cb6fc5c2c6746118b601 |
| 16664 | 1 | `witness[0][1].length` | `21` | 33 |
| 16665 | 33 | `witness[0][1].data` | `02e19552999f809ecfcf6febb24e2e8f6cd4c37e10990218bf4352cb863c80de93` | 02e19552999f809ecfcf6febb24e2e8f6cd4c37e10990218bf4352cb863c80de93 |
| 16698 | 4 | `tx.locktime` | `c6724d00` | 5075654 |

## 交易 63: `444ee8ed86ed1429c9bd6bad45d2b6ccdc874900515593f38dbe0c4354050713`

| 偏移 | 字节数 | 字段 | 原始字节（线缆序） | 解释值 |
|---:|---:|---|---|---|
| 16702 | 4 | `tx.version` | `02000000` | 2 |
| 16706 | 1 | `tx.marker` | `00` | 0 |
| 16707 | 1 | `tx.flag` | `01` | 1 |
| 16708 | 1 | `tx.input_count` | `01` | 1 |
| 16709 | 32 | `vin[0].prev_txid` | `78c492d86d1c2768a1e75bb568ef5dd263688980dc029d3f05362cc6c2336b26` | 266b33c2c62c36053f9d02dc80896863d25def68b55be7a168271c6dd892c478 |
| 16741 | 4 | `vin[0].vout` | `01000000` | 1 |
| 16745 | 1 | `vin[0].scriptSig_length` | `00` | 0 |
| 16746 | 0 | `vin[0].scriptSig` | `（空）` |  |
| 16746 | 4 | `vin[0].sequence` | `fdffffff` | 4294967293 |
| 16750 | 1 | `tx.output_count` | `02` | 2 |
| 16751 | 8 | `vout[0].value` | `4c32023100000000` | 822227532 |
| 16759 | 1 | `vout[0].scriptPubKey_length` | `16` | 22 |
| 16760 | 22 | `vout[0].scriptPubKey` | `0014b923ab6f3d10840af2159cfaf65d5153416d31e3` | OP_0 b923ab6f3d10840af2159cfaf65d5153416d31e3 |
| 16782 | 8 | `vout[1].value` | `a20e020000000000` | 134818 |
| 16790 | 1 | `vout[1].scriptPubKey_length` | `16` | 22 |
| 16791 | 22 | `vout[1].scriptPubKey` | `0014f1649598dd3b33d6de6521f4fc2f648fb308796a` | OP_0 f1649598dd3b33d6de6521f4fc2f648fb308796a |
| 16813 | 1 | `witness[0].item_count` | `02` | 2 |
| 16814 | 1 | `witness[0][0].length` | `47` | 71 |
| 16815 | 71 | `witness[0][0].data` | `30440220778295d3be83eac0989bdb8be14c5a6e3fb7384a04bc5c44e47b4483488c873a022028afffd8063383d251af25def8d75090554f2ba49894c81e86282416b3a80bbc01` | 30440220778295d3be83eac0989bdb8be14c5a6e3fb7384a04bc5c44e47b4483488c873a022028afffd8063383d251af25def8d75090554f2ba49894c81e86282416b3a80bbc01 |
| 16886 | 1 | `witness[0][1].length` | `21` | 33 |
| 16887 | 33 | `witness[0][1].data` | `0282530a6493f8709ad381d9618be236ce4385121abd4b79ed4973c66b2772cecd` | 0282530a6493f8709ad381d9618be236ce4385121abd4b79ed4973c66b2772cecd |
| 16920 | 4 | `tx.locktime` | `c7724d00` | 5075655 |

## 交易 64: `aaef49e19035afb0686e54b9236ddec67f28240d5d78d40969d40a2746fb3e17`

| 偏移 | 字节数 | 字段 | 原始字节（线缆序） | 解释值 |
|---:|---:|---|---|---|
| 16924 | 4 | `tx.version` | `02000000` | 2 |
| 16928 | 1 | `tx.marker` | `00` | 0 |
| 16929 | 1 | `tx.flag` | `01` | 1 |
| 16930 | 1 | `tx.input_count` | `01` | 1 |
| 16931 | 32 | `vin[0].prev_txid` | `487726afb0adb5f80d5e7b81a1450804d8ff7b402bb1fddc50142751cfe51d32` | 321de5cf51271450dcfdb12b407bffd8040845a1817b5e0df8b5adb0af267748 |
| 16963 | 4 | `vin[0].vout` | `00000000` | 0 |
| 16967 | 1 | `vin[0].scriptSig_length` | `00` | 0 |
| 16968 | 0 | `vin[0].scriptSig` | `（空）` |  |
| 16968 | 4 | `vin[0].sequence` | `fdffffff` | 4294967293 |
| 16972 | 1 | `tx.output_count` | `02` | 2 |
| 16973 | 8 | `vout[0].value` | `fa47386600000000` | 1714964474 |
| 16981 | 1 | `vout[0].scriptPubKey_length` | `16` | 22 |
| 16982 | 22 | `vout[0].scriptPubKey` | `00143eb0b32570a582289fead1e028e839c996330919` | OP_0 3eb0b32570a582289fead1e028e839c996330919 |
| 17004 | 8 | `vout[1].value` | `4ed4010000000000` | 119886 |
| 17012 | 1 | `vout[1].scriptPubKey_length` | `16` | 22 |
| 17013 | 22 | `vout[1].scriptPubKey` | `0014142ee2c97e65ff9ee69a17a64469b66f146f87a9` | OP_0 142ee2c97e65ff9ee69a17a64469b66f146f87a9 |
| 17035 | 1 | `witness[0].item_count` | `02` | 2 |
| 17036 | 1 | `witness[0][0].length` | `47` | 71 |
| 17037 | 71 | `witness[0][0].data` | `304402201f2a932c2d902a87a348ad83dcde3e54375cc93187ba7244b1b281c7b0c5ba1b022067fa442dc391c6a8ac2d578a7f007629c43a683d17411efa6bade299ebb8630901` | 304402201f2a932c2d902a87a348ad83dcde3e54375cc93187ba7244b1b281c7b0c5ba1b022067fa442dc391c6a8ac2d578a7f007629c43a683d17411efa6bade299ebb8630901 |
| 17108 | 1 | `witness[0][1].length` | `21` | 33 |
| 17109 | 33 | `witness[0][1].data` | `036e7e22090cc77629c021e57cb619e9a0d4db9036e973317880b7c833e9caf955` | 036e7e22090cc77629c021e57cb619e9a0d4db9036e973317880b7c833e9caf955 |
| 17142 | 4 | `tx.locktime` | `c7724d00` | 5075655 |

## 交易 65: `e8b95e453f50d431d2267fa442dae1c82f84aa91314f6ce90941b30e01eb7a2b`

| 偏移 | 字节数 | 字段 | 原始字节（线缆序） | 解释值 |
|---:|---:|---|---|---|
| 17146 | 4 | `tx.version` | `02000000` | 2 |
| 17150 | 1 | `tx.marker` | `00` | 0 |
| 17151 | 1 | `tx.flag` | `01` | 1 |
| 17152 | 1 | `tx.input_count` | `01` | 1 |
| 17153 | 32 | `vin[0].prev_txid` | `3ee8d9cb0138b714ada80b1f390ac2bd48be310eb04719da390aa1dd1cd0b8c4` | c4b8d01cdda10a39da1947b00e31be48bdc20a391f0ba8ad14b73801cbd9e83e |
| 17185 | 4 | `vin[0].vout` | `01000000` | 1 |
| 17189 | 1 | `vin[0].scriptSig_length` | `00` | 0 |
| 17190 | 0 | `vin[0].scriptSig` | `（空）` |  |
| 17190 | 4 | `vin[0].sequence` | `fdffffff` | 4294967293 |
| 17194 | 1 | `tx.output_count` | `02` | 2 |
| 17195 | 8 | `vout[0].value` | `7fe4ac5d00000000` | 1571611775 |
| 17203 | 1 | `vout[0].scriptPubKey_length` | `16` | 22 |
| 17204 | 22 | `vout[0].scriptPubKey` | `00143c41e96d114c75ced4b46f6446d2003a3b6e1243` | OP_0 3c41e96d114c75ced4b46f6446d2003a3b6e1243 |
| 17226 | 8 | `vout[1].value` | `ea98020000000000` | 170218 |
| 17234 | 1 | `vout[1].scriptPubKey_length` | `16` | 22 |
| 17235 | 22 | `vout[1].scriptPubKey` | `0014ea11dcb4b5a042e9ed3bb4a681ec3216c71efb56` | OP_0 ea11dcb4b5a042e9ed3bb4a681ec3216c71efb56 |
| 17257 | 1 | `witness[0].item_count` | `02` | 2 |
| 17258 | 1 | `witness[0][0].length` | `47` | 71 |
| 17259 | 71 | `witness[0][0].data` | `3044022020bde59e8f32f6061b79c0ac4d2ca7d1480d6655bd6d9d6901fcae2643380ad802201aaf74ceb22936fd7ab00c6d8d85e4f84944ce373016e86d919dafec22fbcb0401` | 3044022020bde59e8f32f6061b79c0ac4d2ca7d1480d6655bd6d9d6901fcae2643380ad802201aaf74ceb22936fd7ab00c6d8d85e4f84944ce373016e86d919dafec22fbcb0401 |
| 17330 | 1 | `witness[0][1].length` | `21` | 33 |
| 17331 | 33 | `witness[0][1].data` | `0314e634088eb86e2d592a02641c13cc58257552fe6cb984bfb381edf845ea2ce1` | 0314e634088eb86e2d592a02641c13cc58257552fe6cb984bfb381edf845ea2ce1 |
| 17364 | 4 | `tx.locktime` | `c7724d00` | 5075655 |

## 交易 66: `ae48cc308a52d39240d9c58e4ef0a01fb23f1f83193d044eeb5e3100f271c973`

| 偏移 | 字节数 | 字段 | 原始字节（线缆序） | 解释值 |
|---:|---:|---|---|---|
| 17368 | 4 | `tx.version` | `02000000` | 2 |
| 17372 | 1 | `tx.marker` | `00` | 0 |
| 17373 | 1 | `tx.flag` | `01` | 1 |
| 17374 | 1 | `tx.input_count` | `01` | 1 |
| 17375 | 32 | `vin[0].prev_txid` | `792beccd93e58aed4a54c44729f48330639fceca93b08b68510f6ace2982d7b4` | b4d78229ce6a0f51688bb093cace9f633083f42947c4544aed8ae593cdec2b79 |
| 17407 | 4 | `vin[0].vout` | `00000000` | 0 |
| 17411 | 1 | `vin[0].scriptSig_length` | `00` | 0 |
| 17412 | 0 | `vin[0].scriptSig` | `（空）` |  |
| 17412 | 4 | `vin[0].sequence` | `fdffffff` | 4294967293 |
| 17416 | 1 | `tx.output_count` | `02` | 2 |
| 17417 | 8 | `vout[0].value` | `306ad46200000000` | 1658087984 |
| 17425 | 1 | `vout[0].scriptPubKey_length` | `16` | 22 |
| 17426 | 22 | `vout[0].scriptPubKey` | `00148eecdded9862244a581162d0d5a2706ce83e0837` | OP_0 8eecdded9862244a581162d0d5a2706ce83e0837 |
| 17448 | 8 | `vout[1].value` | `11a5010000000000` | 107793 |
| 17456 | 1 | `vout[1].scriptPubKey_length` | `16` | 22 |
| 17457 | 22 | `vout[1].scriptPubKey` | `0014a2ceec4a23a11db0fe2ca816206276ae54e37c9a` | OP_0 a2ceec4a23a11db0fe2ca816206276ae54e37c9a |
| 17479 | 1 | `witness[0].item_count` | `02` | 2 |
| 17480 | 1 | `witness[0][0].length` | `47` | 71 |
| 17481 | 71 | `witness[0][0].data` | `3044022033f68eab644a3d9c7c4ff6ac058f9cb7bf1dd2d941135899952460d1c41d092102204d33351e1913e1fd0f9529ad510f258403caf6b17a6af8f6cbb179db19e2486501` | 3044022033f68eab644a3d9c7c4ff6ac058f9cb7bf1dd2d941135899952460d1c41d092102204d33351e1913e1fd0f9529ad510f258403caf6b17a6af8f6cbb179db19e2486501 |
| 17552 | 1 | `witness[0][1].length` | `21` | 33 |
| 17553 | 33 | `witness[0][1].data` | `0285fcedbe2fc86e172b30b85159cc42ebdd6eb867e2582ac21666c9cf0ed60e4b` | 0285fcedbe2fc86e172b30b85159cc42ebdd6eb867e2582ac21666c9cf0ed60e4b |
| 17586 | 4 | `tx.locktime` | `c7724d00` | 5075655 |

## 交易 67: `6b397a19c461937f5ad994accb66e520615a5a92c78d8f9bc7ac7f4fffb0bf90`

| 偏移 | 字节数 | 字段 | 原始字节（线缆序） | 解释值 |
|---:|---:|---|---|---|
| 17590 | 4 | `tx.version` | `02000000` | 2 |
| 17594 | 1 | `tx.marker` | `00` | 0 |
| 17595 | 1 | `tx.flag` | `01` | 1 |
| 17596 | 1 | `tx.input_count` | `01` | 1 |
| 17597 | 32 | `vin[0].prev_txid` | `670af279fff8ee28b7aa6a6e783b1e077d8154d09b0015803043716ab8a82d51` | 512da8b86a7143308015009bd054817d071e3b786e6aaab728eef8ff79f20a67 |
| 17629 | 4 | `vin[0].vout` | `00000000` | 0 |
| 17633 | 1 | `vin[0].scriptSig_length` | `00` | 0 |
| 17634 | 0 | `vin[0].scriptSig` | `（空）` |  |
| 17634 | 4 | `vin[0].sequence` | `fdffffff` | 4294967293 |
| 17638 | 1 | `tx.output_count` | `02` | 2 |
| 17639 | 8 | `vout[0].value` | `4e03f63600000000` | 922092366 |
| 17647 | 1 | `vout[0].scriptPubKey_length` | `16` | 22 |
| 17648 | 22 | `vout[0].scriptPubKey` | `001459178dff80c77900b0f58b3a1ae4a6b75764eb9e` | OP_0 59178dff80c77900b0f58b3a1ae4a6b75764eb9e |
| 17670 | 8 | `vout[1].value` | `1519020000000000` | 137493 |
| 17678 | 1 | `vout[1].scriptPubKey_length` | `16` | 22 |
| 17679 | 22 | `vout[1].scriptPubKey` | `0014d079738b516cc896f6de222bf4389d00a03efd86` | OP_0 d079738b516cc896f6de222bf4389d00a03efd86 |
| 17701 | 1 | `witness[0].item_count` | `02` | 2 |
| 17702 | 1 | `witness[0][0].length` | `47` | 71 |
| 17703 | 71 | `witness[0][0].data` | `304402206e05d29fd22c53b32f46fb8af1533bebb31d9075bb98fd384cb5371c7f997ffc022052cd59dc5d29a59806910458c6573a6afc88dd523ef1f3a962d8453442a3b18701` | 304402206e05d29fd22c53b32f46fb8af1533bebb31d9075bb98fd384cb5371c7f997ffc022052cd59dc5d29a59806910458c6573a6afc88dd523ef1f3a962d8453442a3b18701 |
| 17774 | 1 | `witness[0][1].length` | `21` | 33 |
| 17775 | 33 | `witness[0][1].data` | `029e0aa91a98efd48abbb33933b8090987493ea7dcb415d0312c891c38999334af` | 029e0aa91a98efd48abbb33933b8090987493ea7dcb415d0312c891c38999334af |
| 17808 | 4 | `tx.locktime` | `c7724d00` | 5075655 |

## 交易 68: `ae9288b6416957f72ef36aa1c3fdf8e70ebaa043870d0ff87172696f9349d59e`

| 偏移 | 字节数 | 字段 | 原始字节（线缆序） | 解释值 |
|---:|---:|---|---|---|
| 17812 | 4 | `tx.version` | `02000000` | 2 |
| 17816 | 1 | `tx.marker` | `00` | 0 |
| 17817 | 1 | `tx.flag` | `01` | 1 |
| 17818 | 1 | `tx.input_count` | `01` | 1 |
| 17819 | 32 | `vin[0].prev_txid` | `b026dd6133ac4b55f0466e25745200d67ab381ec51ac5f5742bf288b2f21c1c3` | c3c1212f8b28bf42575fac51ec81b37ad6005274256e46f0554bac3361dd26b0 |
| 17851 | 4 | `vin[0].vout` | `00000000` | 0 |
| 17855 | 1 | `vin[0].scriptSig_length` | `00` | 0 |
| 17856 | 0 | `vin[0].scriptSig` | `（空）` |  |
| 17856 | 4 | `vin[0].sequence` | `fdffffff` | 4294967293 |
| 17860 | 1 | `tx.output_count` | `02` | 2 |
| 17861 | 8 | `vout[0].value` | `386a416e00000000` | 1849780792 |
| 17869 | 1 | `vout[0].scriptPubKey_length` | `16` | 22 |
| 17870 | 22 | `vout[0].scriptPubKey` | `0014ced4e44d4d18027bc321cdd4c4b214b67ca2f273` | OP_0 ced4e44d4d18027bc321cdd4c4b214b67ca2f273 |
| 17892 | 8 | `vout[1].value` | `58f6020000000000` | 194136 |
| 17900 | 1 | `vout[1].scriptPubKey_length` | `16` | 22 |
| 17901 | 22 | `vout[1].scriptPubKey` | `001408ca789f9373aecd251a6a0da355a3061758767e` | OP_0 08ca789f9373aecd251a6a0da355a3061758767e |
| 17923 | 1 | `witness[0].item_count` | `02` | 2 |
| 17924 | 1 | `witness[0][0].length` | `47` | 71 |
| 17925 | 71 | `witness[0][0].data` | `304402201cb89f12fc724de80d9cca7fd21b0c888b5327e818e4a08a544e4f6acd9b2b9502204354bc82d7d536f862264996c37d4022fc51889aec9e7555d19bb4f02bd5c68e01` | 304402201cb89f12fc724de80d9cca7fd21b0c888b5327e818e4a08a544e4f6acd9b2b9502204354bc82d7d536f862264996c37d4022fc51889aec9e7555d19bb4f02bd5c68e01 |
| 17996 | 1 | `witness[0][1].length` | `21` | 33 |
| 17997 | 33 | `witness[0][1].data` | `03c8ab197caeb268ed9d57c72099a7f735e6e70d36e9b9ef5deb1bb50d3b428123` | 03c8ab197caeb268ed9d57c72099a7f735e6e70d36e9b9ef5deb1bb50d3b428123 |
| 18030 | 4 | `tx.locktime` | `c7724d00` | 5075655 |

## 交易 69: `ce0a1930cce471f99820414ddc52019584ba702ec3ceccc1ca702813a4ac16e5`

| 偏移 | 字节数 | 字段 | 原始字节（线缆序） | 解释值 |
|---:|---:|---|---|---|
| 18034 | 4 | `tx.version` | `02000000` | 2 |
| 18038 | 1 | `tx.marker` | `00` | 0 |
| 18039 | 1 | `tx.flag` | `01` | 1 |
| 18040 | 1 | `tx.input_count` | `01` | 1 |
| 18041 | 32 | `vin[0].prev_txid` | `c1ff2a0713c44dbfc68c9ae90ac274fc440a87f4c8df2ff7373132c81202f483` | 83f40212c8323137f72fdfc8f4870a44fc74c20ae99a8cc6bf4dc413072affc1 |
| 18073 | 4 | `vin[0].vout` | `01000000` | 1 |
| 18077 | 1 | `vin[0].scriptSig_length` | `00` | 0 |
| 18078 | 0 | `vin[0].scriptSig` | `（空）` |  |
| 18078 | 4 | `vin[0].sequence` | `fdffffff` | 4294967293 |
| 18082 | 1 | `tx.output_count` | `02` | 2 |
| 18083 | 8 | `vout[0].value` | `68aa2e2500000000` | 623815272 |
| 18091 | 1 | `vout[0].scriptPubKey_length` | `16` | 22 |
| 18092 | 22 | `vout[0].scriptPubKey` | `0014da99ce09cf5593b1e4b5a996e553f39dc6f60d9c` | OP_0 da99ce09cf5593b1e4b5a996e553f39dc6f60d9c |
| 18114 | 8 | `vout[1].value` | `7fc9030000000000` | 248191 |
| 18122 | 1 | `vout[1].scriptPubKey_length` | `16` | 22 |
| 18123 | 22 | `vout[1].scriptPubKey` | `00142f35c5e9965b5d40b797d0ad5cb1925441517d34` | OP_0 2f35c5e9965b5d40b797d0ad5cb1925441517d34 |
| 18145 | 1 | `witness[0].item_count` | `02` | 2 |
| 18146 | 1 | `witness[0][0].length` | `47` | 71 |
| 18147 | 71 | `witness[0][0].data` | `304402206931a062a98e0ff372e19a39ba3b19061dd1a1daef65793820a3c3c6047bdfa60220464787fdb5a0a9e9c1e3121559b5d718c0363bd08da03f652e49502928b21c0201` | 304402206931a062a98e0ff372e19a39ba3b19061dd1a1daef65793820a3c3c6047bdfa60220464787fdb5a0a9e9c1e3121559b5d718c0363bd08da03f652e49502928b21c0201 |
| 18218 | 1 | `witness[0][1].length` | `21` | 33 |
| 18219 | 33 | `witness[0][1].data` | `0281157ab37b5d907f9127c2692dc5e829f4cde56003b07de0d13f369774b0e860` | 0281157ab37b5d907f9127c2692dc5e829f4cde56003b07de0d13f369774b0e860 |
| 18252 | 4 | `tx.locktime` | `c7724d00` | 5075655 |

## 交易 70: `0c8ca9b6293fd477e10129aaf18d1bda4ab21da41947ad257e161f9cee1e0513`

| 偏移 | 字节数 | 字段 | 原始字节（线缆序） | 解释值 |
|---:|---:|---|---|---|
| 18256 | 4 | `tx.version` | `02000000` | 2 |
| 18260 | 1 | `tx.marker` | `00` | 0 |
| 18261 | 1 | `tx.flag` | `01` | 1 |
| 18262 | 1 | `tx.input_count` | `01` | 1 |
| 18263 | 32 | `vin[0].prev_txid` | `8f2fba4711cd4f349803191efc86cd9431b6f1d97fe37f35a0cd8b9294ff1a6a` | 6a1aff94928bcda0357fe37fd9f1b63194cd86fc1e190398344fcd1147ba2f8f |
| 18295 | 4 | `vin[0].vout` | `01000000` | 1 |
| 18299 | 1 | `vin[0].scriptSig_length` | `00` | 0 |
| 18300 | 0 | `vin[0].scriptSig` | `（空）` |  |
| 18300 | 4 | `vin[0].sequence` | `fdffffff` | 4294967293 |
| 18304 | 1 | `tx.output_count` | `02` | 2 |
| 18305 | 8 | `vout[0].value` | `2b12020000000000` | 135723 |
| 18313 | 1 | `vout[0].scriptPubKey_length` | `19` | 25 |
| 18314 | 25 | `vout[0].scriptPubKey` | `76a9147185c4ad44ee6315db6fdca6e2b1527cdec1a02888ac` | OP_DUP OP_HASH160 7185c4ad44ee6315db6fdca6e2b1527cdec1a028 OP_EQUALVERIFY OP_CHECKSIG |
| 18339 | 8 | `vout[1].value` | `b0e4e54c00000000` | 1290134704 |
| 18347 | 1 | `vout[1].scriptPubKey_length` | `19` | 25 |
| 18348 | 25 | `vout[1].scriptPubKey` | `76a914d0b771251674c65e60687687cc6e709adbddbd3788ac` | OP_DUP OP_HASH160 d0b771251674c65e60687687cc6e709adbddbd37 OP_EQUALVERIFY OP_CHECKSIG |
| 18373 | 1 | `witness[0].item_count` | `02` | 2 |
| 18374 | 1 | `witness[0][0].length` | `47` | 71 |
| 18375 | 71 | `witness[0][0].data` | `304402206327882f54abdd97a26b3d2cd9fa1ca503095050607c6f9e0c6c73f3fb2afd7302205f9cc6150d4e8beca63070cb50faceba8972d7b84c82041f92c9f516c6a9963301` | 304402206327882f54abdd97a26b3d2cd9fa1ca503095050607c6f9e0c6c73f3fb2afd7302205f9cc6150d4e8beca63070cb50faceba8972d7b84c82041f92c9f516c6a9963301 |
| 18446 | 1 | `witness[0][1].length` | `21` | 33 |
| 18447 | 33 | `witness[0][1].data` | `025efb98bde1fc72c2a6296cef7ea06a40d68aae702f5ad6bdb02a65e3d29ab57b` | 025efb98bde1fc72c2a6296cef7ea06a40d68aae702f5ad6bdb02a65e3d29ab57b |
| 18480 | 4 | `tx.locktime` | `c7724d00` | 5075655 |

## 交易 71: `e2571f2f2bc8d608d4407ca778dc1656d488471cbda77dde9a05731089880018`

| 偏移 | 字节数 | 字段 | 原始字节（线缆序） | 解释值 |
|---:|---:|---|---|---|
| 18484 | 4 | `tx.version` | `02000000` | 2 |
| 18488 | 1 | `tx.marker` | `00` | 0 |
| 18489 | 1 | `tx.flag` | `01` | 1 |
| 18490 | 1 | `tx.input_count` | `01` | 1 |
| 18491 | 32 | `vin[0].prev_txid` | `06ca627254abafc485007087d9db3c67a53c04a33c76682ed8034bc72becd119` | 19d1ec2bc74b03d82e68763ca3043ca5673cdbd987700085c4afab547262ca06 |
| 18523 | 4 | `vin[0].vout` | `01000000` | 1 |
| 18527 | 1 | `vin[0].scriptSig_length` | `00` | 0 |
| 18528 | 0 | `vin[0].scriptSig` | `（空）` |  |
| 18528 | 4 | `vin[0].sequence` | `fdffffff` | 4294967293 |
| 18532 | 1 | `tx.output_count` | `02` | 2 |
| 18533 | 8 | `vout[0].value` | `75fd506900000000` | 1766915445 |
| 18541 | 1 | `vout[0].scriptPubKey_length` | `19` | 25 |
| 18542 | 25 | `vout[0].scriptPubKey` | `76a9140dab17c78f849bbe1fc56692556958dd01b15dd588ac` | OP_DUP OP_HASH160 0dab17c78f849bbe1fc56692556958dd01b15dd5 OP_EQUALVERIFY OP_CHECKSIG |
| 18567 | 8 | `vout[1].value` | `f7b2010000000000` | 111351 |
| 18575 | 1 | `vout[1].scriptPubKey_length` | `19` | 25 |
| 18576 | 25 | `vout[1].scriptPubKey` | `76a91495e14edec78c0c74e7f7cd4b42e84436008d64d888ac` | OP_DUP OP_HASH160 95e14edec78c0c74e7f7cd4b42e84436008d64d8 OP_EQUALVERIFY OP_CHECKSIG |
| 18601 | 1 | `witness[0].item_count` | `02` | 2 |
| 18602 | 1 | `witness[0][0].length` | `47` | 71 |
| 18603 | 71 | `witness[0][0].data` | `304402206cf0a81c6498882de5137d6a6a2e5e8a6977112abbace619aaaa27c320714f66022065dfe5e6f4dec9fee25aa7b754e9f5dd5083212dd99e64428cef2d39a84e6de601` | 304402206cf0a81c6498882de5137d6a6a2e5e8a6977112abbace619aaaa27c320714f66022065dfe5e6f4dec9fee25aa7b754e9f5dd5083212dd99e64428cef2d39a84e6de601 |
| 18674 | 1 | `witness[0][1].length` | `21` | 33 |
| 18675 | 33 | `witness[0][1].data` | `0288f8b16b305405c98c14bc8dff3f85117e44b5bf46dfcfadbadea0c34a16c067` | 0288f8b16b305405c98c14bc8dff3f85117e44b5bf46dfcfadbadea0c34a16c067 |
| 18708 | 4 | `tx.locktime` | `c7724d00` | 5075655 |

## 交易 72: `c1b03cda7ea30238dec63623e1dcf2523c5fe9ef49cd87d44d62d0c6024297a2`

| 偏移 | 字节数 | 字段 | 原始字节（线缆序） | 解释值 |
|---:|---:|---|---|---|
| 18712 | 4 | `tx.version` | `02000000` | 2 |
| 18716 | 1 | `tx.input_count` | `01` | 1 |
| 18717 | 32 | `vin[0].prev_txid` | `6c8e248749fd563b6ff47bcd72cc051c01b820c076bd76e1612090a7bfbffd86` | 86fdbfbfa7902061e176bd76c020b8011c05cc72cd7bf46f3b56fd4987248e6c |
| 18749 | 4 | `vin[0].vout` | `00000000` | 0 |
| 18753 | 1 | `vin[0].scriptSig_length` | `6a` | 106 |
| 18754 | 106 | `vin[0].scriptSig` | `47304402202730c3e5535071883568242c5198136bd97de5681b74bb474427ea29325f0b7e02201c1cc298f33b9bbe0108f2e3642f6bdfca731bea8a92c5f1cf110abc4d5649f30121030df94c8b57206ce5bf4230bd37882fd1fc647588595ee4ec464d5fca81edebee` | 304402202730c3e5535071883568242c5198136bd97de5681b74bb474427ea29325f0b7e02201c1cc298f33b9bbe0108f2e3642f6bdfca731bea8a92c5f1cf110abc4d5649f301 030df94c8b57206ce5bf4230bd37882fd1fc647588595ee4ec464d5fca81edebee |
| 18860 | 4 | `vin[0].sequence` | `fdffffff` | 4294967293 |
| 18864 | 1 | `tx.output_count` | `02` | 2 |
| 18865 | 8 | `vout[0].value` | `e43b875e00000000` | 1585920996 |
| 18873 | 1 | `vout[0].scriptPubKey_length` | `19` | 25 |
| 18874 | 25 | `vout[0].scriptPubKey` | `76a91457488eb8643bf42d9acb3a896bc0dc5b277d57a888ac` | OP_DUP OP_HASH160 57488eb8643bf42d9acb3a896bc0dc5b277d57a8 OP_EQUALVERIFY OP_CHECKSIG |
| 18899 | 8 | `vout[1].value` | `6606030000000000` | 198246 |
| 18907 | 1 | `vout[1].scriptPubKey_length` | `19` | 25 |
| 18908 | 25 | `vout[1].scriptPubKey` | `76a914f5ca6930b57d37e135e2f97a3e3732e9ea59634988ac` | OP_DUP OP_HASH160 f5ca6930b57d37e135e2f97a3e3732e9ea596349 OP_EQUALVERIFY OP_CHECKSIG |
| 18933 | 4 | `tx.locktime` | `c7724d00` | 5075655 |

## 交易 73: `0bc1bc6c68665ade6bb068b2ec9211670f027d3fc80704b80bc68b7bcb023017`

| 偏移 | 字节数 | 字段 | 原始字节（线缆序） | 解释值 |
|---:|---:|---|---|---|
| 18937 | 4 | `tx.version` | `02000000` | 2 |
| 18941 | 1 | `tx.marker` | `00` | 0 |
| 18942 | 1 | `tx.flag` | `01` | 1 |
| 18943 | 1 | `tx.input_count` | `01` | 1 |
| 18944 | 32 | `vin[0].prev_txid` | `3aef32517be2e89e313ddf9e5017725f759464c2a6cfc66f52582bbe8806ba86` | 86ba0688be2b58526fc6cfa6c26494755f7217509edf3d319ee8e27b5132ef3a |
| 18976 | 4 | `vin[0].vout` | `00000000` | 0 |
| 18980 | 1 | `vin[0].scriptSig_length` | `17` | 23 |
| 18981 | 23 | `vin[0].scriptSig` | `160014ac029e6cf8a385464d0608efab7e6b1371c0d4d5` | 0014ac029e6cf8a385464d0608efab7e6b1371c0d4d5 |
| 19004 | 4 | `vin[0].sequence` | `fdffffff` | 4294967293 |
| 19008 | 1 | `tx.output_count` | `02` | 2 |
| 19009 | 8 | `vout[0].value` | `d352050000000000` | 348883 |
| 19017 | 1 | `vout[0].scriptPubKey_length` | `16` | 22 |
| 19018 | 22 | `vout[0].scriptPubKey` | `00146b3f659f2f847e60f5018a06d802bace6b06dbb7` | OP_0 6b3f659f2f847e60f5018a06d802bace6b06dbb7 |
| 19040 | 8 | `vout[1].value` | `e09ada6400000000` | 1692048096 |
| 19048 | 1 | `vout[1].scriptPubKey_length` | `16` | 22 |
| 19049 | 22 | `vout[1].scriptPubKey` | `0014b82bd84fe7e6f8048862c4a16332cb5710532445` | OP_0 b82bd84fe7e6f8048862c4a16332cb5710532445 |
| 19071 | 1 | `witness[0].item_count` | `02` | 2 |
| 19072 | 1 | `witness[0][0].length` | `47` | 71 |
| 19073 | 71 | `witness[0][0].data` | `304402205ef43236f51bd0acfefa38e6911403240ef73d89cf77e335d342456d4f9c3c62022016c3b4d36e0b0174c7aaa2bf2f36d02b343557ecd6c7506fab3ba9be0dfe726c01` | 304402205ef43236f51bd0acfefa38e6911403240ef73d89cf77e335d342456d4f9c3c62022016c3b4d36e0b0174c7aaa2bf2f36d02b343557ecd6c7506fab3ba9be0dfe726c01 |
| 19144 | 1 | `witness[0][1].length` | `21` | 33 |
| 19145 | 33 | `witness[0][1].data` | `02de9997ccf25663f6127d4ac1803862cf3ecdf59ccef3f0657134808cb997c93c` | 02de9997ccf25663f6127d4ac1803862cf3ecdf59ccef3f0657134808cb997c93c |
| 19178 | 4 | `tx.locktime` | `c7724d00` | 5075655 |

## 交易 74: `f4cad19cdb33776bc1c4a20670dc2e73d834f15fd3aa259035a108c1546c6f7b`

| 偏移 | 字节数 | 字段 | 原始字节（线缆序） | 解释值 |
|---:|---:|---|---|---|
| 19182 | 4 | `tx.version` | `01000000` | 1 |
| 19186 | 1 | `tx.input_count` | `01` | 1 |
| 19187 | 32 | `vin[0].prev_txid` | `6a03d76570215fa9cd35a5ce9d8b1603f40088fa43e0e9bbda2393d7f8f0c63a` | 3ac6f0f8d79323dabbe9e043fa8800f403168b9dcea535cda95f217065d7036a |
| 19219 | 4 | `vin[0].vout` | `01000000` | 1 |
| 19223 | 1 | `vin[0].scriptSig_length` | `6a` | 106 |
| 19224 | 106 | `vin[0].scriptSig` | `4730440220389548f9225290fbc14e6abfbf70292ab3d3fa35c2a0ea007168ce95b4171bc80220293251784358eb249a6b71ca8f4878f8105821a726a6b1a1b3da709104289b3c012103fafc6c143b408d16a41719d7704d6f3437cef88784e3ba719fdf84938bb8c3a3` | 30440220389548f9225290fbc14e6abfbf70292ab3d3fa35c2a0ea007168ce95b4171bc80220293251784358eb249a6b71ca8f4878f8105821a726a6b1a1b3da709104289b3c01 03fafc6c143b408d16a41719d7704d6f3437cef88784e3ba719fdf84938bb8c3a3 |
| 19330 | 4 | `vin[0].sequence` | `ffffffff` | 4294967295 |
| 19334 | 1 | `tx.output_count` | `02` | 2 |
| 19335 | 8 | `vout[0].value` | `1027000000000000` | 10000 |
| 19343 | 1 | `vout[0].scriptPubKey_length` | `16` | 22 |
| 19344 | 22 | `vout[0].scriptPubKey` | `0014c8c43f9b09e2aadeb3fc1d200da042443bfd3b90` | OP_0 c8c43f9b09e2aadeb3fc1d200da042443bfd3b90 |
| 19366 | 8 | `vout[1].value` | `b855020000000000` | 153016 |
| 19374 | 1 | `vout[1].scriptPubKey_length` | `19` | 25 |
| 19375 | 25 | `vout[1].scriptPubKey` | `76a914dde46fb4984c9f70feb156473aab2ee1868a604188ac` | OP_DUP OP_HASH160 dde46fb4984c9f70feb156473aab2ee1868a6041 OP_EQUALVERIFY OP_CHECKSIG |
| 19400 | 4 | `tx.locktime` | `00000000` | 0 |

## 交易 75: `adedb24a40de45a0ad85d88b6c9035b852ed4ad5cef7d2bab57ae67e114ba933`

| 偏移 | 字节数 | 字段 | 原始字节（线缆序） | 解释值 |
|---:|---:|---|---|---|
| 19404 | 4 | `tx.version` | `01000000` | 1 |
| 19408 | 1 | `tx.input_count` | `01` | 1 |
| 19409 | 32 | `vin[0].prev_txid` | `80554bfd352b7017a717bd1d776ca4c957116cdda8a1e3767cc2ce5aaa689773` | 739768aa5acec27c76e3a1a8dd6c1157c9a46c771dbd17a717702b35fd4b5580 |
| 19441 | 4 | `vin[0].vout` | `01000000` | 1 |
| 19445 | 1 | `vin[0].scriptSig_length` | `6b` | 107 |
| 19446 | 107 | `vin[0].scriptSig` | `483045022100aadb85aa1f52ac285765347daca6c857128e12651ed668f00ba94e3c7457e402022046dfc351202a62f8eae6d28bd314d611f764e5d053012b67c94f6b813af15da5012102ca6e8883c76587087b68ed1a68e40148005c928c3d04f218fad4cc82c5753cfc` | 3045022100aadb85aa1f52ac285765347daca6c857128e12651ed668f00ba94e3c7457e402022046dfc351202a62f8eae6d28bd314d611f764e5d053012b67c94f6b813af15da501 02ca6e8883c76587087b68ed1a68e40148005c928c3d04f218fad4cc82c5753cfc |
| 19553 | 4 | `vin[0].sequence` | `ffffffff` | 4294967295 |
| 19557 | 1 | `tx.output_count` | `02` | 2 |
| 19558 | 8 | `vout[0].value` | `e803000000000000` | 1000 |
| 19566 | 1 | `vout[0].scriptPubKey_length` | `19` | 25 |
| 19567 | 25 | `vout[0].scriptPubKey` | `76a914343793e1a9dec99270a82f8bd3fd38c20ad22ae588ac` | OP_DUP OP_HASH160 343793e1a9dec99270a82f8bd3fd38c20ad22ae5 OP_EQUALVERIFY OP_CHECKSIG |
| 19592 | 8 | `vout[1].value` | `33c3020000000000` | 181043 |
| 19600 | 1 | `vout[1].scriptPubKey_length` | `19` | 25 |
| 19601 | 25 | `vout[1].scriptPubKey` | `76a914795165bc87638674400fad440bbcd9cddfe7a5f588ac` | OP_DUP OP_HASH160 795165bc87638674400fad440bbcd9cddfe7a5f5 OP_EQUALVERIFY OP_CHECKSIG |
| 19626 | 4 | `tx.locktime` | `00000000` | 0 |

## 交易 76: `c9cc7a3b97ed774ca9093a5a3a76a14ad360f792bd47359068ae910d072f2034`

| 偏移 | 字节数 | 字段 | 原始字节（线缆序） | 解释值 |
|---:|---:|---|---|---|
| 19630 | 4 | `tx.version` | `02000000` | 2 |
| 19634 | 1 | `tx.marker` | `00` | 0 |
| 19635 | 1 | `tx.flag` | `01` | 1 |
| 19636 | 1 | `tx.input_count` | `01` | 1 |
| 19637 | 32 | `vin[0].prev_txid` | `834af5d32f9749c4a60b6d85a70790b258ac111dd4ae58f493c08ea29e6f8c28` | 288c6f9ea28ec093f458aed41d11ac58b29007a7856d0ba6c449972fd3f54a83 |
| 19669 | 4 | `vin[0].vout` | `01000000` | 1 |
| 19673 | 1 | `vin[0].scriptSig_length` | `17` | 23 |
| 19674 | 23 | `vin[0].scriptSig` | `1600146d6754a041264713d36b3f396af19d6871fccaec` | 00146d6754a041264713d36b3f396af19d6871fccaec |
| 19697 | 4 | `vin[0].sequence` | `01000000` | 1 |
| 19701 | 1 | `tx.output_count` | `02` | 2 |
| 19702 | 8 | `vout[0].value` | `1b06000000000000` | 1563 |
| 19710 | 1 | `vout[0].scriptPubKey_length` | `17` | 23 |
| 19711 | 23 | `vout[0].scriptPubKey` | `a914b09f82739508fe18a4a2372fca3278bca146f1ad87` | OP_HASH160 b09f82739508fe18a4a2372fca3278bca146f1ad OP_EQUAL |
| 19734 | 8 | `vout[1].value` | `1103000000000000` | 785 |
| 19742 | 1 | `vout[1].scriptPubKey_length` | `17` | 23 |
| 19743 | 23 | `vout[1].scriptPubKey` | `a914f3b10d6da6df4e7366c875b4ea547af034172d0e87` | OP_HASH160 f3b10d6da6df4e7366c875b4ea547af034172d0e OP_EQUAL |
| 19766 | 1 | `witness[0].item_count` | `02` | 2 |
| 19767 | 1 | `witness[0][0].length` | `47` | 71 |
| 19768 | 71 | `witness[0][0].data` | `3044022053aa133ec043b238de59319c0d03ccef1134b09c983ab9a4c9cb529fe32cdce002203b5324ee968161fe135d3dd929b5f9157719b8c99e13c30efdb28cb5924ba3d601` | 3044022053aa133ec043b238de59319c0d03ccef1134b09c983ab9a4c9cb529fe32cdce002203b5324ee968161fe135d3dd929b5f9157719b8c99e13c30efdb28cb5924ba3d601 |
| 19839 | 1 | `witness[0][1].length` | `21` | 33 |
| 19840 | 33 | `witness[0][1].data` | `02a3938da9d27c38d0dc0218c7d681a7aeae57966b37e43293220e0eedfb32d411` | 02a3938da9d27c38d0dc0218c7d681a7aeae57966b37e43293220e0eedfb32d411 |
| 19873 | 4 | `tx.locktime` | `00000000` | 0 |

## 交易 77: `0b9bf19ee0f9882213f1817f128be28ef288d87e017bd2ac6271b1083807dc3c`

| 偏移 | 字节数 | 字段 | 原始字节（线缆序） | 解释值 |
|---:|---:|---|---|---|
| 19877 | 4 | `tx.version` | `02000000` | 2 |
| 19881 | 1 | `tx.marker` | `00` | 0 |
| 19882 | 1 | `tx.flag` | `01` | 1 |
| 19883 | 1 | `tx.input_count` | `01` | 1 |
| 19884 | 32 | `vin[0].prev_txid` | `8408819ccf6ddfd8cddd951262195778748b6c12d5c3e697eb0e9e5e8bfd83a3` | a383fd8b5e9e0eeb97e6c3d5126c8b74785719621295ddcdd8df6dcf9c810884 |
| 19916 | 4 | `vin[0].vout` | `01000000` | 1 |
| 19920 | 1 | `vin[0].scriptSig_length` | `00` | 0 |
| 19921 | 0 | `vin[0].scriptSig` | `（空）` |  |
| 19921 | 4 | `vin[0].sequence` | `fdffffff` | 4294967293 |
| 19925 | 1 | `tx.output_count` | `02` | 2 |
| 19926 | 8 | `vout[0].value` | `5f06000000000000` | 1631 |
| 19934 | 1 | `vout[0].scriptPubKey_length` | `16` | 22 |
| 19935 | 22 | `vout[0].scriptPubKey` | `0014e09acc19ee72d9ceb58dd5c1f538e5c8de5e0fa7` | OP_0 e09acc19ee72d9ceb58dd5c1f538e5c8de5e0fa7 |
| 19957 | 8 | `vout[1].value` | `5d8e020000000000` | 167517 |
| 19965 | 1 | `vout[1].scriptPubKey_length` | `16` | 22 |
| 19966 | 22 | `vout[1].scriptPubKey` | `00142f39a75b23e581ea4c15efa86017672910efea43` | OP_0 2f39a75b23e581ea4c15efa86017672910efea43 |
| 19988 | 1 | `witness[0].item_count` | `02` | 2 |
| 19989 | 1 | `witness[0][0].length` | `48` | 72 |
| 19990 | 72 | `witness[0][0].data` | `30450221008f978f146904965d22b804abdd0d9508c4e0cc235322faa3af84c0bd72b9def802205b5ae2afea2f860b53b06ffba633a45375abb0e112c6fa0fa11f612698882db001` | 30450221008f978f146904965d22b804abdd0d9508c4e0cc235322faa3af84c0bd72b9def802205b5ae2afea2f860b53b06ffba633a45375abb0e112c6fa0fa11f612698882db001 |
| 20062 | 1 | `witness[0][1].length` | `21` | 33 |
| 20063 | 33 | `witness[0][1].data` | `0272b5fd5318d1e37a018110790ce64c9c056fa0243fbf2c814ae82a5090e35611` | 0272b5fd5318d1e37a018110790ce64c9c056fa0243fbf2c814ae82a5090e35611 |
| 20096 | 4 | `tx.locktime` | `00000000` | 0 |

## 交易 78: `36edefcfcca79a085898cb1a4a3fb584bb5691a4b4a4be0555716deb4d0d165e`

| 偏移 | 字节数 | 字段 | 原始字节（线缆序） | 解释值 |
|---:|---:|---|---|---|
| 20100 | 4 | `tx.version` | `02000000` | 2 |
| 20104 | 1 | `tx.marker` | `00` | 0 |
| 20105 | 1 | `tx.flag` | `01` | 1 |
| 20106 | 1 | `tx.input_count` | `02` | 2 |
| 20107 | 32 | `vin[0].prev_txid` | `e9082314a167392e32bc31006e9dd6bfed1c3fde7011fe5d28af579f1683283f` | 3f2883169f57af285dfe1170de3f1cedbfd69d6e0031bc322e3967a1142308e9 |
| 20139 | 4 | `vin[0].vout` | `00000000` | 0 |
| 20143 | 1 | `vin[0].scriptSig_length` | `00` | 0 |
| 20144 | 0 | `vin[0].scriptSig` | `（空）` |  |
| 20144 | 4 | `vin[0].sequence` | `fdffffff` | 4294967293 |
| 20148 | 32 | `vin[1].prev_txid` | `8ed275e0e2c504fccd635788fe92dff30ac3600e34a5bd92bae28776b6a35bf3` | f35ba3b67687e2ba92bda5340e60c30af3df92fe885763cdfc04c5e2e075d28e |
| 20180 | 4 | `vin[1].vout` | `00000000` | 0 |
| 20184 | 1 | `vin[1].scriptSig_length` | `00` | 0 |
| 20185 | 0 | `vin[1].scriptSig` | `（空）` |  |
| 20185 | 4 | `vin[1].sequence` | `fdffffff` | 4294967293 |
| 20189 | 1 | `tx.output_count` | `02` | 2 |
| 20190 | 8 | `vout[0].value` | `5034030000000000` | 210000 |
| 20198 | 1 | `vout[0].scriptPubKey_length` | `19` | 25 |
| 20199 | 25 | `vout[0].scriptPubKey` | `76a914908bede265019208e13d232980bd785b66c51d1088ac` | OP_DUP OP_HASH160 908bede265019208e13d232980bd785b66c51d10 OP_EQUALVERIFY OP_CHECKSIG |
| 20224 | 8 | `vout[1].value` | `b412000000000000` | 4788 |
| 20232 | 1 | `vout[1].scriptPubKey_length` | `16` | 22 |
| 20233 | 22 | `vout[1].scriptPubKey` | `0014ee0ace0d161abcab8369f8adc0f577fcbc9d4de5` | OP_0 ee0ace0d161abcab8369f8adc0f577fcbc9d4de5 |
| 20255 | 1 | `witness[0].item_count` | `02` | 2 |
| 20256 | 1 | `witness[0][0].length` | `47` | 71 |
| 20257 | 71 | `witness[0][0].data` | `30440220035591aca0de94e15f9138c9d1df4ee7316e86036aab7c134b10358c2a69ff8e02202ca2984e6f11ddbf38ea4e816a23152331a88668fe2eb4fe8752998a15b38db401` | 30440220035591aca0de94e15f9138c9d1df4ee7316e86036aab7c134b10358c2a69ff8e02202ca2984e6f11ddbf38ea4e816a23152331a88668fe2eb4fe8752998a15b38db401 |
| 20328 | 1 | `witness[0][1].length` | `21` | 33 |
| 20329 | 33 | `witness[0][1].data` | `03b5368fb2da273f46a44b9d274e69b783498fbdd9fdb62679d944b3560ca62fce` | 03b5368fb2da273f46a44b9d274e69b783498fbdd9fdb62679d944b3560ca62fce |
| 20362 | 1 | `witness[1].item_count` | `02` | 2 |
| 20363 | 1 | `witness[1][0].length` | `48` | 72 |
| 20364 | 72 | `witness[1][0].data` | `3045022100fd8015799c8735aff84703b511f3d32b18ee306517a9aa3712993a1486ab4dc4022004e262cab329280f5a60b4d44110a10af5d1dfd9d9d92e16948555d8ce31e78b01` | 3045022100fd8015799c8735aff84703b511f3d32b18ee306517a9aa3712993a1486ab4dc4022004e262cab329280f5a60b4d44110a10af5d1dfd9d9d92e16948555d8ce31e78b01 |
| 20436 | 1 | `witness[1][1].length` | `21` | 33 |
| 20437 | 33 | `witness[1][1].data` | `03b5368fb2da273f46a44b9d274e69b783498fbdd9fdb62679d944b3560ca62fce` | 03b5368fb2da273f46a44b9d274e69b783498fbdd9fdb62679d944b3560ca62fce |
| 20470 | 4 | `tx.locktime` | `00000000` | 0 |

## 交易 79: `eee0ce0f2452b38ae0abbd3efe0fa38a63533333c3718cf5c544817d73487275`

| 偏移 | 字节数 | 字段 | 原始字节（线缆序） | 解释值 |
|---:|---:|---|---|---|
| 20474 | 4 | `tx.version` | `02000000` | 2 |
| 20478 | 1 | `tx.marker` | `00` | 0 |
| 20479 | 1 | `tx.flag` | `01` | 1 |
| 20480 | 1 | `tx.input_count` | `01` | 1 |
| 20481 | 32 | `vin[0].prev_txid` | `effef53b9d204a439e8e89270a975b72f69c67408aedfb3165f5686c3fea94b3` | b394ea3f6c68f56531fbed8a40679cf6725b970a27898e9e434a209d3bf5feef |
| 20513 | 4 | `vin[0].vout` | `01000000` | 1 |
| 20517 | 1 | `vin[0].scriptSig_length` | `17` | 23 |
| 20518 | 23 | `vin[0].scriptSig` | `1600146479461f2be7105fb2c07d5942704167f3f869ad` | 00146479461f2be7105fb2c07d5942704167f3f869ad |
| 20541 | 4 | `vin[0].sequence` | `01000000` | 1 |
| 20545 | 1 | `tx.output_count` | `01` | 1 |
| 20546 | 8 | `vout[0].value` | `c941020000000000` | 147913 |
| 20554 | 1 | `vout[0].scriptPubKey_length` | `17` | 23 |
| 20555 | 23 | `vout[0].scriptPubKey` | `a914a9505d31814acb484ce50e224953a50b9beeff1487` | OP_HASH160 a9505d31814acb484ce50e224953a50b9beeff14 OP_EQUAL |
| 20578 | 1 | `witness[0].item_count` | `02` | 2 |
| 20579 | 1 | `witness[0][0].length` | `48` | 72 |
| 20580 | 72 | `witness[0][0].data` | `3045022100b8767f3783d7bace542108881c9fa5e99510626368e094fbbf6e732ad14e28f202203881bde54e50bdc66275816da0287152e4d56428924fc3f8ae852e2fa84d959d01` | 3045022100b8767f3783d7bace542108881c9fa5e99510626368e094fbbf6e732ad14e28f202203881bde54e50bdc66275816da0287152e4d56428924fc3f8ae852e2fa84d959d01 |
| 20652 | 1 | `witness[0][1].length` | `21` | 33 |
| 20653 | 33 | `witness[0][1].data` | `02abcac2e506939962652d0729b8ff252203abc054b8c3c9a6d0f959702d8ffd1f` | 02abcac2e506939962652d0729b8ff252203abc054b8c3c9a6d0f959702d8ffd1f |
| 20686 | 4 | `tx.locktime` | `00000000` | 0 |

## 交易 80: `79003aad16c88b343b529398490c61c3a8b788e83109151055c93025aadc4aa0`

| 偏移 | 字节数 | 字段 | 原始字节（线缆序） | 解释值 |
|---:|---:|---|---|---|
| 20690 | 4 | `tx.version` | `02000000` | 2 |
| 20694 | 1 | `tx.marker` | `00` | 0 |
| 20695 | 1 | `tx.flag` | `01` | 1 |
| 20696 | 1 | `tx.input_count` | `01` | 1 |
| 20697 | 32 | `vin[0].prev_txid` | `79bd2c4a07960c4e3b405c6b015fe2c0bad2ea72a224f2a0124f8636dc372e13` | 132e37dc36864f12a0f224a272ead2bac0e25f016b5c403b4e0c96074a2cbd79 |
| 20729 | 4 | `vin[0].vout` | `01000000` | 1 |
| 20733 | 1 | `vin[0].scriptSig_length` | `17` | 23 |
| 20734 | 23 | `vin[0].scriptSig` | `160014eba65baa3daa299c53c2a68678d96b95a9cbd145` | 0014eba65baa3daa299c53c2a68678d96b95a9cbd145 |
| 20757 | 4 | `vin[0].sequence` | `01000000` | 1 |
| 20761 | 1 | `tx.output_count` | `02` | 2 |
| 20762 | 8 | `vout[0].value` | `1b29000000000000` | 10523 |
| 20770 | 1 | `vout[0].scriptPubKey_length` | `17` | 23 |
| 20771 | 23 | `vout[0].scriptPubKey` | `a914b09f82739508fe18a4a2372fca3278bca146f1ad87` | OP_HASH160 b09f82739508fe18a4a2372fca3278bca146f1ad OP_EQUAL |
| 20794 | 8 | `vout[1].value` | `cac1000000000000` | 49610 |
| 20802 | 1 | `vout[1].scriptPubKey_length` | `17` | 23 |
| 20803 | 23 | `vout[1].scriptPubKey` | `a914d6f6efd88aa955d63bc67bb497b07b7c764e624187` | OP_HASH160 d6f6efd88aa955d63bc67bb497b07b7c764e6241 OP_EQUAL |
| 20826 | 1 | `witness[0].item_count` | `02` | 2 |
| 20827 | 1 | `witness[0][0].length` | `47` | 71 |
| 20828 | 71 | `witness[0][0].data` | `30440220453d3f36db123664ff07b1c19bb9f211701e6b94d84682daad3e0375b231091602204e3816aec1ff4a0e10499360733fb65293a788f06dad7b507efb516203728c6601` | 30440220453d3f36db123664ff07b1c19bb9f211701e6b94d84682daad3e0375b231091602204e3816aec1ff4a0e10499360733fb65293a788f06dad7b507efb516203728c6601 |
| 20899 | 1 | `witness[0][1].length` | `21` | 33 |
| 20900 | 33 | `witness[0][1].data` | `03c1e3a4ea05a0c0477f0e52a1435a704eabef8c27d51216b97b9ceb41ce5e1428` | 03c1e3a4ea05a0c0477f0e52a1435a704eabef8c27d51216b97b9ceb41ce5e1428 |
| 20933 | 4 | `tx.locktime` | `00000000` | 0 |

## 交易 81: `40e4b820fb5df2b6a0fb23a2c7038a4631e3e2cca77d54ba1d37fafa9e6cb0df`

| 偏移 | 字节数 | 字段 | 原始字节（线缆序） | 解释值 |
|---:|---:|---|---|---|
| 20937 | 4 | `tx.version` | `02000000` | 2 |
| 20941 | 1 | `tx.marker` | `00` | 0 |
| 20942 | 1 | `tx.flag` | `01` | 1 |
| 20943 | 1 | `tx.input_count` | `01` | 1 |
| 20944 | 32 | `vin[0].prev_txid` | `fbd9627b3d3dcf3fd5bc224a696d611ab4d9c5334252f8e81c36bbee5814f038` | 38f01458eebb361ce8f8524233c5d9b41a616d694a22bcd53fcf3d3d7b62d9fb |
| 20976 | 4 | `vin[0].vout` | `01000000` | 1 |
| 20980 | 1 | `vin[0].scriptSig_length` | `17` | 23 |
| 20981 | 23 | `vin[0].scriptSig` | `1600142d76fda7e260958d5d410f8d6620a0d14c3572e5` | 00142d76fda7e260958d5d410f8d6620a0d14c3572e5 |
| 21004 | 4 | `vin[0].sequence` | `01000000` | 1 |
| 21008 | 1 | `tx.output_count` | `02` | 2 |
| 21009 | 8 | `vout[0].value` | `1411000000000000` | 4372 |
| 21017 | 1 | `vout[0].scriptPubKey_length` | `17` | 23 |
| 21018 | 23 | `vout[0].scriptPubKey` | `a914b09f82739508fe18a4a2372fca3278bca146f1ad87` | OP_HASH160 b09f82739508fe18a4a2372fca3278bca146f1ad OP_EQUAL |
| 21041 | 8 | `vout[1].value` | `5103000000000000` | 849 |
| 21049 | 1 | `vout[1].scriptPubKey_length` | `17` | 23 |
| 21050 | 23 | `vout[1].scriptPubKey` | `a914790e079177ae412286175359ef6bd3fcdd40355987` | OP_HASH160 790e079177ae412286175359ef6bd3fcdd403559 OP_EQUAL |
| 21073 | 1 | `witness[0].item_count` | `02` | 2 |
| 21074 | 1 | `witness[0][0].length` | `48` | 72 |
| 21075 | 72 | `witness[0][0].data` | `3045022100c7bfdb8fcddd1ec233435097efc80a9bd61967ba58352d9a47c2a8cda1fa9aab02200a0e3ecef5606289975f0e11175d6600b3b1d08e8634bd7909b4ac799809e87b01` | 3045022100c7bfdb8fcddd1ec233435097efc80a9bd61967ba58352d9a47c2a8cda1fa9aab02200a0e3ecef5606289975f0e11175d6600b3b1d08e8634bd7909b4ac799809e87b01 |
| 21147 | 1 | `witness[0][1].length` | `21` | 33 |
| 21148 | 33 | `witness[0][1].data` | `03bef5d73c44c3b5d45d48c59e8f8c0aebae9334e49ceabffcf296d5653292410a` | 03bef5d73c44c3b5d45d48c59e8f8c0aebae9334e49ceabffcf296d5653292410a |
| 21181 | 4 | `tx.locktime` | `00000000` | 0 |

## 交易 82: `dd149f69675bc3e8198e9dc4a68cf8edd60efcac5025398f57c040ff620afbf3`

| 偏移 | 字节数 | 字段 | 原始字节（线缆序） | 解释值 |
|---:|---:|---|---|---|
| 21185 | 4 | `tx.version` | `02000000` | 2 |
| 21189 | 1 | `tx.marker` | `00` | 0 |
| 21190 | 1 | `tx.flag` | `01` | 1 |
| 21191 | 1 | `tx.input_count` | `01` | 1 |
| 21192 | 32 | `vin[0].prev_txid` | `369c451411af436a4389f15d0995e3067640549c67358392ac36c45f06915a50` | 505a91065fc436ac928335679c54407606e395095df189436a43af1114459c36 |
| 21224 | 4 | `vin[0].vout` | `00000000` | 0 |
| 21228 | 1 | `vin[0].scriptSig_length` | `23` | 35 |
| 21229 | 35 | `vin[0].scriptSig` | `220020b80728837349412c3cdb758d93bd25ef67ed2838907c54ce2ffacea0f0036365` | 0020b80728837349412c3cdb758d93bd25ef67ed2838907c54ce2ffacea0f0036365 |
| 21264 | 4 | `vin[0].sequence` | `feffffff` | 4294967294 |
| 21268 | 1 | `tx.output_count` | `02` | 2 |
| 21269 | 8 | `vout[0].value` | `e698130000000000` | 1284326 |
| 21277 | 1 | `vout[0].scriptPubKey_length` | `17` | 23 |
| 21278 | 23 | `vout[0].scriptPubKey` | `a91416efa6be847cb013aa3192c84cf29b8cc8519d5a87` | OP_HASH160 16efa6be847cb013aa3192c84cf29b8cc8519d5a OP_EQUAL |
| 21301 | 8 | `vout[1].value` | `1027000000000000` | 10000 |
| 21309 | 1 | `vout[1].scriptPubKey_length` | `16` | 22 |
| 21310 | 22 | `vout[1].scriptPubKey` | `0014e41391effbbfcb914628b6b2e59c05cbbf740235` | OP_0 e41391effbbfcb914628b6b2e59c05cbbf740235 |
| 21332 | 1 | `witness[0].item_count` | `04` | 4 |
| 21333 | 1 | `witness[0][0].length` | `00` | 0 |
| 21334 | 0 | `witness[0][0].data` | `（空）` |  |
| 21334 | 1 | `witness[0][1].length` | `47` | 71 |
| 21335 | 71 | `witness[0][1].data` | `304402207ac0f0af381c8ecea3c16a897b8fd5d377f8365b3b0a553193ea4d38bb37bd6802201f6018118771b51b09fa07e86660194e2fdd7017f49630d85cbd3b0661a3a27501` | 304402207ac0f0af381c8ecea3c16a897b8fd5d377f8365b3b0a553193ea4d38bb37bd6802201f6018118771b51b09fa07e86660194e2fdd7017f49630d85cbd3b0661a3a27501 |
| 21406 | 1 | `witness[0][2].length` | `47` | 71 |
| 21407 | 71 | `witness[0][2].data` | `3044022009ff9274700cbdac2a8a6697d5f8c87057f98494d29ef280ab1521765556436a022011ce4f93d9ad33aad91844a091645b28f1904adf77d2eedbba3da03aae1330a001` | 3044022009ff9274700cbdac2a8a6697d5f8c87057f98494d29ef280ab1521765556436a022011ce4f93d9ad33aad91844a091645b28f1904adf77d2eedbba3da03aae1330a001 |
| 21478 | 1 | `witness[0][3].length` | `69` | 105 |
| 21479 | 105 | `witness[0][3].data` | `5221029c09f128798be9d8b6137b568cc6abb595807768c4179e3674411d6e14ca94042103de348025f922cbc65dbf9340e79d67a813a6beab845539e8847eaf862ec0758a2103bda9fc3ebda9145eadbdd396dfbda31db4e4eed7c7bcb242fc14c14ec8f20b2553ae` | 5221029c09f128798be9d8b6137b568cc6abb595807768c4179e3674411d6e14ca94042103de348025f922cbc65dbf9340e79d67a813a6beab845539e8847eaf862ec0758a2103bda9fc3ebda9145eadbdd396dfbda31db4e4eed7c7bcb242fc14c14ec8f20b2553ae |
| 21584 | 4 | `tx.locktime` | `00000000` | 0 |

## 交易 83: `254099d0bca2738be72aeff985b9b4ec49b1afa9396aca3bb6841e3ba8469ff5`

| 偏移 | 字节数 | 字段 | 原始字节（线缆序） | 解释值 |
|---:|---:|---|---|---|
| 21588 | 4 | `tx.version` | `02000000` | 2 |
| 21592 | 1 | `tx.marker` | `00` | 0 |
| 21593 | 1 | `tx.flag` | `01` | 1 |
| 21594 | 1 | `tx.input_count` | `01` | 1 |
| 21595 | 32 | `vin[0].prev_txid` | `24056bef6e464c774fbbac0094969c9fd68e2e1cb98baecd7218f2fa0fae07a6` | a607ae0ffaf21872cdae8bb91c2e8ed69f9c969400acbb4f774c466eef6b0524 |
| 21627 | 4 | `vin[0].vout` | `01000000` | 1 |
| 21631 | 1 | `vin[0].scriptSig_length` | `17` | 23 |
| 21632 | 23 | `vin[0].scriptSig` | `160014731f4af8cf4d2706c8b769e750966608e5437c88` | 0014731f4af8cf4d2706c8b769e750966608e5437c88 |
| 21655 | 4 | `vin[0].sequence` | `01000000` | 1 |
| 21659 | 1 | `tx.output_count` | `02` | 2 |
| 21660 | 8 | `vout[0].value` | `b808000000000000` | 2232 |
| 21668 | 1 | `vout[0].scriptPubKey_length` | `17` | 23 |
| 21669 | 23 | `vout[0].scriptPubKey` | `a914b09f82739508fe18a4a2372fca3278bca146f1ad87` | OP_HASH160 b09f82739508fe18a4a2372fca3278bca146f1ad OP_EQUAL |
| 21692 | 8 | `vout[1].value` | `7d02000000000000` | 637 |
| 21700 | 1 | `vout[1].scriptPubKey_length` | `17` | 23 |
| 21701 | 23 | `vout[1].scriptPubKey` | `a914a592ab33e8f8a8a4596a0746d1e60ec3d130d5e187` | OP_HASH160 a592ab33e8f8a8a4596a0746d1e60ec3d130d5e1 OP_EQUAL |
| 21724 | 1 | `witness[0].item_count` | `02` | 2 |
| 21725 | 1 | `witness[0][0].length` | `47` | 71 |
| 21726 | 71 | `witness[0][0].data` | `304402202465fb6363bbed59ab15580679b87e0e719ac34208ac0d85982bca04d9c8868202202277769296a4a7b39a467840df0b0589e67cd8342e7126a52e90a2e016b6b4c901` | 304402202465fb6363bbed59ab15580679b87e0e719ac34208ac0d85982bca04d9c8868202202277769296a4a7b39a467840df0b0589e67cd8342e7126a52e90a2e016b6b4c901 |
| 21797 | 1 | `witness[0][1].length` | `21` | 33 |
| 21798 | 33 | `witness[0][1].data` | `030d3fe08402ad5e3f35fc664c4afac9f1eb2590c6ab192be9b650cea24ff6dbda` | 030d3fe08402ad5e3f35fc664c4afac9f1eb2590c6ab192be9b650cea24ff6dbda |
| 21831 | 4 | `tx.locktime` | `00000000` | 0 |

## 交易 84: `9b670015859b2f37827d0ae5f71cee5fb642689bff8f5a6d83d224b1084c03fc`

| 偏移 | 字节数 | 字段 | 原始字节（线缆序） | 解释值 |
|---:|---:|---|---|---|
| 21835 | 4 | `tx.version` | `02000000` | 2 |
| 21839 | 1 | `tx.marker` | `00` | 0 |
| 21840 | 1 | `tx.flag` | `01` | 1 |
| 21841 | 1 | `tx.input_count` | `01` | 1 |
| 21842 | 32 | `vin[0].prev_txid` | `357497f2554eef14882e73032a25e1804c2572109f961ad153159014f48c0834` | 34088cf414901553d11a969f1072254c80e1252a03732e8814ef4e55f2977435 |
| 21874 | 4 | `vin[0].vout` | `01000000` | 1 |
| 21878 | 1 | `vin[0].scriptSig_length` | `17` | 23 |
| 21879 | 23 | `vin[0].scriptSig` | `160014db2dbd8c46f7bee44986d158a8b147638a0166dc` | 0014db2dbd8c46f7bee44986d158a8b147638a0166dc |
| 21902 | 4 | `vin[0].sequence` | `01000000` | 1 |
| 21906 | 1 | `tx.output_count` | `02` | 2 |
| 21907 | 8 | `vout[0].value` | `f514000000000000` | 5365 |
| 21915 | 1 | `vout[0].scriptPubKey_length` | `17` | 23 |
| 21916 | 23 | `vout[0].scriptPubKey` | `a914b09f82739508fe18a4a2372fca3278bca146f1ad87` | OP_HASH160 b09f82739508fe18a4a2372fca3278bca146f1ad OP_EQUAL |
| 21939 | 8 | `vout[1].value` | `f303010000000000` | 66547 |
| 21947 | 1 | `vout[1].scriptPubKey_length` | `17` | 23 |
| 21948 | 23 | `vout[1].scriptPubKey` | `a914da8d42a7db29f05eb3b0e7e491b13f45eff7e90487` | OP_HASH160 da8d42a7db29f05eb3b0e7e491b13f45eff7e904 OP_EQUAL |
| 21971 | 1 | `witness[0].item_count` | `02` | 2 |
| 21972 | 1 | `witness[0][0].length` | `47` | 71 |
| 21973 | 71 | `witness[0][0].data` | `304402200cc61863d7b9420a72ea2fc976a57e32919d633e95564acca8e31a109306817702205287d5c82af926b10f24dc191dd46db27a3fef599cfdc590a1e790e4569cec7b01` | 304402200cc61863d7b9420a72ea2fc976a57e32919d633e95564acca8e31a109306817702205287d5c82af926b10f24dc191dd46db27a3fef599cfdc590a1e790e4569cec7b01 |
| 22044 | 1 | `witness[0][1].length` | `21` | 33 |
| 22045 | 33 | `witness[0][1].data` | `038d4773ce73b67676e73289332f09b3c7eefda292773b4d2a5a0dcd76c9184511` | 038d4773ce73b67676e73289332f09b3c7eefda292773b4d2a5a0dcd76c9184511 |
| 22078 | 4 | `tx.locktime` | `00000000` | 0 |

## 交易 85: `f8d5680734e371b62e9fa0dde62a84bcab19f7bb677bbb42f8efb6371edf3e27`

| 偏移 | 字节数 | 字段 | 原始字节（线缆序） | 解释值 |
|---:|---:|---|---|---|
| 22082 | 4 | `tx.version` | `01000000` | 1 |
| 22086 | 1 | `tx.input_count` | `01` | 1 |
| 22087 | 32 | `vin[0].prev_txid` | `1b609c4ee761c04abf5824ce5b17b63017df38403e7ba71a98ff783611964cd7` | d74c96113678ff981aa77b3e4038df1730b6175bce2458bf4ac061e74e9c601b |
| 22119 | 4 | `vin[0].vout` | `01000000` | 1 |
| 22123 | 1 | `vin[0].scriptSig_length` | `6b` | 107 |
| 22124 | 107 | `vin[0].scriptSig` | `483045022100b5e8951d95d5449d1cd4b875b51971fea9477c2994174cbcfc604092f233db3c02201268909e87da7175f9bdb1c1f6bc801b46fc1bcff75488ec7c820aba830f2149012102a61dacdac54e257c3c64e1d0e644b5d393e7972c01094320fbb6649543c76e6d` | 3045022100b5e8951d95d5449d1cd4b875b51971fea9477c2994174cbcfc604092f233db3c02201268909e87da7175f9bdb1c1f6bc801b46fc1bcff75488ec7c820aba830f214901 02a61dacdac54e257c3c64e1d0e644b5d393e7972c01094320fbb6649543c76e6d |
| 22231 | 4 | `vin[0].sequence` | `ffffffff` | 4294967295 |
| 22235 | 1 | `tx.output_count` | `02` | 2 |
| 22236 | 8 | `vout[0].value` | `ff3c000000000000` | 15615 |
| 22244 | 1 | `vout[0].scriptPubKey_length` | `17` | 23 |
| 22245 | 23 | `vout[0].scriptPubKey` | `a914b97d534af4e68a8075ee41f9501628b7641df71387` | OP_HASH160 b97d534af4e68a8075ee41f9501628b7641df713 OP_EQUAL |
| 22268 | 8 | `vout[1].value` | `f1bc000000000000` | 48369 |
| 22276 | 1 | `vout[1].scriptPubKey_length` | `19` | 25 |
| 22277 | 25 | `vout[1].scriptPubKey` | `76a914a2f561d77c0efa8cdd1d6185aeb59acac50bdf6688ac` | OP_DUP OP_HASH160 a2f561d77c0efa8cdd1d6185aeb59acac50bdf66 OP_EQUALVERIFY OP_CHECKSIG |
| 22302 | 4 | `tx.locktime` | `00000000` | 0 |

## 交易 86: `5b43c9220bbbd97639e4e00851e9bbaceffcbd6554dce60f7b3371279d091c89`

| 偏移 | 字节数 | 字段 | 原始字节（线缆序） | 解释值 |
|---:|---:|---|---|---|
| 22306 | 4 | `tx.version` | `02000000` | 2 |
| 22310 | 1 | `tx.marker` | `00` | 0 |
| 22311 | 1 | `tx.flag` | `01` | 1 |
| 22312 | 1 | `tx.input_count` | `01` | 1 |
| 22313 | 32 | `vin[0].prev_txid` | `ff2f71f922774c9925993126e4406f9044259880e007be19d820789ffbd8a9cb` | cba9d8fb9f7820d819be07e080982544906f40e426319925994c7722f9712fff |
| 22345 | 4 | `vin[0].vout` | `01000000` | 1 |
| 22349 | 1 | `vin[0].scriptSig_length` | `00` | 0 |
| 22350 | 0 | `vin[0].scriptSig` | `（空）` |  |
| 22350 | 4 | `vin[0].sequence` | `ffffffff` | 4294967295 |
| 22354 | 1 | `tx.output_count` | `02` | 2 |
| 22355 | 8 | `vout[0].value` | `e02e000000000000` | 12000 |
| 22363 | 1 | `vout[0].scriptPubKey_length` | `16` | 22 |
| 22364 | 22 | `vout[0].scriptPubKey` | `0014345398a6ad9f6198c160c9b4d33a903a095e686a` | OP_0 345398a6ad9f6198c160c9b4d33a903a095e686a |
| 22386 | 8 | `vout[1].value` | `ad212a0100000000` | 19538349 |
| 22394 | 1 | `vout[1].scriptPubKey_length` | `16` | 22 |
| 22395 | 22 | `vout[1].scriptPubKey` | `0014635df6a11acc784e8882ed3c620fd06e220d3e72` | OP_0 635df6a11acc784e8882ed3c620fd06e220d3e72 |
| 22417 | 1 | `witness[0].item_count` | `02` | 2 |
| 22418 | 1 | `witness[0][0].length` | `47` | 71 |
| 22419 | 71 | `witness[0][0].data` | `304402203915efd1defa574db9bd888a690ad45da2d9a530b248dfea3bd231b87857ab770220370196218d585e58a8b397c28f5a34f6384a8953a2a0be3bee539440de48e1ad01` | 304402203915efd1defa574db9bd888a690ad45da2d9a530b248dfea3bd231b87857ab770220370196218d585e58a8b397c28f5a34f6384a8953a2a0be3bee539440de48e1ad01 |
| 22490 | 1 | `witness[0][1].length` | `21` | 33 |
| 22491 | 33 | `witness[0][1].data` | `03eb72d1b6304d047b61578076d6a4c438cfa33e2465595c565a869bdb63157a1b` | 03eb72d1b6304d047b61578076d6a4c438cfa33e2465595c565a869bdb63157a1b |
| 22524 | 4 | `tx.locktime` | `00000000` | 0 |

> 偏移从 0 开始；多字节整数按比特币协议使用小端序。
