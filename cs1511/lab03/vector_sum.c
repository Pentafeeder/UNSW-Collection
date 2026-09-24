// By Kevin Le z5481482
#include <stdio.h>

struct vector {
    int x_l;
    int y_l;
    int z_l;
};

int main(void) {

    //////////////// DO NOT CHANGE ANY OF THE CODE BELOW HERE //////////////////
    struct vector first_vector;
    struct vector second_vector;

    // Scans in vector values from user
    // Carefully read how these scanf's work ~ Try to understand it
    printf("Please enter the values of the first vector (x, y, z): ");
    scanf("%d %d %d", &first_vector.x_l, &first_vector.y_l, &first_vector.z_l);

    printf("Please enter the values of the second vector (x, y, z): ");
    scanf("%d %d %d", &second_vector.x_l, &second_vector.y_l, &second_vector.z_l);

    struct vector sum_vector;
    //////////////// DO NOT CHANGE ANY OF THE CODE ABOVE HERE //////////////////

    ////////////////////////////////////////////////////////////////////////////
    ///////////////////// ONLY WRITE CODE BELOW HERE ///////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    // TODO: Fill in `sum_vector` by adding each component of `first_vector`
    // and `second_vector`

    sum_vector.x_l = first_vector.x_l + second_vector.x_l;
    sum_vector.y_l = first_vector.y_l + second_vector.y_l;
    sum_vector.z_l = first_vector.z_l + second_vector.z_l;

    ////////////////////////////////////////////////////////////////////////////
    ///////////////////// ONLY WRITE CODE ABOVE HERE ///////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    printf("The resulting sum vector is:\n");
    printf("x: %d\n", sum_vector.x_l);
    printf("y: %d\n", sum_vector.y_l);
    printf("z: %d\n", sum_vector.z_l);
    return 0;
}