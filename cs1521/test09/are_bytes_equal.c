#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


int main(int argc, char *argv[]) {

    FILE *file1 = fopen(argv[1], "r");
    FILE *file2 = fopen(argv[3], "r");

    fseek(file1, atoi(argv[2]), SEEK_SET);
    fseek(file2, atoi(argv[4]), SEEK_SET);

    int character1 = fgetc(file1);
    int character2 = fgetc(file2);


    if (character1 != EOF && character2 != EOF) {
        
        if (character1 == character2) {
            printf("byte %s in %s and byte %s in %s are the same\n", 
                        argv[2], argv[1], argv[4], argv[3]);
            return 0;
        }       
    }

    printf("byte %s in %s and byte %s in %s are not the same\n",
             argv[2], argv[1], argv[4], argv[3]);

    return 0;
}