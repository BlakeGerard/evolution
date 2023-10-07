#include "evo.h"

#include "assert.h"
#include "float.h"
#include "inttypes.h"
#include "math.h"
#include "stdbool.h"
#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"

#define EVO_START_ACTORS 1
#define EVO_MAX_ACTORS 100

#define EVO_N_ITERS 0
#define EVO_SELECTION_QUOTA 0.5
#define EVO_TOURNAMENT_SIZE 3
#define EVO_REPRODUCTION_FIXED 2
#define EVO_ACTOR_MAX_AGE 100

static void reproduction(ActorArray arena_A, ActorArray arena_B) {
  ReproductionFixedOffspringCount(arena_A, arena_B, EVO_REPRODUCTION_FIXED);
}

static void selection(const ActorArray arena_A, ActorArray arena_B,
                      float selection_quota) {
  return TournamentSelection(arena_A, arena_B, EVO_TOURNAMENT_SIZE,
                             selection_quota);
}

static void evaluation(ActorArray arena, const Phenotype *env,
                       unsigned env_len) {
  ActorArrayEvaluateActors(arena, env, env_len);
}

static void evolution(const Phenotype *env, unsigned env_len, unsigned iters) {
  ActorArray arena_A = ActorArrayCreate(EVO_MAX_ACTORS);
  ActorArray arena_B = ActorArrayCreate(EVO_MAX_ACTORS);

  ActorArrayInitializeActors(&arena_A, EVO_START_ACTORS);

  ActorArrayPrint(arena_A);

  for (unsigned iter = 0; iter < iters; ++iter) {
    evaluation(arena_A, env, env_len);

    ActorArrayPrint(arena_A);

    ActorArrayPrintFitnessStatistics(arena_A);

    //    selection(arena_A, arena_B, EVO_SELECTION_QUOTA);

    //    reproduction(arena_A, arena_B);
  }

  printf("Final cohort:\n");
  evaluation(arena_A, env, env_len);
  ActorArrayPrintFitnessStatistics(arena_A);

  ActorArrayFree(&arena_A);
  ActorArrayFree(&arena_B);
}

// ----------------------
//  main
// ----------------------

int main(int argc, char *argv[]) {
  srand(time(0));
  (void)argc;
  (void)argv;

  // y = mx + b
  Phenotype env[6] = {{0, 0}, {1, 2}, {2, 4}, {3, 6}, {4, 8}, {5, 10}};

  clock_t start = clock();
  evolution(env, 6, EVO_N_ITERS);
  clock_t end = clock();
  double elapsed = (end - start) / (double)CLOCKS_PER_SEC;
  printf("Evolution time: %f\n", elapsed);

  PrintActorArrayMetrics();

  return 0;
}
