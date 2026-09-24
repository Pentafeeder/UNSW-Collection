// assignment1 (cs defense)
//
// This program was written by [Kevin Le] (z5481482)
// on [10/03/2023]
//
// TODO: Description of program

#include <stdio.h>

#define MAP_ROWS 6
#define MAP_COLUMNS 12

////////////////////////////////////////////////////////////////////////////////
/////////////////////////// USER DEFINED TYPES  ////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
enum land_type {
    GRASS,
    WATER,
    PATH_START,
    PATH_END,
    PATH_UP,
    PATH_RIGHT,
    PATH_DOWN,
    PATH_LEFT,
    TELEPORTER
};

enum entity {
    EMPTY,
    ENEMY,
    BASIC_TOWER,
    POWER_TOWER,
    FORTIFIED_TOWER,
};

struct tile {
    enum land_type land;
    enum entity entity;

    int n_enemies;
};

struct coord {
    int row, col;
};

struct moving {
    int row, col;
    int n_enemies;
    int exists;
};

////////////////////////////////////////////////////////////////////////////////
////////////////////////  YOUR FUNCTION PROTOTYPE  /////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// TODO: Put your function prototypes here
void enter_lake(struct tile map[MAP_ROWS][MAP_COLUMNS]);
int valid_point(int row, int column);
int enter_path(struct tile map[MAP_ROWS][MAP_COLUMNS], struct coord start);
void spawn_enemies(struct tile map[MAP_ROWS][MAP_COLUMNS], struct coord start);
int place_towers(struct tile map[MAP_ROWS][MAP_COLUMNS], int money);
void print_tower_error(void);
int move_enemies(struct tile map[MAP_ROWS][MAP_COLUMNS], struct coord start,
                    struct coord end, struct moving move_to[], int array_size);
int upgrade_tower(struct tile map[MAP_ROWS][MAP_COLUMNS], int money);
int search_enemies_to_attack(struct tile map[MAP_ROWS][MAP_COLUMNS], 
                                int money, int path_size, struct coord start);
void attack(struct tile map[MAP_ROWS][MAP_COLUMNS],  struct coord position, 
                int attacks);
////////////////////////////////////////////////////////////////////////////////
////////////////////// PROVIDED FUNCTION PROTOTYPE  ////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void initialise_map(struct tile map[MAP_ROWS][MAP_COLUMNS]);
void print_map(struct tile map[MAP_ROWS][MAP_COLUMNS], int lives, int money);
void print_tile(struct tile tile, int entity_print);

int main(void) {
    // This `map` variable is a 2D array of `struct tile`s.
    // It is `MAP_ROWS` x `MAP_COLUMNS` in size (which is 6x12 for this
    // assignment!)
    struct tile map[MAP_ROWS][MAP_COLUMNS];

    // This will initialise all tiles in the map to have GRASS land and EMPTY
    // entity values.
    initialise_map(map);
    
    // TODO: Start writing code here!

    // TODO: Stage 1.1 - Scan in lives, money and start/ending points, then
    // print out the map!
    int lives;
    int money;
    struct coord start;
    struct coord end;

    printf("Starting Lives: ");
    scanf("%d", &lives);
    printf("Starting Money($): ");
    scanf("%d", &money);
    printf("Start Point: ");
    scanf("%d %d", &start.row, &start.col);
    printf("End Point: ");
    scanf("%d %d", &end.row, &end.col);

    map[start.row][start.col].land = PATH_START;
    map[end.row][end.col].land = PATH_END;
    
    print_map(map, lives, money);
    // TODO: Stage 1.2 - Scan in the initial enemies. Make sure you change the
    // `entity` at the starting position to be ENEMY, and that you update the
    // `n_enemies` value at that position to be this scanned value!
    
    printf("Initial Enemies: "); 
    spawn_enemies(map, start);

    print_map(map, lives, money);
    
    // stage 1.3 - adds lake
    enter_lake(map);
    print_map(map, lives, money);

    int path_size = enter_path(map, start);
    struct moving move_to[path_size];

    print_map(map, lives, money);
    
    //gets command until end of game (ctrl + D is inputted or no more lives)
    char command;
    int lives_lost = 0;
    printf("Enter Command: ");
    int valid = scanf(" %c", &command);
    while (valid == 1 && lives > 0) {
        if (command == 'e') {
            spawn_enemies(map, start);
        } else if (command == 't') {
            money = place_towers(map, money);
        } else if (command == 'm') {
            
            lives_lost = move_enemies(map, start, end, move_to, path_size);
            lives = lives - lives_lost;
            
            printf("%d enemies reached the end!\n", lives_lost);
        } else if (command == 'u') {
            money = upgrade_tower(map, money);
        } else if (command == 'a') {
            money = search_enemies_to_attack(map, money, path_size, start);
        }
       
        print_map(map, lives, money);
        
        if (lives > 0) {
            printf("Enter Command: ");
            valid = scanf(" %c", &command);
        } else {
            printf("Oh no, you ran out of lives!");
            valid = 0;
        }
    }
    printf("\nGame Over!\n");

    return 0;
}


