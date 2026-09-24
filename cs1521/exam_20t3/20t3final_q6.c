#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdint.h>

int main(int argc, char *argv[]) {

    FILE *file = fopen(argv[1], "r");

    int read_char;
    int bits_set = 0;
    while ((read_char = fgetc(file)) != EOF) {
        uint8_t bit_mask = 1;
        for (int i = 0; i < 8; i++) {
            if ((bit_mask & read_char) != 0) {
                bits_set++;

            }
            bit_mask <<= 1;

        }
    }

    fclose(file);

    printf("%s has %d bits set\n", argv[1], bits_set);
    return 0;
}