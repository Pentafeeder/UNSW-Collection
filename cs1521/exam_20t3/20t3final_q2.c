// COMP1521 20T3 final exam Q2 starter code

#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

// given a uint32_t,
// return 1 iff the least significant bit
// is equal to the most significant bit
// return 0 otherwise
int final_q2(uint32_t value) {
    uint32_t bit_mask = 1;

    int least_sig_bit = value & bit_mask;

    int most_sig_bit = (value & (bit_mask << 31)) >> 31; 
    
    return most_sig_bit == least_sig_bit;    // REPLACE ME WITH YOUR CODE
}
