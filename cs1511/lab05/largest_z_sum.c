// Find the largest sum of numbers in a z shape.
// Edited by Kevin Le z5481482
// on 26/03/2023

#include <stdio.h>
#include <assert.h>

#define MAX_SIZE 100

int largest_z_sum(int size, int array[MAX_SIZE][MAX_SIZE]);

int find_z_sum(int array[MAX_SIZE][MAX_SIZE], int row_shift, int col_shift, int current_size,
        int largest_sum);

// DO NOT CHANGE THIS MAIN FUNCTION
int main(void) {
    int array[MAX_SIZE][MAX_SIZE];

    // Get the array size.
    int size;
    printf("Enter 2D array side length: ");
    scanf("%d", &size);
    assert(size >= 3);

    // Scan in values for the array.
    printf("Enter 2D array values:\n");
    int i = 0;
    while (i < size) {
        int j = 0;
        while (j < size) {
            assert(scanf("%d", &array[i][j]) == 1);
            j++;
        }
        i++;
    }

    printf("The largest z sum is %d.\n", largest_z_sum(size, array));

    return 0;
}

// Return the largest sum of numbers in a z shape.
int largest_z_sum(int size, int array[MAX_SIZE][MAX_SIZE]) {
    // Put your code here.
    // find sum of z
    // find sum of every z starting frmo smallest
    int largest_sum = 0;
    int current_size = 3;
    while (current_size >= 3 && current_size <= size) {
        
        int row_shift = 0;
        int col_shift = 0;
        int shift = size - current_size + 1;
        while (row_shift < shift) {
            col_shift = 0;
            while (col_shift < shift) {
                largest_sum = find_z_sum(array, row_shift, col_shift, 
                                            current_size, largest_sum);   
                col_shift++;   
            }
            row_shift++;
        }
        
        current_size++;
    }
    return largest_sum;
}

int find_z_sum(int array[MAX_SIZE][MAX_SIZE], int row_shift, 
        int col_shift, int current_size, int largest_sum) {
    int row = 0;
    int sum = 0;
    while (row < current_size) {
        int col = 0;
        if (row == 0 || row == current_size - 1) {
            while (col < current_size) {
                sum += array[row + row_shift][col + col_shift];  
                col++;
            }
        } else if (row > 0 && row < current_size - 1) {
            sum += array[row + row_shift][current_size - row - 1 + col_shift];
        }
        row++;
    }
    if (sum > largest_sum) {
        largest_sum = sum;
    }
    return largest_sum;
}