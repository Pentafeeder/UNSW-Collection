#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>  

int main(int argc, char *argv[]) {

    if (argc != 2) {
        fprintf(stderr, "Usage: <filename>");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");

    if (file == NULL) {
        perror("Error");
        return 1;
    }

    int line = 0;
    int byte;
    while ((byte = fgetc(file)) != EOF) {
        printf("byte %4d: %3d 0x%02x", line, byte, byte);
        line++;
        if (isprint(byte)) {
            printf(" \'%c\'", byte);
        }
        
        putchar('\n');
    }
    fclose(file);
    return 0;
}