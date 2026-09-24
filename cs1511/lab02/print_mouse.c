// Prints out an ascii mouse to the terminal
// art from: https://www.asciiart.eu/animals/rodents/mice
// by Kevin Le z5481482
// on 22/02/2023

#include <stdio.h>

////////////////////////////////////////////////////////////////////////////
///////////////////// ONLY WRITE CODE BELOW HERE ///////////////////////////
////////////////////////////////////////////////////////////////////////////

// TODO: Write a procedure called print_mouse
// which outputs this ascii mouse (don't forget to escape '\'s ):

// _  _
//(o)(o)--.
// \../ (  )
// m\/m--m'`---
void print_mouse(void) {
    printf(" _  _\n");
    printf("(o)(o)--. \n"); 
    printf(" \\../ (  )\n");
    printf(" m\\/m--m\'`---\n");
}

int main(void){
    print_mouse();
    return 0;
}



