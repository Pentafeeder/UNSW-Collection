// by Kevin Le z5481482
// takes input and prints word as many times as it is long

#include <stdio.h>
#include <string.h>

#define MAX_ARRAY 50
int main(void) {
    char array[MAX_ARRAY];
    printf("Input word: ");
    
    fgets(array, MAX_ARRAY, stdin);
    int length = strlen(array);
    printf("\nWord square is: \n");
    for (int i = 0; i < length - 1; i++) {
        printf("%s", array);
    }
    return 0;
}