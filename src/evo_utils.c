#include "evo_utils.h"

#include "stdlib.h"

bool randProb(float probability) {
  return ((double)rand() / RAND_MAX) <= probability;
}

// Random integer in the range [min, max]
int randRange(int min, int max) {
  return min + rand() % (max + 1 - min);
}