////////////////////////////////////////////////////////////////////////////////
/////////////////////////////  YOUR FUNCTIONS //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// TODO: Put your functions here
void enter_lake(struct tile map[MAP_ROWS][MAP_COLUMNS]) {
    int lake_row, lake_col, row = 0, col = 0, height, width;
    
    printf("Enter Lake: ");
    scanf("%d %d %d %d", &lake_row, &lake_col, &height, &width);
    
    if (!valid_point(lake_row + height, lake_col + width) || 
            !valid_point(lake_row, lake_col)) {
        printf("Error: Lake out of bounds, ignoring...\n");
    } else {
        while (row < height) {
            col = 0;
            while (col < width) {
                map[lake_row + row][lake_col + col].land = WATER;
                col++;
            }
            row++;
        }
    }
}

int enter_path(struct tile map[MAP_ROWS][MAP_COLUMNS], 
                    struct coord start) {
    printf("Enter Path: ");
    int row = start.row, col = start.col;
    char direction;
    int path = scanf(" %c", &direction);
    int path_size = 0;
    while (path == 1) {
        
        if (direction == 'u') {
            map[row][col].land = PATH_UP;
            --row;
        } else if (direction == 'r') {
            map[row][col].land = PATH_RIGHT;
            ++col;
        } else if (direction == 'd') {
            map[row][col].land = PATH_DOWN;
            ++row;
        } else if (direction == 'l') {
            map[row][col].land = PATH_LEFT;
            --col;
        }
        
        if (direction != ' ') {
            path_size++;
        }

        if (direction != '\n') {
            path = scanf("%c", &direction);
        } else {
            path = 0;
        }
    }
    return path_size;
}


void spawn_enemies(struct tile map[MAP_ROWS][MAP_COLUMNS], struct coord start) {
    int enemies;
    scanf(" %d", &enemies);
    if (enemies > 0) {
        map[start.row][start.col].entity = ENEMY;
        map[start.row][start.col].n_enemies += enemies;
    }
}

int place_towers(struct tile map[MAP_ROWS][MAP_COLUMNS], int money) {
    int row, col;
    scanf("%d %d", &row, &col);
    
    if (valid_point(row, col)) {
        int entity = map[row][col].entity;
        int land_type = map[row][col].land;

        if (entity == EMPTY && land_type == GRASS && money >= 200) {
            map[row][col].entity = BASIC_TOWER;
            printf("Tower successfully created!\n");
            return money - 200;
        } else {
            print_tower_error();
        }
    } else {
        print_tower_error();

    }
    return money;
}

void print_tower_error(void) {
    printf("Error: Tower creation unsuccessful. ");
    printf("Make sure you have at least $200 and that the tower is ");           
    printf("placed on a grass block with no entity.\n");
}

