#include "basic_bit_op.h"
#include <stdbool.h>
#include <stdio.h>

void test_basic_bit_op() {
  uint8_t val = 2;
  set_bit(&val, 0);

  if (val != 3) {
    fprintf(stderr, "expected 3 got%d", val);
    return;
  }

  val = 3;
  // test val: 00000011
  // expected val: 00000010
  clear_bit(&val, 0);
  if (val != 2) {
    fprintf(stderr, "expected 2 got: %d", val);
    return;
  }

  val = 4;
  // test val: 00000100
  // expected val: 00000101
  toggle_bit(&val, 0);
  if (val != 5) {
    fprintf(stderr, "expected 5 got: %d", val);
    return;
  }

  // test val: 00000100
  bool result = is_bit_set(4, 2);
  if (result == 0) {
    fprintf(stderr, "expected true got: %d\n", result);
    return;
  }

  int countSetBits = count_set_bits(14);
  printf("%d", countSetBits);
  if (countSetBits != 3) {
    fprintf(stderr, "expected 3 got: %d\n", countSetBits);
    return;
  }
}

int main() { test_basic_bit_op(); }
