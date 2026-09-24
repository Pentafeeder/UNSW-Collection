// by Kevin Le z5481482 on 28/02/2023
// ordering 3 integers without loops or if statements (and only using 3 variables)

#include <stdio.h>

int main(void) {
    int num1, num2, num3;

    printf("Enter integer: ");
    scanf("%d", &num1);
    
    printf("Enter integer: ");
    scanf("%d", &num2);

    printf("Enter integer: ");
    scanf("%d", &num3);
    
    printf("The integers in order are: %d %d %d\n", 
            num1*(num1 == num2 && num1 == num3) + 
            (num2*(num2 < num1) + num3*(num3 < num1) + num1*(num1 < num2 || num1 < num3))*(num1 == num2 || num1 == num3 || num2 == num3) + 
            (num1 != num2 && num1 != num3 && num3 != num2)*(num3*(num3 < num1 && num3 < num2) + num2*(num1 > num2 && num2 < num3) + num1*(num1 < num2 && num1 < num3)),
            
            num2*(num1 == num2 || num2 == num3) + num3*(num1 == num3)*(num1 != num2) +
            (num1 != num2 && num2 != num3 && num2 != num1)*(num1*((num1 > num3 && num1 < num2) || (num1 < num3 && num1 > num2)) + num2*((num2 < num3 && num2 > num1) || (num2 > num3 && num2 < num1)) + num3*((num3 < num1 && num3 > num2) || (num1 < num3 && num3 < num2))),
            
            num3*(num3 == num2 && num1 == num3) + 
            (num2*(num2 > num3 && num2 == num1) + num1*(num1 > num2 && num1 == num3) + num3*((num3 > num1 && num3 == num2) || (num3 > num2 && num3 > num1)))*(num3 == num2 || num1 == num3 || num2 == num1) + 
            (num3 != num2 && num1 != num3 && num2 != num1)*(num1*(num1 > num2 && num1 > num3) + num2*(num2 > num3 && num2 > num1) + num3*(num3 > num2 && num3 > num1))
            );


    return 0;
}
