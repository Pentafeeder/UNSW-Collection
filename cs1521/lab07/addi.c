// generate the encoded binary for an addi instruction, including opcode and operands

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include "addi.h"

// return the encoded binary MIPS for addi $t,$s, i
uint32_t addi(int t, int s, int i) {

    uint32_t addi = 0;
    uint16_t reduced_i = i; // converts fffffffd to fffd for encoding
    
    // since there are 31 registers, register numbers will only take up 5 bits 
    t <<= 16;           // 00000000000100010000000000000000
    s <<= 21;           // 00000010011000000000000000000000

    uint32_t bit_mask = 1;
    bit_mask <<= 29;    // 00100000000000000000000000000000
    
    addi |= bit_mask;
    addi |= s;
    addi |= t;
    addi |= reduced_i;  

    return addi;        // 00100010011100011111111111111101

}
