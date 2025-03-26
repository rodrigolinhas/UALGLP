#include <stdio.h>

int* retorna_ponteiro() {
    int x = 10; // Variável local (alocada na stack)
    return &x;  // Retorna endereço de uma variável que será destruída
}

int main(void) {
    int* y = retorna_ponteiro(); // y é um "dangling pointer"
    printf("Endereço retornado: %p\n", (void*)y); // Imprime o endereço (ainda válido)
    printf("Valor de y: %d\n", *y); // Comportamento indefinido: valor corrupto ou crash
    return 0;
}