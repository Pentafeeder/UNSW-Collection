#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    FILE *test_file = fopen("test.txt", "w");

    char string[] = "This is a line of data";
    int length = strlen(string);

    fwrite(string, 1, length, test_file);

    fclose(test_file);

    // FILE *reopen = fopen("test.txt", "r+");

    // fseek(reopen, length / 2, SEEK_SET);

    // char added_string[] = " this part was added ";
    // int len_new = strlen(added_string);

    // fwrite(added_string, 1, len_new, reopen);

    // fclose(reopen);

    // int total_length = length + len_new;
    FILE *read = fopen("test.txt", "r");


    char read_string[length + 1];
    read_string[length] = '\0';
    fread(read_string, 1, length, read);

    printf("%s\n", read_string);

    return 0;
}