int move_enemies(struct tile map[MAP_ROWS][MAP_COLUMNS], struct coord start,
                    struct coord end, struct moving move_to[], int array_size) {
    int moves, current_move = 0;
    int lives_lost = 0;
    int row = start.row, col = start.col;
    int direction;
    int enemy_counter = 0;
    struct coord position;
    scanf(" %d", &moves);
    
    // loops through path and identifies if there is enemy or not
    while (enemy_counter < array_size) {
        if (map[row][col].entity == ENEMY) {
            move_to[enemy_counter].exists = 1;
            move_to[enemy_counter].n_enemies = map[row][col].n_enemies;
            map[row][col].n_enemies = 0;
            map[row][col].entity = EMPTY;
        } else {
            move_to[enemy_counter].exists = 0;
        }
        
        position.row = row;
        position.col = col;
        current_move = 0;
        // moves location of enemies along path and stores in move_to[] after
        while (current_move < moves) {
            direction = map[position.row][position.col].land;     
            if (direction == PATH_UP) {    
                position.row--; 
            } else if (direction == PATH_RIGHT) {
                position.col++;
            } else if (direction == PATH_DOWN) {
                position.row++;
            } else if (direction == PATH_LEFT) {
                position.col--;
            }
            // stores first step only for next path
            if (current_move == 0) {
                row = position.row;
                col = position.col;
            }

            if (position.row == end.row && position.col == end.col && 
                    move_to[enemy_counter].exists == 1) {
                lives_lost += move_to[enemy_counter].n_enemies;
                move_to[enemy_counter].exists = 0;
            }  
            
            current_move++;
        }
        
        move_to[enemy_counter].row = position.row;
        move_to[enemy_counter].col = position.col;
        
        enemy_counter++;
    } 
    
    enemy_counter = 0;
    // reassigns new location for enemy on map (except for end)
    while (enemy_counter < array_size) {
        if (move_to[enemy_counter].exists == 1) {
            row = move_to[enemy_counter].row;
            col = move_to[enemy_counter].col;

            map[row][col].n_enemies = move_to[enemy_counter].n_enemies;
            map[row][col].entity = ENEMY;

            move_to[enemy_counter].n_enemies = 0;
            move_to[enemy_counter].exists = 0;
        }
        
        enemy_counter++;
    }
    return lives_lost;
}

int upgrade_tower(struct tile map[MAP_ROWS][MAP_COLUMNS], int money) {
    int row, col;
    scanf("%d %d", &row, &col);
    int tower_type = map[row][col].entity;

    if (!valid_point(row, col)) {
        printf("Error: Upgrade target is out-of-bounds.\n");
    } else if (tower_type != BASIC_TOWER && tower_type != POWER_TOWER  &&
                    tower_type != FORTIFIED_TOWER) {
        printf("Error: Upgrade target contains no tower entity.\n");
    } else if (tower_type == FORTIFIED_TOWER) {
        printf("Error: Tower cannot be upgraded further.\n");
    } else if ((money < 300 && tower_type == BASIC_TOWER) || 
                    (money < 500 && tower_type == POWER_TOWER)) {
        printf("Error: Insufficient Funds.\n");
    } else {
        if (tower_type == BASIC_TOWER && money >= 300) {
            money -= 300;
            map[row][col].entity = POWER_TOWER;
        } else {
            money -= 500;
            map[row][col].entity = FORTIFIED_TOWER;
        }
        printf("Upgrade Successful!\n");
    }

    return money;
}

int search_enemies_to_attack(struct tile map[MAP_ROWS][MAP_COLUMNS], int money, 
                                int path_size, struct coord start) {
    int attacks;
    scanf(" %d", &attacks);
    struct coord position;
    position.row = start.row;
    position.col = start.col;
    
    int direction = map[position.row][position.col].land;
    int enemies_destroyed = 0;
    
    for (int i = 0; i < path_size; i++) {
        direction = map[position.row][position.col].land;
        
        if (map[position.row][position.col].entity == ENEMY) {
            int enemy_holder = map[position.row][position.col].n_enemies;
            attack(map, position, attacks);
            enemies_destroyed += enemy_holder - map[position.row][position.col].n_enemies;
            if (map[position.row][position.col].n_enemies < 1) {
                map[position.row][position.col].entity = EMPTY;
            }
            while (map[position.row][position.col].n_enemies < 0) {
                map[position.row][position.col].n_enemies++;
                enemies_destroyed--;
            }       
            
        }

        if (direction == PATH_UP) {    
            position.row--; 
        } else if (direction == PATH_RIGHT) {
            position.col++;
        } else if (direction == PATH_DOWN) {
            position.row++;
        } else if (direction == PATH_LEFT) {
            position.col--;
        }

    }
    printf("%d enemies destroyed!\n", enemies_destroyed);
    money += enemies_destroyed * 5;
    return money;
}

