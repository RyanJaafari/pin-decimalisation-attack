#ifndef ATTACK_H
#define ATTACK_H

#include "pin.h"

/* mode: 0 = vulnerable, 1 = fixed-table, 2 = integrity-bound (simulated)
   max_attempts: cap on number of tries
   returns: attempts used, or -1 if failed within max_attempts */
int run_attack_for_pin(const char true_pin[PIN_LEN + 1],
                       const char validation_data[VALIDATION_DATA_LEN + 1],
                       const char offset[OFFSET_LEN + 1],
                       int mode,
                       int max_attempts);

#endif
