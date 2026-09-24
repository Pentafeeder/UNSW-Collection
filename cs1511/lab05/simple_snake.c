// A simpler version of the famous Snake game!
//
// Written by Rory Golledge (z5308772) on 3/3/23
// Modified by Kevin Le (z5481482) on 14/03/2023
//

#include <stdio.h>

#define SIZE 8

enum land {
    NOT_VISITED,
    VISITED,
    SNAKE,
    APPLE
};

void initialise_map(enum land map[SIZE][SIZE]);
void print_map(enum land map[SIZE][SIZE]);

int main(void) {
    enum land map[SIZE][SIZE];
    initialise_map(map);
 
    printf("Welcome to Snake!\n");

    // TODO: Complete the program
    printf("Please enter apple location: ");
    int apple_x, apple_y;
    scanf("%d %d", &apple_y, &apple_x);
    
    printf("Please enter snake location: ");
    int snake_x, snake_y;
    scanf("%d %d", &snake_y, &snake_x);
    
    map[snake_y][snake_x] = SNAKE;
    map[apple_y][apple_x] = APPLE;
    
    print_map(map);

    do {
        char direction;
        scanf(" %c", &direction);
        map[snake_y][snake_x] = VISITED;
        if (direction == 'u') {
            snake_y--;
        } else if (direction == 'r') {
            snake_x++;
        } else if (direction == 'd') {
            snake_y++;
        } else if (direction == 'l') {
            snake_x--;
        }
        map[snake_y][snake_x] = SNAKE;
        print_map(map);
    } while (snake_y != apple_y || snake_x != apple_x);
    printf("Chomp!\n");
    return 0;
}

/**
 * Initialises the given `map` such that all tiles are `NOT_VISITED`
 * 
 * Parameters:
 *     map - The map to initialise
 * 
 * Returns:
 *     Nothing
 */
void initialise_map(enum land map[SIZE][SIZE]) {
    for (int row = 0; row < SIZE; ++row) {
        for (int col = 0; col < SIZE; ++col) {
            map[row][col] = NOT_VISITED;
        }
    }
}

/**
 * Prints the given `map` such that all enum values are printed as nice
 * characters.
 * 
 * Parameters:
 *     map - The map to print out
 * 
 * Returns:
 *     Nothing
 */
void print_map(enum land map[SIZE][SIZE]) {
    for (int row = 0; row < SIZE; ++row) {
        for (int col = 0; col < SIZE; ++col) {
            if (map[row][col] == NOT_VISITED) {
                printf(". ");
            } else if (map[row][col] == VISITED) {
                printf("- ");
            } else if (map[row][col] == SNAKE) {
                printf("S ");
            } else if (map[row][col] == APPLE) {
                printf("A ");
            }
        }
        printf("\n");
    }
}