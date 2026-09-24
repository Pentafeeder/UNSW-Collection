#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIZE 5

struct coordinate {
    int x;
    int y;
};

double e_dist(struct coordinate p0, struct coordinate p1);
void adjacent_distances(struct coordinate arr[SIZE], int size);

int main(void) {

    // Only your function is called during testing
    // Any changes in this main function will not
    // be used in testing

    struct coordinate array1[SIZE] = {{.x = 1, .y = 1},
                                        {.x = 2, .y = 2},
                                        {.x = 9, .y = 2},
                                        {.x = 2, .y = 9},
                                        {.x = 0, .y = 0}};

    adjacent_distances(array1, SIZE);

    return 0;
}

void adjacent_distances(struct coordinate arr[SIZE], int size) {
    // TODO: Print the distances between adjacent coordinates
    
    // Your function should NOT return anything
    // Your function SHOULD print the distances

    for (int i = 0; i < SIZE - 1; i++) {
        double distance;
        double x_difference = arr[i].x - arr[i + 1].x;
        double y_difference = arr[i].y - arr[i + 1].y;
        x_difference *= x_difference;
        y_difference *= y_difference;
        distance = sqrt(x_difference + y_difference);
        printf("Dist: %lf\n", distance);
    }
}

double e_dist(struct coordinate p0, struct coordinate p1) {

    return sqrt((p1.x - p0.x)*(p1.x - p0.x)*1.0 +  (p1.y - p0.y)*(p1.y - p0.y)*1.0);
}
