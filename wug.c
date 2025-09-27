#include "wug.h"
#include <stdlib.h> 
#include <string.h> 
#include <stdio.h> 
#include <stdint.h>
#include <stdbool.h>


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



void genome2features(const int genome[16], int features[4]) {
  
  const int SUPER_GENOME[16] = {1, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 1, 1, 0, 0};
  

  const int ZONES[4][4] = {
    {0, 2, 7, 14}, // InteligC*ncia
    {1, 6, 9, 10}, // Beleza
    {3, 8, 12, 15},// ForC'a
    {4, 5, 11, 13} // Velocidade
  };

  for (int c = 0; c < 4; c++) { 
    features[c] = 1; 
    
    for (int g = 0; g < 4; g++) { 
      int gene_pos = ZONES[c][g];
      
      if (genome[gene_pos] != SUPER_GENOME[gene_pos]) {
        features[c] = 0; 
        break; 
      }
    }
  }
}



int rank(const wug_t* w) {
  int features[4];
  
  
  genome2features(w->genome, features); 

  int rank_count = 0;
  for (int i = 0; i < 4; i++) {
    if (features[i] == 1) {
      rank_count++;
    }
  }

  return rank_count;
}



bool insert_ranked(wug_t** population, wug_t* w, int* size, int capacity) {
  int wug_rank = rank(w);
  
  
  if (*size == capacity) {
    int last_wug_rank = rank(population[*size - 1]);

    if (wug_rank <= last_wug_rank) {
      return false; // Wug ignorado
    }
    
    
    free(population[*size - 1]);
    (*size)--; 
  }

  
  int i = *size - 1;
  while (i >= 0 && rank(population[i]) < wug_rank) {
    population[i + 1] = population[i];
    i--;
  }

  
  population[i + 1] = w;

  
  (*size)++;

  return true; 
}


void print_wug(wug_t *w) {
  int features[4];
  genome2features(w->genome, features); 
  
  char* genome_str = array_string(w->genome, 16);
  char* features_str = array_string(features, 4);

  
  printf("%c %s %s %d", w->gender, genome_str, features_str, rank(w));

  free(genome_str);
  free(features_str);
}


void print_population(wug_t** population, const int size) {
  printf("PopulaC'C#o Atual (Tamanho: %d):\n", size);
  printf("Ordem | GC*nero | Genoma | Features | Rank\n");
  for (int i = 0; i < size; i++) {
    printf("%4d | %c | ", i, population[i]->gender);
    
    
    int features[4];
    genome2features(population[i]->genome, features); 
    char* genome_str = array_string(population[i]->genome, 16);
    char* features_str = array_string(features, 4);
    
    printf("%s | %s | %d\n", genome_str, features_str, rank(population[i]));
    
    free(genome_str);
    free(features_str);
  }
}



int report_population(wug_t** population, const int size) {
  int super_wug_count = 0;
  int feature_counts[16] = {0}; 

  for (int i = 0; i < size; i++) {
    int features[4];
    genome2features(population[i]->genome, features);
    
    
    uint8_t bits = features2bits(features); 
    feature_counts[bits]++;

    
    if (bits == 15) { 
      super_wug_count++;
    }
  }

  printf("\n-- PadrC5es de CaracterC-sticas na PopulaC'C#o (Report) --\n");
  for (int i = 0; i < 16; i++) {
    if (feature_counts[i] > 0) {
      int features[4];
      bits2features((uint8_t)i, features); 
      
      char* features_str = array_string(features, 4);
      printf("PadrC#o %s: %d wug(s)\n", features_str, feature_counts[i]);
      free(features_str);
    }
  }

  return super_wug_count;
}

