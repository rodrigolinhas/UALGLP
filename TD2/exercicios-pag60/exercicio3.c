#include <stdio.h>
#include <stdlib.h>
#include "dynvec_search.h"
#include "plg.h"

int main(void) {
    dynvec *dv = dynvec_create(sizeof(int));
    int valores[] = {10, 20, 30, 40, 50};
    
    for(int i = 0; i < 5; i++)
        dynvec_push(dv, &valores[i]);

    int chave = 30;
    
    // Pesquisa linear
    int *resultado = dynvec_lsearch(dv, &chave, compara_int);
    
    // Pesquisa binária (requer vetor ordenado)
    qsort(dv->data, dv->length, dv->elem_size, compara_int);
    resultado = dynvec_bsearch(dv, &chave, compara_int);
    
    if(resultado)
        printf("Valor encontrado: %d\n", *resultado);
    
    dynvec_free(dv);
    return 0;
}