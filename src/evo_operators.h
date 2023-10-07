#ifndef EVO_OPERATORS_H
#define EVO_OPERATORS_H

#include "evo_actorarray.h"

void TournamentSelection(ActorArray arena_A, ActorArray arena_B,
                         unsigned tournament_size, float quota);
void ReproductionFixedOffspringCount(ActorArray arena_A, ActorArray arena_B,
                                     unsigned num_offspring);

#endif
