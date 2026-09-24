#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

// Provided Functions
struct node *create_node(int data);
void print_list(struct node *head);
struct node *insert_at_head(struct node *head, int data);
struct node *insert_at_tail(struct node *tail, int data);

int main(void) {

    struct node *head = NULL;

    // TODO: Read integers until EOF
    // For each integer, alternate inserting at tail 
    //      and inserting at head
    int data;
    int index = 0;
    while (scanf(" %d", &data) == 1) {
        if (index % 2 == 0) {
            head = insert_at_head(head, data);
        } else {
            head = insert_at_tail(head, data);
        }
        index++;
    }

    print_list(head);
    
    return 0;
}

// Mallocs a new node and returns a pointer to it
struct node *create_node(int data) {
    struct node *new_node = malloc(sizeof(struct node));
    new_node->next = NULL;
    new_node->data = data;
    return new_node;
}

// Prints a linked list
void print_list(struct node *head) {
    struct node *curr = head;
    while (curr != NULL) {
        printf("%d -> ", curr->data);
        curr = curr->next;
    }
    printf("X\n");
}

struct node *insert_at_head(struct node *head, int data) {
    struct node *new_node = create_node(data);
    new_node->next = head;
    return new_node;
}

struct node *insert_at_tail(struct node *head, int data) {
    struct node *new_node = create_node(data);
    struct node *current = head;
   
    while (current->next != NULL) {
        current = current->next;
    }
    new_node->next = current->next;
    current->next = new_node;

    return head;
}