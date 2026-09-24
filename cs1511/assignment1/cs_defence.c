// assignment1 (cs defense)
//
// This program was written by [Kevin Le] (z5481482)
// on [10/03/2023]
//
// This program is a 2D text-based game inspired by the video game Bloon Tower
// Defence. It allows users to set up a map and input commands for the game

#include <stdio.h>

#define MAP_ROWS 6
#define MAP_COLUMNS 12
#define POTENTIAL_PATH_SIZE 72
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

struct move_object {
    int row, col;
    int n_enemies;
    int exists;
};

////////////////////////////////////////////////////////////////////////////////
////////////////////////  YOUR FUNCTION PROTOTYPE  /////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// TODO: Put your function prototypes here
void get_command(struct tile map[MAP_ROWS][MAP_COLUMNS], int money, int lives, 
        int path_size, struct coord start, 
        struct move_object path[POTENTIAL_PATH_SIZE] );

void enter_lake(struct tile map[MAP_ROWS][MAP_COLUMNS]);

int enter_path(struct tile map[MAP_ROWS][MAP_COLUMNS], struct coord start, 
        struct move_object path[POTENTIAL_PATH_SIZE]);

void spawn_enemies(struct tile map[MAP_ROWS][MAP_COLUMNS], struct coord start);

int place_towers(struct tile map[MAP_ROWS][MAP_COLUMNS], int money);

void print_tower_error(void);

int move_enemies(struct tile map[MAP_ROWS][MAP_COLUMNS], int path_size, 
        struct move_object path[POTENTIAL_PATH_SIZE]);

void relocate_enemies(struct tile map[MAP_ROWS][MAP_COLUMNS], 
        struct move_object move_to[], int path_size);

int teleporting(struct tile map[MAP_ROWS][MAP_COLUMNS], 
        struct move_object path[POTENTIAL_PATH_SIZE], int teleport_amount, 
        int counter);

int upgrade_tower(struct tile map[MAP_ROWS][MAP_COLUMNS], int money);

int search_enemies_to_attack(struct tile map[MAP_ROWS][MAP_COLUMNS], 
        int money, int path_size, struct move_object path[POTENTIAL_PATH_SIZE]);

void search_towers_in_range(struct tile map[MAP_ROWS][MAP_COLUMNS],  
        struct move_object path[POTENTIAL_PATH_SIZE], int attacks, 
        int position);

void attack(struct tile map[MAP_ROWS][MAP_COLUMNS], int attacks, 
        struct coord search_position, 
        struct move_object path[POTENTIAL_PATH_SIZE], int position);

void enter_rain(struct tile map[MAP_ROWS][MAP_COLUMNS]);

void change_to_rain(struct tile map[MAP_ROWS][MAP_COLUMNS], 
        struct coord spacing, struct coord offset, struct coord rain);

void create_flood(struct tile map[MAP_ROWS][MAP_COLUMNS]);

void flood_surroundings(struct tile map[MAP_ROWS][MAP_COLUMNS], int row, 
        int col);

void create_teleporter(struct tile map[MAP_ROWS][MAP_COLUMNS], 
        struct move_object path[POTENTIAL_PATH_SIZE], int path_size);

int teleporter_on_path(struct move_object path[POTENTIAL_PATH_SIZE], 
        struct coord teleporter1, struct coord teleporter2, int counter);

int valid_point(int row, int column);

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
    
    // TODO: Stage 1.1 - Scan in lives, money and start/ending points, then
    // print out the map!
    int lives;
    printf("Starting Lives: ");
    scanf("%d", &lives);
    int money;
    printf("Starting Money($): ");
    scanf("%d", &money);
    struct coord start;
    printf("Start Point: ");
    scanf("%d %d", &start.row, &start.col);
    struct coord end;
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
    
    // Takes user input and adds lake
    enter_lake(map);
    print_map(map, lives, money);
    
    // Creates array of struct the size of map to store path in.
    // Path is then created and returns size of path for later use.
    struct move_object path[POTENTIAL_PATH_SIZE];
    int path_size = enter_path(map, start, path);
    print_map(map, lives, money);
    
    // Gets command until end of game (ctrl + D is inputted or no more lives)
    get_command(map, money, lives, path_size, start, path);
    return 0;
}


