// Takes the user's birth year and prints out corresponding zodiac animal
// Written by Kevin Le (z5481482) 
// on 01/03/2023

#include <stdio.h>

// This year corresponds to the Rat.
#define MIN_YEAR 1900

// Enum defining the different zodiac ANIMALS
enum zodiac_animal {
    RAT,
    OX,
    TIGER,
    RABBIT,
    DRAGON,
    SNAKE,
    HORSE,
    GOAT,
    MONKEY,
    ROOSTER,
    DOG,
    PIG
};

int main(void) {
    printf("Enter the year of your birth: ");
    //TODO complete the program:
    int year;
    scanf("%d", &year);
    int zodiac = (year - MIN_YEAR) % 12;

    if (zodiac == RAT) {
        printf("You were born in the year of the Rat!\n");
    }
    if (zodiac == OX) {
        printf("You were born in the year of the Ox!\n");
    }
    if (zodiac == TIGER) {
        printf("You were born in the year of the Tiger!\n");
    }
    if (zodiac == RABBIT) {
        printf("You were born in the year of the Rabbit!\n");
    }
    if (zodiac == DRAGON) {
        printf("You were born in the year of the Dragon!\n");
    }
    if (zodiac == SNAKE) {
        printf("You were born in the year of the Snake!\n");
    }
    if (zodiac == HORSE) {
        printf("You were born in the year of the Horse!\n");
    }
    if (zodiac == GOAT) {
        printf("You were born in the year of the Goat!\n");
    }
    if (zodiac == MONKEY) {
        printf("You were born in the year of the Monkey!\n");
    }
    if (zodiac == ROOSTER) {
        printf("You were born in the year of the Rooster!\n");
    }
    if (zodiac == DOG) {
        printf("You were born in the year of the Dog!\n");
    }
    if (zodiac == PIG) {
        printf("You were born in the year of the Pig!\n");
    }
    

    return 0;
}