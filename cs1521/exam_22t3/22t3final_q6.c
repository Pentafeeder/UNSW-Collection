// COMP1521 22T3 ... final exam, question 6

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void include_line(FILE *file_from, FILE *file_to, int nth_line);

int main(int argc, char *argv[]) {

    assert(argc == 3);

    char *filename = argv[1];
    int line = atoi(argv[2]);

    assert(line > 0);

    FILE *file = fopen(filename, "r");

    FILE *temp = fopen("temp.txt", "w");

    include_line(file, temp, line);
    
    int byte = fgetc(file);
    while (byte != EOF && byte != '\n') {
        byte = fgetc(file);
    }

    byte = fgetc(file);
    while (byte != EOF) {
        fputc(byte, temp);
        byte = fgetc(file);
    }

    fclose(temp);
    fclose(file);
    file = fopen(filename, "w");
    temp = fopen("temp.txt", "r");
    
    while ((byte = fgetc(temp)) != EOF) {
        fputc(byte, file);
    }

    fclose(file);
    fclose(temp);




    return 0;
}




void include_line(FILE *file_from, FILE *file_to, int nth_line) {
    int current_line = 1;
    int new_line = 0;
    int byte = fgetc(file_from);
    while (current_line < nth_line && byte != EOF) {
        while (byte != EOF && new_line == 0) {
            if (byte == '\n') {
                new_line = 1;
            }
            fputc(byte, file_to);
            byte = fgetc(file_from);
        }
        new_line = 0;
        current_line++;
    }
}
