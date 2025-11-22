#include <stdio.h>
#include "pin.h"
#include "attack.h"

int main(void) {
    int num_pins = 100;      /* how many random PINs to test */
    int max_attempts = 100;  /* cap on attempts per PIN */
    int mode = 0;            /* 0 = vulnerable (for later modes) */

    printf("pin,attempts,mode\n");

    for (int i = 0; i < num_pins; i++) {
        char pin[PIN_LEN + 1];
        char validation_data[VALIDATION_DATA_LEN + 1];
        char offset[OFFSET_LEN + 1];

        generate_random_pin(pin);
        compute_reference_data(pin, validation_data, offset);

        int attempts = run_attack_for_pin(pin, validation_data, offset, mode, max_attempts);
        printf("%s,%d,%d\n", pin, attempts, mode);
    }

    return 0;
}
