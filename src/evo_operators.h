#ifndef EVO_OPERATORS_H
#define EVO_OPERATORS_H

#include "evo_actorarray.h"
#include "evo_environment_array.h"

void EvaluateActors(ActorArray arr, const EnvironmentArray env);

void TournamentSelection(const ActorArray arena_A, ActorArray* arena_B,
                         unsigned tournament_size, float quota);

void ReproductionFixedOffspringCount(ActorArray* arena_A,
                                     const ActorArray arena_B,
                                     unsigned num_offspring);

#endif