void attack(struct tile map[MAP_ROWS][MAP_COLUMNS], struct coord position, int attacks) {
    struct coord search;
    
    search.row = position.row - 2;
    search.col = position.col - 2;
    
    while (!valid_point(search.row, position.col)) {
        search.row++;
    }
    int valid_col = search.col;
    while (!valid_point(position.row, valid_col)) {
        valid_col++;
    }
    
    while (search.row < position.row + 3 && valid_point(search.row, position.col)) {
        search.col = valid_col;
        while (search.col < position.col + 3 && valid_point(position.row, search.col)) {
            
            if (map[search.row][search.col].entity == FORTIFIED_TOWER) {
                map[position.row][position.col].n_enemies -= 3 * attacks;
            } 
            
            if ((search.col >= position.col - 1 && search.col <= position.col + 1) && 
                    (search.row >= position.row - 1 && search.row <= position.row + 1)) {
                if (map[search.row][search.col].entity == BASIC_TOWER) {
                    map[position.row][position.col].n_enemies -= 1 * attacks;
                } else if (map[search.row][search.col].entity == POWER_TOWER) {
                    map[position.row][position.col].n_enemies -= 2 * attacks;
                }
            }
            
            search.col++;
        }
        
        search.row++;
    }
}

//maybe make own attack function
int valid_point(int row, int column) {
    return !(row < 0 || row > MAP_ROWS || column > MAP_COLUMNS || column < 0);
}

////////////////////////////////////////////////////////////////////////////////
/////////////////////////// PROVIDED FUNCTIONS  ///////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/**
 * Initialises map tiles to contain GRASS land and EMPTY entity.
 * 
 * Parameters:
 *     map - The map to initialise.
 * Returns:
 *     Nothing.
 */
void initialise_map(struct tile map[MAP_ROWS][MAP_COLUMNS]) {
    for (int row = 0; row < MAP_ROWS; ++row) {
        for (int col = 0; col < MAP_COLUMNS; ++col) {
            map[row][col].land = GRASS;
            map[row][col].entity = EMPTY;
            map[row][col].n_enemies = 0;
        }
    }
}

/**
 * Prints all map tiles based on their value, with a header displaying lives
 * and money.
 * 
 * Parameters:
 *     map   - The map to print tiles from.
 *     lives - The number of lives to print with the map.
 *     money - The amount of money to print with the map.
 * Returns:
 *     Nothing.
 */
void print_map(struct tile map[MAP_ROWS][MAP_COLUMNS], int lives, int money) {
    printf("\nLives: %d Money: $%d\n", lives, money);
    for (int row = 0; row < MAP_ROWS * 2; ++row) {
        for (int col = 0; col < MAP_COLUMNS; ++col) {
            print_tile(map[row / 2][col], row % 2);
        }
        printf("\n");
    }
}

/**
 * Prints either the land or entity component of a single tile, based on
 * the `land_print` parameter;
 * 
 * Parameters:
 *     tile         - The tile to print the land/entity from
 *     land_print - Whether to print the land part of the tile or the entity
 *         part of the tile. If this value is 0, it prints the land, otherwise
 *         it prints the entity.
 * Returns:
 *     Nothing.
 */
void print_tile(struct tile tile, int land_print) {
    if (land_print) {
        if (tile.land == GRASS) {
            printf(" . ");
        } else if (tile.land == WATER) {
            printf(" ~ ");
        } else if (tile.land == PATH_START) {
            printf(" S ");
        } else if (tile.land == PATH_END) {
            printf(" E ");
        } else if (tile.land == PATH_UP) {
            printf(" ^ ");
        } else if (tile.land == PATH_RIGHT) {
            printf(" > ");
        } else if (tile.land == PATH_DOWN) {
            printf(" v ");
        } else if (tile.land == PATH_LEFT) {
            printf(" < ");
        } else if (tile.land == TELEPORTER) {
            printf("( )");
        } else {
            printf(" ? ");
        }
    } else {
        if (tile.entity == EMPTY) {
            printf("   ");
        } else if (tile.entity == ENEMY) {
            printf("%03d", tile.n_enemies);
        } else if (tile.entity == BASIC_TOWER) {
            printf("[B]");
        } else if (tile.entity == POWER_TOWER) {
            printf("[P]");
        } else if (tile.entity == FORTIFIED_TOWER) {
            printf("[F]");
        } else {
            printf(" ? ");
        }
    }
}







==========
// assignment1 (cs defense)
//
// This program was written by [Kevin Le] (z5481482)
// on [10/03/2023]
//
// TODO: Description of program

#include <stdio.h>

#define MAP_ROWS 6
#define MAP_COLUMNS 12

