#include "evo_genotype.h"
#include "evo_utils.h"

#include "assert.h"
#include "stddef.h"
#include "stdio.h"
#include "stdlib.h"

void GenotypeInitialize(Genotype *g) {
  for (size_t i = 0; i < EVO_GENOTYPE_CHROMOSOME_BYTES; ++i)
    g->buf_[i] = rand(); // int truncated.
}

void GenotypeMutate(Genotype *g, float intensity) {
  unsigned num_mutations_ub = EVO_GENOTYPE_CHROMOSOME_BITS() * intensity;
  unsigned num_mutations = randRange(0, num_mutations_ub);

  printf("mutations ub:  %u\n", num_mutations_ub);
  printf("num mutations: %u\n", num_mutations);
  
  for (unsigned m = 0; m < num_mutations; ++m) {
    size_t mutation_segment_index = randRange(0, EVO_GENOTYPE_CHROMOSOME_BYTES);
    uint8_t mutation_point_index = randRange(0, EVO_BYTE_SIZE);

    uint8_t* mutation_segment = &g->buf_[mutation_segment_index];
    uint8_t mask = (uint8_t)1 << mutation_point_index;

    (*mutation_segment) ^= mask;
  }
}

void GenotypeCrossover(Genotype *g, float probability) {

}

void GenotypeRecombine(Genotype* g) {
  GenotypeMutate(g, EVO_GENOTYPE_MUTATION_INTENSITY);
  GenotypeCrossover(g, EVO_GENOTYPE_CROSSOVER_RATE);
}

void GenotypePrint(const Genotype *g) {
  printf("Genotype { ");
  for (size_t i = 0; i < EVO_GENOTYPE_CHROMOSOME_BYTES; ++i) {
    printf("%3d ", g->buf_[i]);
  }
  printf("}\n");
}
