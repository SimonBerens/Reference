### parity_naive
The naive approach processes one bit at a time, xoring the bit under examination with the current parity. Xoring has the 
effect of performing an addition with no carry, which suits our purposes since we only need to store the number of bits 
modulo 2. This approach has a time complexity of O(n) where n is the number of bits it takes to represent the number.

### parity_clear_lowest_bit
Similar to count_bits, we can take advantage of the fact that x &= (x - 1) resets the lowest set bit. Again, this makes
it a lot faster for sparse numbers but the complexity is still O(n).

### parity_self_xor
Xoring the two halves of a number turns out to preserve its parity. This is because equal bits will have no effect on
the parity, so we can set them to 0, while different bits will change the parity, so essentially we have to find the
parity of the number of different bits. Because this is a recursive definition, we can keep xoring the number with its 
two halves (which we make smaller each iteration) until there is only 1 valid bit, which we extract with a bit mask.
Note that the upper bits become useless, but they do not affect the calculation after they are used. This approach has a
time complexity of O(logn). 

### parity_lookup_table
This approach uses a precomputed lookup table to remove the final 4 xors. This approach should only be used on either 
massive numbers or many numbers to offset the cost of generating the lookup table. Like parity_self_xor, this has a 
time complexity of O(logn).

### other
parity_self_xor and parity_lookup_table seem to be dependent on the number of bits in the number, but with a few tricks 
O(logn) complexity can be maintained. Namely, to find the the lowest power of 2 bits that is needed to represent the
number, one simply has to do something like this:
```python
def parity(x: int) -> int:
    bits: int = 1
    while (1 << bits) < x:
        bits *= 2
    # ...
```
From there, continue perform xor/lookup as usual, starting with `x ^= (x >> (bits / 2))`.