#include "bit_rotate.h"

// return the value bits rotated left n_rotations
uint16_t bit_rotate(int n_rotations, uint16_t bits) {
    uint16_t rotated_bits = bits;
    n_rotations %= 16;

    if (n_rotations < 0) {
        n_rotations = 16 + n_rotations;
    }

    rotated_bits >>= 16 - n_rotations;
    bits <<= n_rotations;

    return bits | rotated_bits;
}
