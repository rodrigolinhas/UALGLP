#include <stdio.h>
#include <stdlib.h>

int var_global; // Variável global

int soma(int a, int b) {
    int resultado = a + b; // Variável local em soma()
    printf("Endereco de a em soma(): %p\n", &a);
    printf("Endereco de b em soma(): %p\n", &b);
    printf("Endereco de resultado em soma(): %p\n", &resultado);
    return resultado;
}

int main(void) {
    int var_local1 = 10; // Variável local 1 em main()
    int var_local2 = 20; // Variável local 2 em main()
    int resultado = soma(var_local1, var_local2);
    printf("Endereco de var_local1 em main(): %p\n", &var_local1);
    printf("Endereco de var_local2 em main(): %p\n", &var_local2);
    printf("Endereco de resultado em main(): %p\n", &resultado);
    printf("Endereco de var_global: %p\n", &var_global);
    return 0;
}