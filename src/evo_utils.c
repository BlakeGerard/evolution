#include "evo_utils.h"

#include "stdlib.h"

bool randProb(float probability) {
  return ((double)rand() / (RAND_MAX + 1.0)) <= probability;
}

// Random integer in the range [min, max]
int randRange(int min, int max) { return min + rand() % (max + 1 - min); }

float randFloat(float min, float max) {
  return min + (rand() / (float)RAND_MAX) * (max - min);
}
