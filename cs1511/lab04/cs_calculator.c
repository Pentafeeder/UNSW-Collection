// takes in user input and performs mathematical operations on them
// by Kevin Le z5481482
// on 08/03/2023

#include <stdio.h>


int main(void) {
    int num1, num2;
    char instruction;
    printf("Enter instruction: ");
    while (scanf(" %c", &instruction) > 0) {
        if (instruction == 'p') {
            scanf("%d %d", &num1, &num2);
            int result = num1;
            for (int i = 1; i < num2; i++) {
                result = result * num1;
            }
            printf("%d\n", result);
        } else if (instruction == 's') {
            scanf("%d", &num1);
            printf("%d\n", num1 * num1);
        }
        printf("Enter instruction: ");
        
    }
}


