#include <iostream>
#include <array>

using namespace std;

ushort parity_naive(ulong x) {
    ushort parity = 0;
    while (x) {
        parity ^= (x & 1u);
        x >>= 1u;
    }
    return parity;
}

ushort parity_clear_lowest_bit(ulong x) {
    ushort parity = 0;
    while (x) {
        parity ^= 1u;
        x &= (x - 1);
    }
    return parity;
}

ushort parity_self_xor(ulong x) {
    x ^= x >> 32u;
    x ^= x >> 16u;
    x ^= x >> 8u;
    x ^= x >> 4u;
    x ^= x >> 2u;
    x ^= x >> 1u;
    return x & 1u;
}


template <uint LookupBitSize>
struct LookupTable {
    LookupTable() {
        for (uint i = 0; i < 1u << LookupBitSize; ++i)
            table[i] = parity_self_xor(i);
    }

    array<uint, 1u << LookupBitSize> table;

    inline uint operator[](uint i) const {
        return table[i];
    }

    constexpr uint get_mask() {
        return (1u << LookupBitSize) - 1;
    }

    constexpr uint get_lookup_bit_size() {
        return LookupBitSize;
    }
};

LookupTable<16> lookupTable;

ushort parity_lookup_table(ulong x) {
    x ^= x >> 32u;
    x ^= x >> 16u;
    return lookupTable[x & lookupTable.get_mask()];
}

ushort parity_library(uint x) {
    return __builtin_popcount(x) % 2;
}

int main() {}