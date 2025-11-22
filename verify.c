#include "verify.h"
#include <string.h>

/* Simplified IBM-3624-style model:
   - validation_data is a hex-like string
   - each nibble is mapped through decimal_table
   - combined with offset
   - compared to entered_pin */
int verify_pin(const char entered_pin[PIN_LEN + 1],
               const char validation_data[VALIDATION_DATA_LEN + 1],
               const int decimal_table[16],
               const char offset[OFFSET_LEN + 1]) {

    char derived_pin[PIN_LEN + 1];

    for (int i = 0; i < PIN_LEN; i++) {
        char c = validation_data[i];
        int nibble;
        if (c >= '0' && c <= '9')      nibble = c - '0';
        else if (c >= 'A' && c <= 'F') nibble = 10 + (c - 'A');
        else                           nibble = 0;

        int dec_digit = decimal_table[nibble] % 10;
        int off_digit = offset[i] - '0';
        int pin_digit = (dec_digit + off_digit) % 10;
        derived_pin[i] = '0' + pin_digit;
    }
    derived_pin[PIN_LEN] = '\0';

    return (strncmp(derived_pin, entered_pin, PIN_LEN) == 0);
}
