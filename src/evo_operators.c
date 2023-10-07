#include "evo_operators.h"
#include "evo_utils.h"

#include "assert.h"
#include "float.h"
#include "math.h"
#include "stdio.h"

// We only want to select a subset of the population for reproduction.
// We do this by multiplying the current population size by
// the selection quota and rounding up.
// Note: We also move up to the closest even number, for now.
static unsigned TournamentSelectionNumSelections(unsigned num_actors,
                                                 float selection_quota) {
  assert(0.0 < selection_quota && selection_quota < 1.0);
  unsigned num_selections = ceilf(num_actors * selection_quota);
  num_selections =
      (num_selections % 2 == 0) ? num_selections : num_selections + 1;
  return num_selections;
}

void TournamentSelection(ActorArray arena_A, ActorArray arena_B,
                         unsigned tournament_size, float quota) {
  unsigned selection_size = TournamentSelectionNumSelections(arena_A.len, quota);
  ActorArray selected = ActorArrayCreate(selection_size);

  unsigned num_selected = 0;
  while (num_selected < selection_size) {
    Actor *winner = NULL;
    for (unsigned i = 0; i < tournament_size; ++i) {
      size_t index = randRange(0, arena_A.len - 1);
      printf("index %zu\n", index);
      Actor *actor = ActorArrayAccess(arena_A, index);

      if (actor->status == EVO_STATUS_TOURNAMENT ||
          actor->status == EVO_STATUS_TOURNAMENT_SELECTED) {
        printf("Actor tournament|selected -> same\n");
        continue;
      }

      if (actor->status == EVO_STATUS_CLEAR) {
        printf("Actor clear -> tournament\n");
        actor->status = EVO_STATUS_TOURNAMENT;
      } else if (actor->status == EVO_STATUS_SELECTED) {
        printf("Actor selected -> tournament_selected\n");
        actor->status = EVO_STATUS_TOURNAMENT_SELECTED;
      }

      if (winner == NULL || actor->fitness < winner->fitness) {
        printf("This should only happen three times\n"); // it's not
        winner = actor;
      }
    }

    if (winner->status == EVO_STATUS_TOURNAMENT) {
      winner->status = EVO_STATUS_SELECTED;
      ActorArrayPushBack(&arena_B, winner);
      ++num_selected;
      printf("num_selected: %d\n", num_selected);
    }
    ActorArrayClearStatusesPreserveSelected(arena_A);
  }
  assert(arena_B.len == num_selected &&
         "Failed to select the requested number of Actors.");
}

void ReproductionFixedOffspringCount(ActorArray arena_A, ActorArray arena_B,
                                     unsigned num_offspring) {
  unsigned generation_len =
      arena_B.len + ((unsigned)ceil(arena_B.len / 2.0) * num_offspring);
  (void)generation_len;
}
