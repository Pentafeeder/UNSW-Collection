// COMP1521 22T3 ... final exam, question 4

#include <stdint.h>

int _22t3final_q4(uint32_t x) {
    
    int highest_consecutive = 0;
    uint32_t bit_mask = 0x03;
    int consecutive_set_bit = x & 1;
    
    for (int i = 0; i < 32; i++) {
        uint32_t bit = x & bit_mask;
        bit >>= i;

        if (bit == 0x03) {
            consecutive_set_bit++;
        } else if (bit == 0x02) {
            consecutive_set_bit = 1;
        } else if (bit == 0x01) {
            if (consecutive_set_bit > highest_consecutive) {
                highest_consecutive = consecutive_set_bit;
            }
            consecutive_set_bit = 0;
        }
        
        if (i < 31) {
           bit_mask <<= 1;
        }

    }

    if (consecutive_set_bit > highest_consecutive) {
        highest_consecutive = consecutive_set_bit;
    }

    return highest_consecutive;
}
