#ifndef EVO_UTILS_H
#define EVO_UTILS_H

#include "stdbool.h"

#ifdef DEBUG
#define CHECKED_ACCESS(array, len, index) \
  ((index >= 0 && index < (len)) ? &(array)[index] : NULL
#else
#define CHECKED_ACCESS(array, len, index) \
  &(array)[index]
#endif

bool randProb(float probability);
int randRange(int min, int max);

#endif
