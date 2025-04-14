/**
 * strcpy e strncpy 
 * Copiam o conteúdo de uma string para outra.
 *  strcpy(destino, origem) copia a string inteira.
 *  strncpy(destino, origem, n) copia até n caracteres.
 */


#include <stdio.h>
#include <string.h>
int main(void) {
    char num1[100];
    char num2[100];
    printf("Digite as 2 strings: ");
    scanf("%s\n %s", &num1, &num2);
    char num3[100];
    strcpy(num3, num1);
    printf("A 1a string numa nova var gracas ao strcpy: %s\n", num3);
    printf("A 2a string: %s\n", num2);
    return 0;
}
 /*#include <stdio.h>
#include <string.h>
int main() {
    char origem[] = "Exemplo";
    char destino[20];
    strcpy(destino, origem);
    printf("Destino: %s\n", destino);
    return 0;
}*/