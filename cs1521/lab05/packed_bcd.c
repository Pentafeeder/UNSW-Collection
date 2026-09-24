#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#define N_BCD_DIGITS 8

uint32_t packed_bcd(uint32_t packed_bcd);

int main(int argc, char *argv[]) {

    for (int arg = 1; arg < argc; arg++) {
        long l = strtol(argv[arg], NULL, 0);
        assert(l >= 0 && l <= UINT32_MAX);
        uint32_t packed_bcd_value = l;

        printf("%lu\n", (unsigned long)packed_bcd(packed_bcd_value));
    }

    return 0;
}

// given a packed BCD encoded value between 0 .. 99999999
// return the corresponding integer
uint32_t packed_bcd(uint32_t packed_bcd_value) {

    // PUT YOUR CODE HERE
    int bit_mask = 1;
    bit_mask <<= 4;
    bit_mask -= 1;
    int decimal_value = 0;
    int power = 1;
    for (int i = 0; i < 8; i++) {
        int integer = bit_mask & packed_bcd_value;
        decimal_value += integer * power;
        power *= 10;
        packed_bcd_value >>= 4;
    }
    return decimal_value;
}
