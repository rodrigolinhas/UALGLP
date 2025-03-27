#include <stdio.h>

int* retorna_ponteiro() {
    int p = 10; // Variável local (alocada na stack)
    return &p; // Retorna o endereço da variável local
}

int main(void) {
    int* p = retorna_ponteiro();            // p é um "dangling pointer"
    printf("Endereço retornado: %p\n", p); 
    printf("Valor de p: %d\n", *p);       // Comportamento indefinido: valor corrupto ou crash
                                         // A variável local p foi desalocada da stack
    return 0;
}