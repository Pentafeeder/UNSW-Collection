// reads an odd integer and print nxn spiral square of asteriks
// By Kevin Le z5481842
// on 03/03/2023

/*
Plan: check odd and even conditions for row + column
IF: row = even, do line of asteriks (except for when col is ends -- 
alternates. IE first time includes col, do it once, next time, include both, 
then do right end - 1, etc. ) -> to do this, do if (is odd AND < column counter + 1 / > )
IF: col = even, do line of asteriks (same as row above)
IF:  */
#include <stdio.h>

int main(void) {
    int row = 0, column_counter = 0, size;
    printf("Enter size: ");
    scanf("%d", &size);
    
    while (row < size) {
        int column = 0;
        while (column < size) {
            int column_bool = column % 2 == 0 && (column < column_counter || column > size - (1 * column_counter));
            if (row % 2 == 0 && !(column_bool)) {
                printf("*");
            }
            else if (row % 2 == 0 && (column_bool)) {
                printf("-");
            }
            else if(row % 2 == 1 && !(column_bool)) {
                printf("-");
            }
            else if(row % 2 == 1 && (column_bool)) {
                printf("*");
            }
            column++;
        }
        printf("\n");
        if ()
        
        row++;
    }

}