#include "pin.h"
#include <stdlib.h>
#include <time.h>

/* Generate a random 4-digit PIN as a string */
void generate_random_pin(char pin[PIN_LEN + 1])
{
    static int seeded = 0;
    if (!seeded)
    {
        srand((unsigned int)time(NULL));
        seeded = 1;
    }
    for (int i = 0; i < PIN_LEN; i++)
    {
        int d = rand() % 10;
        pin[i] = '0' + d;
    }
    pin[PIN_LEN] = '\0';
}

/* Simplified IBM-3624-style reference data:
   - embed the true PIN into the first positions of validation_data
   - zero offset
   With the default decimal table, verify_pin(true_pin, ...) will accept. */
void compute_reference_data(const char pin[PIN_LEN + 1],
                            char validation_data[VALIDATION_DATA_LEN + 1],
                            char offset[OFFSET_LEN + 1])
{
    /* Put the PIN digits into the first PIN_LEN chars of validation_data */
    for (int i = 0; i < PIN_LEN; i++)
    {
        validation_data[i] = pin[i];
    }

    /* Fill the rest with a repeating hex pattern */
    const char *hexchars = "0123456789ABCDEF";
    for (int i = PIN_LEN; i < VALIDATION_DATA_LEN; i++)
    {
        validation_data[i] = hexchars[i % 16];
    }
    validation_data[VALIDATION_DATA_LEN] = '\0';

    /* Offset is all zeros */
    for (int i = 0; i < OFFSET_LEN; i++)
    {
        offset[i] = '0';
    }
}
