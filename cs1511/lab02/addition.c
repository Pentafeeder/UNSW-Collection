// Prints out an ascii mouse to the terminal
// art from: https://www.asciiart.eu/animals/rodents/mice
// by Kevin Le z5481482
// on 22/02/2023

#include <stdio.h>



int main(void){
    int students;
    int tutors;
    printf("Please enter the number of students and tutors: ");
    scanf("%d %d", &students, &tutors);
    printf("%d + %d = %d \n", students, tutors, students + tutors);
    return 0;
}
