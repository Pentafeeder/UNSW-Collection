#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    FILE *file = fopen(argv[1], "w");
    if (file == NULL) {
        perror("Error: ");
        return 1;
    }

    for (int i = 2; i < argc; i++) {
        int int_input = atoi(argv[i]);

        if (int_input > 255 || int_input < 0) {
            fprintf(stderr, "%d outside of range 0 to 255\n", int_input);
            return 1;
        }   

        fputc(int_input, file);
    }

    fclose(file);

    return 0;
}