#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "plg.h"

int compara_string(const void *a, const void *b) {
    return strcmp(*(const char**)a, *(const char**)b);
}

int main(void) {
    char *nomes[] = {"Ana", "Carlos", "Pedro", "Zacarias"};
    char *chave = "Pedro";
    int tamanho = sizeof(nomes)/sizeof(nomes[0]);

    // Pesquisa binária
    char **resultado = bsearch(&chave, nomes, tamanho, sizeof(char*),compara_string);
    if(resultado)
        printf("Binária: Encontrado %s\n", *resultado);
    else
        printf("Binária: Não encontrado\n");

    // Pesquisa linear
    resultado = pesquisa_linear_generica(nomes, tamanho, sizeof(char*), &chave, compara_string);    
    if(resultado)
        printf("Linear: Encontrado %s\n", *resultado);
    else
        printf("Linear: Não encontrado\n");

    return 0;
}