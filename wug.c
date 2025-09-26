#include "wug.h"
#include <stdlib.h>
#include <string.h>

wug_t* create_wug(int genome[16], gender_t g) {
  // Aloca memC3ria para a estrutura wug_t
  wug_t* new_wug = (wug_t*) malloc(sizeof(wug_t));
  if (new_wug == NULL) {
    return NULL; // Retorna NULL em caso de falha na alocaC'C#o
  }

  // Copia os 16 genes do genoma
  for (int i = 0; i < 16; i++) {
    new_wug->genome[i] = genome[i];
  }

  // Define o gC*nero do wug
  new_wug->gender = g;

  return new_wug;
}

