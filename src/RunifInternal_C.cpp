#include "RunifInternal_C.hpp"

namespace RNG_C {

// Initializing the array with a seed
void MT_sgenrand(unsigned int *mt, int seed, int *mti) {
  int i;
  for (i = 0; i < N; i++) {
    mt[i] = seed & 0xffff0000;
    seed = 69069 * seed + 1;
    mt[i] |= (seed & 0xffff0000) >> 16;
    seed = 69069 * seed + 1;
  }
  *mti = N;
}

// Initialization by "sgenrand()" is an example.Theoretically,
//     there are 2 ^
//         19937 - 1 possible states as an initial state.Essential bits in
//                 "seed_array[]" is following 19937 bits
//     : (seed_array[0] & UPPER_MASK),
//     seed_array[1], ...,
//     seed_array[N - 1].(seed_array[0] & LOWER_MASK) is
//     discarded.Theoretically, (seed_array[0] & UPPER_MASK), seed_array[1],
//     ..., seed_array[N - 1] can take any values except all zeros.
double MT_genrand(MersenneTwister *MT) {
  unsigned int y;
  unsigned int *mt = MT->i_seed + 1;
  static unsigned int mag01[2] = {0x0, MATRIX_A};
  int mti = N + 1;
  mti = MT->i_seed[0];

  if (mti >= N) { // generate N words at one time
    int kk;

    if (mti == N + 1) {
      MT_sgenrand(mt, 4357, &mti);
    }
    for (kk = 0; kk < N - M; kk++) {
      y = (mt[kk] & UPPER_MASK) | (mt[kk + 1] & LOWER_MASK);
      mt[kk] = mt[kk + M] ^ (y >> 1) ^ mag01[y & 0x1];
    }
    for (; kk < N - 1; kk++) {
      y = (mt[kk] & UPPER_MASK) | (mt[kk + 1] & LOWER_MASK);
      mt[kk] = mt[kk + (M - N)] ^ (y >> 1) ^ mag01[y & 0x1];
    }
    y = (mt[N - 1] & UPPER_MASK) | (mt[0] & LOWER_MASK);
    mt[N - 1] = mt[M - 1] ^ (y >> 1) ^ mag01[y & 0x1];

    mti = 0;
  }

  y = mt[mti++];
  y ^= TEMPERING_SHIFT_U(y);
  y ^= TEMPERING_SHIFT_S(y) & TEMPERING_MASK_B;
  y ^= TEMPERING_SHIFT_T(y) & TEMPERING_MASK_C;
  y ^= TEMPERING_SHIFT_L(y);
  MT->i_seed[0] = mti;

  return ((double)y * 2.3283064365386963e-10); /* reals: [0,1)-interval */
}

}; // namespace RNG_C
