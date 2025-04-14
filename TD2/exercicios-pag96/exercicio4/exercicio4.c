/**
 * strcmp e strncmp
 * Compara duas strings.
 *  strcmp retorna 0 se as strings são iguais; um valor negativo se a primeira é menor; e um valor positivo se a primeira é maior.
 *  strncmp compara até os primeiros n caracteres de duas strings, funcionando de forma similar ao strcmp .
 */

 #include <stdio.h>
 #include <string.h>
 int main(void) {
    char str1[100];
    char str2[100];
    printf("Digite as 2 strings: ");
    scanf("%s\n %s", &str1, &str2);
    int resultado = strcmp(str1, str2);
    if (resultado == 0)     printf("As strings são iguais.\n");
    else if (resultado < 0) printf("str1 é maior em ordem lexicográfica que str2.\n");
    else                    printf("str1 é menor em ordem lexicográfica que str2.\n");
    return 0;
}
 
 
  /*#include <stdio.h>
 #include <string.h>
 int main() {
     char str1[] = "abc";
     char str2[] = "abd";
     int resultado = strcmp(str1, str2);
     if (resultado == 0) {
         printf("As strings são iguais.\n");
     } else if (resultado < 0) {
         printf("str1 é menor que str2.\n");
     } else {
         printf("str1 é maior que str2.\n");
     }
     return 0;
 }*/