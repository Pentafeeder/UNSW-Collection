// cs_cs 
//
// This program was written by Kevin Le (z5481482)
// on [07/04/2023]
//
// Allows user to create a system of trains and carriages and edit them


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

////////////////////////////////////////////////////////////////////////////////
///////////////////////////      Contants       ////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// Provided constants
#define ID_SIZE 6

// Provided enums
enum carriage_type {INVALID_TYPE, PASSENGER, BUFFET, RESTROOM, FIRST_CLASS};

// TODO: Your #defines/enums can go here:
#define TRUE 1
#define FALSE 0
#define REMOVE_PASSENGERS 'd'
#define SEAT_PASSENGERS 's'
#define MOVE_PASSENGERS 'm'
#define SPLIT_TRAIN 'S'
#define MERGE_TRAIN 'M'
#define COUNT_TOTAL 'T'
#define IDENTICAL_STRING 0
////////////////////////////////////////////////////////////////////////////////
/////////////////////////// USER DEFINED TYPES  ////////////////////////////////
////////////////////////////////////////////////////////////////////////////////



// A Train Carriage
struct carriage {
    // carriage id in the form #"N1002", unique, null terminated
    char carriage_id[ID_SIZE];
    //  Type of the carriage
    enum carriage_type type;
    // Maximum number of passengers 
    int capacity;
    // Current number of passengers
    int occupancy;

    struct carriage *next;
};

// TODO: Any additional structs you want to add can go here:
struct train {
    struct carriage *carriages;
    struct train *next;
};

struct count_details {
    int capacity;
    int occupancy;
    int carriage_amount;
    int wrong_order;
};

struct carriage_range {
    struct carriage *move_from;
    struct carriage *move_to;
};

struct head_train {
    struct train *head;
};

struct train_details {
    struct carriage *previous_carriage;
    struct carriage *current_carriage;
    struct train *current_train;
};
////////////////////////////////////////////////////////////////////////////////
////////////////////// PROVIDED FUNCTION PROTOTYPE  ////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void print_usage(void);
void print_carriage(struct carriage *carriage);
void scan_id(char id_buffer[ID_SIZE]);
enum carriage_type scan_type(void);
void print_train_summary(
    int is_selected, 
    int n, 
    int capacity, 
    int occupancy,
    int num_carriages
);
int compare_double(double n1, double n2);

// Additional provided function prototypes
// You won't need to use these functions!
// We use just them to implement some of the provided helper functions.
int scan_token(char *buffer, int buffer_size);
char *type_to_string(enum carriage_type type);
enum carriage_type string_to_type(char *type_str);

////////////////////////////////////////////////////////////////////////////////
////////////////////////  YOUR FUNCTION PROTOTYPE  /////////////////////////////
////////////////////////////////////////////////////////////////////////////////
struct carriage *create_carriage(
    char id[ID_SIZE], 
    enum carriage_type type,
    int capacity
);
// TODO: Put your function prototypes here
void append_command(struct train *train);
void append_carriage(char id[ID_SIZE], 
        enum carriage_type type, 
        int capacity, 
        struct train *train);
void print_train(struct train *train);
void insert_command(struct train *train);
void insert_carriage(char id[ID_SIZE],
        enum carriage_type type, 
        int capacity,
        int position, 
        struct train *train);
void seat_or_remove_command(struct train *train, 
        char command);
struct count_details count_total_passengers(struct train *train, 
        char command);
void count_passengers_in_range(struct train *train, 
        char command);
struct carriage *find_passenger_carriage(struct train *train,
        char id[ID_SIZE], 
        char command);
int check_carriage(char id[ID_SIZE], 
        enum carriage_type type, 
        int capacity, 
        struct train *train);
void seat_passengers(struct carriage_range carriage, 
        int passengers, 
        char command);
int check_before_moving(struct train *train, 
        char command, 
        int passengers, 
        char id[ID_SIZE]);
struct count_details count_passengers(struct carriage_range carriage);
void move_passengers_command(struct train *train, 
        char command);
int check_available_space(struct carriage *destination_carriage, 
        int num_move);
void create_train(struct head_train *head_train, 
        struct train *selected);
struct train *select_forward_train(struct train *selected);
struct train *select_backward_train(struct head_train *head_train,
        struct train *selected);
void print_train_list(struct head_train *head_train, 
        struct train *selected,
        char command);
void remove_carriage_command(struct train *selected, 
        char command);
void remove_carriage(struct train *selected, 
        struct carriage *carriage);
struct train *remove_train(struct head_train *head_train, 
        struct train *selected);
void clear_memory(struct head_train *head_train);
void merge_trains(struct train *selected);
int check_positive_int(int num);
void split_trains_command(struct train *selected, 
    char command);
void search_train_to_split(struct train *selected,
        char (*carriage_ids) [] [ID_SIZE],
        int row);
struct train_details *split_train(struct carriage *current_carriage,
        struct carriage *previous_carriage,
        struct train *current_train,
        char id[ID_SIZE], 
        char (*carriage_ids) [] [ID_SIZE],
        int row,
        int current_row,
        int deleted);
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

