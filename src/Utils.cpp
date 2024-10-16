#include "Utils.hpp"

namespace Random {

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
} // namespace Random
