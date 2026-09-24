#include <stdlib.h>
#include <stdio.h>
#include <math.h>
extern char **environ;

int main(int argc, char *argv[]) {
    char *var1 = getenv(argv[1]);
    char *var2 = getenv(argv[2]);

    
    int value1;
    int value2;

    if (var1 == NULL) {
        value1 = 42;   
    } else {
        value1 = atoi(var1);
    }

    if (var2 == NULL) {
        value2 = 42;
    } else {
        value2 = atoi(var2);
    }
    printf("%d\n", abs(value1 - value2) < 10);

    return 0;
}