int main(void) {
    printf("Welcome to Carriage Simulator\nAll aboard!\nEnter command: ");

    struct head_train *head_train = malloc(sizeof(struct head_train));
    head_train->head = malloc(sizeof(struct train));
    head_train->head->carriages = NULL;
    head_train->head->next = NULL;
    struct train *selected = head_train->head;

    char command;
    while (scanf(" %c", &command) == 1) {
        if (command == '?') {
            print_usage();
        } else if (command == 'a') {
            append_command(selected);
        } else if (command == 'p') {
            print_train(selected);
        } else if (command == 'i') {
            insert_command(selected);
        } else if (command == 's' || command == 'd') {
            seat_or_remove_command(selected, command);
        } else if (command == 'T') {
            count_total_passengers(selected, command);
        } else if (command == 'c') {
            count_passengers_in_range(selected, command);
        } else if (command == 'm') {
            move_passengers_command(selected, command);
        } else if (command == 'N') {
            create_train(head_train, selected);
        } else if (command == '>') {
            selected = select_forward_train(selected);
        } else if (command == '<') {
            selected = select_backward_train(head_train, selected);
        } else if (command == 'P') {
            print_train_list(head_train, selected, command);
        } else if (command == 'r') {
            remove_carriage_command(selected, command);
        } else if (command == 'R') {
            selected = remove_train(head_train, selected);
        } else if (command == 'M') {
            if (selected->next != NULL) {
                merge_trains(selected);
            }
        } else if (command == 'S') {
            split_trains_command(selected, command);
        }
        printf("Enter command: ");
    }   
    clear_memory(head_train);
    return 0;
}

////////////////////////////////////////////////////////////////////////////////
/////////////////////////////  YOUR FUNCTIONS //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


// Allocates memory to create a linked list node of struct carriage, assigning 
// its type, capacity, occupancy, id string and a NULL pointer as its next node 
// 
// Parameters:
//      id      - a char array of length ID_SIZE, which contains the id of the new
//                carriage
//      type    - an carriage_type enum, which contains the carriage type for the
//                new carriage
//      capacity - an integer denoting max amount of passengers the train can hold 
// Returns:
//      A carriage struct with properties of the new carriage
//
struct carriage *create_carriage(
    char id[ID_SIZE], 
    enum carriage_type type,
    int capacity
) {
    struct carriage *new_carriage = malloc(sizeof(struct carriage));
    new_carriage->type = type;
    new_carriage->capacity = capacity;
    new_carriage->occupancy = 0;
    new_carriage->next = NULL;
    
    for (int i = 0; i < ID_SIZE; i++) {        
        new_carriage->carriage_id[i] = id[i];
    }

    return new_carriage; 
}

/**
 * @brief Takes in input from user to get ready to append carriage onto train
 * 
 * @param train - The selected train struct where the carriage will be added
 * @return Nothing 
 */
void append_command(struct train *train) {
    char id[ID_SIZE];
    enum carriage_type type;
    int capacity;
    
    scan_id(id);
    type = scan_type();    
    scanf(" %d", &capacity);

    int valid = check_carriage(id, type, capacity, train);
    if (valid == TRUE) {
        append_carriage(id, type, capacity, train);
        printf("Carriage: \'%s\' attached!\n", id);

    }
}

/**
 * @brief Will loop to end of linked list of carriages and add a new carriage 
 * 
 * @param id       - an array of char with length of ID_SIZE which serves as the carriage's identity
 * @param type     - an enum of carriage_type which indicates the carriage's type
 * @param capacity - an integer denoting max amount of passengers the carriage can hold
 * @param train    - the selected train struct where carriage will be appended
 * @return Nothing
 */
void append_carriage(char id[ID_SIZE], 
        enum carriage_type type,
        int capacity, 
        struct train *train
) {
    struct carriage *new_carriage = create_carriage(id, type, capacity);
    struct carriage *carriage = train->carriages;
    
    if (carriage == NULL) {
        train->carriages = new_carriage;
    } else {
        while (carriage->next != NULL) {
            carriage = carriage->next;
        }
        carriage->next = new_carriage;
    }
}

/**
 * @brief Will print the list of carriages within a train struct
 * 
 * @param train - a train struct which contains the list of carriages to be printed
 * @return Nothing
 */
void print_train(struct train *train) {
    struct carriage *carriage = train->carriages;
    
    if (carriage == NULL || train == NULL) {
        printf("This train is empty!\n");
    } else {
        while (carriage != NULL) {
            print_carriage(carriage);
            carriage = carriage->next;
        }
    }
}

/**
 * @brief Checks whether an inputted carriage is valid
 * 
 * @param id       - a char array of size 6 containing carriage id
 * @param type     - a carriage_type enum denoting type of carriage
 * @param capacity - an integer denoting max amount of passengers the carriage can hold
 * @param train    - the train struct containing the carriage;
 * @return integer of 0 or 1 corresponding to FALSE and TRUE
 */
int check_carriage(char id[ID_SIZE], 
        enum carriage_type type, 
        int capacity, 
        struct train *train
) {    
    int valid = TRUE;
    
    if (type == INVALID_TYPE) {
        printf("ERROR: Invalid carriage type\n");
        valid = FALSE;
    } else if (capacity <= 0 || capacity > 999) {
        printf("ERROR: Capacity should be between 1 and 999\n");
        valid = FALSE;
    } else {
        struct carriage *check_carriage = train->carriages;
        
        while (check_carriage != NULL && valid == TRUE) {
            if (strcmp(id, check_carriage->carriage_id) == IDENTICAL_STRING) {
                printf("ERROR: a carriage with id: \'%s\' "
                        "already exists in this train\n", id);
                valid = FALSE;
            }
            
            check_carriage = check_carriage->next;
        }
    }
    return valid;
}

