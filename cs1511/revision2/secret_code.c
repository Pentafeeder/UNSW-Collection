#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char char1;
    char char2;
    while (scanf("%c%c", &char1, &char2) == 2) {
        if (char1 < char2) {
            printf("%c", char1);
        } else {
            printf("%c", char2);
        }
    }
    printf("\n");
    return 0;

}