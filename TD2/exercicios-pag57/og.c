// O(1) - Melhor caso
// O(log n) - Pior caso
// O(1) - Espaço adicional

#include <stdio.h>

int pesquisa_binaria(int arr[], int esquerda, int direita, int chave) {
    while (esquerda <= direita) {
        // calcular o indice no meio, a média, sem ariscar
        // um integer overflow!
        int meio = esquerda + (direita - esquerda) / 2;
        if (arr[meio] == chave) return meio; // encontramos!
        if (arr[meio] < chave) esquerda = meio + 1;
                                    // ajustar o intervalo,
                                    // olhando para a direita
        else direita = meio - 1;    // ajustar o intervalo,
                                    // olhando para a esquerda
    }
    return -1;
}
int main() {
    int numeros[] = {10, 20, 30, 40, 50, 60, 70};
    int chave = 30;
    int tamanho = sizeof(numeros) / sizeof(numeros[0]);
    int resultado = pesquisa_binaria(numeros, 0, tamanho - 1, chave);
    if (resultado != -1)
        printf("Elemento encontrado no índice %d\n", resultado);
    else printf("Elemento não encontrado\n");
    return 0;
}