/**
 * @brief Takes user input and gets ready to insert carriage into train
 * 
 * @param train - the train struct where carriage will be inserted.
 * @return Nothing
 */
void insert_command(struct train *train) {
    int position;
    char id[ID_SIZE];
    enum carriage_type type;
    int capacity;

    scanf(" %d", &position);
    scan_id(id);
    type = scan_type();
    scanf(" %d", &capacity);
    
    int valid = TRUE;
    
    if (position < 0) {
        printf("ERROR: n must be at least 0\n");
        valid = FALSE;
    } else {
        valid = check_carriage(id, type, capacity, train);
    }
    
    if (valid == TRUE) {
        insert_carriage(id, type, capacity, position, train);
    }
}

/**
 * @brief Loops through carriage list of train and inserts train at desired index
 * 
 * @param id       - a char array of length ID_SIZE containing carriage id
 * @param type     - an carriage_type enum denoting carriage type
 * @param capacity - an integer denoting max amount of passengers the carriage can hold
 * @param position - an integer denoting desired position of inserted carriage starting from 0
 * @param train    - the train struct where carriages will be inserted
 * @return Nothing
 */
void insert_carriage(char id[ID_SIZE],
        enum carriage_type type, 
        int capacity,
        int position,
        struct train *train
) {
    struct carriage *new_carriage = create_carriage(id, type, capacity);
    struct carriage *current = train->carriages;
    if (position == 0 || current == NULL) {
        new_carriage->next = current;
        train->carriages = new_carriage;
    } else {
        int index = 0;
        // Loops until just before intended position
        while (current->next != NULL && index < position - 1) {
            current = current->next;
            index++;
        }
        
        new_carriage->next = current->next;
        current->next = new_carriage;
    }   
    printf("Carriage: \'%s\' inserted!\n", id);     
}

/**
 * @brief Adds passengers onto carriage and prints appropriate message depending
 *        on command
 * 
 * @param carriage   - a carriage_range struct containing the carriages in which 
 *                     to seat new passengers or move passengers from and to
 * @param passengers - the number of passengers to be seated 
 * @param command    - a char containing the command that was inputted
 * @return Nothing
 */
void seat_passengers(struct carriage_range carriage, 
        int passengers, 
        char command
) {
    struct carriage *current = carriage.move_to;
    
    while (passengers > 0 && current != NULL) {
        int available_seats = current->capacity - current->occupancy;
        int passengers_seated;
        
        if (available_seats >= passengers) {
            current->occupancy += passengers;
            passengers = 0;
        } else {
            current->occupancy = current->capacity;
            passengers -= available_seats;
        }
        
        passengers_seated = available_seats - current->capacity + 
                                current->occupancy;
        
        if (passengers_seated > 0 && command == SEAT_PASSENGERS) {
            printf("%d passengers added to %s\n", 
                    passengers_seated, current->carriage_id);
        } else if (passengers_seated > 0 && command == MOVE_PASSENGERS) {
            printf("%d passengers moved from %s to %s\n", passengers_seated,
                    (carriage.move_from)->carriage_id, current->carriage_id);
        }
        
        current = current->next;
    } 
    
    if (passengers > 0 && command == SEAT_PASSENGERS) {
        printf("%d passengers could not be seated\n", passengers);
    } 
}

/**
 * @brief Loops through carriage list to find carriage specified carriage and prints 
 *        if it does not exist
 * 
 * @param train   - a train struct containing the carriages which are being searched.
 * @param id      - a char array of length ID_SIZE containing the id of carriage being searched for.
 * @param command - a char denoting command to provide context of how this function is being used.
 *                  Will change its output depending on command.
 * @return A struct carriage pointer containing carriage if it exists or NULL if it doesn't
 */
struct carriage *find_passenger_carriage(struct train *train, 
        char id[ID_SIZE], 
        char command
) {
    struct carriage *carriage = train->carriages;

    if (carriage != NULL) {
        while (strcmp(carriage->carriage_id, id) != IDENTICAL_STRING && 
                carriage->next != NULL) {
            carriage = carriage->next;
        }  
        if (carriage->next == NULL && 
                strcmp(carriage->carriage_id, id) != IDENTICAL_STRING) {
            carriage = carriage->next;
        }
    }
    
    if (carriage == NULL && command != SPLIT_TRAIN && command != MERGE_TRAIN) {
        printf("ERROR: No carriage exists with id: \'%s\'\n", id);
    }
    return carriage;
}

/**
 * @brief Gets input to either remove or seat passengers and prints appropriate message
 * 
 * @param train   - a train struct containing the carriages where passengers will be removed/seated
 * @param command - char denoting whether function is used to remove or seat passengers
 * @return Nothing
 */
void seat_or_remove_command(struct train *train, char command) {
    char id[ID_SIZE];
    int passengers;

    scan_id(id);
    scanf(" %d", &passengers);
 
    int valid = check_before_moving(train, command, passengers, id);
    struct carriage *carriage = NULL;
    
    if (valid == TRUE && command == REMOVE_PASSENGERS) {
        carriage = find_passenger_carriage(train, id, command);
        carriage->occupancy -= passengers;
        printf("%d passengers removed from %s\n", passengers, 
                carriage->carriage_id);
    } else if (valid == TRUE && command == SEAT_PASSENGERS) {
        carriage = find_passenger_carriage(train, id, command);
        struct carriage_range range;
        range.move_to = carriage;
        seat_passengers(range, passengers, command);
    }
    
}

