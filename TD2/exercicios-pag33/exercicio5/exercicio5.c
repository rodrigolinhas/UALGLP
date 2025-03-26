#include <stdio.h>
#include <stdlib.h>

int main(void) {
    //stack
    int x = 10; 
    int y = 20;
    int z = 30;
    printf("Endereco de x (stack): %p\n", (void *)&x);
    printf("Endereco de y (stack): %p\n", (void *)&y);
    printf("Endereco de z (stack): %p\n", (void *)&z);
    //heap
    int* a = malloc(sizeof(int));
    int* b = malloc(sizeof(int));
    int* c = malloc(sizeof(int)); 
    printf("Endereco de x (heap): %p\n", (void *)a);
    printf("Endereco de y (heap): %p\n", (void *)b);
    printf("Endereco de z (heap): %p\n", (void *)c);
    free(a);
    free(b);
    free(c); 
    
    /**
     * Isso ocorre porque a stack cresce para endereços menores 
     * (de cima para baixo na memória).
     * A heap cresce para endereços maiores 
     * (de baixo para cima na memória).
     */
    return 0;
}