/**
 * strchr e strrchr
 *  strchr: Procura a primeira ocorrência de um caractere na string.
 *  strrchr: Procura a última ocorrência de um caractere na string
 */

#include <stdio.h>
#include <string.h>
int main(void) {
    char frase[100];
    char letra;
    printf("Digite a string: ");
    fgets(frase, sizeof(frase), stdin);
    printf("Digite o caractere: ");
    scanf(" %c", &letra);
    
    char *ptr = strchr(frase, letra);
    if (ptr != NULL)    printf("Primeira ocorrência de '%c': %s\n", letra, ptr);
    else                printf("Caractere não encontrado.\n");
    
    char *ptr2 = strrchr(frase, letra);
    if (ptr2 != NULL)   printf("Última ocorrência de '%c': %s\n", letra, ptr2);
    else                printf("Caractere não encontrado.\n");
    
    return 0;
}

/*
Exemplo (strchr):
#include <stdio.h>
#include <string.h>
int main() {
    char frase[] = "Procure a letra 'a' nesta frase.";
    char *ptr = strchr(frase, 'a');
    if (ptr != NULL)
        printf("Primeira ocorrência de 'a': %s\n", ptr);
    else
        printf("Caractere não encontrado.\n");
    return 0;
}

Exemplo (strrchr):
#include <stdio.h>
#include <string.h>
int main() {
    char frase[] = "Procure a última ocorrência da letra 'a'.";
    char *ptr = strrchr(frase, 'a');
    if (ptr != NULL)
        printf("Última ocorrência de 'a': %s\n", ptr);
    else
        printf("Caractere não encontrado.\n");
    return 0;
}
*/