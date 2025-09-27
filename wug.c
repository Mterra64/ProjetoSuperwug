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
 * ImplementaC'C#o da QuestC#o 4: Adiciona um wug C  populaC'C#o, mantendo a ordem (rank decrescente)
 * e respeitando a capacidade mC!xima.
 */
bool insert_ranked(wug_t** population, wug_t* w, int* size, int capacity) {
  int wug_rank = rank(w);
  
  // 1. Caso de exclusC#o: Se a populaC'C#o estiver cheia,
  // verifica se o novo wug nC#o tem rank suficiente.
  if (*size == capacity) {
    int last_wug_rank = rank(population[*size - 1]);
    // Se o rank do novo wug C) menor ou igual ao C:ltimo, C) ignorado.
    if (wug_rank <= last_wug_rank) {
      return false; // Wug ignorado
    }
    
    // Libera a memC3ria do wug de menor rank que serC! substituC-do.
    free(population[*size - 1]);
    (*size)--; // Reduz o tamanho temporariamente para a inserC'C#o
  }

  // 2. Encontra a posiC'C#o correta (busca o primeiro wug com rank menor)
  int i = *size - 1;
  while (i >= 0 && rank(population[i]) < wug_rank) {
    // Move o wug atual para a direita para abrir espaC'o
    population[i + 1] = population[i];
    i--;
  }

  // 3. Insere o novo wug na posiC'C#o encontrada
  population[i + 1] = w;

  // 4. Atualiza o tamanho
  (*size)++;

  return true; // Wug inserido
}

/*
 * ImplementaC'C#o da QuestC#o 5: Imprime os dados de um wug.
 */
void print_wug(wug_t *w) {
  int features[4];
  genome2features(w->genome, features); 
  
  char* genome_str = array_string(w->genome, 16);
  char* features_str = array_string(features, 4);

  // Exemplo de impressC#o do wug
  printf("%c %s %s %d", w->gender, genome_str, features_str, rank(w));

  free(genome_str);
  free(features_str);
}

/*
 * ImplementaC'C#o da QuestC#o 5: Imprime todos os wugs da populaC'C#o em ordem.
 */
void print_population(wug_t** population, const int size) {
  printf("PopulaC'C#o Atual (Tamanho: %d):\n", size);
  printf("Ordem | GC*nero | Genoma | Features | Rank\n");
  for (int i = 0; i < size; i++) {
    printf("%4d | %c | ", i, population[i]->gender);
    
    // Obtenha os dados para impressC#o em coluna
    int features[4];
    genome2features(population[i]->genome, features); 
    char* genome_str = array_string(population[i]->genome, 16);
    char* features_str = array_string(features, 4);
    
    printf("%s | %s | %d\n", genome_str, features_str, rank(population[i]));
    
    free(genome_str);
    free(features_str);
  }
}


/*
 * ImplementaC'C#o da QuestC#o 6: Conta os padrC5es de features e o nC:mero de superwugs.
 */
int report_population(wug_t** population, const int size) {
  int super_wug_count = 0;
  // Array para contar a frequC*ncia de cada um dos 16 padrC5es de features (2^4 = 16)
  int feature_counts[16] = {0}; 

  for (int i = 0; i < size; i++) {
    int features[4];
    genome2features(population[i]->genome, features);
    
    // Converte o array de features em um C:nico valor (0 a 15) para indexar a contagem
    uint8_t bits = features2bits(features); 
    feature_counts[bits]++;

    // Verifica se C) um superwug (todas as features = 1)
    if (bits == 15) { // 15 em decimal C) 1111 em binC!rio
      super_wug_count++;
    }
  }

  printf("\n-- PadrC5es de CaracterC-sticas na PopulaC'C#o (Report) --\n");
  for (int i = 0; i < 16; i++) {
    if (feature_counts[i] > 0) {
      int features[4];
      // Converte o C-ndice de volta para o array de features para a impressC#o
      bits2features((uint8_t)i, features); 
      
      char* features_str = array_string(features, 4);
      printf("PadrC#o %s: %d wug(s)\n", features_str, feature_counts[i]);
      free(features_str);
    }
  }

  return super_wug_count;
}

