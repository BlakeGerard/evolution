#ifndef EVO_GENOTYPE_H
#define EVO_GENOTYPE_H

#include "stdint.h"

#define EVO_BYTE_SIZE 8
#define EVO_GENOTYPE_CHROMOSOME_BYTES 8
#define EVO_GENOTYPE_MUTATION_INTENSITY 0.02
#define EVO_GENOTYPE_CROSSOVER_RATE 0.01

#define EVO_GENOTYPE_CHROMOSOME_BITS()                                          \
  (EVO_GENOTYPE_CHROMOSOME_BYTES * EVO_BYTE_SIZE)

typedef struct {
  uint8_t buf_[EVO_GENOTYPE_CHROMOSOME_BYTES];
} Genotype;

void GenotypeInitialize(Genotype *g);
void GenotypeMutate(Genotype *g, float probability);
void GenotypeCrossover(Genotype *g, float probability);
void GenotypeRecombine(Genotype *g);
void GenotypePrint(const Genotype *g);

#endif
