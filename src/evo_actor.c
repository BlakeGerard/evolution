#include "evo_actor.h"

#include "math.h"
#include "stdio.h"

void ActorPrint(const Actor* act) {
  printf("Actor {\n");
  GenotypePrint(&act->g);
  PhenotypePrint(&act->p);
  printf("Fitness: %.3f\n", act->fitness);
  printf("Age: %d\n", act->age);
  printf("Status: %d\n", act->status);
  printf("}\n\n");
}

void ActorInitialize(Actor* act) {
  GenotypeInitialize(&act->g);
  PhenotypeInitialize(&act->p, &act->g);
  act->fitness = 0;
  act->age = 0;
  act->status = EVO_STATUS_CLEAR;
}

float ActorResponse(const Actor* act, float x) {
  float response = act->p.p0 * x + act->p.p1;
  return response;
}

void ActorFitness(Actor* act, const Phenotype* env, size_t env_len) {
  act->fitness = 0;
  for (size_t i = 0; i < env_len; ++i) {
    float response = ActorResponse(act, env[i].p0); 
    act->fitness += pow((env[i].p1 - response), 2);
  }
}
