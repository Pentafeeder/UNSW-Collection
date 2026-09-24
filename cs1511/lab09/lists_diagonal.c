// Returns 1 if there is a diagonal pattern and 0 if there isn't
// Edited by Kevin Le z5481482 
// on 12/04/2023

#include <stdio.h>
#include <stdlib.h>

// Do not edit these structs. You may use them exactly as
// they are but you cannot make changes to them

// A node in a linked list
struct node {
    int data;
    struct node *next;
};

// a list_node in a linked list. Each list_node
// contains a list of nodes.
struct list_node {
    struct node *my_list;
    struct list_node *next;
};

// Treat the linked lists like they're a 2D array
// and return 1 if the first element is repeated
// diagonally through the lists
int has_diagonal(struct list_node *head) {
    struct node *row = head->my_list;
    int diag_index = 0;
    int pattern = row->data;
    int valid = 1;
    while (row != NULL) {
        struct node *current_col = row;
        int col_index = 0;
        while (current_col != NULL && col_index <= diag_index) {
            if (col_index == diag_index && current_col->data != pattern) {
                valid = 0;
            }
            col_index++;
            current_col = current_col->next;
        }
        diag_index++;
        row = row->next;
    }

    return valid;
}

// This helper function is for the main below and will
// have no effect on your has_diagonal. It does not
// need to be modified.
struct node *make_list(int a, int b, int c);

// This is a main function which could be used
// to test your has_diagonal function.
// It will not be marked.
// Only your has_diagonal function will be marked.
//
// It's recommended to change the int values in this
// main to test whether your has_diagonal is working.
int main(void) {
    struct list_node *head = malloc(sizeof (struct list_node));
    struct list_node *l = head;
    
    // create the first list
    l->my_list = make_list(5, 0, 0);
    
    // create the second list
    l->next = malloc(sizeof (struct list_node));
    l = l->next;
    l->my_list = make_list(0, 5, 0);
    
    // create the third list
    l->next = malloc(sizeof (struct list_node));
    l = l->next;
    l->my_list = make_list(0, 0, 5);
    l->next = NULL;
    
    printf("The result of has_diagonal is: %d\n", has_diagonal(head));
    
    return 0;
}

struct node *make_list(int a, int b, int c) {
    struct node *head = malloc(sizeof (struct node));
    struct node *n = head;
    n->data = a;
    n->next = malloc(sizeof (struct node));
    n = n->next;
    n->data = b;
    n->next = malloc(sizeof (struct node));
    n = n->next;
    n->data = c;
    n->next = NULL;
    
    return head;
}



/* for tut (returning copy of original list while deleting original)
struct node *new_head = malloc
new_head->data = head->data;

struct node *new_previous = new_head;

struct node *previous = head;
struct node *current = previous->next;


while (current != NULL) {
    struct node *new_current = malloc;
    new_current->data = current->data;
    new_previous->next = new_current;
    free(previous);
    previous = current;
    current = current->next;
    new_previous = new_previous->next;
}

free(previous);

return new_head;*/