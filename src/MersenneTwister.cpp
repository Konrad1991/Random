#include "MersenneTwister.hpp"

namespace Random {

void rng_init(MersenneTwister *mt, int seed) {
  for (size_t i = 0; i <= N; i++) {
    seed = seed * 69069 + 1;
    mt->i_seed[i] = seed;
  }
}

void fixup_seeds(MersenneTwister *mt) {
  if (mt->initial) {
    mt->i_seed[0] = 624;
    mt->initial = false;
  }
  if (mt->i_seed[0] <= 0) {
    mt->i_seed[0] = 624;
  }
  bool all_zero = true;
  for (size_t i = 1; i <= N; i++) {
    if (mt->i_seed[i] != 0) {
      all_zero = false;
      break;
    }
  }
  if (all_zero) {
    int new_seed = (int)time(NULL);
    rng_init(mt, new_seed);
  }
}

MersenneTwister mersenne_twister(int seed) {
  MersenneTwister mt;
  mt.initial = true;
  int scrambled_seed = init_scrambling(seed);
  rng_init(&mt, scrambled_seed);
  fixup_seeds(&mt);
  return mt;
}

} // namespace Random
