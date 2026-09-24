#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int *array = NULL;
    int num;
    int size = 0;
    scanf(" %d", &num);
    while (num != 0) {
        array = realloc(array, sizeof(int) * (size + 1));
        array[size++] = num;
        scanf(" %d", &num);
    }
    // prints even index;
    for (int i = 0; i < size; i += 2) {
        printf("%d ", array[i]);
    }
    //prints odd index
    for (int j = 1; j < size; j += 2) {
        printf("%d ", array[j]);
    }
    
    printf("\n");
    free(array);
}
