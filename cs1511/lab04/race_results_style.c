// 
// Written 08/03/2023
// By Kevin Le z5481482
//
// takes car race results and prints them according to car number
//

#include <stdio.h>


#define MAX_CARS 20

struct race_result {
    // TODO: fill this in with the details of the result of a single car in the
    // race.
    //
    // i.e. This struct should contain:
    //      the car number (int), 
    //      and the race time (double).
    int car_num;
    double race_time;
};


// Prints the race result in the correct format.
void print_result(int car_number, double race_time);

int main(void) {

    // TODO: Declare an array of structs of size MAX_CARS
    struct race_result array[MAX_CARS]  = {};

    printf("How many cars in the race? ");
    // TODO: scan in number of cars in the race
    int car_amount;
    scanf("%d", &car_amount);

    printf("Enter results:\n");
    // TODO: scan in the details of each car into the array
    for (int i = 0; i < car_amount; i++) {
        scanf("%d %lf", &array[i].car_num, &array[i].race_time);
    }
    printf("Results:\n");
    
    // TODO: print all the results
    for (int i = 0; i < car_amount; i++) {
        print_result(array[i].car_num, array[i].race_time);
    }

    return 0;
}


//  Prints the race result in the correct format.
//
// Parameters:
// - `car_number` -- The car number of the result
// - `race_time` -- The time the car took to finish the race.
//
// Returns: nothing.
void print_result(int car_number, double race_time) {
    
    printf("%2d: %.2lf\n", car_number, race_time);
}