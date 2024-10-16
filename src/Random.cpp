#include "MersenneTwister.hpp"

// basically runif
// [[Rcpp::export]]
Rcpp::NumericVector MT(unsigned int seed, unsigned int n) {
  Random::MersenneTwister mt = Random::mersenne_twister(seed);
  Rcpp::NumericVector v(n);
  for (unsigned int i = 0; i < n; i++) {
    v[i] = Random::fixup(Random::MT_genrand(&mt));
  }
  return v;
}
