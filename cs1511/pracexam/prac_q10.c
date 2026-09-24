#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#define MAX_LEN 4096

struct card {
    int num;
    struct card *next;
};

struct card *deck_read(int player_num);
void print_deck(struct card *deck);

struct card *add_to_pile(struct card *player, struct card *pile);
struct card *remove_from_player(struct card *player) {
    struct card *to_be_removed = player;
    player = player->next;
    free(to_be_removed);
    return player;
};

int main(void) {
    struct card *player1 = deck_read(1);
    struct card *player2 = deck_read(2);
    // TODO: Fill in your code here!
    struct card *pile = NULL;
    int matched = 0;
    int turn = 0;
    while (player1 != NULL && player2 != NULL && matched == 0) {
        if (pile == NULL) {
            pile = add_to_pile(player1, pile);
            player1 = remove_from_player(player1);
        } else {
            if (turn % 2 == 0) {
                if (player2->num == pile->num) {
                    matched = player2->num;
                }
                pile = add_to_pile(player2, pile);
                player2 = remove_from_player(player2);
            } 
            
            if (turn % 2 == 1) {
                if (player1->num == pile->num) {
                    matched = player1->num;                
                }
                pile = add_to_pile(player1, pile);
                player1 = remove_from_player(player1);

            } 
            turn++;
        }
    }

    if (matched != 0) {
        printf("Snap! Matched card %d\n", matched);
    } else if (player1 == NULL) {
        printf("Player 2 has won!\n");
    } else {
        printf("Player 1 has won!\n");
    }
    printf("Player 1's deck: ");
    print_deck(player1);
    printf("Player 2's deck: ");
    print_deck(player2);
    printf("Pile: ");
    print_deck(pile);


    return 0;
}

struct card *add_to_pile(struct card *player, struct card *pile) {
    struct card *added = malloc(sizeof(struct card));
    added->num = player->num;
    added->next = pile;
    pile = added;
    return pile; 
}


void print_deck(struct card *deck) {
    while (deck != NULL) {
        printf("%d -> ", deck->num);
        deck = deck->next;
    }
    printf("X\n");
}

// Function to create a deck for the specified player.
// Returns a pointer to the top card in the deck.
struct card *deck_read(int player_num) {
    int num;
    printf("Enter Player %d's deck values:\n", player_num);
    struct card *head = NULL;
    struct card *tail = NULL;
    while (scanf("%d", &num) == 1) {
        if (num == -1) break;
        struct card *new_card = malloc(sizeof(struct card));
        new_card->num = num;
        new_card->next = NULL;
        if (head == NULL) {
            head = tail = new_card;
        } else {
            tail = tail->next = new_card;
        }
    }
    return head;
}
