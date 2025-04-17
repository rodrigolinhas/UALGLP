#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[50];
    int idade;
    float altura;
} Pessoa;

int compara_pessoa_nome(const void *a, const void *b) {
    const Pessoa *pa = (const Pessoa*)a;
    const Pessoa *pb = (const Pessoa*)b;
    return strcmp(pa->nome, pb->nome);
}

int main() {
    Pessoa pessoas[] = {
        {"Ana", 25, 1.65},
        {"Carlos", 30, 1.80},
        {"Pedro", 28, 1.75},
        {"Zacarias", 45, 1.90}
    };
    Pessoa chave = {.nome = "Pedro"};
    int tamanho = sizeof(pessoas)/sizeof(pessoas[0]);

    // Array precisa estar ordenado para binary search
    qsort(pessoas, tamanho, sizeof(Pessoa), compara_pessoa_nome);

    Pessoa *resultado = bsearch(
        &chave, pessoas, tamanho, sizeof(Pessoa),
        compara_pessoa_nome
    );

    if(resultado)
        printf("Encontrado: %s, %d anos\n", 
              resultado->nome, resultado->idade);
    
    return 0;
}