#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
int check_vowel(char character);


int main(int argc, char *argv[]) {

    if (argc != 2) {
        fprintf(stderr, "Usage: provide only 1 argument (file to be read)\n");
        exit(1);
    }

    FILE *stream = fopen(argv[1], "r");

    if (stream == NULL) {
        perror(argv[1]);
        exit(1);
    }

    int input;
    int vowel_count = 0;
    while ((input = fgetc(stream)) != EOF) {
        vowel_count += check_vowel(input);
    }
    printf("%d\n", vowel_count);

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