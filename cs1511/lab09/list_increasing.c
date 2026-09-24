// Determines whether a given list is in increasing order or not, 
// represnted by 1 and 0 respectively
// Edited by Kevin Le z5481482
// on 11/04/2023

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct node {
    struct node *next;
    int          data;
};

int increasing(struct node *head);
struct node *array_to_list(int len, int array[]);

#define MAX_INIT_LIST_LEN 100

// DO NOT MODIFY THIS FUNCTION!
int main() {
    // Need to read in a number of ints into an array
    printf("How many numbers in initial list?: ");
    int list_size = 0;
    scanf("%d", &list_size);
    int initial_elems[MAX_INIT_LIST_LEN] = {0};
    int n_read = 0;
    while (n_read < list_size && scanf("%d", &initial_elems[n_read])) {
        n_read++;
    }

    // create linked list from first set of inputs
    struct node *head = NULL;
    if (n_read > 0) {
        // list has elements
        head = array_to_list(n_read, initial_elems);
    }

    int result = increasing(head);
    printf("%d\n", result);

    return 0;
}


// return 1 if values in a linked list are in increasing order,
// return 0, otherwise

int increasing(struct node *head) {

    // PUT YOUR CODE HERE (change the next line!)
    struct node *current = head; 
    int is_increasing = 1;
    if (current == NULL) {
        return 1;
    } else {
        int previous = current->data;
        current = current->next;
        while (current != NULL) {
            if (current->data <= previous) {
                is_increasing = 0;
            }
            previous = current->data;
            current = current->next;
        }
    } 
        
    return is_increasing;

}


// DO NOT CHANGE THIS FUNCTION

// DO NOT CHANGE THIS FUNCTION
// create linked list from array of strings
struct node *array_to_list(int len, int array[]) {
    struct node *head = NULL;
    int i = len - 1;
    while (i >= 0) {
        struct node *n = malloc(sizeof (struct node));
        assert(n != NULL);
        n->next = head;
        n->data = array[i];
        head = n;
        i -= 1;
    }   
    return head;
}