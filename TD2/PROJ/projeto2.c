#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_PALAVRA 30 // Tamanho máximo de uma palavra
#define MAX_PALAVRAS 50000 // Número máximo de palavras diferentes
#define TOP_N 30 // Número de palavras a serem exibidas

typedef struct {
    char palavra[MAX_PALAVRA];
    int contagem;
} Entrada;
//struct denominada "Entrada" que armazena a palavra e a respetiva contagem

Entrada palavras[MAX_PALAVRAS];
int total = 0;
//array de estruturas "Entrada" para armazenar as palavras e contagens, e uma variável total para contar o número de palavras diferentes

void limpar(char *s) {
    int i, j = 0;
    for (i = 0; s[i]; i++) {
        if (isalpha((unsigned char)s[i]) || s[i] == ' ' || s[i] == '.'){
            s[j++] = s[i];
        }
    }
    s[j] = '\0';
}
//função que remove os acentos e caracteres não alfabéticos, mantendo apenas letras e espaços
//e armazena a string limpa na mesma variável

void adicionar_palavra(char *s) {
    limpar(s);
    if (strlen(s) == 0) return;

    for (int i = 0; i < total; i++) {
        if (strcmp(palavras[i].palavra, s) == 0) {
            palavras[i].contagem++;
            return;
        }
    }
    // percorre todas as palavras já guardadas no array palavras[].
    // com strcmp compara se a nova palavra s já existe no array.
    // Se encontrar igual: Incrementa a contagem com palavras[i].contagem++
    //E sai da função (return), porque já tratou essa palavra.
    //se não econtrar igual vai para o strcpy

    if (total >= MAX_PALAVRAS) {
        exit(1);
    }

    strcpy(palavras[total].palavra, s);
    palavras[total].contagem = 1;
    total++;
}
//“bloco de registo” das palavras novas no ranking
//copia palavras para a estrutura "Entrada" e inicia a contagem com 1


int comparar_frequencia(const void *a, const void *b) {
    Entrada *p1 = (Entrada *)a;
    Entrada *p2 = (Entrada *)b;
    return p2->contagem - p1->contagem;
}

int main() {
    char linha[256];

    while (fgets(linha, sizeof(linha), stdin)) {
        char *token = strtok(linha, " \t\n");
        while (token) {
            adicionar_palavra(token);
            token = strtok(NULL, " \t\n");
        }
    }

        // 2º ordenação: ordem por frequência (qsort)
    qsort(palavras, total, sizeof(Entrada), comparar_frequencia);

    for (int i = 0; i < TOP_N && i < total; i++) {
        printf("%d %s\n", palavras[i].contagem, palavras[i].palavra);
    }

    return 0;
}
