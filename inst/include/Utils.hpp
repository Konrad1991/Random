#include <stdbool.h>
#include <stdio.h>
#include <time.h>

#ifndef UTILS_H
#define UTILS_H

namespace Random {
#define N 624
#define i2_32m1 2.328306437080797e-10

typedef struct {
  unsigned int i_seed[N + 1];
  int mti;
  int n_seed;
  bool initial;
} MersenneTwister;

double fixup(double obj);
int init_scrambling(int seed);

} // namespace Random
#endif
