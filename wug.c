#include "wug.h"
#include <stdlib.h> 
#include <string.h> 
#include <stdio.h> 
#include <stdint.h>
#include <stdbool.h>

/*
 * ImplementaC'C#o da QuestC#o 1: Cria e aloca memC3ria para um novo wug.
 */
wug_t* create_wug(int genome[16], gender_t g) {
  wug_t* new_wug = (wug_t*) malloc(sizeof(wug_t));
  if (new_wug == NULL) {
    return NULL; 
  }

  for (int i = 0; i < 16; i++) {
    new_wug->genome[i] = genome[i];
  }

  new_wug->gender = g;

  return new_wug;
}


/*
 * ImplementaC'C#o da QuestC#o 2: Decodifica o genoma para 4 features (0 ou 1).
 */
void genome2features(const int genome[16], int features[4]) {
  // Genoma Superwug: 1011100101001100
  const int SUPER_GENOME[16] = {1, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 1, 1, 0, 0};
  
  // Mapeamento de Zonas: I(0), B(1), F(2), V(3)
  const int ZONES[4][4] = {
    {0, 2, 7, 14}, // InteligC*ncia
    {1, 6, 9, 10}, // Beleza
    {3, 8, 12, 15},// ForC'a
    {4, 5, 11, 13} // Velocidade
  };

  for (int c = 0; c < 4; c++) { 
    features[c] = 1; // Assume excepcional (1) inicialmente
    
    for (int g = 0; g < 4; g++) { 
      int gene_pos = ZONES[c][g];
      
      if (genome[gene_pos] != SUPER_GENOME[gene_pos]) {
        features[c] = 0; 
        break; 
      }
    }
  }
}


/*
 * ImplementaC'C#o da QuestC#o 3: Calcula o rank do wug (nC:mero de caracterC-sticas excepcionais).
 */
int rank(const wug_t* w) {
  int features[4];
  
  // Depende da Q2
  genome2features(w->genome, features); 

  int rank_count = 0;
  for (int i = 0; i < 4; i++) {
    if (features[i] == 1) {
      rank_count++;
    }
  }

  return rank_count;
}


/*
 * ImplementaC'C#o da QuestC#o 4: Insere um wug na populaC'C#o (stub temporC!rio).
 */
bool insert_ranked(wug_t** population, wug_t* w, int* size, int capacity) {
    // CC3digo virC! aqui quando Q4 for implementada
    return false;
}

/*
 * ImplementaC'C#o da QuestC#o 5: Imprime os dados de um wug (stub temporC!rio).
 */
void print_wug(wug_t *w) {
    // CC3digo virC! aqui quando Q5 for implementada
}

/*
 * ImplementaC'C#o da QuestC#o 5: Imprime toda a populaC'C#o (stub temporC!rio).
 */
void print_population(wug_t** population, const int size) {
    // CC3digo virC! aqui quando Q5 for implementada
}

/*
 * ImplementaC'C#o da QuestC#o 6: Conta os padrC5es de features e o nC:mero de superwugs (stub temporC!rio).
 */
int report_population(wug_t** population, const int size) {
    // CC3digo virC! aqui quando Q6 for implementada
    return 0;
}
