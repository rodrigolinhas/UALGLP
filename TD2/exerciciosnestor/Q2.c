#include<stdio.h>
#include<stdlib.h>

int main(void) {
    int x, y;
    int ary[4] = { 11, 22, 33, 44 };
    int *ptr;
    ptr = ary;
    //o da esquerda aponta para o valor da direita é o endereço
    ptr++;
    printf("%d %p\n", *ptr, ptr);
}

// Resposta: 22 @x7ffc3ae795e4