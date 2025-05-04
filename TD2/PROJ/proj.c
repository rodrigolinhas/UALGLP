#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct { char *word; int count; } Item;

/* Comparador de itens: primeiro por contagem (decrescente), depois por palavra (alfabética) */
int item_cmp(const void *pa, const void *pb) {
    const Item *a = pa, *b = pb;
    if (b->count != a->count) 
        return b->count - a->count;
    return strcmp(a->word, b->word);
}

/* Exemplo de função para ler e contar palavras */
void processa_texto() {
    char buffer[10000];
    setlocale(LC_ALL, "");  // Ajusta localidade (opcional)
    while (fgets(buffer, sizeof(buffer), stdin)) {
        /* Remover '\n' final */
        buffer[strcspn(buffer, "\r\n")] = '\0'; 
        /* Converter para minúsculas e substituir não-letras por espaço */
        for (char *p = buffer; *p; ++p) {
            unsigned char c = (unsigned char)*p;
            *p = tolower(c);
            if (!isalpha(c)) *p = ' ';  // delimita pontuação, dígitos etc.
        }
        /* Separar tokens por espaço e contar */
        char *tok = strtok(buffer, " ");
        while (tok) {
            // adicionar ou incrementar palavra no vetor dinâmico (não mostrado)
            // ex: insereOuIncrementa(tok);
            tok = strtok(NULL, " ");
        }
    }
    /* Após ler tudo, ordena os itens já contados */
    // qsort(items, total_items, sizeof(Item), item_cmp);
    /* Imprime os N primeiros conforme solicitado */
}
