/**
 * strcat e strncat
 * Concatena (junta) duas strings.
 *  strcat(destino, fonte) adiciona o conteúdo de fonte ao final de destino .
 *  strncat(destino, fonte, n) concatena até n caracteres.
 */

#include <stdio.h>
#include <string.h>
int main(void) {
    char str1[100];
    char str2[100];
    printf("Digite as 2 strings: ");
    scanf("%s\n %s", &str1, &str2);
    strcat(str1, str2);
    printf("A string concatenada é: %s\n", str1);
    return 0;
}
 
 
  /*#include <stdio.h>
#include <string.h>
int main() {
    char frase[50] = "Olá"; // repare no tamanho 50
    char complemento[] = ", Mundo!";
    strcat(frase, complemento);
    printf("Frase concatenada: %s\n", frase);
    return 0;
}*/