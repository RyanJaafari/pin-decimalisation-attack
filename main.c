#include <stdio.h>
#include "pin.h"
#include "attack.h"

int main(void) {
    int num_pins = 100;      /* how many random PINs to test */
    int max_attempts = 100;  /* cap on attempts per PIN */

    /* CSV header */
    printf("pin,attempts,mode,comment\n");

    for (int i = 0; i < num_pins; i++) {
        char pin[PIN_LEN + 1];
        char validation_data[VALIDATION_DATA_LEN + 1];
        char offset[OFFSET_LEN + 1];

        generate_random_pin(pin);
        compute_reference_data(pin, validation_data, offset);

        /* Run all three modes for each PIN */
        for (int mode = 0; mode <= 2; mode++) {
            int attempts = run_attack_for_pin(pin, validation_data, offset, mode, max_attempts);

            if (attempts > 0) {
                printf("%s,%d,%d,\"PIN %s found in %d attempts in mode %d\"\n",
                       pin, attempts, mode, pin, attempts, mode);
            } else {
                printf("%s,%d,%d,\"PIN %s not found within max attempts (%d) in mode %d\"\n",
                       pin, attempts, mode, pin, max_attempts, mode);
            }
        }
    }

    return 0;
}
