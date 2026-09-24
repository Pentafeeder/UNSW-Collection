#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Provide at least 2 arguments: file path and 1 or more positions\n");
        exit(1);
    }

    FILE *file = fopen(argv[1], "r");

    if (file == NULL) {
        perror(argv[1]);
        exit(1);
    }

    for (int i = 2; i < argc; i++) {
        if (fseek(file, atoi(argv[i]), SEEK_SET) == -1) {
            perror(argv[1]);
            exit(1);
        }

        int byte = fgetc(file);
         

        printf("%d - 0x%02X", byte, byte);
        if (isprint(byte)) {
            printf(" - \'%c\'", byte);
        }   
        putchar('\n');
    }


    return 0;
}