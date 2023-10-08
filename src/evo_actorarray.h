#ifndef EVO_ACTORARRAY_H
#define EVO_ACTORARRAY_H

#include "evo_actor.h"

typedef struct {
  Actor* buf;
  unsigned len;
  unsigned cap;
} ActorArray;

// Create an empty ActorArray with given capacity.
// Memory is uninitialized.
ActorArray ActorArrayCreate(unsigned capacity);

// Free the underlying memory, set its pointer to NULL, and zero
// out len and cap.
void ActorArrayFree(ActorArray* arr);

// Initialize num Actors in the ActorArray and set
// the ActorArray::len equal to num. A pointer to the memory
// space of each Actor is passed to ActorInitialize()
void ActorArrayInitializeActors(ActorArray* arr, size_t num);

// Get pointer to Actor at the given index.
// index must be <= ActorArray::len.
Actor* ActorArrayAccess(const ActorArray arr, unsigned index);

// Copy the contents at the given Actor* to the back of the ActorArray
Actor* ActorArrayPushBack(ActorArray* arr, const Actor* act);

// Set the ActorArray::len to zero. The underlying memory is untouched.
void ActorArrayReset(ActorArray* arr);

// Print the ActorArray to the stdout.
void ActorArrayPrint(const ActorArray arr);

// Swap the Actors at the given indices.
void ActorArraySwapActors(ActorArray arr, unsigned i, unsigned j);

// Shuffle the array in-place.
void ActorArrayShuffle(ActorArray arr);

// Internal metrics
void ActorArrayPrintFitnessStatistics(const ActorArray arr);
void PrintActorArrayMetrics();

#endif
