#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

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
    if (!fgets(buf, sizeof buf, stdin) || sscanf(buf, "%d", n) != 1) return NULL;
    int total = *n;
    No **nos = malloc(total * sizeof *nos);
    for (int i = 0; i < total; i++) {
        // Ler ID (ex: [0])
        fgets(buf, sizeof buf, stdin);

        // Ler descritivo até encontrar >>>
        char desc[MAXTXT] = {0};
        char *desc_ptr = desc;
        int desc_size = MAXTXT;
        int found_end = 0;

        while (fgets(buf, sizeof buf, stdin)) {
            if (strstr(buf, "<<<")) {
                // Ignora a linha com <<<
                continue;
            }
            char *end_marker = strstr(buf, ">>>");
            if (end_marker) {
                *end_marker = '\0';
                strncat(desc_ptr, buf, desc_size - 1);
                found_end = 1;
                break;
            } else {
                strncat(desc_ptr, buf, desc_size - 1);
                desc_size -= strlen(buf);
                desc_ptr += strlen(buf);
            }
        }
        if (!found_end) {
            // Tratar erro de formato
            free(nos);
            return NULL;
        }

        // Processar tipo e nopcoes
        TipoCena tipo;
        int nop = 0;
        fgets(buf, sizeof buf, stdin); // Linha após >>>
        if (strstr(buf, "WON")) {
            tipo = WON;
        } else if (strstr(buf, "FAILED")) {
            tipo = FAILED;
        } else {
            sscanf(buf, ">>><%d>", &nop); // Captura o padrão ">>><2>"            
            tipo = NORMAL;
        }

        // Processar opções se for NORMAL
        char **opts = NULL;
        if (tipo == NORMAL) {
            fgets(buf, sizeof buf, stdin); // Linha ***

            opts = malloc(nop * sizeof(char*));
            for (int j = 0; j < nop; j++) {
                fgets(buf, sizeof buf, stdin);
                buf[strcspn(buf, "\n")] = '\0';
                char *dot = strchr(buf, '.');
                if (dot) {
                    opts[j] = strdup(dot + 2);
                } else {
                    opts[j] = strdup("");
                }
            }
            fgets(buf, sizeof buf, stdin); // Linha ***
        }

        // Criar Cena e No
        Cena *c = criaCena(desc, tipo, nop, opts);
        nos[i] = criaNo(c, (tipo == NORMAL) ? nop : 0);
        if (opts) {
            for (int j = 0; j < nop; j++) free(opts[j]);
            free(opts);
        }
    }
    return nos;
}

// Add this function to parse IDs from a string
int* parseIds(const char *line, int *count) {
    int capacity = 10;
    int *ids = malloc(capacity * sizeof(int));
    *count = 0;
    char *token = strtok((char*)line, " ");
    while (token) {
        if (*count >= capacity) {
            capacity *= 2;
            ids = realloc(ids, capacity * sizeof(int));
        }
        ids[(*count)++] = atoi(token);
        token = strtok(NULL, " ");
    }
    return ids;
}


void construirGrafo(No **nos, int n) {
    char idLine[MAXTXT];
    fgets(idLine, sizeof idLine, stdin);
    
    int count; // Declare 'count' here
    int *ids = parseIds(idLine, &count); // Implement parseIds
    int idx = 0;
    
    for (int i = 0; i < n; i++) {
        No *no = nos[i];
        if (no->cena->tipo == NORMAL) {
            for (int j = 0; j < no->nvizinhos; j++) {
                int id = ids[idx++];
                juntaVizinhoNo(no, j, nos[id]);
            }
        }
    }
    free(ids);
}

void executarJogo(historia *h, int *choices, int numChoices) {
    int choiceIdx = 0;
    No *cur = h->cena_ativa;
    
    while (choiceIdx < numChoices) {
        mostraCenaNo(cur);
        TipoCena t = estadoCenaNo(cur);
        if (t != NORMAL) {
            printf("%s!\n", t == WON ? "GANHOU" : "PERDEU");
            return;
        }
        int esc = choices[choiceIdx++];
        if (esc < 0 || esc >= cur->nvizinhos) {
            printf("STANDBY!\n");
            return;
        }
        cur = proximoNo(cur, esc);
    }
    printf("STANDBY!\n");
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