/**
 * @brief checks whether conditions for removing/seating passengers are valid 
 * 
 * @param train      - a train struct containing carriages to be checked 
 * @param command    - a char denoting context to use this function
 * @param passengers - an integer containing amount of passengers to remove/seat
 * @param id         - a char array of length SIZE_ID containing
 * @return integer of 1 or 0 denoting whether it is valid or not 
 */
int check_before_moving(struct train *train, 
        char command, 
        int passengers, 
        char id[ID_SIZE]
) {
    int valid = FALSE;
    
    if (check_positive_int(passengers) == TRUE) {
        struct carriage *carriage = find_passenger_carriage(train, id, command);
        if (carriage == NULL) {}
        else if (passengers > carriage->occupancy && 
                command == REMOVE_PASSENGERS) {
            printf("ERROR: Cannot remove %d passengers from %s\n", 
                    passengers, carriage->carriage_id);
        } else {
            valid = TRUE;
        }
    } 
    return valid;
}

/**
 * @brief Checks whether a given integer is a positive integer
 * 
 * @param num - an int which will be checked
 * @return Integer of 1 or 0 denoting whether it is a positive integer or not
 */
int check_positive_int(int num) {
    int valid = TRUE;
    if (num <= 0) {
        printf("ERROR: n must be a positive integer\n");
        valid = FALSE;
    }
    return valid;
}

/**
 * @brief Counts total number of passengers currently on the train, the total
 *        capacity of the train, and the number of carriages in the train
 * 
 * @param train   - a train struct where its occupancy, capacity, and number of carriages
 *                  will be counted
 * @param command - a char denoting how the function will be used
 * @return A count_details struct containing details of its count (occupancy, capacity, carriage amount) 
 */
struct count_details count_total_passengers(struct train *train, char command) {
    struct count_details total;
    total.occupancy = 0;
    total.capacity = 0;
    total.carriage_amount = 0;
    
    if (train->carriages != NULL) {
        struct carriage_range range;
        range.move_from = train->carriages;
        range.move_to = NULL;
        total = count_passengers(range);
    }
    
    if (command == COUNT_TOTAL) {
        printf("Total occupancy: %d\n", total.occupancy);
        printf("Unoccupied capacity: %d\n", total.capacity - total.occupancy);
    }
    return total;
}

/**
 * @brief Counts total number of occupied seats and capacity between two given 
 *        carriages and displays appropriate message if valid or invalid ranges
 * 
 * @param train   - a train struct where carriages will be counted 
 * @param command - a char denoting context of how finding_passenger_carriage() will
 *                  perform
 * @return Nothing
 */
void count_passengers_in_range(struct train *train, char command) {
    char start_id[ID_SIZE];
    char end_id[ID_SIZE];

    scan_id(start_id);
    scan_id(end_id);
    
    struct carriage_range range;
    range.move_from = find_passenger_carriage(train, start_id, command);

    struct count_details total;
    total.occupancy = 0;
    total.capacity = 0;
    
    if (range.move_from != NULL) {
        range.move_to = find_passenger_carriage(train, end_id, command);
        if (range.move_to != NULL) {
            total = count_passengers(range);
            if (total.wrong_order == 1) {
                printf("ERROR: Carriages are in the wrong order\n");
            } else {
                printf("Occupancy: %d\n", total.occupancy);
                printf("Unoccupied: %d\n", total.capacity - total.occupancy);
            }
        }
    }
}   

/**
 * @brief Counts number of carriages, occupied seats, and capacity for a given range of carriages.
 *        Also checks if given range of carriages is in order.
 * 
 * @param carriage 
 * @return A count_details struct containing an integer of counted number of carriages, occupied seats, and capacity
 *         as well as whether it the given carriage range is in the wrong order.
 */
struct count_details count_passengers(struct carriage_range carriage) {
    struct count_details total;
    total.occupancy = 0;
    total.capacity = 0;
    total.carriage_amount = 0;
    total.wrong_order = FALSE;
    
    int include = TRUE;
    struct carriage *current = carriage.move_from;
    // Loops from specified start carriage until last carriage in train or until 
    // specified end carriage
    while (current->next != NULL && include == TRUE) {
        total.occupancy += current->occupancy;
        total.capacity += current->capacity;
        
        if (carriage.move_to != NULL) {
            if (strcmp(current->carriage_id, (carriage.move_to)->carriage_id) == 
                    IDENTICAL_STRING) {
                include = FALSE;
            }
        }
        total.carriage_amount++;
        current = current->next;
    }
    
    // Checks if specified end carriage is NULL (meaning it will count all carriages)
    // or if it is last carriage which also happens to be specified end carriage to loop 
    // to, then adds as usual and signifies that carriages are in right order.
    if (carriage.move_to == NULL || (current->next == NULL && 
            strcmp(current->carriage_id, (carriage.move_to)->carriage_id) == 
            IDENTICAL_STRING)) {
        total.occupancy += current->occupancy;
        total.capacity += current->capacity;
        total.carriage_amount++;
        current = current->next;
        include = FALSE;
    } 
    if (include == TRUE) {
        total.wrong_order = TRUE;
    }
    return total; 
}

/**
 * @brief takes user input to get ready to move passengers and prints appropriate 
 *        message if valid or invalid.
 * 
 * @param train   - A train struct containing the carriages where the passengers 
 *                  will be moved between 
 * @param command - a char which provides context of how other functions will be used
 *                  to remove and reseat passengers and for error-checking.
 * @return Nothing
 */
