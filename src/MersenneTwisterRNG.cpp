#include <Rcpp.h>

#define i2_32m1 2.328306437080797e-10
#define M 397
#define MATRIX_A 0x9908b0df   /* constant vector a */
#define UPPER_MASK 0x80000000 /* most significant w-r bits */
#define LOWER_MASK 0x7fffffff /* least significant r bits */

// Tempering parameters
#define TEMPERING_MASK_B 0x9d2c5680
#define TEMPERING_MASK_C 0xefc60000
#define TEMPERING_SHIFT_U(y) (y >> 11)
#define TEMPERING_SHIFT_S(y) (y << 7)
#define TEMPERING_SHIFT_T(y) (y << 15)
#define TEMPERING_SHIFT_L(y) (y >> 18)

namespace Random {

template <int N = 624> class MersenneTwisterRNG {
private:
  unsigned int i_seed[N + 1];
  int mti;
  bool initial;

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

  void rng_init(int seed) {
    for (size_t i = 0; i <= N; i++) {
      seed = seed * 69069 + 1;
      i_seed[i] = seed;
    }
  }

  void fixup_seeds() {
    if (initial) {
      i_seed[0] = 624;
      initial = false;
    }
    if (i_seed[0] <= 0) {
      i_seed[0] = 624;
    }
    bool all_zero = true;
    for (size_t i = 1; i <= N; i++) {
      if (i_seed[i] != 0) {
        all_zero = false;
        break;
      }
    }
    if (all_zero) {
      int new_seed = (int)time(NULL);
      rng_init(new_seed);
    }
  }

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

  double MT_genrand() {
    unsigned int y;
    unsigned int *mt = i_seed + 1;
    static unsigned int mag01[2] = {0x0, MATRIX_A};
    int mti = N + 1;
    mti = i_seed[0];

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
    i_seed[0] = mti;

    return ((double)y * 2.3283064365386963e-10); /* reals: [0,1)-interval */
  }

public:
  MersenneTwisterRNG(int seed) : initial(true), mti(0) {
    int scrambled_seed = init_scrambling(seed);
    rng_init(scrambled_seed);
    fixup_seeds();
  }

  double runif() { return fixup(MT_genrand()); }
};

} // namespace Random

// [[Rcpp::export]]
Rcpp::NumericVector MT_CPP(unsigned int seed, unsigned int n) {
  Random::MersenneTwisterRNG mt(seed);
  Rcpp::NumericVector v(n);
  for (unsigned int i = 0; i < n; i++) {
    v[i] = mt.runif();
  }
  return v;
}
