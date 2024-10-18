#include "MersenneTwister_C.hpp"

// basically runif
// [[Rcpp::export]]
Rcpp::NumericVector unif_mt_c(unsigned int seed, unsigned int n) {
  RNG_C::MersenneTwister mt = RNG_C::mersenne_twister(seed);
  Rcpp::NumericVector v(n);
  for (unsigned int i = 0; i < n; i++) {
    v[i] = RNG_C::fixup(RNG_C::MT_genrand(&mt));
  }
  return v;
}
