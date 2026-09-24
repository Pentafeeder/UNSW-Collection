#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdint.h>


int main(int argc, char *argv[]) {
    if (argc != 2) {
        perror("Please provide only one argument (file name).\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");

    if (file == NULL) {
        perror("File does not exist.\n");
        return 1;
    }

    int LIT_header[] = {0x4C, 0x49, 0x54};
    int byte;
    int counter = 0;

    while ((byte = fgetc(file)) != EOF) {
        if (counter < 3 && byte != LIT_header[counter]) {
            perror("Magic number is not correct.\n");
            return 1;
        } else if (counter >= 3) {
            int byte_size = byte - '0';
            if (byte_size > 8 || byte_size < 1) {
                perror("Invalid number of bytes for the record stored.\n");
                return 1;
            }

            uint8_t output[byte_size];
            int valid = fread(output, 1, byte_size, file);
            
            if (valid < byte_size) {
                fprintf(stderr, "Record too short\n");
                return 1;
            } 

            uint64_t LIT_integer = 0;
         
            for (int i = 0; i < byte_size; i++) {
                uint64_t bit_mask = output[i];
                bit_mask <<= i * 8;
                LIT_integer |= bit_mask;
            }

            

            printf("%lu\n", LIT_integer);
        }

        counter++;
    }

    if (counter < 3) {
        perror("File is not long enough to contain a complete header.\n");
        return 1;
    } 

   

    return 0;
}