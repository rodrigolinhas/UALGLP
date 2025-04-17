#include <stdio.h>

int pesquisa_linear(int arr[], int tamanho, int chave, int *comparacoes) {
    *comparacoes = 0; // Inicializa o contador
    for (int i = 0; i < tamanho; i++) {
        (*comparacoes)++; // Conta cada comparação
        if (arr[i] == chave) {
            return i; // Retorna o índice do elemento encontrado
        }
    }
    return -1; // Elemento não encontrado
}

int main(void) {
    int numeros[] = {10, 20, 30, 40, 50};
    int chave = 30;
    int tamanho = sizeof(numeros) / sizeof(numeros[0]);
    int comparacoes;

    int resultado = pesquisa_linear(numeros, tamanho, chave, &comparacoes);

    if (resultado != -1) {
        printf("Elemento encontrado no índice %d\n", resultado);
        printf("Comparações realizadas: %d\n", comparacoes);
    } else {
        printf("Elemento não encontrado\n");
    }

    return 0;
}
