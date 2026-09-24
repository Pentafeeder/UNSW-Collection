// Written by <Kevin Le> (<z5481482>) 
// on <14/03/2023>
//
// Interactive program to scan in and calculate 
// details about the weather

#define NUM_TEMPS 4
#define NUM_HUMIDITY 5

#include <stdio.h>

void intro(void);
double get_avg_temp(double temps[NUM_TEMPS]);
double get_avg_humidity(double temps[NUM_HUMIDITY]);
void give_temp_info(double average_temp);
void give_humidity_info(double average_humidity);

int main(void) {

    // Intro
    intro();

    // Read Temperatures
    printf("Please enter the past %d day(s) worth of temperatures.\n", NUM_TEMPS);

    double temps[NUM_TEMPS] = {0.0};
    int counter = 0;
    while (counter < NUM_TEMPS) {
        scanf("%lf", &temps[counter]);
        counter++;
    }

    // Read Humidities
    printf("Please enter the last %d days(s) worth of humidities\n", NUM_HUMIDITY);
    double humidity[NUM_HUMIDITY] = {0.0};
    counter = 0;
    while (counter < NUM_HUMIDITY) {
        scanf("%lf", &humidity[counter]);
        counter++;
    }

    // Get average Temperature
    double average_temp = get_avg_temp(temps); 

    // Get average humidity
    double average_humidity = get_avg_humidity(humidity);

    // Give info about average temp
    give_temp_info(average_temp);

    // Give info about average humidity
    give_humidity_info(average_humidity);

    return 0;
}

void intro(void) {
    printf("Hello and welcome to CS Weather!\n");
    printf("=======================================\n");
    printf("This program will help you to analyse a given weather patten\n");
    printf("and make some predictions about the coming day\n");
}

double get_avg_temp(double temps[NUM_TEMPS]) {
    int counter = 0;
    double sum = 0.0;
    while (counter < NUM_TEMPS)
    {
        sum += temps[counter];
        counter++;
    }
    double average_temp = sum / NUM_TEMPS;
    return average_temp;
}

double get_avg_humidity(double humidity[NUM_HUMIDITY]) {
    int counter = 0;
    double sum = 0.0;
    while (counter < NUM_HUMIDITY)
    {
        sum += humidity[counter];
        counter++;
    }
    double average_humidity = sum / NUM_HUMIDITY;
    return average_humidity;
}

void give_temp_info(double average_temp) {
    printf("The average temperature was: %lf\n", average_temp);
    if (average_temp >= 28.0) {
        printf("It will be hot tomorrow!");
    } else if (average_temp >= 15.0 && average_temp < 28.0 ) {
        printf("Should be a lovely temperature tomorrow.\n");
    } else {
        printf("It'll be chilly tomorrow, pack a jumper!\n");
    }
}

void give_humidity_info(double average_humidity) {
    printf("The average humidity was: %lf\n", average_humidity);
    if (average_humidity > 80.0) {
        printf("It will be humid tomorrow.\n");
    } else {
        printf("Shouldn't be too humid tomorrow.\n");
    }
}