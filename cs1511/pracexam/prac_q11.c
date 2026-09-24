#include <stdio.h>
#include <stdlib.h>

#define MAX_DIGITS 1501
#define MAX_N 5000

int main(int argc, char *argv[] ) {
    int n = atoi(argv[1]);

    int sequence[MAX_N][MAX_DIGITS];
    //setting base
    for (int i = 0; i < 3; i++) {
        sequence[i] = 1;
    }

    if (n <= 3) {
        printf("%d\n", sequence[n]);
    }


    return 0;
}

void sum(int sequence[], int n) {

}

void select_to_add(int sequence[][])
