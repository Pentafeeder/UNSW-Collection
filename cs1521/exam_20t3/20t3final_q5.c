#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>

int main(int argc, char *argv[]) {

    struct stat stats;
  
    int file_size = stats.st_size;

    FILE *copy_file = fopen(argv[3], "w");
    FILE *file_to_copy = fopen(argv[2], "r");

    int bytes_to_copy = file_size - atoi(argv[1]);

    if (bytes_to_copy > 0) {
        int char_copy;
        for (int i = 0; i < bytes_to_copy; i++) {
            char_copy = fgetc(file_to_copy);
            fputc(char_copy, copy_file);
        }
    }

    fclose(file_to_copy);
    fclose(copy_file);

    return 0;
}