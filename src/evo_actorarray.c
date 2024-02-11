#include "evo_actorarray.h"
#include "evo_utils.h"

#include "assert.h"
#include "math.h" // for sqrt
#include "stdio.h"
#include "stdlib.h"
#include "string.h" // for memcpy

// Internal metrics
static int actor_array_create_count = 0;
static int actor_array_delete_count = 0;
static unsigned long long actor_array_bytes_allocated = 0;
static unsigned long long actor_array_bytes_copied = 0;

ActorArray ActorArrayCreate(unsigned capacity) {
  ActorArray arr;
  arr.buf = (Actor*)malloc(sizeof(Actor) * capacity);
  if (!arr.buf) {
    printf("[%s] Failed to allocate memory for ActorArray.\n", __func__);
    exit(EXIT_FAILURE);
  }
  arr.len = 0;
  arr.cap = capacity;

  actor_array_create_count += 1;
  actor_array_bytes_allocated += sizeof(Actor) * capacity;
  return arr;
}

void ActorArrayFree(ActorArray* arr) {
  free(arr->buf);
  arr->buf = NULL;
  arr->len = 0;
  arr->cap = 0;
  actor_array_delete_count += 1;
}

void ActorArrayInitializeActors(ActorArray* arr, size_t num) {
  assert(num <= arr->cap &&
         "Requested initialization of more actors than the array's capacity.");
  for (size_t i = 0; i < num; ++i) {
    ActorInitializeRandom(ActorArrayAccess(*arr, i));
    arr->len += 1;
  }
}

Actor* ActorArrayAccess(const ActorArray arr, unsigned index) {
  assert(index <= arr.len && "Out-of-bounds access to ActorArray");
  return &arr.buf[index];
}

Actor* ActorArrayPushBack(ActorArray* arr, const Actor* act) {
  assert(arr->len + 1 <= arr->cap &&
         "Attempted to PushBack to full ActorArray.");
  Actor* existing = ActorArrayAccess(*arr, arr->len);
  *existing = *act;
  arr->len += 1;
  return existing;
}

void ActorArrayReset(ActorArray* arr) { arr->len = 0; }

void ActorArrayPrint(const ActorArray arr) {
  printf("---------------\n");
  printf("[len = %u, cap = %u]\n", arr.len, arr.cap);
  for (unsigned i = 0; i < arr.len; ++i)
    ActorPrint(ActorArrayAccess(arr, i));
  printf("---------------\n");
}

void ActorArraySwapActors(ActorArray arr, unsigned i, unsigned j) {
  Actor* act_i = ActorArrayAccess(arr, i);
  Actor* act_j = ActorArrayAccess(arr, j);
  Actor tmp = *act_i;
  *act_i = *act_j;
  *act_j = tmp;
}

void ActorArrayShuffle(ActorArray arr) {
  unsigned n = arr.len;

  if (n == 1)
    return;

  for (unsigned i = 0; i <= n - 2; ++i) {
    unsigned j = randRange(i, n - 1);
    ActorArraySwapActors(arr, i, j);
  }
}

void ActorArrayPrintFitnessStatistics(const ActorArray arr) {
  unsigned count = 0;
  float mean = 0;
  float var = 0;
  for (unsigned i = 0; i < arr.len; ++i) {
    float new_value = ActorArrayAccess(arr, i)->fitness;
    count += 1;
    float d0 = new_value - mean;
    mean += d0 / count;
    float d1 = new_value - mean;
    var += d0 * d1;
  }
  var /= count;
  float stddev = sqrt(var);
  printf("mean, stddev: %.3f, %.3f\n", mean, stddev);
}

void PrintActorArrayMetrics() {
  printf("--- ActorArray Metrics ---\n");
  printf("Arrays created: %d\n", actor_array_create_count);
  printf("Arrays deleted: %d\n", actor_array_delete_count);
  printf("Bytes allocated: %llu\n", actor_array_bytes_allocated);
  printf("Bytes    copied: %llu\n", actor_array_bytes_copied);
  printf("--------------------------\n");
}
