#include <stdio.h>

void funcao_stack_overflow(int n) {
    int t[10000]; // Vetor grande na stack
    printf("Chamada %d - Endereço de t: %p\n", n, (void *)&t);
    funcao_stack_overflow(n + 1); // Chamada recursiva sem condição de parada
}

int main() {
    funcao_stack_overflow(1);
    return 0;
}