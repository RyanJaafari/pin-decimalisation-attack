#include "attack.h"
#include "verify.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>

/* Default decimalisation table: identity 0..9, then wrap */
static void default_decimal_table(int table[16]) {
    for (int i = 0; i < 16; i++) {
        table[i] = i % 10;
    }
}

/* For now: simple random guessing attack.
   Later you can upgrade this to an adaptive table attack. */
int run_attack_for_pin(const char true_pin[PIN_LEN + 1],
                       const char validation_data[VALIDATION_DATA_LEN + 1],
                       const char offset[OFFSET_LEN + 1],
                       int mode,
                       int max_attempts) {
    (void)mode; /* unused for now */

    static int seeded = 0;
    if (!seeded) {
        srand((unsigned int)time(NULL));
        seeded = 1;
    }

    int decimal_table[16];
    default_decimal_table(decimal_table);

    for (int attempt = 1; attempt <= max_attempts; attempt++) {
        char guess[PIN_LEN + 1];
        for (int i = 0; i < PIN_LEN; i++) {
            guess[i] = '0' + (rand() % 10);
        }
        guess[PIN_LEN] = '\0';

        int ok = verify_pin(guess, validation_data, decimal_table, offset);
        if (ok && strncmp(guess, true_pin, PIN_LEN) == 0) {
            return attempt;  /* success */
        }
    }
    return -1;  /* failed within max_attempts */
}
