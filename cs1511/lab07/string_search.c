// searches a string and how many occurences of our "search term" exists in it
// By Kevin Le z5481482
// on 27/03/2023

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXIMUM 128
int main(int argc, char *argv[]) {
    printf("Enter list of words:\n");
    char word[MAXIMUM];
    int found = 0;
    
    while (fgets(word, MAXIMUM, stdin) != NULL) {   
        int length = strlen(word);
        word[length - 1] = '\0';     
        for (int i = 1; i < argc; i++) {
            

            if (strcmp(word, argv[i]) == 0) {
                found++;
            }
        }
        
    }
    printf("There were %d occurrence(s) in the input.\n", found);          
    return 0;
}