void move_passengers_command(struct train *train, char command) {
    char source_id[ID_SIZE];
    char destination_id[ID_SIZE];
    int num_move;

    scan_id(source_id);
    scan_id(destination_id);
    scanf(" %d", &num_move);

    struct carriage *source_carriage = NULL;
    struct carriage *destination_carriage = NULL;

    int source_valid = check_before_moving(train, REMOVE_PASSENGERS, num_move, 
            source_id);
    // Checks validity of source carriage first before checking destination carriage 
    if (source_valid == TRUE) {
        int destination_valid = check_before_moving(train, SEAT_PASSENGERS, 
                num_move, destination_id);
        if (destination_valid == TRUE) {
            source_carriage = find_passenger_carriage(train, source_id, command);
            destination_carriage = find_passenger_carriage(train, 
                destination_id, command);
        }
    }

    if (destination_carriage != NULL) {
        if (check_available_space(destination_carriage, num_move) == TRUE) {
            struct carriage_range carriage;
            carriage.move_from = source_carriage;
            carriage.move_to = destination_carriage;
            carriage.move_from->occupancy -= num_move;
            seat_passengers(carriage, num_move, MOVE_PASSENGERS);
        }        
    }
}

/**
 * @brief Checks whether there is enough space in the carriages from where the passengers will
 *        be moved to and downwards (overflow).
 * 
 * @param destination_carriage - A carriage struct where passengers will initially be moved to
 * @param num_move             - The number of passengers being moved
 * @return An integer denoting whether there is enough space or not 
 */
int check_available_space(struct carriage *destination_carriage, int num_move) {
    int valid = TRUE;
    
    struct carriage_range carriage;
    carriage.move_from = destination_carriage;
    carriage.move_to = NULL;

    struct count_details total;
    total = count_passengers(carriage);
    
    if (total.capacity - total.occupancy < num_move) {
        printf("ERROR: not enough space to move passengers\n");
        valid = FALSE;
    }
    return valid;
}

/**
 * @brief Allocates memory to create a linked list node of struct train and
 *        inserts it behind currently selected train or at head if train list 
 *        contains only 1 train node.
 * 
 * @param head_train - A struct of head_train containing the head of the train list
 * @param selected   - A struct of train which will be used as reference to insert the new
 *                     train behind.
 */
void create_train(struct head_train *head_train, struct train *selected) {
    struct train *new_train = malloc(sizeof(struct train));
    struct train *current = head_train->head;
    
    if (current->next == NULL || current == selected) {
        new_train->next = current;  
        new_train->carriages = NULL;
        head_train->head = new_train;
    } else {
        while (current->next != selected) {
            current = current->next;
        }  
        new_train->next = selected;
        current->next = new_train;
        new_train->carriages = NULL;
    }
    
}

/**
* @brief Changes selected train to the next train if next train is not NULL
*
* @param selected - A struct train which gives reference of what the new selected should be
* @return A struct train which is the new selected train.
**/
struct train *select_forward_train(struct train *selected) {
    if (selected != NULL && selected->next != NULL) {
        selected = selected->next;
    }
    return selected;
}

/**
 * @brief Changes selected train to the previous train node
 * 
 * @param head_train - A struct head_train which contains the head of the train list
 * @param selected   - A struct train which gives reference of what the new selected should be
 * @return A struct train which is the new selected train
 */
struct train *select_backward_train(struct head_train *head_train, 
        struct train *selected
) {
    struct train *current = head_train->head;
    if (current != NULL && current != selected) {
        if (current->next != NULL) {
            while (current->next != selected && current != NULL) {
                current = current->next;
            }
            selected = current;
        }
    }
    return selected;
}

/**
 * @brief Prints the summary of all train nodes in the train list
 * 
 * @param head_train - A head_train struct containing the head of the train list
 * @param selected   - A train struct which gives reference for which is the selected train in the
 *                     train list
 * @return Nothing
 */
void print_train_list(struct head_train *head_train, 
        struct train *selected,
        char command
) {
    struct train *current = head_train->head;
    int position = 0;
    
    while (current != NULL) {
        int is_selected = (current == selected);
        struct count_details total;
        total = count_total_passengers(current, command);
        print_train_summary(is_selected, position, total.capacity, 
                                total.occupancy, total.carriage_amount);
        position++;
        current = current->next;
    }
}

/**
 * @brief Takes user input in order to remove a carriage struct from the carriage list
 * 
 * @param selected - A train struct containing the carriage list where the carriage will be removed
 * @param command  - A char which provides context of how the find_passenger_carriage() function will
 *                   behave
 * @return Nothing
 */
void remove_carriage_command(struct train *selected, char command) {
    char id[ID_SIZE];

    scan_id(id);

    struct carriage *carriage;
    carriage = find_passenger_carriage(selected, id, command);
    if (carriage != NULL) {
        remove_carriage(selected, carriage);
    }
}

/**
 * @brief Removes a specified carriage from a train struct node, freeing memory
 * 
 * @param selected - A train struct where the carriage will be removed from
 * @param carriage - A carriage struct which will be removed and freed from memory
 * @return Nothing
 */
void remove_carriage(struct train *selected, struct carriage *carriage) {
    struct carriage *current = selected->carriages;
    
    if (current == carriage) {
        selected->carriages = current->next;
        free(current);
    } else {
        while (current != NULL && current->next != carriage) {
            current = current->next;
        }
        current->next = carriage->next;
        free(carriage);
    }
}

