#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIARY_PATH "/.diary"
int main(int argc, char *argv[]) {
    
    char *home_path = getenv("HOME");

    if (home_path == NULL) {
        fprintf(stderr, "HOME not set\n");
        exit(1);
    }

    int concatenated_length = strlen(home_path) + strlen(DIARY_PATH) + 1;

    char *concatenated_path = malloc(sizeof(char) * concatenated_length);
    

    snprintf(concatenated_path, concatenated_length, "%s%s", home_path, DIARY_PATH);

    FILE *stream = fopen(concatenated_path, "a");   

    if (stream == NULL) {
        perror(concatenated_path);
        exit(1);
    }

    for (int i = 1; i < argc; i++) {
        fwrite(argv[i], 1, strlen(argv[i]), stream);   
        fputc(' ', stream);
    }   
    fputc('\n', stream);
    fclose(stream);
    free(concatenated_path);
    
    return 0;
}