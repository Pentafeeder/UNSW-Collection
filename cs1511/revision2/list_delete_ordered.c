#include <stdio.h>
#include <stdlib.h>

// Do not edit this struct. You may use it exactly as
// it is but you cannot make changes to it

// A node in a linked list
struct node {
    int data;
    struct node *next;
};

// ADD ANY FUNCTION DECLARATIONS YOU WISH TO USE HERE

// Remove any nodes in a list that are higher 
// than the node directly after them.
// Return the head of the list.
// The returned list must have no disorder in it!
struct node *remove_disorder(struct node *head) {
    // WRITE YOUR CODE HERE (you may need to change the line below)
    if (head == NULL || head->next == NULL) {
        return head;
    } else if (head->next->next == NULL) {
        if (head->data > head->next->data) {
            struct node *to_be_removed = head;
            head = head->next;
            free(to_be_removed);
        }
    } else {
        struct node *previous = head;
        struct node *current = previous->next;
        struct node *next = current->next;
        int removed = 0;
        int no_procedure = 0;
        while(next != NULL && head->next->next != NULL) {
            if (current->data > next->data) {
                struct node *to_be_removed = current;
                previous->next = next;
                current = next;
                next = next->next;
                removed++;
                free(to_be_removed);
            } else {
                previous = current;
                current = next;
                next = next->next;
            }
            
            if (removed != 0 && next == NULL) {
                previous = head;
                current = previous->next;
                next = current->next;
                removed = 0;
            } 

        } 
        current = head;
        next = current->next;
        if (current->data > next->data) {
            free(current);
            head = next;
        }
    }
    
    return head;
}

// These helper functions are for the main below and will
// have no effect on your remove_disorder. They do not
// need to be modified.
struct node *make_list(int a, int b, int c, int d);
void printList(struct node *head);

// This is a main function which could be used
// to test your remove_disorder function.
// It will not be marked.
// Only your remove_disorder function will be marked.
//
// It's recommended to change the int values in this
// main to test whether your remove_disorder is working.
int main(void) {
    

    // test with the first removal causing more disorder
    struct node *ordered = make_list(1,4,2,3);
    ordered = remove_disorder(ordered);
    printList(ordered);
    
    
    return 0;
}


// A simple function to make a linked list with 3 elements
// This function is purely for the main above
// You will be tested with lists that are more and less
// than 3 elements long
struct node *make_list(int a, int b, int c, int d) {
    struct node *head = malloc(sizeof (struct node));
    struct node *n = head;
    n->data = a;
    n->next = malloc(sizeof (struct node));
    n = n->next;
    n->data = b;
    n->next = malloc(sizeof (struct node));
    n = n->next;
    n->data = c;
    n->next = malloc(sizeof (struct node));
    n = n->next;
    n->data = d;
    n->next = NULL;
    
    return head;
}

void printList(struct node *head) {
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}
// ADD ANY FUNCTION DEFINITIONS YOU WISH TO USE HERE