////////////////////////////////////////////////////////////////////////////////
/////////////////////////////  YOUR FUNCTIONS //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// TODO: Put your functions here

/**
 * @brief Continuously gets command from user until user has no more lives or inputs
 *          CTRL + D
 * 
 * @param map       - the map which will display enemies, towers, paths and more
 * @param money     - the amount of money which the user has starts off with
 * @param lives     - the amount of lives which the user starts off with
 * @param path_size - an integer depicting the amount of path tiles originally given by user
 * @param start     - a struct containing coordinates of START tile
 * @param path      - an array of structs containing coordinates of 
 */
void get_command(struct tile map[MAP_ROWS][MAP_COLUMNS], int money, int lives, 
        int path_size, struct coord start, 
        struct move_object path[POTENTIAL_PATH_SIZE] ) {
    char command;
    int lives_lost = 0;
    
    printf("Enter Command: ");
    int valid = scanf(" %c", &command);
    
    while (valid == 1) {
        if (command == 'e') {
            spawn_enemies(map, start);
        } else if (command == 't') {
            // places towers and returns new money sum
            money = place_towers(map, money);
        } else if (command == 'm') {
            // moves enemies and returns amount of lives lost in that move
            lives_lost = move_enemies(map, path_size, path);
            lives -= lives_lost;
            printf("%d enemies reached the end!\n", lives_lost);
        } else if (command == 'u') {
            // returns new money sum after upgrading
            money = upgrade_tower(map, money);
        } else if (command == 'a') {
            // returns new money sum after killing enemies
            money = search_enemies_to_attack(map, money, path_size, path);
        } else if (command == 'r') {
            enter_rain(map);
        } else if (command == 'f') {
            int repetitions;
            scanf(" %d", &repetitions);
            for (int i = 0; i < repetitions; i++) {
                create_flood(map);
            }
        } else if (command == 'c') {
            create_teleporter(map, path, path_size);
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
}
/**
 * @brief Takes user coordinates along with height and width of desired lake and
 *          prints that part of the map into WATER tiles if valid
 * 
 * @param map 
 * @return Nothing
 */
void enter_lake(struct tile map[MAP_ROWS][MAP_COLUMNS]) {
    int lake_row;
    int lake_col; 
    int height;
    int width;
    int row = 0; 
    int col = 0; 
    
    printf("Enter Lake: ");
    scanf("%d %d %d %d", &lake_row, &lake_col, &height, &width);
    
    if (!valid_point(lake_row + height - 1, lake_col + width - 1) || 
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
/**
 * @brief Takes user input and creates a path on the map and stores coordinates
 *          of each path tile in a separate array for later use
 * 
 * @param map   - the map where the path will be displayed
 * @param start - a struct containing coordinates of the START tile
 * @param path  - an array of struct where the coordinates of each path tile
 *          will be stored for later use
 * @return Integer of amount of path tiles  
 */
int enter_path(struct tile map[MAP_ROWS][MAP_COLUMNS], struct coord start, 
        struct move_object path[POTENTIAL_PATH_SIZE]) {
    printf("Enter Path: ");
    int row = start.row; 
    int col = start.col;
    char direction;
    int valid_direction = scanf(" %c", &direction);
    int path_size = 0;

    path[path_size].row = row;
    path[path_size].col = col;

    while (valid_direction == 1) {

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
            path[path_size].row = row;
            path[path_size].col = col;
            path[path_size].exists = 1;
        }

        if (direction != '\n') {
            valid_direction = scanf("%c", &direction);
        } else {
            valid_direction = 0;
        }
    }
    return path_size;
}

/**
 * @brief Takes user input and prints out n extra enemies at spawn
 * 
 * @param map   - the map where the enemies will be displayed
 * @param start - a struct containing the coordinates for the START tile
 * @return Nothing
 */
void spawn_enemies(struct tile map[MAP_ROWS][MAP_COLUMNS], struct coord start) {
    int enemies;
    scanf(" %d", &enemies);
    
    if (enemies > 0) {
        map[start.row][start.col].entity = ENEMY;
        map[start.row][start.col].n_enemies += enemies;
    }
}

/**
 * @brief Places towers at specified coordinates if valid and
 *          calculates new money amount for placing tower
 * 
 * @param map   - the map where towers are displayed
 * @param money - the amount of money currently owned
 * @return Integer of new money amount after placing tower
 */
int place_towers(struct tile map[MAP_ROWS][MAP_COLUMNS], int money) {
    int row;
    int col;
    scanf("%d %d", &row, &col);
    
    if (!valid_point(row, col)) {
        print_tower_error();
    } else if (map[row][col].entity == EMPTY &&
                map[row][col].land == GRASS && money >= 200) {
        map[row][col].entity = BASIC_TOWER;
        printf("Tower successfully created!\n");
        return money - 200;
    } else {
        print_tower_error();
    }
    return money;
}

/**
 * @brief Prints error message for an unsuccessful tower placement
 * 
 * @return Nothing
 */
void print_tower_error(void) {
    printf("Error: Tower creation unsuccessful. "
            "Make sure you have at least $200 and that the tower is "
            "placed on a grass block with no entity.\n");
}
/**
 * @brief moves enemies n tiles along path by first finding enemies, then
 *          storing their new location in a different array before using
 *          that array to print on map
 * 
 * @param map       - the map where the enemies and path are displayed
 * @param path_size - the number of path tiles originally 
 * @param path      - the array of structs containing coordinates of patht tiles
 * @return Integer of number of lives lost after moving enemies 
 */
int move_enemies(struct tile map[MAP_ROWS][MAP_COLUMNS], int path_size,
        struct move_object path[POTENTIAL_PATH_SIZE]) {
    int moves;
    int lives_lost = 0;
    int path_counter = 0;
    struct move_object move_to[path_size];

    scanf(" %d", &moves);
    // loops through path and identifies if there is enemy or not
    while (path_counter < path_size) {
        int current_move = 0;
        int teleport = 0;
        int move_counter = path_counter + current_move + teleport;
        int row = path[move_counter].row;
        int col = path[move_counter].col;
        // checks if enemy on path tile and changes tile state if there is
        if (map[row][col].entity == ENEMY) {
            move_to[path_counter].exists = 1;
            move_to[path_counter].n_enemies = map[row][col].n_enemies;
            map[row][col].n_enemies = 0;
            map[row][col].entity = EMPTY;
        } else {
            move_to[path_counter].exists = 0;
        }

        // If there is an enemy, projects location of enemies along path     
        // and stores in the array move_to[] after moving unless it reaches end
        while (current_move < moves && 
                move_counter < path_size - 1 &&
                move_to[path_counter].exists == 1) {
                 
            if (map[row][col].land == TELEPORTER) {
                teleport = teleporting(map, path, teleport, move_counter);
            }
            move_counter = path_counter + current_move + teleport;
            
            if (move_counter >= path_size - 2) {
                lives_lost += move_to[path_counter].n_enemies;
                move_to[path_counter].exists = 0;
            }  
            current_move++;
        }
        move_counter = path_counter + current_move + teleport;
        move_to[path_counter].row = path[move_counter].row;  
        move_to[path_counter].col = path[move_counter].col;      
        path_counter++;
    } 
    // reassigns new location for enemy on map (except for end)
    relocate_enemies(map, move_to, path_size);
    return lives_lost;
}

/**
 * @brief reassigns new location of enemies onto map after moving
 * 
 * @param map       - the map where enemies and path will be displayed
 * @param move_to   - the array of structs containing coordinates of enemies 
 *          still on path after moving
 * @param path_size - an integer depicting the number of path tiles originally
 * @return Nothing
 */
// reassigns new location of enemies onto map after moving
void relocate_enemies(struct tile map[MAP_ROWS][MAP_COLUMNS],
        struct move_object move_to[], int path_size) {
    int row = 0;
    int col = 0;
    int counter = 0;

    while (counter < path_size) {
        if (move_to[counter].exists == 1) {
            row = move_to[counter].row;
            col = move_to[counter].col;

            map[row][col].n_enemies = move_to[counter].n_enemies;
            map[row][col].entity = ENEMY;

            move_to[counter].n_enemies = 0;
            move_to[counter].exists = 0;
        }
        counter++;
    }
}
/**
 * @brief moves enemies on map from one teleporter to the other
 * 
 * @param map             - the map where enemies are moving across
 * @param path            - the array of structs storing original path tile 
 *          coordinates
 * @param teleport_amount - the amount of tiles enemies must move along the path 
 *              to be equivalent to teleporting from one teleporter to the other
 * @param counter         - the index of the path array depicting where the 
 *          first teleporter was
 * @return Integer of how many tiles travelled in original path when teleporting 
 */
int teleporting(struct tile map[MAP_ROWS][MAP_COLUMNS], 
        struct move_object path[POTENTIAL_PATH_SIZE], int teleport_amount, 
        int counter) {
    teleport_amount++;

    while (path[counter + teleport_amount].exists == 0) {
        teleport_amount++;
    }
    teleport_amount--;
    return teleport_amount;
}

/**
 * @brief Progressively transforms tower entity into another at a cost
 * 
 * @param map   - the map where towers are altered
 * @param money - the amount of money the user has which is a determinant in 
            whether a tower can be upgraded
 * @return Integer of new money amount after upgrade
 */
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

/**
 * @brief searches path for enemies to be attacked and calculates money gained
 *          by comparing the difference in enemy amount at a specific path tile
 *          before and after an attack and multiplies it by 5. It is then added 
 *          on to existing money amount and returned for new printed value
 * 
 * @param map       - the map which displays enemies and towers 
 * @param money     - the amount of money the user had before executing command
 * @param path_size - integer depicting number of valid paths in path array
 * @param path      - array of structs containing coordinates of path tiles
 * @return New amount of money after attack in the form of an integer
 */
int search_enemies_to_attack(struct tile map[MAP_ROWS][MAP_COLUMNS], int money, 
        int path_size, struct move_object path[POTENTIAL_PATH_SIZE]) {
    int attacks;
    scanf(" %d", &attacks);
    int enemies_destroyed = 0;
    // loops through path and searches for enemies
    for (int i = 0; i < path_size; i++) { 
        if (map[path[i].row][path[i].col].entity == ENEMY) {
            int enemy_holder = map[path[i].row][path[i].col].n_enemies;
            search_towers_in_range(map, path, attacks, i);
            int current_enemy = map[path[i].row][path[i].col].n_enemies;
            enemies_destroyed += enemy_holder - current_enemy;
            
            if (map[path[i].row][path[i].col].n_enemies < 1) {
                map[path[i].row][path[i].col].entity = EMPTY;
            }
            // corrects for having negative enemies after attack
            while (map[path[i].row][path[i].col].n_enemies < 0) {
                map[path[i].row][path[i].col].n_enemies++;
                enemies_destroyed--;
            }          
        }
    }
    printf("%d enemies destroyed!\n", enemies_destroyed);
    money += enemies_destroyed * 5;
    return money;
}


/**
 * @brief Will search for towers in range of the enemy and attack enemy 
 *          
 * @param map      - the map which displayes enemies and towers
 * @param path     - array of structs which contains coordinates of path tiles, 
 *          used to 
 * @param attacks  - integer depicting how many times user wants to attack
 * @param position - integer depicting which path tile it is searching from in 
 *          path array
 * @return Nothing
 */
void search_towers_in_range(struct tile map[MAP_ROWS][MAP_COLUMNS], 
        struct move_object path[POTENTIAL_PATH_SIZE], int attacks, 
        int position) {
    struct coord search_position;
    // searches from top-left potential range of hitting enemy
    search_position.row = path[position].row - 2;
    search_position.col = path[position].col - 2;
    
    // corrects for out of bounds above and to the left of enemy
    while (!valid_point(search_position.row, path[position].col)) {
        search_position.row++;
    }
    
    int valid_col = search_position.col;

    while (!valid_point(path[position].row, valid_col)) {
        valid_col++;
    }
    // searches row and columns until out of range or out of bounds 
    // to the right and below enemy
    while (search_position.row < path[position].row + 3 &&
            valid_point(search_position.row, path[position].col)) {
        search_position.col = valid_col;
        while (search_position.col < path[position].col + 3 && 
                valid_point(path[position].row, search_position.col)) {  
            attack(map, attacks, search_position, path, position);     
            search_position.col++;
        }   
        search_position.row++;
    }
}

/**
 * @brief attacks enemies if searched tile is a tower and 
 *          enemy in range of specific tower type 
 * 
 * @param map             - the map which displays towers and enemies
 * @param attacks         - the number of times user wants to attack enemies
 * @param search_position - struct containing coordinates of tile being searched
 * @param path            - array of structs containing path where enemies are
 * @param position        - integer depicting which path tile is being attacked 
 *                          in array
 * @return Nothing
 */
void attack(struct tile map[MAP_ROWS][MAP_COLUMNS], int attacks, 
        struct coord search_position, 
        struct move_object path[POTENTIAL_PATH_SIZE], int position) {
    int row = search_position.row;
    int col = search_position.col;
    int enemy_row = path[position].row;
    int enemy_col = path[position].col;
    
    if (map[row][col].entity == FORTIFIED_TOWER) {
        map[enemy_row][enemy_col].n_enemies -= 3 * attacks;
    } 
    
    if ((col >= enemy_col - 1 && col <= enemy_col + 1) && 
            (row >= enemy_row - 1 && row <= enemy_row + 1)) {
        if (map[row][col].entity == BASIC_TOWER) {
            map[enemy_row][enemy_col].n_enemies -= 1 * attacks;
        } else if (map[row][col].entity == POWER_TOWER) {
            map[enemy_row][enemy_col].n_enemies -= 2 * attacks;
        }
    }
}

/**
 * @brief Takes user input for spacing and offset which will print
 *          WATER tiles onto the map originally from (0,0) but shifted
 *          by offset and for every nth tile depicted by spacing. 
 *          (there will be different spacing and offsets for rows and columns)
 *
 * @param map - the map where rain will occur
 * @return Nothing
 */
void enter_rain(struct tile map[MAP_ROWS][MAP_COLUMNS]) {
    struct coord spacing;
    int row_offset;
    int col_offset;

    scanf(" %d %d %d %d", &spacing.row, &spacing.col, &row_offset, &col_offset);
    
    struct coord rain;
    struct coord offset;
    
    rain.row = 0;
    rain.col = 0;
    // Loops through length of map row and column, 
    // but prints out by offset and spacing
    while (rain.row < MAP_ROWS) {
        offset.row = rain.row - (row_offset % spacing.row);
        rain.col = 0;
        while (rain.col < MAP_COLUMNS) {
            offset.col = rain.col - (col_offset % spacing.col);
            change_to_rain(map, spacing, offset, rain);
            rain.col++;
        }
        rain.row++;
    }
}

/**
 * @brief Changes tiles from GRASS to WATER if coordinates align with 
 *         predicted WATER tiles after shifting by offset and with correct 
 *         spacing. Entity will be changed to EMPTY if tower is not 
 *         FORTIFIED_TOWER
 *
 * @param map     - the map where rain will occur
 * @param spacing - struct depicting the space between successive created WATER 
 *          tiles for both row and columns
 * @param offset  - struct depicting the amount of tiles the rain will be
 *          shifted from (0,0) for both row and columns
 * @param rain    - struct containing coordinates of current tile being 
 *          converted to WATER
 * @return Nothings
 */
void change_to_rain(struct tile map[MAP_ROWS][MAP_COLUMNS], 
        struct coord spacing, struct coord offset, struct coord rain) {
    int row = rain.row;
    int col = rain.col;

    if ((offset.col % spacing.col == 0 &&
            offset.row % spacing.row == 0) &&
            map[row][col].land == GRASS) {
        map[row][col].land = WATER;
        int entity = map[row][col].entity;

        if (entity == BASIC_TOWER || entity == POWER_TOWER) {
            map[row][col].entity = EMPTY;
        }
    }
}

/**
 * @brief Will store previous water tiles in an array and then flood the map,
 *         converting GRASS tiles adjacent to previous WATER tiles into WATER 
 *         tiles
 *
 * @param map - the map where WATER tiles will be created
 * @return Nothing
 */

void create_flood(struct tile map[MAP_ROWS][MAP_COLUMNS]) {
    struct coord water[POTENTIAL_PATH_SIZE];
    int row = 0;
    int col = 0;
    int water_tile_count = 0;
    // Checks previous state of map and stores WATER tiles 
    //coordinates into water array
    while (row < MAP_ROWS) {
        col = 0;
        while (col < MAP_COLUMNS) {
            if (map[row][col].land == WATER) {
                water[water_tile_count].row = row;
                water[water_tile_count].col = col;
                water_tile_count++;
            }
            col++;
        }
        row++;
    }
    int counter = 0;
    // prints out WATER tiles adjacent to WATER tiles in water array
    while (counter < water_tile_count) {
        row = water[counter].row;
        col = water[counter].col;
        
        flood_surroundings(map, row - 1, col);
        flood_surroundings(map, row + 1, col);
        flood_surroundings(map, row, col - 1);
        flood_surroundings(map, row, col + 1);
        
        counter++;
    }
}

/**
 * @brief Converts tile to WATER tile if within map and is GRASS tile.
 *          Will also make enitity EMPTY if entity is not FORTIFIED_TOWER
 * 
 * @param map - the map to place water tiles on
 * @param row - the y-axis to place water tile
 * @param col - the x-axis to place water tile
 * @return Nothing
 */
void flood_surroundings(struct tile map[MAP_ROWS][MAP_COLUMNS], int row, 
        int col) {
    if (valid_point(row, col)) {
        if (map[row][col].land == GRASS) {
            map[row][col].land = WATER;
            int entity = map[row][col].entity;

            if (entity != FORTIFIED_TOWER) {
                map[row][col].entity = EMPTY;
            }
        }
    }
}


/**
 * @brief Places teleporter on given coordinates if on path and removes path 
 *          from map in between those teleporters (including other teleporters)
 * @param map       - the map to place teleporters on
 * @param path      - the array containing coordinates of path tiles
 * @param path_size - the integer containing amount of path tiles originally
 * @return Nothing
 */

void create_teleporter(struct tile map[MAP_ROWS][MAP_COLUMNS], 
        struct move_object path[POTENTIAL_PATH_SIZE], int path_size) {
    struct coord teleporter1;
    struct coord teleporter2;
    scanf("%d %d %d %d", &teleporter1.row, &teleporter1.col, 
                        &teleporter2.row, &teleporter2.col);
    int counter = 0;
    int delete_path = -1;
    int on_path = 0;
    // checks if both teleporters are on path
    while (counter < path_size - 1) {
        if (teleporter_on_path(path, teleporter1, teleporter2, counter)) {
            on_path++;
        }
        counter++;
    }

    counter = 0;

    if (on_path != 2 || (!valid_point(teleporter1.row, teleporter1.col) || 
            !valid_point(teleporter2.row, teleporter2.col))) {
        printf("Error: Teleporters can only be created on path tiles.\n");
    } else {
        while (counter < path_size) {
            // if teleporter found, skip over first instance of teleporter (not 
            // other one) and begin to remove path between teleporters from map
            if (teleporter_on_path(path, teleporter1, teleporter2, counter)) {
                map[path[counter].row][path[counter].col].land = TELEPORTER;
                delete_path *= -1;
                counter += (delete_path == 1);
            }
            
            if (delete_path == 1) {
                map[path[counter].row][path[counter].col].land = GRASS;
                map[path[counter].row][path[counter].col].entity = EMPTY;
                path[counter].exists = 0;
            }
            counter++;
        }        
    }
}
/**
 * @brief Checks if the teleporter point is on a certain path tile
 * 
 * @param path        - the array holding path coordinates to check
 * @param teleporter1 - the struct holding coordinates of teleporter1
 * @param teleporter2 - the struct holding coordinates of teleporter2
 * @param counter     - the index depicting which path tile is being compared
 * @return an integer of 0 or 1 depicting whether on path or not
 */
int teleporter_on_path(struct move_object path[POTENTIAL_PATH_SIZE], 
        struct coord teleporter1, struct coord teleporter2, int counter) {
    return ((teleporter1.row == path[counter].row && 
            teleporter1.col == path[counter].col) || 
            (teleporter2.row == path[counter].row && 
            teleporter2.col == path[counter].col));
}

/**
 * @brief Checks whether a point is within the map
 * 
 * @param row    - the point's y-coordinate
 * @param column - the point's x-coordinate
 * @return Integer of 0 or 1 depicting False and True respectively 
 */
int valid_point(int row, int column) {
    return !(row < 0 || row >= MAP_ROWS || column >= MAP_COLUMNS || column < 0);
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
 *     tile       - The tile to print the land/entity from
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