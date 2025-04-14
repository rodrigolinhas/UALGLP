/**
 * strlen Retorna o tamanho de uma string (sem contar o caractere nulo).
 */
#include <stdio.h>
#include <string.h>

int main(void) {
    char texto[100];
    fgets(texto, sizeof(texto), stdin);
    size_t tamanho = strlen(texto);
    printf("O tamanho da string é: %zu\n", tamanho);
    return 0;
}


/*#include <stdio.h>
#include <string.h>

int main() {
    char texto[] = "O C não tem segredos para mim";
    size_t tamanho = strlen(texto);
    printf("O tamanho da string é: %zu\n", tamanho);
    return 0;
}*/