#ifndef EVO_PHENOTYPE_H
#define EVO_PHENOTYPE_H

#include "evo_genotype.h"

typedef struct {
  float p0, p1;
} Phenotype;

void PhenotypeMapFromGenotype(Phenotype* p, const Genotype* g);
void PhenotypeInitialize(Phenotype* p, const Genotype* g);
void PhenotypePrint(const Phenotype* p);

#endif
