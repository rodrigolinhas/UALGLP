/**
 * strtok
 * A função strtok(char *str, const char *delim) divide (tokeniza) uma string em
 * partes (tokens), utilizando os caracteres em delim como delimitadores.
 *  Na primeira chamada: a string original é passada como parâmetro.
 *  Nas chamadas subsequentes: passa-se NULL para continuar a tokenização da mesma string.
 *  Observação: A função strtok() modifica a string original, substituindo os delimitadores
 *  por '\0' 
 */
#include <stdio.h>
#include <string.h>
int main() {
    char str[100];
    const char delim[] = " ";
    printf("Introduza uma string: ");
    fgets(str, sizeof(str), stdin);
    char *token = strtok(str, delim);
    while (token != NULL) {
        printf("Token: %s\n", token);
        token = strtok(NULL, delim);
    }
    return 0;
}
/*  
Exemplo:
#include <stdio.h>
#include <string.h>
int main() {
    char str[] = "C,OCaml,Python,Java,C++";
    const char delim[] = ",";
    char *token = strtok(str, delim);
    while (token != NULL) {
        printf("Token: %s\n", token);
        token = strtok(NULL, delim);
    }
    return 0;
}
Explicação:
Neste exemplo, a string "C,Python,Java,C++" é dividida em tokens separados pela
vírgula. Cada token é impresso individualmente.
*/