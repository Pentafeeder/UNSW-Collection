// takes an integer n and prints a grid n x n with coordinates
// By Kevin Le z5481842
// on 01/03/2023

#include <stdio.h>

int main(void) {
    int width;
    printf("Enter size: ");
    scanf("%d", &width);

    int row = 0;

    while (row < width) {
        int column = 0;
        while (column < width) {
            printf("(%d, %d)", row, column);
            column++;
        }
        printf("\n");
        row++;
    }



    return 0;
}