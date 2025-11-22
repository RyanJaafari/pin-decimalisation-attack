#ifndef PIN_H
#define PIN_H

#define PIN_LEN 4
#define VALIDATION_DATA_LEN 16
#define OFFSET_LEN PIN_LEN

void generate_random_pin(char pin[PIN_LEN + 1]);
void compute_reference_data(const char pin[PIN_LEN + 1],
                            char validation_data[VALIDATION_DATA_LEN + 1],
                            char offset[OFFSET_LEN + 1]);

#endif
