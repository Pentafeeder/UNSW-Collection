#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int *array = NULL;
    int data;
    int counter = 0;
    printf("Enter numbers forward:\n");
    while (scanf(" %d", &data) == 1) {
        array = realloc(array, sizeof(int)*(counter + 1));
        array[counter] = data;
        counter++;
    }

    printf("\nReversed:\n");

    for (int i = 0; i < counter; i++) {
        printf("%d\n", array[counter - 1 - i]);
    }

    free(array);
    return 0;
}

