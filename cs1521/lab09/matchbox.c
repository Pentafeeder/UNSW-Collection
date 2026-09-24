#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "matchbox.h"

#define BYTE_LENGTH 8
#define SEQEUNCE_LENGTH_SIZE 2
struct packed_matchbox pack_matchbox(char *filename) {
    // TODO: complete this function!
    // You may find the definitions in matchbox.h useful.

    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        perror(filename);
        exit(1);
    }

    uint8_t sequence_length[SEQEUNCE_LENGTH_SIZE];
    int bytes_read = fread(sequence_length, 1, SEQEUNCE_LENGTH_SIZE, file);

    if (bytes_read < 2) {
        fprintf(stderr, "Not enough bytes in file to read\n");
        exit(1);
    }

    uint16_t length = 0; 
    for (int i = 0; i < SEQEUNCE_LENGTH_SIZE; i++) {
        length |= sequence_length[i] << (i * BYTE_LENGTH);    
    }

    int bytes_to_store_packed = num_packed_bytes(length);

    uint8_t *packed_bytes = malloc(bytes_to_store_packed);
    
    char bytes[length];
    bytes_read = fread(bytes, 1, length, file);
    
    if (bytes_read < length) {
        fprintf(stderr, "Not enough data\n");
        exit(1);
    }   

    int nth_packed = 0;
    uint8_t packed = 0;
    for (int i = 0; i < length; i++) {
        uint8_t bit_mask = 1;
        if (bytes[i] == '1') {
            packed |= (bit_mask << (BYTE_LENGTH - (i % BYTE_LENGTH) - 1));
        }

        if ((i + 1) % 8 == 0) {
            packed_bytes[nth_packed] = packed;
            nth_packed++;
            packed = 0;
        }
    }
    
    if (nth_packed < bytes_to_store_packed) {
        packed_bytes[nth_packed] = packed;
    }

    struct packed_matchbox matchbox = {
        .sequence_length = length,
        .packed_bytes = packed_bytes
    };

    
    return matchbox;
}
