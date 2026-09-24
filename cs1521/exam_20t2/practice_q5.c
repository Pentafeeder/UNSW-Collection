#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {

    char *path_var1 = getenv(argv[1]);
    char *path_var2 = getenv(argv[2]);

    if (path_var1 == NULL && path_var2 == NULL) {
        printf("1");   
    } else if (path_var1 == NULL || path_var2 == NULL) {
        printf("0");
    } else {
       
        if (strcmp(path_var1, path_var2) == 0) {
            printf("1");
        } else {
            printf("0");
    }
    }

    
    putchar('\n');
    return 0;
}