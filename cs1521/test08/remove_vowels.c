#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
int check_vowel(char character);

int main(int argc, char *argv[]) {

    if (argc != 3) {
        fprintf(stderr, "Please provide only 2 arguments (file to be read, file to contain copy)\n");
        exit(1);
    }

    FILE *file_read = fopen(argv[1], "r");

    if (file_read == NULL) {
        perror(argv[1]);
        exit(1);
    }

    int input_read;

    FILE *written_file = fopen(argv[2], "w");

    while ((input_read = fgetc(file_read)) != EOF) {
        if (!check_vowel(input_read)) {
            fputc(input_read, written_file);
        }
    }

    return 0;
}

int check_vowel(char character) {
    int is_vowel = FALSE;

    if (character == 'a' || character == 'e' || character == 'i' || character == 'o' || character == 'u') {
        is_vowel = TRUE;
    }

    if (character == 'A' || character == 'E' || character == 'I' || character == 'O' || character == 'U') {
        is_vowel = TRUE;
    }

    return is_vowel;
}