#include "genrand.h"
#include "utils.h"

void rng_init(MersenneTwister *mt, int seed) {
  for (size_t i = 0; i <= N; i++) {
    seed = seed * 69069 + 1;
    mt->i_seed[i] = seed;
  }
}

void fixup_seeds(MersenneTwister *mt) {
  if (mt->initial) {
    mt->i_seed[0] = 624;
    mt->initial = false;
  }
  if (mt->i_seed[0] <= 0) {
    mt->i_seed[0] = 624;
  }
  bool all_zero = true;
  for (size_t i = 1; i <= N; i++) {
    if (mt->i_seed[i] != 0) {
      all_zero = false;
      break;
    }
  }
  if (all_zero) {
    int new_seed = (int)time(NULL);
    rng_init(mt, new_seed);
  }
}

MersenneTwister mersenne_twister(int seed) {
  MersenneTwister mt;
  mt.initial = true;
  int scrambled_seed = init_scrambling(seed);
  rng_init(&mt, scrambled_seed);
  fixup_seeds(&mt);
  return mt;
}

double runif(MersenneTwister *mt) { return fixup(MT_genrand(mt)); }

void write_ints_to_file(MersenneTwister *mt, char *filename) {
  FILE *f = fopen(filename, "w");
  for (int i = 0; i < 625; i++) {
    fprintf(f, "%d\n", mt->i_seed[i]);
  }
  fclose(f);
}

void write_doubles_to_file(double *data, int length, char *filename) {
  FILE *f = fopen(filename, "w");
  for (int i = 0; i < length; i++) {
    fprintf(f, "%f\n", data[i]);
  }
  fclose(f);
}

int main() {
  MersenneTwister mt = mersenne_twister(1234);
  double *random_numbers = (double *)malloc(1000 * sizeof(double));
  for (int i = 0; i < 1000; i++) {
    random_numbers[i] = runif(&mt);
  }
  write_doubles_to_file(random_numbers, 1000, "random_numbers.txt");
  free(random_numbers);
}