/**
 * @brief Removes currently selected train struct along with all its carriages, freeing all memory
 *        associated with the carriages and train. The newly selected train node will be the train node
 *        behind the old selected train node.
 * 
 * @param selected   - A train struct denoting the current selected train
 * @param head_train - A head_train struct containing the head of the train list
 * @return A struct train used to update the new selected train after removing the previous one
 */
struct train *remove_train(struct head_train *head_train, struct train *selected) {
    struct carriage *current = selected->carriages;
    
    while (current != NULL) {
        remove_carriage(selected, current);
        current = selected->carriages;
    }
    
    struct train *to_be_removed = selected;
    // Changes selected to next if there is no previous node, 
    // else will change to previous node
    if (head_train->head == selected) {
        head_train->head = select_forward_train(selected);
        selected = head_train->head;
    } else {
        selected = select_backward_train(head_train, selected);
        selected->next = to_be_removed->next;
    }
    
    // Condition indicates that there are no other nodes, therefore remove old train node
    // and create a new train 
    if (selected == to_be_removed) {
        head_train->head = malloc(sizeof(struct train));
        head_train->head->carriages = NULL;
        selected = head_train->head;
        selected->next = NULL;
    } 
    
    free(to_be_removed);

    return selected;
}

/**
 * @brief Removes all train struct nodes and carriage struct nodes created in the program
 * 
 * @param head_train - A head_train struct containing the head of the train list
 * @return Nothing
 */
void clear_memory(struct head_train *head_train) {
    struct train *current = head_train->head;
    // Due to remove_train function, must stop one train before last
    // otherwise it will infinitely loop.
    while (current->next != NULL) {
        current = remove_train(head_train, current);
    }
    
    current = remove_train(head_train, current);
    free(current);
    free(head_train);
    printf("\nGoodbye\n");

}

/**
 * @brief Merges the train in front of the currently selected train into the currently
 *        selected train, combining carriages with the same ID and appending those that have
 *        unique IDs
 * 
 * @param selected - A train struct denoting currently selected train
 * @return Nothing
 */
void merge_trains(struct train *selected) {
    struct train *next_train = selected->next;
    struct carriage *other_carriage = next_train->carriages;
    // searches carriages of next train
    while (other_carriage != NULL) {
        struct carriage *current_carriage = NULL;
        // Searches if there is matching carriage in selected train to decide to 
        // merge or append other_carriage.
        current_carriage = find_passenger_carriage(selected, 
                other_carriage->carriage_id, MERGE_TRAIN);

        if (current_carriage != NULL) {
            current_carriage->capacity += other_carriage->capacity;
            current_carriage->occupancy += other_carriage->occupancy;
        } else {
            enum carriage_type type = other_carriage->type;
            int capacity = other_carriage->capacity;
            append_carriage(other_carriage->carriage_id, type, capacity, selected);
        }
         
        struct carriage *to_be_removed = other_carriage;
        other_carriage = other_carriage->next;
        free(to_be_removed);

    }
    
    selected->next = next_train->next;
    free(next_train);
        
}

/**
 * @brief Takes user input for how many splits and which carriages to split based on ID and gets ready to split
 * 
 * @param selected - A train struct denoting currently selected train in which the carriages will be
 *                   split from.
 * @param command  - A char denoting the command inputted by users, which will provide context
 *                   for how other functions will behave. 
 * @return Nothing
 */
void split_trains_command(struct train *selected, char command) {
    int carriage_inputs;
    scanf(" %d", &carriage_inputs);
    int row = carriage_inputs;

    if (check_positive_int(carriage_inputs) == TRUE) {
        // https://www.geeksforgeeks.org/dynamically-allocate-2d-array-c/
        // The website I used to learn how to dynamically allocate 2d arrays
        char (*carriage_ids) [row] [ID_SIZE] = malloc(sizeof(*carriage_ids));
        printf("Enter ids:\n");
        // Scans id given by user and stores in 2D array
        for (int i = 0; i < row; i++) {
            char id[ID_SIZE];
            scan_id(id);
            
            for (int j = 0; j < ID_SIZE; j++) {
                (*carriage_ids) [i] [j] = id[j];
            }
            
            if (find_passenger_carriage(selected, id, command) == NULL) {
                printf("No carriage exists with id: \'%s\'. Skipping\n", id);
            }    
        }
        
        if (selected->carriages != NULL) {
            search_train_to_split(selected, carriage_ids, row);
        } 
        
        free(*carriage_ids);
    }
}

/**
 * @brief Loops through carriage list of selected train to find carriage to split from train 
 * 
 * @param selected     - A train struct denoting currently selected train to initially split carriages from
 * @param carriage_ids - A dynamically allocated 2D array of char holding the inputted carriage IDs
 * @param row          - An integer denoting index of the carriage_ids that contains the id string
 * @return Nothing
 */
