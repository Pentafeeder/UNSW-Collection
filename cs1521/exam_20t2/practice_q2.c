#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

// given a uint32_t value,
// return 1 iff the least significant (bottom) byte
// is equal to the 2nd least significant byte; and
// return 0 otherwise
int practice_q2(uint32_t value) {
    // PUT YOUR CODE HERE
    uint32_t bit_mask = 0xFF;

    uint32_t least_sig_byte = bit_mask & value;
    bit_mask <<= 8;
    uint32_t second_least_sig_byte = (bit_mask & value) >> 8;

    
    return (least_sig_byte == second_least_sig_byte);
}
