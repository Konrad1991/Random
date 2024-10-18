#include <Rcpp.h>

#define i2_32m1 2.328306437080797e-10
namespace Random {

template <int N = 2> class MarsagliaMultiCarry {
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
    if (i_seed[1] == 0)
      i_seed[1] = 1;
  }

public:
  MarsagliaMultiCarry(int seed) {
    int scrambled_seed = init_scrambling(seed);
    rng_init(scrambled_seed);
    fixup_seeds();
  }

  double runif() {
    i_seed[0] = 36969 * (i_seed[0] & 0177777) + (i_seed[0] >> 16);
    i_seed[1] = 18000 * (i_seed[1] & 0177777) + (i_seed[1] >> 16);
    return fixup(((i_seed[0] << 16) ^ (i_seed[1] & 0177777)) *
                 i2_32m1); /* in [0,1) */
  }
};

} // namespace Random

// [[Rcpp::export]]
Rcpp::NumericVector unif_mmc_cpp(unsigned int seed, unsigned int n) {
  Rcpp::NumericVector v(n);
  Random::MarsagliaMultiCarry mt(seed);
  for (unsigned int i = 0; i < n; i++) {
    v[i] = mt.runif();
  }
  return v;
}