void search_train_to_split(struct train *selected, 
        char (*carriage_ids) [] [ID_SIZE],
        int row) {
    struct carriage *current_carriage = selected->carriages;
    struct carriage *previous_carriage = selected->carriages;
    struct train *current_train = selected;
    int deleted = 0;
    
    while (current_carriage != NULL) {
        int matched = FALSE;
        int current_row = 0;
        // For each carriage, searches whether it matches ID with any of mentioned
        // ids by user       
        while (current_row < (row - deleted) && matched == FALSE) {
            char id[ID_SIZE];
            for (int col = 0; col < ID_SIZE; col++) {
                id[col] = (*carriage_ids) [current_row] [col];
            }
            // If matching ids, then split the train and loop through newly split 
            // train for further splitting.
            if (current_carriage != NULL && 
                    strcmp(current_carriage->carriage_id, id) == IDENTICAL_STRING) {
                
                matched = TRUE;
                struct train_details *new_train = NULL;
                new_train = split_train(current_carriage, previous_carriage, 
                            current_train, id, carriage_ids, row, current_row, 
                            deleted);
                current_train = new_train->current_train;
                previous_carriage = new_train->previous_carriage;
                current_carriage = new_train->current_carriage;
                free(new_train);
            }            

            deleted += matched;
            current_row++;
        }

        if (matched == FALSE) {
            previous_carriage = current_carriage;
            current_carriage = current_carriage->next;
        } 
    }
}

/**
 * @brief Creates a new train to place the newly split carriage into and inserts new train in front of the selected train or
 *        previous newly created train after a split. 
 * 
 * @param current_carriage  - A struct carriage pointer denoting the carriage being split from the train
 * @param previous_carriage - A struct carriage pointer denoting the carriage behind the carriage being split from 
 *                            the train.
 * @param current_train     - A struct train pointer denoting current train node where carriage is being split from.
 * @param id                - A char array of length ID_SIZE containing the id of the carriage being split
 *                            from the train.
 * @param carriage_ids      - A dynamic char 2D array that contains the carriage ids inputted by the user.
 * @param row               - An integer denoting the original number of carriages inputted by the user.
 * @param current_row       - An int index of carriage_id denoting which carriage id is being split,
 *                            and to be removed from the carriage_id array so it is no longer checked.
 * @param deleted           - An int denoting how carriage ids have been removed from carriage_ids array 
 *                            since it has already been split at that carriage.
 * @return A struct train_details containing the updated values of previous_carriage,
 *         current_carriage, and current_train after splitting the train
 */
struct train_details *split_train(struct carriage *current_carriage,
        struct carriage *previous_carriage,
        struct train *current_train,
        char id[ID_SIZE],
        char (*carriage_ids) [] [ID_SIZE],
        int row,
        int current_row,
        int deleted) {
    
    struct train_details *train = malloc(sizeof(struct train_details));
    
    struct train *new_train = malloc(sizeof(struct train));
    new_train->next = current_train->next;
    current_train->next = new_train;
    new_train->carriages = current_carriage;
    
    if (current_carriage == previous_carriage) {
        current_train->carriages = NULL;
        
    } else {
        previous_carriage->next = NULL;
    }

    previous_carriage = new_train->carriages;
    current_carriage = previous_carriage;
    current_train = new_train;
    // Removes any ids already matched with by replacing it with last non-matched 
    // carriage id and reducing number of carriages checked through deleted.
    for (int col = 0; col < ID_SIZE; col++) {
        (*carriage_ids) [current_row] [col] = (*carriage_ids) [row - 1 - deleted] [col];
    }

    train->previous_carriage = previous_carriage;
    train->current_carriage = current_carriage;
    train->current_train = current_train;
    return train;
}
////////////////////////////////////////////////////////////////////////////////
///////////////////////////  PROVIDED FUNCTIONS  ///////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// Prints the Carriage simulator usage instructions,
// displaying the different commands and their arguments.
//
void print_usage(void) {
    printf(
        "=====================[ Carriage Simulator ]=====================\n"
        "      ===============[     Usage Info     ]===============      \n"
        "  a [carriage_id] [type] [capacity]                             \n"
        "    Add a carriage to the train                                 \n"
        "  p                                                             \n"
        "    Print out all of the carriages in the train                 \n"
        "  i [n] [carriage_id] [type] [capacity]                         \n"
        "    Insert a carriage into the train at position `n`            \n"
        "                                                                \n"
        "  s [carriage_id] [n]                                           \n"
        "    Seat `n` passengers onto the train starting from carriage   \n"
        "    `carriage_id`                                               \n"
        "  d [carriage_id] [n]                                           \n"
        "    Remove `n` passengers from carriage `carriage_id`           \n"
        "  T                                                             \n"
        "    Display the total number of passengers and empty seats on   \n"
        "    the train                                                   \n"
        "  c [start_id] [end_id]                                         \n"
        "    Display the number of passengers and empty seats on between \n"
        "    carriage `start_id` and carriage `end_id`                   \n"
        "  m [source_id] [destination_id] [n]                            \n"
        "    Move `n` passengers from one carrige to another, without    \n"
        "    kicking anyone off the train.                               \n"
        "  h [carriage_id]                                               \n"
        "    Display the happiness of passengers in carriage             \n"
        "    `carriage_id`                                               \n"
        "  H                                                             \n"
        "    Display the average happiness of all passengers on the train\n"
        "                                                                \n"
        "  N                                                             \n"
        "    Create a new empty train                                    \n"
        "  >                                                             \n"
        "    Select the next train in the train list.                    \n"
        "  <                                                             \n"
        "    Select the previous train in the train list.                \n"
        "  P                                                             \n"
        "    Display the train list.                                     \n"
        "  r [carriage_id]                                               \n"
        "    Remove carriage `carriage_id` from the selected train.      \n"
        "  R                                                             \n"
        "    Remove the selected train.                                  \n"
        "                                                                \n"
        "  M                                                             \n"
        "    Merge the selected train with the train after it.           \n"
        "  S [n]                                                         \n"
        "    Split the current train into smaller trains.                \n"
        "  O                                                             \n"
        "    Rearrange passengers on the selected train to optimise      \n"
        "    happiness.                                                  \n"
        "  ?                                                             \n"
        "    Show help                                                   \n"
        "================================================================\n"
    );
}


