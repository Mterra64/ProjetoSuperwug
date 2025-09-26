#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "data.h"
#include "util.h" 
#include "wug.h" 

// ProtC3tipos das funC'C5es de teste
void test_create_wug();
void test_rank_and_features();

int main() {
    printf("--- Iniciando Testes do Projeto Superwug ---\n\n");
    
    test_create_wug(); // Testa Q1
    test_rank_and_features(); // Testa Q2 e Q3
    
    printf("\n--- Testes ConcluC-dos ---\n");
    return 0;
}

// ----------------------------------------------------
// Teste da QuestC#o 1: create_wug
// ----------------------------------------------------
void test_create_wug() {
    printf("--- Teste Q1: create_wug ---\n");
    
    // Genoma de teste: 1011100101001100
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


// ----------------------------------------------------
// Teste das QuestC5es 2 e 3: genome2features e rank
// ----------------------------------------------------
void test_rank_and_features() {
    printf("--- Teste Q2 e Q3: genome2features e rank ---\n");
    
    // Cenario 1: O Superwug (Rank Esperado: 4)
    int super_genome[16] = {1, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 1, 1, 0, 0};
    wug_t* super_wug = create_wug(super_genome, M);
    int features_S[4];
    
    genome2features(super_wug->genome, features_S);
    int rank_S = rank(super_wug);
    
    // VerificaC'C#o do Superwug:
    char* features_S_str = array_string(features_S, 4);
    if (rank_S == 4) {
        printf("PASS: Superwug. Rank %d. Features: %s\n", rank_S, features_S_str);
    } else {
        printf("FAIL: Superwug. Rank esperado 4, Obtido %d. Features: %s\n", rank_S, features_S_str);
    }
    free(features_S_str);

    // Cenario 2: O Wug X (Rank Esperado: 1)
    int genome_X[16] = {0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1};
    wug_t* wug_X = create_wug(genome_X, F);
    int features_X[4];
    
    genome2features(wug_X->genome, features_X);
    int rank_X = rank(wug_X);
    
    // VerificaC'C#o do Wug X:
    char* features_X_str = array_string(features_X, 4);
    if (rank_X == 1) {
        printf("PASS: Wug X. Rank %d. Features: %s\n", rank_X, features_X_str);
    } else {
        printf("FAIL: Wug X. Rank esperado 1, Obtido %d. Features: %s\n", rank_X, features_X_str);
    }
    free(features_X_str);

    // Limpeza Final
    free(super_wug);
    free(wug_X);
    printf("--------------------------------------------\n\n");
}
