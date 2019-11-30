from typing import *


def count_bits_naive(x: int) -> int:
    n_bits: int = 0
    while x:
        n_bits += x & 1
        x >>= 1
    return n_bits


def count_bits_clear_lowest_bit(x: int) -> int:
    n_bits: int = 0
    while x:
        n_bits += 1
        x &= (x - 1)
    return n_bits


lookup_bit_size: int = 16
popcount_lookup: List[int] = []
for i in range(2 ** lookup_bit_size):
    popcount_lookup.append(count_bits_clear_lowest_bit(i))
lookup_mask = (1 << lookup_bit_size) - 1


def count_bits_lookup_table(x: int) -> int:
    n_bits: int = 0
    while x:
        n_bits += popcount_lookup[x & lookup_mask]
        x >>= lookup_bit_size
    return n_bits


def count_bits_library(x: int) -> int:
    return bin(x).count('1')
