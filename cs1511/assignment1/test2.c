// By Kevin Le z5481482
#include <stdio.h>

// You may find it helpful to add extra functions here. Procedures that
// encipher/decipher the entire `msg` may be useful.
//
// Likewise, functions that encipher/decipher single letters will help reduce
// code repetition. It is completely up to you whether to create these
// functions, but we *highly* recommend you do for practice!

// Determines ciphering for a given message and prints out the result
void determine_ciphering(char letter1, char letter2, char letter3, char letter4) {
    // TODO: Complete this procedure. This is needed to compile your program.
    struct key {
        int num1, num2, num3, num4;
    };
    struct characters {
        int character1, character2, character3, character4;
    };
    struct key cipher;
    struct characters msg;

    msg.character1 = letter1;
    msg.character2 = letter2;
    msg.character3 = letter3;
    msg.character4 = letter4;

    int *keypointer = &cipher.num1;
    int *msgpointer = &msg.character1;

    int count = 0;
    char to_encrypt;
    int sign = 0;
    char is_capital;
    
    printf("Would you like to encipher or decipher this message (e/d)? ");
    scanf(" %c", &to_encrypt);
    
    if (to_encrypt == 'e') {
        printf("Enter numbers to encipher by: ");
        sign = 1;
    }
    else if (to_encrypt == 'd') {
        printf("Enter numbers to decipher by: ");
        sign = -1;
    }
    scanf("%d %d %d %d", &cipher.num1, &cipher.num2, &cipher.num3, &cipher.num4);
    
    while (count < 4) {
        *keypointer = *keypointer * sign;

        if (*keypointer > 26 || *keypointer < -26) {
            *keypointer = *keypointer%26;
        }
        if (*msgpointer < 97) {
            is_capital = 'A';
        }
        else {
            is_capital = 'a';
        }
        // overflow past z/Z
        if (*msgpointer + *keypointer > is_capital + 26) {
            *keypointer = *msgpointer + *keypointer - is_capital - 26;
            *msgpointer = is_capital + *keypointer;
            
        }
        //overflow past a/A
        else if (*msgpointer + *keypointer < is_capital) {
            *keypointer = *msgpointer + *keypointer - is_capital;
            *msgpointer = is_capital + *keypointer + 26;
        }
        else {
            *msgpointer = *keypointer + *msgpointer;
            
        }
        count++;
        msgpointer++;
        keypointer++;
    }
    msgpointer--;
    letter4 = *msgpointer;
    msgpointer--;
    letter3 = *msgpointer;
    msgpointer--;
    letter2 = *msgpointer;
    msgpointer--;
    letter1 = *msgpointer;
    printf("%c%c%c%c\n", letter1, letter2, letter3, letter4);
}
   
   
////////////////////////////////////////////////////////////////////////////////
///////////////////// DO NOT EDIT THIS MAIN FUNCTION ///////////////////////////
////////////////////////////////////////////////////////////////////////////////
// This main function scans a message and then calls your determine_ciphering
// procedure, passing in the message.
int main(void) {
    // Have a think about how we might implement this with a `struct message`
    // once we've covered structs in the Thursday lecture!
    char letter1;
    char letter2;
    char letter3;
    char letter4;
    // Scan message into the four characters
    printf("Message: ");
    scanf(
        "%c %c %c %c",
        &letter1, &letter2, &letter3, &letter4
    );
    

   
    
 
    

    // Call your determine_ciphering function and pass in the message.
    for i in
    determine_ciphering(letter1, letter2, letter3, letter4);
}
