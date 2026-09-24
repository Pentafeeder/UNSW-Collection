// By Kevin Le z5481842
// on 29/04/2023
// Will ask for height and number of bags and filter no. of bags by height

#include <stdio.h>
#include <stdlib.h>

#define SIZE 5

struct passenger {
    double height;
    int num_bags;
};

int main(void) {

    struct passenger my_array[SIZE];
    
    // printf("Total of %d bags from people over %lf\n", TODO, TODO);
    double selected_height;
    for (int i = 0; i < SIZE; i++) {
        printf("Enter height & number of bags: ");
        scanf(" %lf %d", &my_array[i].height, &my_array[i].num_bags);
    }
    
    printf("Select height: ");
    scanf(" %lf", &selected_height);
    int filtered_num_bags = 0;
    for (int i = 0; i < SIZE; i++) {
        if (my_array[i].height >= selected_height) {
            filtered_num_bags += my_array[i].num_bags;
        }
    }
    
    printf("Total of %d bags from people over %lf\n", filtered_num_bags, selected_height);
        
    return 0;
}