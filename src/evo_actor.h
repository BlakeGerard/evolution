#ifndef EVO_ACTOR_H
#define EVO_ACTOR_H

#include "evo_phenotype.h"

#include "stddef.h"

typedef enum {
  EVO_STATUS_CLEAR = 0,
  EVO_STATUS_TOURNAMENT = 1,
  EVO_STATUS_SELECTED = 2,
  EVO_STATUS_TOURNAMENT_SELECTED = 3,
} ActorStatus;

typedef struct {
  Genotype g;
  Phenotype p;
  int age;
  float fitness;
  ActorStatus status;
} Actor;

void ActorPrint(const Actor* act);
void ActorInitialize(Actor* act);

float ActorResponse(const Actor* act, float x);
void ActorFitness(Actor* act, const Phenotype* env, size_t env_len);

#endif
