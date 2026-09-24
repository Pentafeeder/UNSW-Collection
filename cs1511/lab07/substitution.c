// encrypts a message by replacing one letter in the alphabet with another
// By Kevin Le z5481482
// on 30/03/2023

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_MAP 28
#define MAX_STRING 1000

int remove_duplicates(int length, char source[length]);
int check_valid(int length, char source[length]);
int encrypt_line(char line[MAX_STRING], char mapping[MAX_MAP]);

int main(void) {
    int valid = 0;
    char mapping[MAX_MAP];

    while (valid == 0) {
        printf("Enter mapping:\n");
        valid = (fgets(mapping, MAX_MAP, stdin) == NULL) * -1;
        int map_length = strlen(mapping);
        if (map_length != 27 || remove_duplicates(map_length, mapping) != 27 ||
                 mapping[map_length - 1] != '\n' || 
                 check_valid(map_length, mapping) == 1) {
            printf("Invalid mapping. Please enter a mapping that has 26 unique "
                    "alphabet characters in lowercase.\n"); 
            while (map_length == 27) {
                fgets(mapping, MAX_MAP, stdin);
                map_length = strlen(mapping);
            }
        } else {
            valid = 1;
        }
    }
    
    if (valid == 1) {
        printf("Enter text:\n");
        char message[MAX_STRING];
        char line[MAX_STRING];
        int start = 0;
        int end = 0;

        while (fgets(line, MAX_STRING, stdin) != NULL) {
            start = end;
            int line_length = encrypt_line(line, mapping);
            end += line_length;
            for (int j = 0; j < line_length; j++) {
                message[j + start] = line[j]; 
                printf("%c", message[j + start]); 
            }  
        }
    }
    return 0;
}

int remove_duplicates(int length, char source[length]) {
    int copied = 0;
    int check_destination = 0;
    char destination[length];
    for (int i = 0; i < length; i++) {
        check_destination = 0;
        while (check_destination < copied && 
                destination[check_destination] != source[i]) {
            check_destination++;
        }
        if (check_destination == copied) {
            destination[copied] = source[i];
            copied++;
        }
    }
    return copied;
}

int check_valid(int length, char source[length]) {
    int valid = 0;
    for (int i = 0; i < length; i++) {
        if (source[i] < 'a' && source[i] != '\n') {
            valid = 1;
        }
    }
    return valid;
}

int encrypt_line(char line[MAX_STRING], char mapping[MAX_MAP]) {
    int string_length = strlen(line);
    int line_length = 0;
    for (int i = 0; i < string_length; i++) {
        if (line[i] <= 'z' && line[i] >= 'a') {
            line[i] = mapping[line[i] - 'a'];
        } else if (line[i] <= 'Z' && line[i] >= 'A') {
            line[i] = mapping[line[i] - 'A'] - ('a' - 'A');
        }
        line_length++;
    }
    
    return line_length;
}