////////////////////////////////////////////////////////////////////////////////
/////////////////////////// USER DEFINED TYPES  ////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
enum land_type {
    GRASS,
    WATER,
    PATH_START,
    PATH_END,
    PATH_UP,
    PATH_RIGHT,
    PATH_DOWN,
    PATH_LEFT,
    TELEPORTER
};

enum entity {
    EMPTY,
    ENEMY,
    BASIC_TOWER,
    POWER_TOWER,
    FORTIFIED_TOWER,
};

struct tile {
    enum land_type land;
    enum entity entity;

    int n_enemies;
};

struct coord {
    int row, col;
};

struct moving {
    int row, col;
    int n_enemies;
    int exists;
};

////////////////////////////////////////////////////////////////////////////////
////////////////////////  YOUR FUNCTION PROTOTYPE  /////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// TODO: Put your function prototypes here
void enter_lake(struct tile map[MAP_ROWS][MAP_COLUMNS]);
int valid_point(int row, int column);
int enter_path(struct tile map[MAP_ROWS][MAP_COLUMNS], struct coord start);
void spawn_enemies(struct tile map[MAP_ROWS][MAP_COLUMNS], struct coord start);
int place_towers(struct tile map[MAP_ROWS][MAP_COLUMNS], int money);
void print_tower_error(void);
int move_enemies(struct tile map[MAP_ROWS][MAP_COLUMNS], struct coord start,
                    struct coord end, struct moving move_to[], int array_size);
int upgrade_tower(struct tile map[MAP_ROWS][MAP_COLUMNS], int money);
int search_enemies_to_attack(struct tile map[MAP_ROWS][MAP_COLUMNS], 
                                int money, int path_size, struct coord start);
void search_towers_in_range(struct tile map[MAP_ROWS][MAP_COLUMNS],  
                                struct coord position, int attacks);
void attack(struct tile map[MAP_ROWS][MAP_COLUMNS], int attacks, struct coord position,
                struct coord enemy_position);
////////////////////////////////////////////////////////////////////////////////
////////////////////// PROVIDED FUNCTION PROTOTYPE  ////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void initialise_map(struct tile map[MAP_ROWS][MAP_COLUMNS]);
void print_map(struct tile map[MAP_ROWS][MAP_COLUMNS], int lives, int money);
void print_tile(struct tile tile, int entity_print);

int main(void) {
    // This `map` variable is a 2D array of `struct tile`s.
    // It is `MAP_ROWS` x `MAP_COLUMNS` in size (which is 6x12 for this
    // assignment!)
    struct tile map[MAP_ROWS][MAP_COLUMNS];

    // This will initialise all tiles in the map to have GRASS land and EMPTY
    // entity values.
    initialise_map(map);
    
    // TODO: Start writing code here!

    // TODO: Stage 1.1 - Scan in lives, money and start/ending points, then
    // print out the map!
    int lives;
    int money;
    struct coord start;
    struct coord end;

    printf("Starting Lives: ");
    scanf("%d", &lives);
    printf("Starting Money($): ");
    scanf("%d", &money);
    printf("Start Point: ");
    scanf("%d %d", &start.row, &start.col);
    printf("End Point: ");
    scanf("%d %d", &end.row, &end.col);

    map[start.row][start.col].land = PATH_START;
    map[end.row][end.col].land = PATH_END;
    
    print_map(map, lives, money);
    // TODO: Stage 1.2 - Scan in the initial enemies. Make sure you change the
    // `entity` at the starting position to be ENEMY, and that you update the
    // `n_enemies` value at that position to be this scanned value!
    
    printf("Initial Enemies: "); 
    spawn_enemies(map, start);

    print_map(map, lives, money);
    
    // stage 1.3 - adds lake
    enter_lake(map);
    print_map(map, lives, money);

    int path_size = enter_path(map, start);
    struct moving move_to[path_size];

    print_map(map, lives, money);
    
    //gets command until end of game (ctrl + D is inputted or no more lives)
    char command;
    int lives_lost = 0;
    printf("Enter Command: ");
    int valid = scanf(" %c", &command);
    while (valid == 1 && lives > 0) {
        if (command == 'e') {
            spawn_enemies(map, start);
        } else if (command == 't') {
            money = place_towers(map, money);
        } else if (command == 'm') {
            
            lives_lost = move_enemies(map, start, end, move_to, path_size);
            lives = lives - lives_lost;
            
            printf("%d enemies reached the end!\n", lives_lost);
        } else if (command == 'u') {
            money = upgrade_tower(map, money);
        } else if (command == 'a') {
            money = search_enemies_to_attack(map, money, path_size, start);
        }
       
        print_map(map, lives, money);
        
        if (lives > 0) {
            printf("Enter Command: ");
            valid = scanf(" %c", &command);
        } else {
            printf("Oh no, you ran out of lives!");
            valid = 0;
        }
    }
    printf("\nGame Over!\n");

    return 0;
}


