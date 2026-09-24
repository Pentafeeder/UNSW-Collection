// reads an odd integer and print nxn square of asteriks and dashes
// By Kevin Le z5481842
// on 01/03/2023

#include <stdio.h>

int main(void) {
    int row = 0, star_count = 0, size, middle, column = 0;
    printf("Enter size: ");
    scanf("%d", &size);
    middle = size/2;

    while (row < size) {
        column = 0;
        while (column < size) {
            if (star_count % 4 == 0) {
                printf("*");
            } 
            else {
                printf("-");
            }

            if (column < middle) {
                star_count++;
            } 
            else if (column < size - 1) {
                star_count--;
            }

            column++;
        }        
        
        printf("\n");
        row++;
        
        if (row < middle + 1) {
            star_count--;
        }
        else {
            star_count++;
        }
    }
    return 0;
}