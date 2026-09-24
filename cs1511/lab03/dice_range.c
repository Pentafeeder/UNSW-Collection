// takes n sided dice and m number of dies
// By Kevin Le z5481482
// on 01/03/2023

#include <stdio.h>

int main(void) {
    int dice_side, dice_amount, high_range, low_range;
    float average;

    printf("Enter the number of sides on your dice: ");
    scanf("%d", &dice_side);
    printf("Enter the number of dice being rolled: ");
    scanf("%d", &dice_amount);

    if (dice_side < 4 || dice_amount < 1) {
        printf("These dice will not produce a range.\n");
    }
    else {
        high_range = dice_amount * dice_side;
        low_range = dice_amount;
        printf("Your dice range is %d to %d.\n", low_range, high_range);
        
        average = (high_range*1.0 + low_range*1.0) / 2;
        
        printf("The average value is %f\n", average);
    }

    return 0;
}