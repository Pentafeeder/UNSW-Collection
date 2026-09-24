// Takes in a sentence by user and prints frequency of each letter in that phrase 
// (only for alphabet, and does not include special characters in frequency)
// By Kevin Le z5481482 
// On 31/03/2023

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STRING 1000
#define MAX_ALPHABET 26

int main(void) {
    char line[MAX_STRING];
    double fraction[MAX_ALPHABET] = {0.0};
    int frequency[MAX_ALPHABET] = {0};

    int alphabet_char = 0;

    while (fgets(line, MAX_STRING, stdin) != NULL) {
        int length = strlen(line);
        for (int i = 0; i < length; i++) {
            if (line[i] >= 'A' && line[i] <= 'Z') {
                line[i] += ('a' - 'A');
            }

            if (line[i] >= 'a' && line[i] <= 'z') {
                frequency[line[i] - 'a']++;
                alphabet_char++;
            }
        }
    }
    for (int alphabet = 0; alphabet < MAX_ALPHABET; alphabet++) {
        fraction[alphabet] = (frequency[alphabet] * 1.0) / (alphabet_char * 1.0);
        char character = 'a' + alphabet;
        printf("\'%c\' %lf %d\n", character, fraction[alphabet], frequency[alphabet]);
    }
    

    return 0;
}

