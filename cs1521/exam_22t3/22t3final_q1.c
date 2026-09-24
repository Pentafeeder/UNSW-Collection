// COMP1521 22T3 ... final exam, question 1

#include <stdint.h>

uint32_t _22t3final_q1(uint32_t x) {
    uint32_t bit_mask = 0xFF;

    bit_mask <<= 12;

    return (bit_mask & x) >> 12;
}
