/*
Em vez de implementar manualmente a função de pesquisa binária, podemos usar
bsearch() de <stdlib.h>
*/

#include <stdio.h>
#include <stdlib.h>

int compara_int(const void* a, const void* b) {return (*(int*)a - *(int*)b);}

int main() {
    int numeros[] = {10, 20, 30, 40, 50};
    int chave = 30;
    int tamanho = sizeof(numeros) / sizeof(numeros[0]);
    int* resultado = (int*)bsearch(&chave, numeros, tamanho, sizeof(int), compara_int);
    if (resultado) printf("Elemento encontrado: %d\n", *resultado);
    else printf("Elemento não encontrado\n");
    return 0;
}