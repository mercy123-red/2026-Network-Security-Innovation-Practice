import sys
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT))
import bitcoin_lab as b


class BitcoinLabTests(unittest.TestCase):
    def test_testnet_genesis_block(self):
        raw = bytes.fromhex((ROOT / "samples/testnet_genesis_block.hex").read_text().strip())
        result = b.parse_block(raw)
        self.assertEqual(result["block_hash"], "000000000933ea01ad0ee984209779baaec3ced90fa3f408719526f8d77f4943")
        self.assertTrue(result["merkle_valid"])
        self.assertTrue(result["pow_valid"])
        self.assertEqual(result["transaction_count"], 1)
        self.assertEqual(result["transactions"][0]["txid"],
                         "4a5e1e4baab89f3a32518a88c31bc87f618f76673e2cc77ab2127b7afdeda33b")

    def test_wif_and_address_known_vector(self):
        wif = b.secret_to_wif(1)
        secret, compressed = b.wif_to_secret(wif)
        self.assertEqual(secret, 1)
        self.assertTrue(compressed)
        self.assertEqual(b.p2pkh_address(b.public_key(secret)), "mrCDrCybB6J1vRfbwM5hemdJz73FwDBC8r")

    def test_varint_boundaries(self):
        self.assertEqual(b.encode_varint(0xfc), bytes.fromhex("fc"))
        self.assertEqual(b.encode_varint(0xfd), bytes.fromhex("fdfd00"))
        self.assertEqual(b.encode_varint(0x10000), bytes.fromhex("fe00000100"))


if __name__ == "__main__":
    unittest.main()
