#ifndef EVO_OPERATORS_H
#define EVO_OPERATORS_H

#include "evo_actorarray.h"

ActorArray TournamentSelection(const ActorArray actors, unsigned tournament_size, float quota);
void ReproductionFixedOffspringCount(ActorArray* actors, ActorArray selected,
                                     unsigned num_offspring);

#endif
