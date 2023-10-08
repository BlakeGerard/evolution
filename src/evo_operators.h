#ifndef EVO_OPERATORS_H
#define EVO_OPERATORS_H

#include "evo_phenotype.h"
#include "evo_actorarray.h"

void EvaluateActors(ActorArray arr, const Phenotype *env, unsigned env_len);

void TournamentSelection(ActorArray arena_A, ActorArray arena_B,
                         unsigned tournament_size, float quota);

void ReproductionFixedOffspringCount(ActorArray arena_A, ActorArray arena_B,
                                     unsigned num_offspring);

#endif
