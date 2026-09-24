#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

    FILE *file = fopen(argv[1], "r");

    FILE *temp = fopen("temp.txt", "w");

    uint32_t character;

    while ((character = fgetc(file)) != EOF) {
        if (character < 128) {
            fputc(character, temp);
        }
    }

    fclose(temp);
    fclose(file);

    FILE *non_ascii = fopen(argv[1], "w");

    temp = fopen("temp.txt", "r");

    while ((character = fgetc(temp)) != EOF) {
        fputc(character, non_ascii);
    }

    fclose(temp);
    fclose(non_ascii);

    unlink("temp.txt");

    return 0;
}