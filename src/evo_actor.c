#include "evo_actor.h"
#include "evo_utils.h"

#include "math.h"
#include "stdio.h"

void ActorPrint(const Actor* act) {
  printf("Actor {\n");
  printf("m: %.3f\n", act->m);
  printf("b: %.3f\n", act->b);
  printf("Fitness: %.3f\n", act->fitness);
  printf("Status: %d\n", act->status);
  printf("}\n");
}

void ActorInitializeRandom(Actor* act) {
  act->m = (float)randRange(0, 10);
  act->b = (float)randRange(0, 10);
  act->fitness = 0;
  act->status = EVO_STATUS_CLEAR;
}

float ActorResponse(const Actor* act, float x) {
  float response = act->m * x + act->b;
  return response;
}
