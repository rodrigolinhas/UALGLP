#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "Cena.h"

Cena *criaCena(const char *descritivo, TipoCena tipo, int nopcoes, char **vopcoes) {
    if ((tipo == NORMAL && nopcoes <= 0) || (tipo != NORMAL && nopcoes != 0)) {
        errno = EINVAL;
        return NULL;
    }

    Cena *c = malloc(sizeof *c);
    if (!c) { errno = ENOMEM; return NULL; }

    c->tipo = tipo;
    c->nopcoes = nopcoes;
    c->descritivo = malloc(MAXTXT);
    if (!c->descritivo) { free(c); errno = ENOMEM; return NULL; }
    strncpy(c->descritivo, descritivo, MAXTXT-1);
    c->descritivo[MAXTXT-1] = '\0';

    if (nopcoes > 0) {
        c->vopcoes = malloc(nopcoes * sizeof *c->vopcoes);
        if (!c->vopcoes) { free(c->descritivo); free(c); errno = ENOMEM; return NULL; }
        for (int i = 0; i < nopcoes; i++) {
            size_t len = strnlen(vopcoes[i], MAXTXT-1) + 1;
            c->vopcoes[i] = malloc(len);
            if (!c->vopcoes[i]) {
                for (int j = 0; j < i; j++) free(c->vopcoes[j]);
                free(c->vopcoes);
                free(c->descritivo);
                free(c);
                errno = ENOMEM;
                return NULL;
            }
            strncpy(c->vopcoes[i], vopcoes[i], len-1);
            c->vopcoes[i][len-1] = '\0';
        }
    } else {
        c->vopcoes = NULL;
    }
    return c;
}

void mostrarCena(const Cena *c) {
    if (!c) return;
    printf("<<<\n");
    printf("%s\n", c->descritivo);
    printf(">>>\n");

    if (c->tipo == NORMAL) {
        printf("<%d>\n***\n", c->nopcoes);
        for (int i = 0; i < c->nopcoes; i++) {
            printf("+ %c. %s\n", 'a'+i, c->vopcoes[i]);
        }
        printf("***\n");
    } else {
        printf("<%s>\n***\n***\n", (c->tipo==WON?"WON":"FAILED"));
    }
}

void libertaCena(Cena *c) {
    if (!c) return;
    free(c->descritivo);
    for (int i = 0; i < c->nopcoes; i++) free(c->vopcoes[i]);
    free(c->vopcoes);
    free(c);
}

No *criaNo(Cena *c, int nvizinhos) {
    if (!c || nvizinhos < 0 || (c->tipo==NORMAL && nvizinhos!=c->nopcoes)) {
        errno = EINVAL; return NULL;
    }
    No *n = malloc(sizeof *n);
    if (!n) { errno=ENOMEM; return NULL; }
    n->cena = c;
    n->nvizinhos = nvizinhos;
    n->vizinhos = malloc(nvizinhos * sizeof *n->vizinhos);
    if (!n->vizinhos) { free(n); errno=ENOMEM; return NULL; }
    for (int i=0; i<nvizinhos; i++) n->vizinhos[i]=NULL;
    return n;
}

void juntaVizinhoNo(No *no, int pos, No* v) {
    if (!no || pos<0 || pos>=no->nvizinhos) {
        errno=EINVAL; return;
    }
    no->vizinhos[pos] = v;
}

No *proximoNo(const No *no_ativo, int escolha) {
    if (!no_ativo || !no_ativo->cena
        || no_ativo->nvizinhos!=no_ativo->cena->nopcoes
        || escolha<0 || escolha>=no_ativo->nvizinhos) {
        errno=EINVAL; return NULL;
    }
    return no_ativo->vizinhos[escolha];
}

void mostraCenaNo(const No *no) {
    if (!no) return;
    mostrarCena(no->cena);
}

TipoCena estadoCenaNo(const No *no) {
    if (!no||!no->cena) { errno=EINVAL; return FAILED; }
    return no->cena->tipo;
}

