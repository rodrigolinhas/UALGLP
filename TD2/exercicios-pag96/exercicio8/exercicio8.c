/**
 * strpbrk
 *  A função strpbrk(const char *s1, const char *s2) procura a primeira ocorrência
 *  em s1 de qualquer caractere que esteja presente em s2 . Se encontrar, retorna um
 *  apontador para essa posição na string; caso contrário, retorna NULL 
 */

 #include <stdio.h>
 #include <string.h>
 int main(void) {
    char s1[100];
    char s2[100];
    printf("Introduza uma frase e a seguir um conjunto de caracteres: ");
    fgets(s1, sizeof(s1), stdin);
    fgets(s2, sizeof(s2), stdin);
    char *ptr = strpbrk(s1, s2);
    if (ptr != NULL)    printf("Primeira ocorrência de um dos caracteres de \"%s\": %s\n", s2, ptr);
    else                printf("Nenhum dos caracteres de \"%s\" foi encontrado.\n", s2);
    return 0;
 }
 

/*
 Exemplo:
 #include <stdio.h>
 #include <string.h>
 int main() {
     char s1[] = "Exemplo de string";
     char s2[] = "xyz"; // caracteres a serem procurados
     char *ptr = strpbrk(s1, s2);
     if (ptr != NULL)
         printf("Primeira ocorrência de um dos caracteres de \"%s\": %s\n", s2, ptr);
     else
         printf("Nenhum dos caracteres de \"%s\" foi encontrado.\n", s2);
     return 0;
 }
 Explicação:
 A função busca, na string "Exemplo de string" , a primeira ocorrência de qualquer
 caractere contido em "xyz" . Se nenhum desses caracteres for encontrado, o retorno será
 NULL .
 */