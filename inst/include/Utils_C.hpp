#include <time.h>

#ifndef UTILS_H
#define UTILS_H

namespace RNG_C {
#define N 624
#define i2_32m1 2.328306437080797e-10

typedef struct {
  unsigned int i_seed[N + 1];
  int mti;
  bool initial;
} MersenneTwister;

double fixup(double obj);
int init_scrambling(int seed);

} // namespace RNG_C
#endif
