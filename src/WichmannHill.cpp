#include <Rcpp.h>
#include <thread>

#define i2_32m1 2.328306437080797e-10
namespace Random {

template <int N = 3> class WichmannHill {
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
    i_seed[0] = i_seed[0] % 30269;
    i_seed[1] = i_seed[1] % 30307;
    i_seed[2] = i_seed[2] % 30323;

    /* map values equal to 0 mod modulus to 1. */
    if (i_seed[0] == 0)
      i_seed[0] = 1;
    if (i_seed[1] == 0)
      i_seed[1] = 1;
    if (i_seed[2] == 0)
      i_seed[2] = 1;
  }

public:
  WichmannHill(int seed) {
    int scrambled_seed = init_scrambling(seed);
    rng_init(scrambled_seed);
    fixup_seeds();
  }

  double runif() {
    i_seed[0] = i_seed[0] * 171 % 30269;
    i_seed[1] = i_seed[1] * 172 % 30307;
    i_seed[2] = i_seed[2] * 170 % 30323;
    double value =
        i_seed[0] / 30269.0 + i_seed[1] / 30307.0 + i_seed[2] / 30323.0;
    return fixup(value - (int)value); /* in [0,1) */
  }
};

} // namespace Random

// [[Rcpp::export]]
Rcpp::NumericVector unif_wh_cpp(unsigned int seed, unsigned int n) {
  Rcpp::NumericVector v(n);
  Random::WichmannHill mt(seed);
  for (unsigned int i = 0; i < n; i++) {
    v[i] = mt.runif();
  }
  return v;
}

void gen_rand(double *data, size_t n, Random::WichmannHill<3> &mt) {
  for (size_t i = 0; i < n; i++) {
    data[i] = mt.runif();
  }
}
