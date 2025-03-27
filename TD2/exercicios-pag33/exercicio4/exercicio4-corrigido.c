#include <stdio.h>
#include <stdlib.h>

int* retorna_ponteiro() {
    int* p = malloc(sizeof(int)); // Aloca memória na heap (aponta para a heap)
    (*p) = 33;
    return p;
}

int main(void) {
    int* p = retorna_ponteiro();
    printf("Endereco de p: %p\n", p);
    printf("Valor de p: %d\n", (*p));
    return 0;
}