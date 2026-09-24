// By Kevin Le z5481482
// on 15/03/2023
// removes duplicates from one array and prints them out in another

#include <stdio.h>

int remove_duplicates(int length, int source[length], int destination[length]);

int remove_duplicates(int length, int source[length], int destination[length]) {
    int copied = 0;
    int check_destination = 0;
    for (int i = 0; i < length; i++) {
        check_destination = 0;
        while (check_destination < copied && destination[check_destination] != source[i]) {
            check_destination++;
        }
        if (check_destination == copied) {
            destination[copied] = source[i];
            copied++;
        }
    }
    return copied;
}
