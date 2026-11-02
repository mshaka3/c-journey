#include "basic_bit_op.h"
#include <stdbool.h>
#include <stdint.h>

void set_bit(uint8_t *val, int pos) { *val |= 1 << pos; }
void clear_bit(uint8_t *val, int pos) { *val &= ~(1 << pos); }
void toggle_bit(uint8_t *val, int pos) { *val ^= (1 << pos); }
bool is_bit_set(uint8_t val, int pos) {
  uint8_t value = val;
  value |= (1 << pos);
  return value == val;
}

int count_set_bits(uint8_t val) {
  int count = 0;
  while (val != 1) {
    val = (val >> 1);
    count++;
  }
  return count;
}
