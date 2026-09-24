// COMP1521 22T3 ... final exam, question 7

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char *_22t3final_q7(char *str) {
    char *new_str = malloc(strlen(str) + 1);

    // TODO: replace the following line with your code
    

    for (int i = 0; str[i] != '\0'; i++) {
        int bit_mask = 0xF0;

        int is_valid = 1;
        if ((bit_mask & str[i]) == 0xF0) {

            for(int j = 1; j < 4; j++) {
                if ((str[i + j] & 0xC0 ) != 0x80) {
                    break;
                }
            }
        }

    }
   
    strcpy(new_str, str);

    return new_str;
}


int get_continuation_bytes(int byte) {
    if ()
}


