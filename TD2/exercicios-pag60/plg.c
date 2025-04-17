#include <stdio.h>
#include <string.h>
#include "plg.h"

void* pesquisa_linear_generica(void* base, size_t n, size_t tamanho_elemento, void* chave, int (*cmp)(const void*, const void*)) {
    for (size_t i = 0; i < n; i++) {
        void* elemento = (char*)base + i * tamanho_elemento;
        if (cmp(elemento, chave) == 0) return elemento;
    }
    return NULL;
}

//int compara_int(const void* a, const void* b)   {return (*(int*)a - *(int*)b);}

/*int main() {
    int numeros[] = {10, 20, 30, 40, 50};
    int chave = 30;
    int tamanho = sizeof(numeros) / sizeof(numeros[0]);
    int* resultado = (int*)pesquisa_linear_generica(numeros, tamanho, sizeof(int), &chave, compara_int);
    if (resultado) printf("Elemento encontrado: %d\n", *resultado);
    else printf("Elemento não encontrado\n");
    return 0;
}*/