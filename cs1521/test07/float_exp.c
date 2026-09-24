#include "float_exp.h"

// given the 32 bits of a float return the exponent
uint32_t float_exp(uint32_t f) {
    int bit_mask = 0xFF;
    bit_mask <<= 23;
    return (bit_mask & f) >> 23;
}
