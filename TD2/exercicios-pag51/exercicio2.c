#include <stdio.h>
#include <stdlib.h>

int* pesquisa_linear_multipla(int arr[], int tamanho, int chave, int *num_ocorrencias) {
    int *indices = malloc(tamanho * sizeof(int)); // Aloca memória para o pior caso
    *num_ocorrencias = 0;

    for (int i = 0; i < tamanho; i++) {
        if (arr[i] == chave) {
            indices[*num_ocorrencias] = i; // Armazena o índice
            (*num_ocorrencias)++; // Incrementa o contador de ocorrências
        }
    }

    if (*num_ocorrencias == 0) { // Se nenhuma ocorrência foi encontrada
        free(indices);
        return NULL;
    }

    return indices; // Retorna o array de índices
}

int main(void) {
    int numeros[] = {10, 30, 20, 30, 40, 30};
    int chave = 30;
    int tamanho = sizeof(numeros) / sizeof(numeros[0]);
    int num_ocorrencias;

    int *indices = pesquisa_linear_multipla(numeros, tamanho, chave, &num_ocorrencias);

    if (indices != NULL) {
        printf("Índices encontrados: ");
        for (int i = 0; i < num_ocorrencias; i++) {
            printf("%d ", indices[i]);
        }
        printf("\n");
        free(indices); // Libera a memória alocada
    } else {
        printf("Nenhuma ocorrência encontrada.\n");
    }

    return 0;
}