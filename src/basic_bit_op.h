#include <stdbool.h>
#include <stdint.h>

void set_bit(uint8_t *val, int pos);
void clear_bit(uint8_t *val, int pos);
void toggle_bit(uint8_t *val, int pos);
bool is_bit_set(uint8_t val, int pos);
int count_set_bits(uint8_t val);
