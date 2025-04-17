// O(1) - Melhor caso
// O(n) - Pior caso e Caso médio

#include <stdio.h>
// arr: vector dos elementos
// tamanho: numero dos elementos no vector arr
// chave: o valor por procurar no vector arr
int pesquisa_linear(int arr[], int tamanho, int chave) {
// para todos os elementos arr[i] de arr,
// do primeiro ao último, verificar se
// arr[i] é igual a chave
    for (int i = 0; i < tamanho; i++) {
        if (arr[i] == chave)
            return i; // Retorna o índice do elemento encontrado
    }
    return -1; // Retorna -1 se não encontrar
}

int main(void) {
    int numeros[] = {10, 20, 30, 40, 50};
    int chave = 30;
    int tamanho = sizeof(numeros) / sizeof(numeros[0]);
    int resultado = pesquisa_linear(numeros, tamanho, chave);
    if (resultado != -1)
        printf("Elemento encontrado no índice %d\n", resultado);
    else printf("Elemento não encontrado\n");
    return 0;
}