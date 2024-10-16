#include <stdbool.h>
#include <stdio.h>
#include <time.h>

#ifndef UTILS_H
#define UTILS_H

#define i2_32m1 2.328306437080797e-10

double fixup(double obj) {
  if (obj == 0.0) {
    return 0.5 * i2_32m1;
  }
  if ((1.0 - obj) <= 0.0) {
    return 1.0 - 0.5 * i2_32m1;
  }
  return obj;
}

int init_scrambling(int seed) {
  for (int i = 0; i < 50; i++) {
    seed = seed * 69069 + 1;
  }
  return seed;
}

#endif
