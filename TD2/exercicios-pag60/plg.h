#ifndef PLG_H
#define PLG_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void* pesquisa_linear_generica(void* base, size_t n, size_t tamanho_elemento, void* chave, int (*cmp)(const void*, const void*));

// Declaração inline para evitar duplicação

static inline int compara_int(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

#endif