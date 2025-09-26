#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "wug.h"

void test_create_wug() {
    printf("--- Teste Q1: create_wug ---\n");
    int genome_A[16] = {1, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 1, 1, 0, 0};
    gender_t gender_A = M;

    // AC'C#o: Cria o wug
    wug_t* wug_A = create_wug(genome_A, gender_A);

    // VerificaC'C#o: Checa alocaC'C#o, gC*nero e um valor de genoma
    if (wug_A != NULL && wug_A->gender == M && wug_A->genome[0] == 1 && wug_A->genome[1] == 0) {
        printf("PASS: Wug criado e dados inicializados corretamente.\n");
    } else {
        printf("FAIL: Falha na criaC'C#o/inicializaC'C#o do Wug.\n");
    }

    // C	 crucial liberar a memC3ria!
    free(wug_A);
    printf("--------------------------\n\n");
}

int main() {
    test_create_wug();
    return 0;
}
