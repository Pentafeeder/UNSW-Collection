// Program which prints a letter depending on the user's request.
// by Kevin Le z5481482

#include <stdio.h>

int main(void) {
    

    char is_uppercase;
    int index = 0;
    int add = 0;
    printf("Uppercase: ");

    // TODO: scan is_uppercase
    scanf(" %c", &is_uppercase);
    if (is_uppercase == 'y') {
        index = 'A';
    }
    else if (is_uppercase == 'n') {
        index = 'a';
    }
    
    
    printf("Index: ");

    // TODO: finish the program
    scanf(" %d", &add);
    add = add + index;
    printf("The letter is %c\n", add);

    return 0;
}