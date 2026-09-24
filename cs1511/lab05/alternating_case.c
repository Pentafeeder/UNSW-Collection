// Written by Kevin Le z5481482
// 14/03/2023

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_STRING_LENGTH 1024

//////////////// DO NOT CHANGE ANY OF THE CODE BELOW HERE //////////////////
void make_alternating(char string[MAX_STRING_LENGTH]);

int main (void) {
    //You don't need to understand this code to complete the exercise.

    //Scans in a string from the user.
    char buffer[MAX_STRING_LENGTH];
    fgets(buffer, MAX_STRING_LENGTH, stdin);

    // Runs your function
    make_alternating(buffer);

    // Prints resulting string.
    printf("%s", buffer);

    return 0;
}
//////////////// DO NOT CHANGE ANY OF THE CODE ABOVE HERE //////////////////

////////////////////////////////////////////////////////////////////////////
///////////////////// ONLY WRITE CODE BELOW HERE ///////////////////////////
////////////////////////////////////////////////////////////////////////////

// Modifies `string` so that the first letter is converted to lowercase, 
// and the case of each following letter alternates.
// i.e. in the resulting string: 
//      the first letter is lowercase, 
//      second letter is uppercase, 
//      third letter is lower case, 
//      etc.
//
// e.g.: "Hello" -> "hElLo"
void make_alternating(char string[MAX_STRING_LENGTH]) {
    // TODO: complete this function
    int length = strlen(string);
    
    int counter = 0;
    for (int i = 0; i < length - 1; i++) {
        if ((string[i] >= 'A' && string[i] <= 'Z') ||
                 (string[i] >= 'a' && string[i] <= 'z')) {
            if (counter % 2 == 0 && string[i] < 'a') {
                string[i] += 32;
            } else if (counter % 2 == 1 && string[i] >= 'a') {
                string[i] -= 32;
            }
            counter++;
        }
    }
}

////////////////////////////////////////////////////////////////////////////
///////////////////// ONLY WRITE CODE ABOVE HERE ///////////////////////////
////////////////////////////////////////////////////////////////////////////