// Scan in the a carriage id string into the provided buffer, placing 
// '\0' at the end.
//
// Parameters:
//      id_buffer - a char array of length ID_SIZE, which will be used
//                  to store the id.
// 
// Usage: 
// ```
//      char id[ID_SIZE];
//      scan_id(id);
// ```
void scan_id(char id_buffer[ID_SIZE]) {
    scan_token(id_buffer, ID_SIZE);
}


// Scans a string and converts it to a carriage_type.
//
// Returns:
//      The corresponding carriage_type, if the string was valid,
//      Otherwise, returns INVALID_TYPE.
// 
// Usage: 
// ```
//      enum carriage_type type = scan_type();
// ```
//
enum carriage_type scan_type(void) {
    // This 20 should be #defined, but we've kept it like this to
    // avoid adding additional constants to your code.
    char type[20];
    scan_token(type, 20);
    return string_to_type(type);
}


// Formats and prints out a train carriage struct,
//
// Parameters:
//      carriage - The struct carriage to print.
// 
void print_carriage(struct carriage *carriage) {
    int line_length = 20;

    char *id = carriage->carriage_id;
    char *type = type_to_string(carriage->type);

    printf(" ---------\\/--------- \n");

    int padding = line_length - strlen(id);
    printf("|%*s%s%*s|\n", padding / 2, "", id, (padding + 1) / 2, "");

    padding = line_length - 2 - strlen(type);
    printf("|%*s(%s)%*s|\n", padding / 2, "", type, (padding + 1) / 2, "");

    printf("| Occupancy: %3d/%-3d |\n", 
            carriage->occupancy, 
            carriage->capacity);
    printf(" ---------||--------- \n");
}


// Formats and prints out various information about a given train.
//
// Parameters:
//      is_selected - 1, if this train is the currently selected train, 
//                    0, otherwise.
//      n           - The position of the given train in the list of trains, 
//                    starting from 0.
//      capacity    - The total capacity of the given train.
//      capacity    - The total occupancy of the given train
//      num_carriages   - The number of carriages in the given train.
//
void print_train_summary(
    int is_selected, 
    int n, 
    int capacity, 
    int occupancy,
    int num_carriages
) {
    if (is_selected) {
        printf("--->Train #%d\n", n);
    } else  {
        printf("    Train #%d\n", n);
    }

    printf("        Carriages: %3d\n", num_carriages);
    printf("        Capacity : %3d/%-3d\n", occupancy, capacity);
    printf("    ----------------------\n");

}



// Compares two double (floating point) values. Value are considered
// equal if there is a less than 0.01 difference between them.
// Note: You should use this function if you need to compare doubles
//       to eachother, as it reduces inconsistencies caused by double
//       imprecision.
//
// Parameters:
//      n1 - a floating point value
//      n2 - a floating point value
// 
// Returns:
//      0, if the two values are considered equal.
//      a negative number, if n1 is less than n2,
//      a positive number, if n2 is less than n1,
//
// Usage: 
// ```
//      if (compare_double(n1, n2) > 0) {
//          printf("n1 greater than n2\n");
//      } else if (compare_double(n1, n2) == 0) {
//          printf("n1 is equal to n2\n");
//      } else {
//          printf("n1 is less than n2\n");
//      }
// ```
int compare_double(double n1, double n2) {
    double delta = 0.01;

    double difference = n1 - n2;
    // abs(n1 - n2) < delta 
    if (difference < delta && difference > -delta) {
        return 0;
    }
    if (n1 < n2) {
        return -1;
    }

    return 1;
}


////////////////////////////////////////////////////////////////////////////////
////////////////////// ADDITIONAL PROVIDED FUNCTIONS ///////////////////////////
////////////////////////////////////////////////////////////////////////////////
// You don't need to use any of these   , or understand how they work!
// We use them to implement some of the provided helper functions.

enum carriage_type string_to_type(char *type_str) {
    int len = strlen(type_str);

    if (strncasecmp(type_str, "passenger", len) == 0) {
        return PASSENGER;
    } 
    if (strncasecmp(type_str, "buffet", len) == 0) {
        return BUFFET;
    } 
    if (strncasecmp(type_str, "restroom", len) == 0) {
        return RESTROOM;
    }
    if (strncasecmp(type_str, "first_class", len) == 0) {
        return FIRST_CLASS;
    } 

    return INVALID_TYPE;
}


char *type_to_string(enum carriage_type type) {
    if (type == PASSENGER) {
        return "PASSENGER";
    } else if (type == BUFFET) {
        return "BUFFET";
    } else if (type == FIRST_CLASS) {
        return "FIRST CLASS";
    } else if (type == RESTROOM) {
        return "RESTROOM";
    }

    return "INVALID";
}

int scan_token(char *buffer, int buffer_size) {
    if (buffer_size == 0) {
        return 0;
    }

    char c;
    int i = 0;
    int num_scanned = 0;

    // consume all leading whitespace
    scanf(" ");

    // Scan in characters until whitespace
    while (i < buffer_size - 1
        && (num_scanned = scanf("%c", &c)) == 1 
        && !isspace(c)) {

        buffer[i++] = c;
    }

    if (i > 0) {
        buffer[i] = '\0';
    }

    return num_scanned;
}
