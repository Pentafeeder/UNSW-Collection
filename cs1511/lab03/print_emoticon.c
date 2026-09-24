// Prints out an emoticon depending on how the user is feeling.
// by Kevin Le z5481482
// on 01/03/2023

#include <stdio.h>

enum emoticon {HAPPY = 1, SAD, EMBARASSED, SHOCKED};

////////////////////////////////////////////////////////////////////////////
///////////////////// ONLY WRITE CODE BELOW HERE ///////////////////////////
////////////////////////////////////////////////////////////////////////////

// TODO: Finish the procedure print_emoticon so that it prints out the 
// respective emoticon according to the value of e.

void print_emoticon(enum emoticon e) {
    // TODO: Fill in this procedure.
    
    if (e == 1) {
        printf("^_^");
    }
    else if (e == 2) {
        printf("T_T");
    }
    else if (e == 3) {
        printf(">_<");
    }
    else if (e == 4) {
        printf("*o*");
    }
}

////////////////////////////////////////////////////////////////////////////
///////////////////// ONLY WRITE CODE ABOVE HERE ///////////////////////////
////////////////////////////////////////////////////////////////////////////

//////////////// DO NOT CHANGE ANY OF THE CODE BELOW HERE //////////////////

void print_emoticon_options(void) {
    printf(
        "1: Happy\n"
        "2: Sad\n"
        "3: Embarassed\n"
        "4: Shocked\n");
}

int main(void) {
    
    printf("How are you feeling today?\n");
    print_emoticon_options();

    printf("\nPlease enter the number for your emoticon: ");
    
    int input;
    scanf("%d", &input);

    print_emoticon(input);
    printf("\n");

    return 0;
}
//////////////// DO NOT CHANGE ANY OF THE CODE ABOVE HERE //////////////////