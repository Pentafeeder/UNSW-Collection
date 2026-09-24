// The following code is meant to ask the user to enter a string, print out
// what the user has entered and repeat this until the user enters Ctrl + d.
// However, it contains three lines with issues that you need to fix. Good luck!

#include <stdio.h>

#define MAX_LETTERS 100

int main (void) {
    char my_arr[MAX_LETTERS];
    while (fgets(&my_arr, MAX_LETTERS) != NULL) {
        printf("Enter string: ");
        printf("Input received: %s\n", my_arr);
    }

    return 0;
}

