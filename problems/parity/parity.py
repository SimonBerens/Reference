from typing import *


def parity_naive(x: int) -> int:
    parity: int = 0
    while x:
        parity ^= x & 1
        x >>= 1
    return parity


def parity_clear_lowest_bit(x: int) -> int:
    parity: int = 0
    while x:
        parity ^= 1
        x &= (x - 1)
    return parity


def parity_self_xor(x: int) -> int:
    x ^= x >> 32
    x ^= x >> 16
    x ^= x >> 8
    x ^= x >> 4
    x ^= x >> 2
    x ^= x >> 1
    return x & 1


lookup_bit_size = 16
lookup_table: List[int] = []
for i in range(2 ** lookup_bit_size):
    lookup_table.append(parity_self_xor(i))
lookup_mask = (1 << lookup_bit_size) - 1


def parity_lookup_table(x: int) -> int:
    x ^= x >> 32
    x ^= x >> 16
    return lookup_table[x & lookup_mask]


def parity_library(x: int) -> int:
    return bin(x).count('1') % 2
