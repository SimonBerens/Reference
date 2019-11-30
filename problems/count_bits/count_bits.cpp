#include <iostream>
#include <array>
#include <cmath>
// #include <bit> todo: coming in C++ 20

using namespace std;

/**
 * The naive approach processes one bit at a time
 * O(n) time complexity where n is the number of bits
 */
uint count_bits_naive(ulong x) {
    uint n_bits = 0u;
    while (x) {
        n_bits += x & 1u;
        x >>= 1ul;
    }
    return n_bits;
}

/**
 * This approach takes advantage of the fact that x &= (x - 1) clears the lowest set bit
 * This means we can process multiple bits at a time with a single operation
 * Still O(n) but significantly faster for sparse numbers
 */
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

/**
 * This approach uses a precomputed lookup table
 * This is only useful for processing multiple numbers, or numbers with an extremely large number of bits
 * Still O(n) time complexity
 */
uint count_bits_lookup_table(ulong x) {
    uint n_bits = 0;
    while (x) {
        n_bits += lookupTable[x & lookupTable.get_mask()];
        x >>= lookupTable.get_lookup_bit_size();
    }
    return n_bits;
}

uint count_bits_library(uint x) { // note: __builtin_popcount takes an unsigned integer
    return __builtin_popcount(x); // GCC specific, todo std::popcount coming in C++20
}

// todo: this is called hamming weight and can be implemented much more efficiently, do more research

int main() {}