#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]) {

    if (argc != 4) {
        fprintf(stderr, "Usage: <filename> <start int> <end int>");
        return 1;
    }

    FILE *file = fopen(argv[1], "a"); // files are pointers

    if (file == NULL) {
        perror("Error: ");
        return 1;
    }
    for (int i = 0; i <= (atoi(argv[3]) - atoi(argv[2])); i++) {
        fprintf(file, "%d\n", atoi(argv[2]) + i);    
    }

    fclose(file);
    return 0;
}