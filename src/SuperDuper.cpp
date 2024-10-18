#include <Rcpp.h>

#define i2_32m1 2.328306437080797e-10
namespace Random {

template <int N = 2> class SuperDuper {
private:
  unsigned int i_seed[N];

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
    for (size_t i = 0; i < N; i++) {
      seed = seed * 69069 + 1;
      i_seed[i] = seed;
    }
  }

  void fixup_seeds() {
    if (i_seed[0] == 0)
      i_seed[0] = 1;
    /* I2 = Congruential: must be ODD */
    i_seed[1] |= 1;
  }

public:
  SuperDuper(int seed) {
    int scrambled_seed = init_scrambling(seed);
    rng_init(scrambled_seed);
    fixup_seeds();
  }

  double runif() {
    i_seed[0] ^= ((i_seed[0] >> 15) & 0377777); /* Tausworthe */
    i_seed[0] ^= i_seed[0] << 17;
    i_seed[1] *= 69069;                              /* Congruential */
    return fixup((i_seed[0] ^ i_seed[1]) * i2_32m1); /* in [0,1) */
  }
};

} // namespace Random

// [[Rcpp::export]]
Rcpp::NumericVector unif_sd_cpp(unsigned int seed, unsigned int n) {
  Rcpp::NumericVector v(n);
  Random::SuperDuper rng(seed);
  for (unsigned int i = 0; i < n; i++) {
    v[i] = rng.runif();
  }
  return v;
}
