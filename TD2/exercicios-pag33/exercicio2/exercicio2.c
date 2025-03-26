#include <stdio.h>
#include <stdlib.h>

// Função que aloca memória na heap e retorna o ponteiro
int* aloca_memoria() {
    int *ptr = (int*)malloc(sizeof(int));
    *ptr = 30;
    return ptr;
}

int main() {
    // 1. Declara variavel local na stack e imprime seu Endereco
    int a = 10;
    printf("Endereco da variavel local: %p\n", (void*)&a);

    // 2. Aloca inteiro na heap, atribui valor e imprime Endereco
    int *ptr_heap = (int*)malloc(sizeof(int));
    *ptr_heap = 20;
    printf("Endereco do inteiro alocado na heap: %p\n", (void*)ptr_heap);

    // 3. Chama função que aloca memória e compara Enderecos
    int *ptr_func = aloca_memoria();
    printf("Endereco alocado por aloca_memoria(): %p\n", (void*)ptr_func);

    // Observação: Enderecos da heap são consistentemente diferentes da stack
    // Libera memória alocada para evitar vazamentos
    free(ptr_heap);
    free(ptr_func);

    return 0;
}