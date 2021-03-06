#include <iostream>
#include <array>
#include <cmath>
// todo c++20 #include <bit>

using namespace std;

uint count_bits_naive(ulong x) {
    uint n_bits = 0u;
    while (x) {
        n_bits += x & 1u;
        x >>= 1ul;
    }
    return n_bits;
}

uint count_bits_clear_lowest_bit(ulong x) {
    uint n_bits = 0;
    while (x) {
        ++n_bits;
        x &= (x - 1);
    }
    return n_bits;
}

template <uint LookupBitSize>
struct LookupTable {
    LookupTable() {
        for (uint i = 0; i < 1u << LookupBitSize; ++i)
            table[i] = count_bits_clear_lowest_bit(i);
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


uint count_bits_lookup_table(ulong x) {
    uint n_bits = 0;
    while (x) {
        n_bits += lookupTable[x & lookupTable.get_mask()];
        x >>= lookupTable.get_lookup_bit_size();
    }
    return n_bits;
}

uint count_bits_library(uint x) { // note: __builtin_popcount takes an unsigned integer
    return __builtin_popcount(x); // GCC specific, todo c++20 std::popcount
}

int main() {}