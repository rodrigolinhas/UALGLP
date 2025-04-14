#include <stdio.h>
#include <stdlib.h>

// Função que aloca memória e imprime Endereco
void aloca_memoria() {
    int *k = malloc(sizeof(int));
    printf("Endereco alocado por aloca_memoria(): %p\n", k);
}

int main(void) {
    int a = 10;
    printf("Endereco de a: %p\n", &a);

    int *i = malloc(sizeof(int));
    (*i) = 55;
    printf("Endereco de i: %p\n", i);

    aloca_memoria();

    return 0;
}