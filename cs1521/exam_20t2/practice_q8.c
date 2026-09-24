#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

int get_codepoint(int byte) {
    int codepoint;
    
    if ((byte & 0xF8) == 0xF0) {
        codepoint = 4;
    } else if ((byte & 0xC0))
}



int main(int argc, char *argv[]) {

    FILE *file = fopen(argv[1], "r");

    int valid_UTF_8 = 0;
    int nth_byte;

    int byte;

    while ((byte = fgetc(file)) != EOF) {
        int bit_mask = 0xF0

        int leading_byte = bit_mask & byte;
        int count = 0;
        int follow_byte_mask = 0xC0

        if (leading_byte == 0xF0) {
            while ((byte = fgetc(file)) != EOF && count < 3) {
                if ((byte & follow_byte_mask) != 0x80) {
                    printf("%d")
                }
                count++;
            }
            
            if (count < 3) {

            }
        }

        if (leading_byte == 0xE0) {

        }
        

    }


    return 0;
}