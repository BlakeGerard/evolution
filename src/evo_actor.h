#ifndef EVO_ACTOR_H
#define EVO_ACTOR_H

#include "stddef.h"

typedef enum {
  EVO_STATUS_CLEAR = 0,
  EVO_STATUS_TOURNAMENT = 1,
  EVO_STATUS_SELECTED = 2,
  EVO_STATUS_TOURNAMENT_SELECTED = 3,
} ActorStatus;

typedef struct {
  float m;
  float b;
  float fitness;
  ActorStatus status;
} Actor;

void ActorPrint(const Actor* act);
void ActorInitializeRandom(Actor* act);
float ActorResponse(const Actor* act, float x);

#endif
