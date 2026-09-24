// Given an UTF-8 string, return the index of the first invalid byte.
// If there are no invalid bytes, return -1.

#include <stdint.h>
#include <string.h>

#define BYTE_SIZE 8
// NOTE: can do this more cleanly
// Do NOT change this function's return type or signature.
int invalid_utf8_byte(char *utf8_string) {
    

    int nth_string = 0;
    int surrogate = 0;
    uint8_t bit_mask = 0;
    while (utf8_string[nth_string] != '\0') {
        int i = 0;
        bit_mask = 0x80;
        while (((bit_mask >> i) & utf8_string[nth_string]) > 0 && surrogate == 0) {
            i++;
        } 

        if (i == 1 || i > 4) {
            return nth_string;
        }

        if (surrogate == 0) {
            nth_string++;
        }

        if (surrogate == 0 && i != 0) {
            surrogate = i - 1;
        } else if (surrogate > 0) {
            
            while (surrogate > 0) {
                bit_mask = 0xc0;
                if (utf8_string[nth_string] == '\0') {
                    return nth_string;
                }

                if ((bit_mask & utf8_string[nth_string]) != 0x80) {
                    return nth_string;
                }

                surrogate -= 1;
                nth_string++;
            }
        }

        
       
    }
    

    return -1;
}
