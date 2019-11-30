### count_bits_naive
The naive approach processes one bit at a time, checking if it is set or not. It has O(n) time complexity where n is 
the number of bits needed to represent the number

### count_bits_clear_lowest_bit
This method takes advantage of the fact that by subtracting one from a number you reset its lowest set bit and set all
the 0 bits before it. Thus, bitwise anding it with itself - 1 will reset the lowest set bit. You can use this to skip 
over unset bits in one operation, which greatly speeds things up for sparse numbers. This method still has O(n) time 
complexity.

### count_bits_lookup_table 
This approach uses a precomputed lookup table to speed things up by a the bit width of the lookup table. Thus, despite 
being 16x faster it is still O(n). Also, to offset the constant factor, it is best to use this approach when processing
multiple values.

### other
The number of set bits in a number is called the hamming weight. It can be implemented faster (I think O(logn)).
 
[Bithacks](https://graphics.stanford.edu/~seander/bithacks.html)

[Hamming Weight Divergence](https://math.stackexchange.com/questions/2836040/does-the-hamming-weight-of-n-to-infty-diverge-or-converge)