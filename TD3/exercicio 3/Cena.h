#ifndef CENA_H
#define CENA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Assuma que o tamanho máximo de um texto é definido via uma macro MAXTXT com o valor 4096
#define MAXTXT 4096
//Assuma que o número máximo de escolhas é definido via uma macro MAXCHOICE com o valor 10
#define MAXCHOICE 10

typedef enum {NORMAL, WON, FAILED} TipoCena;

typedef struct Cena {
    char *descritivo;
    TipoCena tipo;
    int nopcoes;
    char **vopcoes;
} Cena;


typedef struct no {
    Cena *cena;             // Apontador para a cena
    struct no **vizinhos;   // Vetor de apontadores para vizinhos
    int nvizinhos;          // Número de vizinhos
} No;

/*
Considere o tipo estrutural historia que tem dois campos. O primeiro campo é um
apontador para o nó que arquiva a cena inicial da história. O segundo campo é um
apontador para o nó que contem a cena atualmente ativa da história a decorrer.
Define o tipo historia 
*/
typedef struct historia {
    No *cena_inicial; // Apontador para a cena inicial
    No *cena_ativa;   // Apontador para a cena atualmente ativa
} historia;

Cena        *criaCena(char *descritivo, TipoCena tipo, int nopcoes, char **vopcoes);
void        mostrarCena(Cena *c);
void        libertaCena(Cena *c);
No          *criaNo(Cena *c, int nvizinhos);
void        juntaVizinhoNo(No *no, int pos, No* v);
No          *proximoNo(No *no_ativo, int escolha);
void        mostraCenaNo(No *no);
TipoCena    estadoCenaNo(No *no);
int         escolheCenaNo(No *no);
historia    *criaHistoria(No *no);

#endif