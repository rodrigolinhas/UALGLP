#ifndef CENA_H
#define CENA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MAXTXT 4096
#define MAXCHOICE 10

typedef enum {NORMAL, WON, FAILED} TipoCena;

typedef struct Cena {
    char *descritivo;
    TipoCena tipo;
    int nopcoes;
    char **vopcoes;
} Cena;

typedef struct No {
    Cena *cena;
    struct No **vizinhos;
    int nvizinhos;
} No;

typedef struct historia {
    No *cena_inicial;
    No *cena_ativa;
} historia;

// Prototypes
Cena        *criaCena(const char *descritivo, TipoCena tipo, int nopcoes, char **vopcoes);
void        mostrarCena(const Cena *c);
void        libertaCena(Cena *c);
No          *criaNo(Cena *c, int nvizinhos);
void        juntaVizinhoNo(No *no, int pos, No* v);
No          *proximoNo(const No *no_ativo, int escolha);
void        mostraCenaNo(const No *no);
TipoCena    estadoCenaNo(const No *no);
int         escolheCenaNo(const No *no);
historia    *criaHistoria(No *no);
No          **lerCenasDoInput(int *n);
void        construirGrafo(No **nos, int n);
void        executarJogo(historia *h);
void        libertarTudo(No **nos, int n, historia *h);

#endif