// By Kevin Le z5481482 28/02/2023
// takes in 3 integers and sorts them in ascending order using if statements only

#include <stdio.h>

int main(void) {
    int num1, num2, num3;
    int temp;
    
    printf("Enter integer: ");
    scanf("%d", &num1);

    printf("Enter integer: ");
    scanf("%d", &num2);

    printf("Enter integer: ");
    scanf("%d", &num3);

    if (num2 < num1) {
        temp = num1;
        num1 = num2;
        num2 = temp; 
    }
    if (num3 < num1) {
        temp = num1;
        num1 = num3;
        num3 = temp;
    }
    if (num3 < num2) {
        temp = num2;
        num2 = num3;
        num3 = temp;
    }

    printf("The integers in order are: %d %d %d\n", num1, num2, num3);

    return 0;
}