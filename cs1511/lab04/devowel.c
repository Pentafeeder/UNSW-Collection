// Takes in a string and prints it w/o vowels
// By Kevin Le z5481482
// on 08/03/2005

#include <stdio.h>
void check_vowel(char character);

int main(void) {
    char character;
    int string = scanf("%c", &character);
    while (string > 0) {
        check_vowel(character);
        string = scanf("%c", &character);
    }
}

void check_vowel(char character) {
    if (!(character == 'a' || character == 'e'|| 
            character == 'i'|| character == 'o'|| character == 'u')) {
        printf("%c", character);   
    }
}


