#include "Rcpp.h"
#include "RunifInternal.hpp"

#ifndef MERSENNETWISTER_H
#define MERSENNETWISTER_H

namespace Random {
void rng_init(MersenneTwister *mt, int seed);
void fixup_seeds(MersenneTwister *mt);
MersenneTwister mersenne_twister(int seed);
} // namespace Random

#endif // !#ifndef MERSENNETWISTER_H
