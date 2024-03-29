#include "evo_operators.h"
#include "evo_utils.h"

#include "assert.h"
#include "float.h"
#include "math.h"
#include "stdio.h"

void EvaluateActors(ActorArray arr, const EnvironmentArray env) {
  for (unsigned i = 0; i < arr.len; ++i) {
    Actor* act = ActorArrayAccess(arr, i);
    act->fitness = 0;
    for (unsigned e = 0; e < env.len; ++e) {
      const Sample* sample = EnvironmentArrayAccess(env, e);
      float response = ActorResponse(act, sample->x);
      act->fitness += pow((sample->y - response), 2);
    }
  }
}

static void TournamentSelectionClearStatuses(ActorArray arr) {
  for (unsigned i = 0; i < arr.len; ++i)
    ActorArrayAccess(arr, i)->status = EVO_STATUS_CLEAR;
}

// Reset statuses before a running a selection tournament.
// EVO_STATUS_CLEAR and EVO_STATUS_SELECTED remain the same.
// EVO_STATUS_TOURNAMENT maps to EVO_STATUS_CLEAR.
// EVO_STATUS_TOURNAMENT_SELECTED maps to EVO_STATUS_SELECTED.
static void TournamentSelectionUpdateStatuses(ActorArray arr) {
  for (unsigned i = 0; i < arr.len; ++i) {
    Actor* act = ActorArrayAccess(arr, i);
    if (act->status == EVO_STATUS_TOURNAMENT)
      act->status = EVO_STATUS_CLEAR;
    else if (act->status == EVO_STATUS_TOURNAMENT_SELECTED)
      act->status = EVO_STATUS_SELECTED;
  }
}

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

static Actor* TournamentSelectionRunTournament(ActorArray arena_A,
                                               unsigned tournament_size) {
  assert(tournament_size >= 1 && "We can't run a size zero tournament.\n");
  Actor* winner = NULL;
  for (unsigned i = 0; i < tournament_size; ++i) {
    size_t index = randRange(0, arena_A.len - 1);
    Actor* actor = ActorArrayAccess(arena_A, index);

    // printf("Rolled index %zu\n", index);
    if (actor->status == EVO_STATUS_TOURNAMENT ||
        actor->status == EVO_STATUS_TOURNAMENT_SELECTED) {
      // printf("Actor tournament|selected -> same\n");
      continue;
    }

    if (actor->status == EVO_STATUS_CLEAR) {
      // printf("Actor clear -> tournament\n");
      actor->status = EVO_STATUS_TOURNAMENT;
    } else if (actor->status == EVO_STATUS_SELECTED) {
      // printf("Actor selected -> tournament_selected\n");
      actor->status = EVO_STATUS_TOURNAMENT_SELECTED;
    }

    if (winner == NULL || actor->fitness < winner->fitness) {
      // printf("Current winner at index %zu\n", index);
      winner = actor;
    }
  }
  return winner;
}

void TournamentSelection(ActorArray arena_A, ActorArray* arena_B,
                         unsigned tournament_size, float quota) {
  unsigned num_selections =
      TournamentSelectionNumSelections(arena_A.len, quota);

  if (arena_A.len < num_selections) {
    printf("We have fewer actors (%d) than the selection quota (%d)\n",
           arena_A.len, num_selections);
    return;
  }

  assert(num_selections < arena_B->cap);
  TournamentSelectionClearStatuses(arena_A);
  ActorArrayReset(arena_B);

  unsigned num_tournaments = 0;
  unsigned times_winner_already_selected = 0;
  unsigned num_selected = 0;
  while (num_selected < num_selections) {
    Actor* winner = TournamentSelectionRunTournament(arena_A, tournament_size);
    ++num_tournaments;

    if (winner->status == EVO_STATUS_TOURNAMENT) {
      // printf("Made a selection.\n");

      winner->status = EVO_STATUS_SELECTED;
      ActorArrayPushBack(arena_B, winner);
      ++num_selected;
    } else {
      ++times_winner_already_selected;
      // printf("Winner was already selected\n");
    }
    TournamentSelectionUpdateStatuses(arena_A);
    // printf("============\n");
  }
  printf("We ran %u tournaments to selected %u actors\n", num_tournaments,
         num_selected);
  printf("A tournament was won by an already selected actor %u times\n",
         times_winner_already_selected);
}

#define EVO_MUTATE_PROB 0.5
Actor MateActors(const Actor* f, const Actor* m) {
  Actor c;

  c.m = (f->m + m->m) / 2;
  c.b = (f->b + m->b) / 2;

  // Mutate
  if (randProb(EVO_MUTATE_PROB)) {
    c.m += randFloat(-2.0, 2.0);
    c.b += randFloat(-2.0, 2.0);
  }
  return c;
}

void ReproductionFixedOffspringCount(ActorArray* arena_A,
                                     const ActorArray arena_B,
                                     unsigned num_offspring) {
  unsigned generation_len =
      arena_B.len + ((unsigned)ceil(arena_B.len / 2.0) * num_offspring);

  assert(generation_len < arena_A->cap);
  assert(arena_B.len % 2 == 0 && "Only working with evens for now\n");
  ActorArrayReset(arena_A);

  for (unsigned i = 0, j = 1; i < arena_B.len - 1 && j < arena_B.len;
       i += 2, j += 2) {
    const Actor* f = ActorArrayAccess(arena_B, i);
    const Actor* m = ActorArrayAccess(arena_B, j);

    ActorArrayPushBack(arena_A, f);
    ActorArrayPushBack(arena_A, m);
    for (unsigned k = 0; k < num_offspring; ++k) {
      Actor c = MateActors(f, m);
      ActorArrayPushBack(arena_A, &c);
    }
  }
}
