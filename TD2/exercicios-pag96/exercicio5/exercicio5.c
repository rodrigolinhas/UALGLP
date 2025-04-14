/**
 * strstr
 * Procura uma substring dentro de uma string. Retorna um apontador para a primeira 
 * ocorrência da substring ou NULL se não for encontrada.
 */

#include <stdio.h>
#include <string.h>
int main(void) {
    char texto[100];
    char sub[100];
    printf("Digite a string: ");
    fgets(texto, sizeof(texto), stdin);
    printf("Digite a palavra: ");
    fgets(sub, sizeof(sub), stdin);
    char *resultado = strstr(texto, sub);
    if (resultado != NULL)  printf("Substring encontrada: %s\n", resultado);
    else                    printf("Substring não encontrada.\n");
    
    return 0;
}
/*
#include <stdio.h>
#include <string.h>
int main() {
    char texto[] = "Encontre a agulha no palheiro";
    char *sub = strstr(texto, "agulha");
    if (sub != NULL)
        printf("Substring encontrada: %s\n", sub);
    else
        printf("Substring não encontrada.\n");
    return 0;
}
*/
