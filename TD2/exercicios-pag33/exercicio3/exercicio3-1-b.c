#include <stdio.h>

void funcao_recursao_infinita(int n) {
    int x; // Variável local na stack
    printf("Chamada %d - Endereço de x: %p\n", n, (void *)&x);
    funcao_recursao_infinita(n + 1); // Chamada recursiva infinita
}

int main() {
    funcao_recursao_infinita(1);
    return 0;
}