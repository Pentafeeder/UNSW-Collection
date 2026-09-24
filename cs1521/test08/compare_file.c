#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    FILE *stream1 = fopen(argv[1], "r");

    FILE *stream2 = fopen(argv[2], "r");

    int input1 = fgetc(stream1);
    int input2 = fgetc(stream2);

    int nth_byte = 0;   
    // note, causes error because of short-circuiting (since input1 EOF, doesnt check input2)
    while (input1 != EOF && input2 != EOF) {
        if (input1 != input2) {
            printf("Files differ at byte %d\n", nth_byte);
            return 0;
        }
        input1 = fgetc(stream1);
        input2 = fgetc(stream2);
        nth_byte++;
    }
   


    if (input1 == EOF && input2 == EOF) {
        printf("Files are identical\n");
    } else if (input1 == EOF) {
        printf("EOF on %s\n", argv[1]);
    } else {
        printf("EOF on %s\n", argv[2]);
    }



    return 0;
}