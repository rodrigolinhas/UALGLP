/**
 * strcspn e strspn
 *  A função strcspn(const char *s1, const char *s2) retorna o comprimento
 *  do segmento inicial da string s1 que não contém nenhum dos caracteres
 *  presentes em s2 . Ou seja, ela conta quantos caracteres consecutivos, a partir do início de s1 , não aparecem em s2 .
 *
 *  A função strspn(const char *s1, const char *s2) retorna o comprimento
 *  do segmento inicial de s1 que contém apenas os caracteres presentes em s2 .
 *  Ela mede quantos caracteres consecutivos, a partir do início de s1 , pertencem ao conjunto definido por s2 .
 */

#include <stdio.h>
#include <string.h>
int main(void) {
    char str1[100];
    char str2[100];
    printf("Introduza uma frase e a seguir um conjunto de caracteres: ");
    fgets(str1, sizeof(str1), stdin);
    fgets(str2, sizeof(str2), stdin);
    size_t span = strcspn(str1, str2);
    printf("Número de caracteres iniciais sem os caracteres recebidos: %zu\n", span);    
    return 0;
}

/*#include <stdio.h>
#include <string.h>
int main(void) {
    char str1[100];
    char str2[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    fgets(str1, sizeof(str1), stdin);
    size_t span = strspn(str1, str2);
    printf("Número de caracteres iniciais que são letras maiúsculas: %zu\n", span);
    return 0;
}*/


/*
Exemplo strcspn :
#include <stdio.h>
#include <string.h>
int main() {
    char s1[] = "Hello, world!";
    char s2[] = " ,!"; // espaço, vírgula e ponto de exclamação
    size_t span = strcspn(s1, s2);
    printf("Número de caracteres iniciais sem ' ', ',' ou '!': %zu\n", span);
    return 0;
}
Explicação:
No exemplo, a função percorre s1 até encontrar um caractere que esteja presente em s2 .
Assim, se a string for "Hello, world!" , o resultado será 5 (pois "Hello" é o segmento
inicial sem espaço, vírgula ou ponto de exclamação).

Exemplo strspn :
#include <stdio.h>
#include <string.h>
int main() {
    char s1[] = "12345abc";
    char s2[] = "0123456789"; // conjunto de dígitos
    size_t span = strspn(s1, s2);
    printf("Número de dígitos iniciais na string: %zu\n", span);
    return 0;
}
Explicação:
Aqui, a função conta quantos caracteres no início de s1 são dígitos. O resultado será 5,
pois os cinco primeiros caracteres são "12345" e o sexto caractere ("a") não está no
conjunto de dígitos.
*/