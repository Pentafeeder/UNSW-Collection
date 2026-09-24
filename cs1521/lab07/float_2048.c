// Multiply a float by 2048 using bit operations only

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include "floats.h"

#define FALSE 0
#define TRUE 1

// separate out the 3 components of a float
float_components_t float_bits(uint32_t f) {
    // PUT YOUR CODE HERE
    float_components_t components;
    
    int sign;
    uint32_t exponent;
    uint32_t mantissa;

    int bit_mask = 0x80000000;
    sign = bit_mask & f;

    if (sign == bit_mask) {
        sign = 1;
    } else {
        sign = 0;
    }
    components.sign = sign;

    bit_mask = 0x7F800000;

    exponent = f & bit_mask;
    exponent >>= 23;
    components.exponent = exponent;

    bit_mask = 1;
    bit_mask <<= 23;
    bit_mask -= 1;
    mantissa = f & bit_mask;
    components.fraction = mantissa;

    return components;
}

// given the 3 components of a float
// return 1 if it is NaN, 0 otherwise
int is_nan(float_components_t f) {
    // PUT YOUR CODE HERE
    int is_nan = FALSE;

    if (f.exponent == 0xFF && f.fraction != 0) {
        is_nan = TRUE;
    } 
    return is_nan;
}

// given the 3 components of a float
// return 1 if it is inf, 0 otherwise
int is_positive_infinity(float_components_t f) {
    // PUT YOUR CODE HERE
    int is_pos_inf = FALSE;

    if (f.exponent == 0xFF && f.fraction == 0 && f.sign == 0) {
        is_pos_inf = TRUE;
    }
    return is_pos_inf;
}

// given the 3 components of a float
// return 1 if it is -inf, 0 otherwise
int is_negative_infinity(float_components_t f) {
    // PUT YOUR CODE HERE
    int is_neg_inf = FALSE;

    if (f.exponent == 0xFF && f.fraction == 0 && f.sign == 1) {
        is_neg_inf = TRUE;
    }
    return is_neg_inf;
}

// given the 3 components of a float
// return 1 if it is 0 or -0, 0 otherwise
int is_zero(float_components_t f) {
    // PUT YOUR CODE HERE
    int is_zero = FALSE;
    if (f.exponent == 0 && f.fraction == 0) {
        is_zero = TRUE;
    }
    return is_zero;
}

// float_2048 is given the bits of a float f as a uint32_t
// it uses bit operations and + to calculate f * 2048
// and returns the bits of this value as a uint32_t
//
// if the result is too large to be represented as a float +inf or -inf is returned
//
// if f is +0, -0, +inf or -inf, or Nan it is returned unchanged
//
// float_2048 assumes f is not a denormal number
//
uint32_t float_2048(uint32_t f) {
    // PUT YOUR CODE HERE
    float_components_t value = float_bits(f);
    
    
    if (is_nan(value) || is_zero(value) || is_positive_infinity(value) || is_negative_infinity(value)) {
        return f;
    }
    
    uint32_t remaining_space = 0xFF - value.exponent;
    if (remaining_space < 11) {
        value.exponent = 0xFF;
        value.fraction = 0;

    } else {   
        value.exponent += 11;
    }
    
    uint32_t floating_point = (value.sign << 31) | (value.exponent << 23) | value.fraction;
    return floating_point;
}
