#include <stdio.h>
#include "Cena.h"

int main(void) {
    int n;
    No **nos = lerCenasDoInput(&n);
    if (!nos) { fprintf(stderr, "Erro ao ler input\n"); return EXIT_FAILURE; }
    construirGrafo(nos, n);
    historia *h = criaHistoria(nos[0]);
    if (!h) { fprintf(stderr, "Erro ao iniciar historia\n"); return EXIT_FAILURE; }
    executarJogo(h);
    libertarTudo(nos, n, h);
    return 0;
}
