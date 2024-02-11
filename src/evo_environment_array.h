#ifndef EVO_ENVIRONMENT_ARRAY_H
#define EVO_ENVIRONMENT_ARRAY_H

typedef struct {
  float x;
  float y;
} Sample;

typedef struct {
  Sample* buf;
  unsigned len;
  unsigned cap;
} EnvironmentArray;

EnvironmentArray EnvironmentArrayCreate(unsigned capacity);

void EnvironmentArrayFree(EnvironmentArray* arr);

const Sample* EnvironmentArrayAccess(const EnvironmentArray arr,
                                     unsigned index);

Sample* EnvironmentArrayMutAccess(const EnvironmentArray arr, unsigned index);

void EnvironmentArrayAdd(EnvironmentArray* arr, float x, float y);

#endif