int escolheCenaNo(const No *no) {
    if (!no) { errno=EINVAL; return -1; }
    int escolha;
    printf("Escolha uma opcao (0-%d): ", no->cena->nopcoes-1);
    if (scanf("%d", &escolha)!=1) {
        int ch;
        while ((ch=getchar())!='\n' && ch!=EOF);
        return -1;
    }
    if (escolha<0 || escolha>=no->cena->nopcoes) return -1;
    return escolha;
}

historia *criaHistoria(No *no) {
    if (!no || !no->cena || no->cena->tipo!=NORMAL) {
        errno=EINVAL; return NULL;
    }
    historia *h = malloc(sizeof *h);
    if (!h) { errno=ENOMEM; return NULL; }
    h->cena_inicial = h->cena_ativa = no;
    return h;
}

No **lerCenasDoInput(int *n) {
    char buf[MAXTXT];
    if (!fgets(buf, sizeof buf, stdin) || sscanf(buf, "%d", n)!=1) return NULL;
    int total = *n;
    No **nos = malloc(total * sizeof *nos);
    for (int i=0; i<total; i++) {
        // Linha de ID
        fgets(buf, sizeof buf, stdin);
        // Linha <<< descricao >>>
        fgets(buf, sizeof buf, stdin);
        char *start = strstr(buf, "<<<");
        char *end = strstr(buf, ">>>");
        *end = '\0'; start += 3;
        char desc[MAXTXT];
        strncpy(desc, start, MAXTXT-1);
        desc[MAXTXT-1] = '\0';
        // Linha tipo/opcoes
        fgets(buf, sizeof buf, stdin);
        TipoCena tipo;
        int nop = 0;
        if (strstr(buf, "WON")) { tipo = WON; }
        else if (strstr(buf, "FAILED")) { tipo = FAILED; }
        else { sscanf(buf, ">>><%d", &nop); tipo = NORMAL; }
        char **opts = NULL;
        if (tipo == NORMAL) {
            opts = malloc(nop * sizeof *opts);
            for (int j=0; j<nop; j++) {
                fgets(buf, sizeof buf, stdin);
                char *p = strchr(buf, '.') + 2;
                buf[strcspn(buf, "\n")] = '\0';
                opts[j] = strdup(p);
            }
        }
        Cena *c = criaCena(desc, tipo, nop, opts);
        nos[i] = criaNo(c, nop);
        if (opts) {
            for (int j=0; j<nop; j++) free(opts[j]);
            free(opts);
        }
    }
    return nos;
}

void construirGrafo(No **nos, int n) {
    char buf[MAXTXT];
    for (int i = 0; i < n; i++) {
        if (nos[i]->cena->tipo == NORMAL) {
            for (int j = 0; j < nos[i]->cena->nopcoes; j++) {
                int id;
                if (!fgets(buf, sizeof buf, stdin) || sscanf(buf, "%d", &id) != 1) {
                    exit(EXIT_FAILURE);
                }
                if (id < 0 || id >= n) exit(EXIT_FAILURE);
                juntaVizinhoNo(nos[i], j, nos[id]);
            }
        }
    }
}

void executarJogo(historia *h) {
    if (!h) return;
    No *cur = h->cena_ativa;
    while (1) {
        mostraCenaNo(cur);
        TipoCena t = estadoCenaNo(cur);
        if (t != NORMAL) {
            printf("%s!\n", t==WON?"GANHOU":"PERDEU");
            return;
        }
        int esc = escolheCenaNo(cur);
        if (esc < 0) { printf("STANDBY!\n"); return; }
        No *nxt = proximoNo(cur, esc);
        if (!nxt) { printf("STANDBY!\n"); return; }
        cur = nxt;
    }
}

void libertarTudo(No **nos, int n, historia *h) {
    for (int i=0; i<n; i++) {
        libertaCena(nos[i]->cena);
        free(nos[i]->vizinhos);
        free(nos[i]);
    }
    free(nos);
    free(h);
}