////////////////////////////////////////////////////////////////////////////////
/////////////////////////////  YOUR FUNCTIONS //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// TODO: Put your functions here
void enter_lake(struct tile map[MAP_ROWS][MAP_COLUMNS]) {
    int lake_row, lake_col, row = 0, col = 0, height, width;
    
    printf("Enter Lake: ");
    scanf("%d %d %d %d", &lake_row, &lake_col, &height, &width);
    
    if (!valid_point(lake_row + height, lake_col + width) || 
            !valid_point(lake_row, lake_col)) {
        printf("Error: Lake out of bounds, ignoring...\n");
    } else {
        while (row < height) {
            col = 0;
            while (col < width) {
                map[lake_row + row][lake_col + col].land = WATER;
                col++;
            }
            row++;
        }
    }
}

int enter_path(struct tile map[MAP_ROWS][MAP_COLUMNS], 
                    struct coord start) {
    printf("Enter Path: ");
    int row = start.row, col = start.col;
    char direction;
    int path = scanf(" %c", &direction);
    int path_size = 0;
    while (path == 1) {
        
        if (direction == 'u') {
            map[row][col].land = PATH_UP;
            --row;
        } else if (direction == 'r') {
            map[row][col].land = PATH_RIGHT;
            ++col;
        } else if (direction == 'd') {
            map[row][col].land = PATH_DOWN;
            ++row;
        } else if (direction == 'l') {
            map[row][col].land = PATH_LEFT;
            --col;
        }
        
        if (direction != ' ') {
            path_size++;
        }

        if (direction != '\n') {
            path = scanf("%c", &direction);
        } else {
            path = 0;
        }
    }
    return path_size;
}


void spawn_enemies(struct tile map[MAP_ROWS][MAP_COLUMNS], struct coord start) {
    int enemies;
    scanf(" %d", &enemies);
    if (enemies > 0) {
        map[start.row][start.col].entity = ENEMY;
        map[start.row][start.col].n_enemies += enemies;
    }
}

int place_towers(struct tile map[MAP_ROWS][MAP_COLUMNS], int money) {
    int row, col;
    scanf("%d %d", &row, &col);
    
    if (valid_point(row, col)) {
        int entity = map[row][col].entity;
        int land_type = map[row][col].land;

        if (entity == EMPTY && land_type == GRASS && money >= 200) {
            map[row][col].entity = BASIC_TOWER;
            printf("Tower successfully created!\n");
            return money - 200;
        } else {
            print_tower_error();
        }
    } else {
        print_tower_error();

    }
    return money;
}

void print_tower_error(void) {
    printf("Error: Tower creation unsuccessful. ");
    printf("Make sure you have at least $200 and that the tower is ");           
    printf("placed on a grass block with no entity.\n");
}

