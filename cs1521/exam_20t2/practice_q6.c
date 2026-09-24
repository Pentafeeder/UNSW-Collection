#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    FILE *file = fopen(argv[1], "r");

    int byte;
    int valid_ascii_bytes = 0;
    while ((byte = fgetc(file)) != EOF) {
        if (byte <= 127) {
            valid_ascii_bytes++;
        }
    }

    printf("%s contains %d ASCII bytes\n", argv[1], valid_ascii_bytes);

    fclose(file);

    return 0;
}