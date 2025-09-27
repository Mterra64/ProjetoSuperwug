#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include "data.h"
#include "util.h" 
#include "wug.h" 

wug_t* create_wug(const int genome[16], gender_t g);
void genome2features(const int genome[16], int features[4]);
int rank(const wug_t* w);
bool insert_ranked(wug_t** population, wug_t* w, int* size, int capacity);
void print_wug(wug_t *w);
void print_population(wug_t** population, const int size);
int report_population(wug_t** population, const int size);

void test_create_wug();
void test_rank_and_features();
void test_population_management(); 

int main() {
    printf("--- Iniciando Testes do Projeto Superwug ---\n\n");
    
   
    test_create_wug(); 
    test_rank_and_features();
    
    // Testa Q4, Q5 e Q6 (O desafio final dos 10 wugs)
    test_population_management();
    
    printf("\n--- Testes ConcluC-dos ---\n");
    return 0;
}

void test_create_wug() {
    printf("--- Teste Q1: create_wug ---\n");
    
    int genome_A[16] = {1, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 1, 1, 0, 0};
    gender_t gender_A = M;

    wug_t* wug_A = create_wug(genome_A, gender_A);
    
    char* genome_str = array_string(wug_A->genome, 16);
    printf("Wug Criado: GC*nero [%c], Genoma %s\n", wug_A->gender, genome_str);
    free(genome_str);

    if (wug_A != NULL && wug_A->gender == M && wug_A->genome[0] == 1 && wug_A->genome[1] == 0) {
        printf("PASS: Wug criado e dados inicializados corretamente.\n");
    } else {
        printf("FAIL: Falha na criaC'C#o/inicializaC'C#o do Wug.\n");
    }

    free(wug_A);
    printf("--------------------------\n\n");
}


void test_rank_and_features() {
    printf("--- Teste Q2 e Q3: genome2features e rank ---\n");
    
    int super_genome[16] = {1, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 1, 1, 0, 0};
    wug_t* super_wug = create_wug(super_genome, M);
    int features_S[4];
    
    genome2features(super_wug->genome, features_S);
    int rank_S = rank(super_wug);
    
    char* features_S_str = array_string(features_S, 4);
    if (rank_S == 4) {
        printf("PASS: Superwug. Rank %d. Features: %s\n", rank_S, features_S_str);
    } else {
        printf("FAIL: Superwug. Rank esperado 4, Obtido %d. Features: %s\n", rank_S, features_S_str);
    }
    free(features_S_str);

    int genome_X[16] = {0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1};
    wug_t* wug_X = create_wug(genome_X, F);
    int features_X[4];
    
    genome2features(wug_X->genome, features_X);
    int rank_X = rank(wug_X);
    
    char* features_X_str = array_string(features_X, 4);
    if (rank_X == 1) {
        printf("PASS: Wug X. Rank %d. Features: %s\n", rank_X, features_X_str);
    } else {
        printf("FAIL: Wug X. Rank esperado 1, Obtido %d. Features: %s\n", rank_X, features_X_str);
    }
    free(features_X_str);

    free(super_wug);
    free(wug_X);
    printf("--------------------------------------------\n\n");
}


void test_population_management() {
    printf("## Teste Q4, Q5 e Q6: Gerenciamento de PopulaC'C#o (10 Wugs, Capacidade 5)\n");
    
    const int CAPACITY = 5; 
    wug_t* population[CAPACITY]; 
    int size = 0;
    int i; 

    const int genome_R4[16] = {1, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 1, 1, 0, 0}; 
    const int genome_R2[16] = {1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0}; 
    const int genome_R1[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; 
    const int genome_R0[16] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}; 
    
    wug_t* wugs_to_insert[10];

    printf("--- CenC!rio de Teste: Capacidade = %d ---\n", CAPACITY);

    wugs_to_insert[0] = create_wug(genome_R2, M);
    wugs_to_insert[1] = create_wug(genome_R4, F);
    wugs_to_insert[2] = create_wug(genome_R2, M);
    wugs_to_insert[3] = create_wug(genome_R1, F);
    wugs_to_insert[4] = create_wug(genome_R4, M);
    wugs_to_insert[5] = create_wug(genome_R0, M);
    wugs_to_insert[6] = create_wug(genome_R2, M);
    wugs_to_insert[7] = create_wug(genome_R4, F);
    wugs_to_insert[8] = create_wug(genome_R1, M);
    wugs_to_insert[9] = create_wug(genome_R2, F);




    for (i = 0; i < 10; i++) {
    bool inserted = insert_ranked(population, wugs_to_insert[i], &size, CAPACITY);
    printf("Tentativa %d (Rank %d): %s\n", 
           i + 1, rank(wugs_to_insert[i]), inserted ? "INSERIDO" : "IGNORADO");
    if (!inserted) {
        free(wugs_to_insert[i]);
    }
}


printf("\n--- PopulaC'C#o Final (Q5: Ordenada por Rank) ---\n");
print_population(population, size);

int super_wugs = report_population(population, size);

printf("\nTotal de Superwugs Retornado (Q6): %d\n", super_wugs);


if (size == CAPACITY && super_wugs == 3) {
    printf("PASS: Gerenciamento de PopulaC'C#o (Q4, Q5, Q6) realizado com sucesso.\n");
} else {
    printf("FAIL: Erro no gerenciamento da PopulaC'C#o. Tamanho: %d, Superwugs: %d.\n", size, super_wugs);
}


for (i = 0; i < size; i++) {
    free(population[i]); 
}
printf("MemC3ria da populaC'C#o final liberada.\n");
printf("----------------------------------------\n");

} 