int move_enemies(struct tile map[MAP_ROWS][MAP_COLUMNS], struct coord start,
                    struct coord end, struct moving move_to[], int array_size) {
    int moves, current_move = 0;
    int lives_lost = 0;
    int row = start.row, col = start.col;
    int direction;
    int enemy_counter = 0;
    struct coord position;
    scanf(" %d", &moves);
    
    // loops through path and identifies if there is enemy or not
    while (enemy_counter < array_size) {
        if (map[row][col].entity == ENEMY) {
            move_to[enemy_counter].exists = 1;
            move_to[enemy_counter].n_enemies = map[row][col].n_enemies;
            map[row][col].n_enemies = 0;
            map[row][col].entity = EMPTY;
        } else {
            move_to[enemy_counter].exists = 0;
        }
        
        position.row = row;
        position.col = col;
        current_move = 0;
        // moves location of enemies along path and stores in move_to[] after
        while (current_move < moves) {
            direction = map[position.row][position.col].land;     
            if (direction == PATH_UP) {    
                position.row--; 
            } else if (direction == PATH_RIGHT) {
                position.col++;
            } else if (direction == PATH_DOWN) {
                position.row++;
            } else if (direction == PATH_LEFT) {
                position.col--;
            }
            // stores first step only for next path
            if (current_move == 0) {
                row = position.row;
                col = position.col;
            }

            if (position.row == end.row && position.col == end.col && 
                    move_to[enemy_counter].exists == 1) {
                lives_lost += move_to[enemy_counter].n_enemies;
                move_to[enemy_counter].exists = 0;
            }  
            
            current_move++;
        }
        
        move_to[enemy_counter].row = position.row;
        move_to[enemy_counter].col = position.col;
        
        enemy_counter++;
    } 
    
    enemy_counter = 0;
    // reassigns new location for enemy on map (except for end)
    while (enemy_counter < array_size) {
        if (move_to[enemy_counter].exists == 1) {
            row = move_to[enemy_counter].row;
            col = move_to[enemy_counter].col;

            map[row][col].n_enemies = move_to[enemy_counter].n_enemies;
            map[row][col].entity = ENEMY;

            move_to[enemy_counter].n_enemies = 0;
            move_to[enemy_counter].exists = 0;
        }
        
        enemy_counter++;
    }
    return lives_lost;
}

int upgrade_tower(struct tile map[MAP_ROWS][MAP_COLUMNS], int money) {
    int row, col;
    scanf("%d %d", &row, &col);
    int tower_type = map[row][col].entity;

    if (!valid_point(row, col)) {
        printf("Error: Upgrade target is out-of-bounds.\n");
    } else if (tower_type != BASIC_TOWER && tower_type != POWER_TOWER  &&
                    tower_type != FORTIFIED_TOWER) {
        printf("Error: Upgrade target contains no tower entity.\n");
    } else if (tower_type == FORTIFIED_TOWER) {
        printf("Error: Tower cannot be upgraded further.\n");
    } else if ((money < 300 && tower_type == BASIC_TOWER) || 
                    (money < 500 && tower_type == POWER_TOWER)) {
        printf("Error: Insufficient Funds.\n");
    } else {
        if (tower_type == BASIC_TOWER && money >= 300) {
            money -= 300;
            map[row][col].entity = POWER_TOWER;
        } else {
            money -= 500;
            map[row][col].entity = FORTIFIED_TOWER;
        }
        printf("Upgrade Successful!\n");
    }

    return money;
}

int search_enemies_to_attack(struct tile map[MAP_ROWS][MAP_COLUMNS], int money, 
                                int path_size, struct coord start) {
    int attacks;
    scanf(" %d", &attacks);
    struct coord position;
    position.row = start.row;
    position.col = start.col;
    int direction = map[position.row][position.col].land;
    int enemies_destroyed = 0;
    for (int i = 0; i < path_size; i++) {
        direction = map[position.row][position.col].land;
        
        if (map[position.row][position.col].entity == ENEMY) {
            int enemy_holder = map[position.row][position.col].n_enemies;
            search_towers_in_range(map, position, attacks);
            enemies_destroyed += enemy_holder - map[position.row][position.col].n_enemies;
            if (map[position.row][position.col].n_enemies < 1) {
                map[position.row][position.col].entity = EMPTY;
            }
            while (map[position.row][position.col].n_enemies < 0) {
                map[position.row][position.col].n_enemies++;
                enemies_destroyed--;
            }       
            
        }

        if (direction == PATH_UP) {    
            position.row--; 
        } else if (direction == PATH_RIGHT) {
            position.col++;
        } else if (direction == PATH_DOWN) {
            position.row++;
        } else if (direction == PATH_LEFT) {
            position.col--;
        }

    }
    printf("%d enemies destroyed!\n", enemies_destroyed);
    money += enemies_destroyed * 5;
    return money;
}

void search_towers_in_range(struct tile map[MAP_ROWS][MAP_COLUMNS], struct coord enemy_position, 
                                int attacks) {
   
    struct coord search_position;
    search_position.row = enemy_position.row - 2;
    search_position.col = enemy_position.col - 2;
    while (!valid_point(search_position.row, enemy_position.col)) {
        search_position.row++;
    }
    int valid_col = search_position.col;
    while (!valid_point(enemy_position.row, valid_col)) {
        valid_col++;
    }
    
    while (search_position.row < search_position.row + 3 &&
            valid_point(search_position.row, enemy_position.col)) {
        search_position.col = valid_col;
        while (search_position.col < enemy_position.col + 3 && 
                valid_point(enemy_position.row, search_position.col)) {  
            attack(map, attacks, search_position, enemy_position);     
            search_position.col++;
        }   
        search_position.row++;
    }
}

