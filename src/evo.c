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

#define EVO_N_ITERS 1
#define EVO_N_ACTORS 1
#define EVO_SELECTION_QUOTA 0.5
#define EVO_TOURNAMENT_SIZE 3
#define EVO_REPRODUCTION_FIXED 2
#define EVO_ACTOR_MAX_AGE 100

static void reproduction(ActorArray* actors, ActorArray selected) {
  ReproductionFixedOffspringCount(actors, selected, EVO_REPRODUCTION_FIXED);
}

static ActorArray selection(const ActorArray actors, float selection_quota) {
  return TournamentSelection(actors, EVO_TOURNAMENT_SIZE, selection_quota);
}

static void evaluation(const ActorArray actors, const Phenotype* env, unsigned env_len) {
  ActorArrayEvaluateActors(actors, env, env_len);
}

static void evolution(const Phenotype* env, unsigned env_len, unsigned iters) {
  ActorArray actors = ActorArrayCreate(EVO_N_ACTORS);
  ActorArrayInitializeToCapacity(&actors);
  
  for (unsigned iter = 0; iter < iters; ++iter) {
    evaluation(actors, env, env_len);

    ActorArrayPrint(actors);

    ActorArrayPrintFitnessStatistics(actors);

    //    ActorArray selected = selection(actors, EVO_SELECTION_QUOTA);

    //    reproduction(&actors, selected);

    // ActorArrayFree(&selected);
  }

  printf("Final cohort:\n");
  evaluation(actors, env, env_len);
  ActorArrayPrintFitnessStatistics(actors);
  ActorArrayFree(&actors);
}

// ---------------------- 
//  main 
// ----------------------

int main(int argc, char *argv[]) {
  srand(time(0));
  (void) argc;
  (void) argv;

  // y = mx + b
  Phenotype env[6] = {{0, 0},
                      {1, 2},
                      {2, 4},
                      {3, 6},
                      {4, 8},
                      {5, 10}};

  clock_t start = clock();
  evolution(env, 6, EVO_N_ITERS);
  clock_t end = clock();
  double elapsed = (end-start)/(double)CLOCKS_PER_SEC;
  printf("Evolution time: %f\n", elapsed);

  PrintActorArrayMetrics();

  return 0;
}
