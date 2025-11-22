#ifndef VERIFY_H
#define VERIFY_H

#include "pin.h"

/* decimal_table: array of 16 ints mapping 0..15 -> 0..9
   returns 1 if entered_pin is accepted, 0 otherwise */
int verify_pin(const char entered_pin[PIN_LEN + 1],
               const char validation_data[VALIDATION_DATA_LEN + 1],
               const int decimal_table[16],
               const char offset[OFFSET_LEN + 1]);

#endif
