#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "basin.h"

#define BYTE 8

size_t convert_LIT(size_t value);

int main(void) {


    // FILE *error = fopen("no_file.txt", "r");

    // if (error == NULL) {
    //     perror("no_file.txt");
    //     exit(1);

    // }

    size_t integer = 0xcdab00ba0000aa00;
    printf("%zx\n", integer);
    FILE *test_file = fopen("test_file.txt", "w");
    

    integer = convert_LIT(integer);

    if (integer == -1) {
        printf("size_t still contains negative\n");
        return 1;
    }

    printf("%zx lit\n", integer);
    fwrite(&integer, 1, 8, test_file);
    fclose(test_file);

    FILE *read_file = fopen("test_file.txt", "r");

    size_t num = 0;
    fread(&num, 1, 4, read_file);
    printf("%zx\n", num);

    num = convert_LIT(num);

    printf("%zx\n", num);

    fclose(read_file);
    return 0;
}

size_t convert_LIT(size_t value) {
    size_t LIT_int = 0;
    size_t bit_mask = 0xFF;

    for (int i = 0; i < sizeof(size_t); i++) {
        size_t swapped = (value & bit_mask) >> (BYTE * i);
        LIT_int |= swapped << (BYTE * (sizeof(size_t) - (i + 1)));
        
        bit_mask <<= BYTE;
    }
    
    return -1;
}




// int convert_LIT(char *string) {
//     int array_size = strlen(string);

//     char *LIT_str = malloc(sizeof(char) * array_size);
//     int LIT_int = 0;
//     uint32_t bit_mask = 0xFF;
//     for (int i = 0; i < sizeof(int); i++) {
//         int swapped = (value & bit_mask) >> (8 * i);
//         LIT_int |= swapped << (32 - 8 * (i + 1));
        
//         if (i < 3) {
//             bit_mask <<= 8;
//         }
//     }

//     return LIT_int;
// }

// size_t convert_LIT(size_t *value) {
//     size_t LIT_int = 0;
//     size_t bit_mask = 0xFF;
//     printf("%lu\n", sizeof(value));
//     for (int i = 0; i < sizeof(value); i++) {
//         size_t swapped = (*value & bit_mask) >> (8 * i);
//         LIT_int |= swapped << (sizeof(value) * 8 - 8 * (i + 1));
        
//         bit_mask <<= 8;
//     }

//     printf("%zx\n", LIT_int);

//     return LIT_int;
// }