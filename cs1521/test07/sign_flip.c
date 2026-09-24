#include "sign_flip.h"

// given the 32 bits of a float return it with its sign flipped
uint32_t sign_flip(uint32_t f) {
    uint32_t bit_mask = 1;
    bit_mask <<= 31;
    if ((bit_mask & f) >> 31 == 1) {
        f <<= 1;
        f >>= 1;
    } else {
        f |= bit_mask;
    }
    return f;
    
}
