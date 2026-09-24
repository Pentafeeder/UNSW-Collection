#include <stdio.h>
#include <stdlib.h>
 
int main()
{
    
    
    int row;
    int col;
    printf("Enter row, col:");
    scanf(" %d %d", &row, &col);
 
    char (*arr)[row + 1][col + 1] = malloc(sizeof *arr);
    char sample[] = "abcdefghijklmnopqrstuvwxyz";
    int count = 0;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            (*arr)[i][j] = sample[count++];
        }
        (*arr)[i][col] = '\0';
    }

 
    for (int i = 0; i < row; i++) {
        printf("%s ", (*arr)[i]);
    }
 
 
    free(arr);
     
    return 0;
}