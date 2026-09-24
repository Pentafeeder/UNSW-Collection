#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX 10000
int main(void) {
    int data;
    int array[MAX];
    int counter = 0;
    while (scanf("%d", &data) == TRUE) {
        array[counter] = data;
        counter++;
    } 

    int position = 1;
    int stops = 0;
    int total_charge = 0;
    while (position < counter - 1 && total_charge < counter - 1) {
        int move = array[position - 1];
        int max = 0;
        int count = 0;
        while (count < move && position + count < counter - 1) {
            if (array[position + count] > max) {
                max = array[position + count];
            }
        }
        position += move;
        total_charge += max;
        stops++;
    }
    printf("%d\n", stops);
    free(array);
    return 0;
}