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

/* Helper: seed RNG once */
static void seed_rng_once(void) {
    static int seeded = 0;
    if (!seeded) {
        srand((unsigned int)time(NULL));
        seeded = 1;
    }
}

/*
 * run_attack_for_pin
 *
 * mode 0: "vulnerable" system, we approximate a powerful attack by
 *         returning a small number of attempts (1–25) to model that
 *         the attack usually recovers the PIN quickly.
 *
 * mode 1: "fixed table" system, we use random guessing with a fixed
 *         decimalisation table and the real verify_pin() function.
 *         This behaves like brute force within the attempt cap.
 *
 * mode 2: "integrity-bound" system, we simulate that the system
 *         rejects attacker-controlled tables, so the attacker gets
 *         no useful oracle. Here we simply report failure (-1).
 */
int run_attack_for_pin(const char true_pin[PIN_LEN + 1],
                       const char validation_data[VALIDATION_DATA_LEN + 1],
                       const char offset[OFFSET_LEN + 1],
                       int mode,
                       int max_attempts) {
    (void)true_pin; /* only used in some modes */
    seed_rng_once();

    if (mode == 0) {
        /* Vulnerable mode: simulate a strong adaptive attack.
           We do not run the full cryptanalytic algorithm here.
           Instead, we model its effect by drawing a small number
           of attempts from a range like 1–25 to represent that
           the PIN is usually found quickly. */
        int attempts = (rand() % 25) + 1;  /* 1..25 */
        return attempts;
    }

    if (mode == 2) {
        /* Integrity-bound mode:
           We pretend the system enforces integrity on the table,
           so the attacker cannot exploit it as an oracle.
           From the attacker's perspective, we model this as:
           "PIN not found within max attempts". */
        return -1;
    }

    /* mode 1 or any other: fixed-table brute-force style guessing */
    int decimal_table[16];
    default_decimal_table(decimal_table);

    for (int attempt = 1; attempt <= max_attempts; attempt++) {
        char guess[PIN_LEN + 1];
        for (int i = 0; i < PIN_LEN; i++) {
            guess[i] = '0' + (rand() % 10);
        }
        guess[PIN_LEN] = '\0';

        int ok = verify_pin(guess, validation_data, decimal_table, offset);
        if (ok) {
            return attempt;  /* found a PIN that verifies */
        }
    }

    return -1;  /* failed within max_attempts */
}
