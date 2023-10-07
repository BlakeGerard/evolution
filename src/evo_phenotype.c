#include "evo_phenotype.h"

#include "stdio.h"

void PhenotypeMapFromGenotype(Phenotype* p, const Genotype* g) {
  p->p0 = (float)(g->buf_[2]);
  p->p1 = (float)(g->buf_[6]);
}

void PhenotypeInitialize(Phenotype* p, Genotype* g) {
  GenotypeRecombine(g);
  PhenotypeMapFromGenotype(p, g);
}

void PhenotypePrint(const Phenotype* p) {
  printf("Phenotype {\n");
  printf("  p0: %.3f\n", p->p0);
  printf("  p1: %.3f\n", p->p1);
  printf("}\n");
}
