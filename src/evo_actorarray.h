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
Actor* ActorArrayAccess(const ActorArray arr, unsigned index);
Actor* ActorArrayPushBack(ActorArray* arr, const Actor* act);
void ActorArrayReset(ActorArray* arr);
void ActorArrayFree(ActorArray* arr);

// Algorithms
void ActorArrayShuffle(ActorArray arr);
void ActorArraySwapActors(ActorArray arr, unsigned i, unsigned j);

void ActorArrayInitializeActors(ActorArray* arr, size_t num);
void ActorArrayPrint(const ActorArray arr);
void ActorArrayClearStatusesPreserveSelected(const ActorArray arr);
void ActorArrayEvaluateActors(const ActorArray arr, const Phenotype* env, unsigned env_len);

void ActorArrayPrintFitnessStatistics(const ActorArray arr);

void PrintActorArrayMetrics();

#endif
