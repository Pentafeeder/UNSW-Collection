// swap pairs of bits of a 64-bit value, using bitwise operators

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

// return value with pairs of bits swapped
uint64_t bit_swap(uint64_t value) {
    // PUT YOUR CODE HERE
    
    uint64_t swapped_bits = 0;
    int nth_bit_pair = 0;

    for (int i = 0; i < 32; i++) {
      
        uint64_t bit1 = 1;
        uint64_t bit2 = 1;
       
        bit1 <<= nth_bit_pair;
        bit2 <<= nth_bit_pair + 1;

        bit1 = bit1 & value;
        bit2 = bit2 & value;
        
        // swapping bits
        bit1 <<= 1;
        bit2 >>= 1;

        swapped_bits = swapped_bits | bit1;
        swapped_bits = swapped_bits | bit2;

          nth_bit_pair += 2;
    }
    return swapped_bits;
}
