#include <stdio.h>
#include "Cena.h"

int main(void) {
    int n;
    No **nos = lerCenasDoInput(&n);
    if (!nos) { fprintf(stderr, "Erro ao ler input\n"); return EXIT_FAILURE; }
    construirGrafo(nos, n);
    historia *h = criaHistoria(nos[0]);
    if (!h) { fprintf(stderr, "Erro ao iniciar historia\n"); return EXIT_FAILURE; }

    // Read choices from input
    int choices[MAXCHOICE];
    int numChoices = 0;
    char buf[MAXTXT];
    if (fgets(buf, sizeof buf, stdin)) {
        char *token = strtok(buf, " ");
        while (token && numChoices < MAXCHOICE) {
            choices[numChoices++] = atoi(token);
            token = strtok(NULL, " ");
        }
    }

    executarJogo(h, choices, numChoices);
    libertarTudo(nos, n, h);
    return 0;
}