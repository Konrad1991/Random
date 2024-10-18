#include "Rcpp.h"
#include "RunifInternal_C.hpp"

#ifndef MERSENNETWISTER_H
#define MERSENNETWISTER_H

namespace RNG_C {
void rng_init(MersenneTwister *mt, int seed);
void fixup_seeds(MersenneTwister *mt);
MersenneTwister mersenne_twister(int seed);
} // namespace RNG_C

#endif // !#ifndef MERSENNETWISTER_H
