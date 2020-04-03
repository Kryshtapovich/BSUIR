#include <iostream>
#include "lfsr.h"

void lfsr_calculate(uint16_t *reg) 
{
    unsigned zero_bit = get_bit(*reg, 0);
    unsigned second_bit = get_bit(*reg, 2);
    unsigned third_bit = get_bit(*reg, 3);
    unsigned fifth_bit = get_bit(*reg, 5);

    unsigned res_bit = ((zero_bit ^ second_bit) ^ third_bit) ^ fifth_bit;

    *reg >>= 1;

    set_bit(reg, 15, res_bit);
}

unsigned get_bit(uint16_t x, unsigned position) 
{
    return (x >> position) & 1;
}

void set_bit(uint16_t *x, unsigned position, unsigned value) 
{
    *x  ^= (-value ^ *x) & (1 << position);
}