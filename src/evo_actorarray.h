#ifndef EVO_ACTORARRAY_H
#define EVO_ACTORARRAY_H

#include "evo_actor.h"

typedef struct {
  Actor* buf;
  unsigned len;
  unsigned cap;
} ActorArray;

// General utilities 
ActorArray ActorArrayCreate(unsigned capacity);
void ActorArrayResize(ActorArray* arr, unsigned new_capacity);
void ActorArrayCopyTo(const ActorArray src, ActorArray* dst);
Actor* ActorArrayAccess(const ActorArray arr, unsigned index);
Actor* ActorArrayPushBack(ActorArray* arr, const Actor* act);
void ActorArrayReset(ActorArray* arr);
void ActorArrayFree(ActorArray* arr);

// Algorithms
void ActorArrayShuffle(ActorArray arr);
void ActorArraySwapActors(ActorArray arr, unsigned i, unsigned j);

void ActorArrayInitializeToCapacity(ActorArray* arr);
void ActorArrayPrint(const ActorArray arr);
void ActorArrayClearStatusesPreserveSelected(const ActorArray arr);
void ActorArrayEvaluateActors(const ActorArray arr, const Phenotype* env, unsigned env_len);

void ActorArrayPrintFitnessStatistics(const ActorArray arr);

void PrintActorArrayMetrics();

#endif
