// Read in a number, and determine whether it is negative.
// by the user: Kevin Le z5481482


#include <stdio.h>

//////////////// DO NOT CHANGE ANY OF THE CODE BELOW HERE //////////////////
// Procedures for outputting user messages:

// Outputs: "You have entered a positive number.\n"
void print_positive_message(void) {
    printf("You have entered a positive number.\n");
}

// Outputs: "Don't be so negative!\n"
void print_negative_message(void) {
    printf("Don't be so negative!\n");
}

// Outputs: "You have entered zero.\n"
void print_zero_message(void) {
    printf("You have entered zero.\n");
}

//////////////// DO NOT CHANGE ANY OF THE CODE ABOVE HERE //////////////////


int main(void) {

    // TODO: scan in a number and test whether it is positive, negative or 0.
    // TODO: use the procedures defined above to print the relevant message.
    int num;
    scanf("%d", &num);
    if (num < 0) {
        print_negative_message();
    }
    else if (num > 0) {
        print_positive_message();
    }
    else if (num == 0) {
        print_zero_message();
    }
    return 0;
}