void attack(struct tile map[MAP_ROWS][MAP_COLUMNS], int attacks, struct coord position,
                struct coord enemy_position) {
    printf("%d %d", position.row, position.col);
    if (map[position.row][position.col].entity == FORTIFIED_TOWER) {
        map[enemy_position.row][enemy_position.col].n_enemies -= 3 * attacks;
    } 
    
    if ((position.col >= enemy_position.col - 1 && position.col <= enemy_position.col + 1) && 
            (position.row >= enemy_position.row - 1 && position.row <= enemy_position.row + 1)) {
        if (map[position.row][position.col].entity == BASIC_TOWER) {
            map[enemy_position.row][enemy_position.col].n_enemies -= 1 * attacks;
        } else if (map[position.row][position.col].entity == POWER_TOWER) {
            map[enemy_position.row][enemy_position.col].n_enemies -= 2 * attacks;
        }
    }
}

//maybe make own attack function
int valid_point(int row, int column) {
    return !(row < 0 || row > MAP_ROWS || column > MAP_COLUMNS || column < 0);
}

////////////////////////////////////////////////////////////////////////////////
/////////////////////////// PROVIDED FUNCTIONS  ///////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/**
 * Initialises map tiles to contain GRASS land and EMPTY entity.
 * 
 * Parameters:
 *     map - The map to initialise.
 * Returns:
 *     Nothing.
 */
void initialise_map(struct tile map[MAP_ROWS][MAP_COLUMNS]) {
    for (int row = 0; row < MAP_ROWS; ++row) {
        for (int col = 0; col < MAP_COLUMNS; ++col) {
            map[row][col].land = GRASS;
            map[row][col].entity = EMPTY;
            map[row][col].n_enemies = 0;
        }
    }
}

/**
 * Prints all map tiles based on their value, with a header displaying lives
 * and money.
 * 
 * Parameters:
 *     map   - The map to print tiles from.
 *     lives - The number of lives to print with the map.
 *     money - The amount of money to print with the map.
 * Returns:
 *     Nothing.
 */
void print_map(struct tile map[MAP_ROWS][MAP_COLUMNS], int lives, int money) {
    printf("\nLives: %d Money: $%d\n", lives, money);
    for (int row = 0; row < MAP_ROWS * 2; ++row) {
        for (int col = 0; col < MAP_COLUMNS; ++col) {
            print_tile(map[row / 2][col], row % 2);
        }
        printf("\n");
    }
}

/**
 * Prints either the land or entity component of a single tile, based on
 * the `land_print` parameter;
 * 
 * Parameters:
 *     tile         - The tile to print the land/entity from
 *     land_print - Whether to print the land part of the tile or the entity
 *         part of the tile. If this value is 0, it prints the land, otherwise
 *         it prints the entity.
 * Returns:
 *     Nothing.
 */
void print_tile(struct tile tile, int land_print) {
    if (land_print) {
        if (tile.land == GRASS) {
            printf(" . ");
        } else if (tile.land == WATER) {
            printf(" ~ ");
        } else if (tile.land == PATH_START) {
            printf(" S ");
        } else if (tile.land == PATH_END) {
            printf(" E ");
        } else if (tile.land == PATH_UP) {
            printf(" ^ ");
        } else if (tile.land == PATH_RIGHT) {
            printf(" > ");
        } else if (tile.land == PATH_DOWN) {
            printf(" v ");
        } else if (tile.land == PATH_LEFT) {
            printf(" < ");
        } else if (tile.land == TELEPORTER) {
            printf("( )");
        } else {
            printf(" ? ");
        }
    } else {
        if (tile.entity == EMPTY) {
            printf("   ");
        } else if (tile.entity == ENEMY) {
            printf("%03d", tile.n_enemies);
        } else if (tile.entity == BASIC_TOWER) {
            printf("[B]");
        } else if (tile.entity == POWER_TOWER) {
            printf("[P]");
        } else if (tile.entity == FORTIFIED_TOWER) {
            printf("[F]");
        } else {
            printf(" ? ");
        }
    }
}