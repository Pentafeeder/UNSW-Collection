#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 257
#define ALPHABET_LENGTH 28

int already_matched(char character, char matched[ALPHABET_LENGTH]);
void lower_case(char string[MAX_LENGTH]);

int main(void) {
    char matched[ALPHABET_LENGTH];
    char string1[MAX_LENGTH];
    char string2[MAX_LENGTH];
    int matching = 0;

    matched[0] = ' ';
    matched[1] = '\0';

    fgets(string1, MAX_LENGTH, stdin);
    fgets(string2, MAX_LENGTH, stdin);

    lower_case(string1);
    lower_case(string2);

    int length1 = strlen(string1);
    int length2 = strlen(string2);

    string1[length1 - 1] = '\0'; // these arent needed
    string2[length2 - 1] = '\0'; // already done by fgets
    int counter1 = 0;
    while (string1[counter1] != '\0') {
        int counter2 = 0;
        if (already_matched(string1[counter1], matched) == 0) {
            int match = 0;
            while (string2[counter2] != '\0' && match == 0) {
                if (string2[counter2] == string1[counter1]) {
                    match++;
                }
                counter2++;
            }
            matching += match;
        }
        counter1++;
    } 
    printf("%d\n", matching);
}

int already_matched(char character, char matched[ALPHABET_LENGTH]) {
    int matches = 0;
    int counter = 0;
    while (matched[counter] != '\0') {
        if (matched[counter] == character) {
            matches++;
        }
        counter++;
    }

    if (matches == 0) {
        matched[counter++] = character;
        matched[counter] = '\0';
    }
    return matches;
}

void lower_case(char string[MAX_LENGTH]) {
    int counter = 0;
    while (string[counter] != '\0') {
        if (string[counter] <= 'Z' && string[counter] >= 'A') {
            string[counter] += ('a' - 'A');
        }
        counter++;
    }
}