// A program that takes input from user and counts up to (inclusive) that number
// By Kevin Le z5481482

#include <stdio.h>

int main(void) {
    int counter = 0;
    int num;
    printf("Enter number: ");
    scanf("%d", &num);
    if (num > 0) {
        while (counter <= num) {
            printf("%d\n", counter);
            counter++;
        }
    }
    else {
        while (counter >= num) {
            printf("%d\n", counter);
            counter--;
        }
    }
    
    return 0;
}