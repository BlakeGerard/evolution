#include "evo_environment_array.h"

#include "assert.h"
#include "stdio.h"
#include "stdlib.h"

EnvironmentArray EnvironmentArrayCreate(unsigned capacity) {
  EnvironmentArray arr;
  arr.buf = (Sample*)malloc(sizeof(Sample) * capacity);

  if (!arr.buf) {
    printf("[%s] Failed to allocate memory for EnvironmentArray.\n", __func__);
    exit(EXIT_FAILURE);
  }
  arr.len = 0;
  arr.cap = capacity;
  return arr;
};

void EnvironmentArrayFree(EnvironmentArray* arr) {
  assert(arr->buf && "Attempted to free an uninitialized EnvironmentArray.");
  free(arr->buf);
  arr->buf = NULL;
  arr->len = 0;
  arr->cap = 0;
}

const Sample* EnvironmentArrayAccess(const EnvironmentArray arr,
                                     unsigned index) {
  assert(index <= arr.cap && "Access outside of EnvironmentArray capacity.");
  return &arr.buf[index];
}

Sample* EnvironmentArrayMutAccess(const EnvironmentArray arr, unsigned index) {
  assert(index <= arr.cap && "Access outside of EnvironmentArray capacity.");
  return &arr.buf[index];
}

void EnvironmentArrayAdd(EnvironmentArray* arr, float x, float y) {
  if (arr->len + 1 > arr->cap)
    return;
  Sample* sample = EnvironmentArrayMutAccess(*arr, arr->len);
  sample->x = x;
  sample->y = y;
  arr->len += 1;
}
