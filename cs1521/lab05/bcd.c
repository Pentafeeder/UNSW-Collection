#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

int bcd(int bcd_value);

int main(int argc, char *argv[]) {

    for (int arg = 1; arg < argc; arg++) {
        long l = strtol(argv[arg], NULL, 0);
        assert(l >= 0 && l <= 0x0909);
        int bcd_value = l;

        printf("%d\n", bcd(bcd_value));
    }

    return 0;
}

// given a  BCD encoded value between 0 .. 99
// return corresponding integer
int bcd(int bcd_value) {

    // PUT YOUR CODE HERE
    int bit_mask = 1;
    bit_mask <<= 8;                     // bit_mask = 10000000
    bit_mask -= 1;                      // bit_mask = 01111111 (8th bit part of tens place)
    int units = bcd_value & bit_mask;

    bcd_value >>= 8;
    int tens = bcd_value & bit_mask;

    return tens * 10 + units;
}

