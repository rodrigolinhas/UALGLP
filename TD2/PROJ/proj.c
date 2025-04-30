#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

typedef struct Dynvec {
    void *data;
    size_t elem_size;
    size_t capacity;
    size_t length;
} dynvec;

#define DYNVEC_INIT_CAPACITY 4

dynvec* dynvec_create(size_t elem_size) {
    dynvec *v = malloc(sizeof(dynvec));
    if (!v) { errno = ENOMEM; return NULL; }
    v->elem_size = elem_size;
    v->capacity = DYNVEC_INIT_CAPACITY;
    v->length = 0;
    v->data = malloc(v->capacity * elem_size);
    if (!v->data) { errno = ENOMEM; free(v); return NULL; }
    return v;
}

void dynvec_push(dynvec *v, const void *elem) {
    if (v->length >= v->capacity) {
        v->capacity *= 2;
        v->data = realloc(v->data, v->capacity * v->elem_size);
        if (!v->data) { perror("realloc falhou"); exit(1); }
    }
    memcpy((char*)v->data + v->length * v->elem_size, elem, v->elem_size);
    v->length++;
}

void* dynvec_get(const dynvec *v, size_t i) {
    return (char*)v->data + i * v->elem_size;
}

void dynvec_set(dynvec *v, size_t i, const void *elem) {
    memcpy((char*)v->data + i * v->elem_size, elem, v->elem_size);
}

size_t dynvec_length(const dynvec *v) {
    return v->length;
}

void dynvec_free(dynvec *v) {
    if (!v) return;
    free(v->data);
    free(v);
}

void dynvec_swap(dynvec *v, size_t i, size_t j) {
    if (i == j) return;
    void *tmp = malloc(v->elem_size);
    void *pi = dynvec_get(v,i), *pj = dynvec_get(v,j);
    memcpy(tmp, pi, v->elem_size);
    memcpy(pi, pj, v->elem_size);
    memcpy(pj, tmp, v->elem_size);
    free(tmp);
}

// Insertion sort (alfabético)
void insertion_sort_dynvec(dynvec *v, int (*cmp)(const void*, const void*)) {
    size_t n = v->length;
    for (size_t i = 1; i < n; i++) {
        char key[v->elem_size];
        memcpy(key, dynvec_get(v,i), v->elem_size);
        size_t j = i;
        while (j > 0 && cmp(dynvec_get(v,j-1), key) > 0) {
            dynvec_set(v, j, dynvec_get(v,j-1));
            j--;
        }
        dynvec_set(v, j, key);
    }
}

// Quicksort (contadores)
static size_t partition_dynvec(dynvec *v,
    int (*cmp)(const void*, const void*), size_t lo, size_t hi)
{
    void *pivot = dynvec_get(v,hi);
    size_t i = lo;
    for (size_t j = lo; j < hi; j++) {
        if (cmp(dynvec_get(v,j), pivot) < 0) {
            dynvec_swap(v, i, j);
            i++;
        }
    }
    dynvec_swap(v, i, hi);
    return i;
}

static void quicksort_rec(dynvec *v,
    int (*cmp)(const void*, const void*), size_t lo, size_t hi)
{
    if (lo < hi) {
        size_t p = partition_dynvec(v, cmp, lo, hi);
        if (p > 0) quicksort_rec(v, cmp, lo, p-1);
        quicksort_rec(v, cmp, p+1, hi);
    }
}

void quicksort_dynvec(dynvec *v, int (*cmp)(const void*, const void*)) {
    if (v->length > 0)
        quicksort_rec(v, cmp, 0, v->length-1);
}

// Estrutura para contar palavras
typedef struct {
    char *word;
    int count;
} WordCount;

// Comparadores
int cmp_alpha(const void *a, const void *b) {
    return strcmp(((WordCount*)a)->word, ((WordCount*)b)->word);
}
int cmp_count_desc(const void *a, const void *b) {
    int ca = ((WordCount*)a)->count;
    int cb = ((WordCount*)b)->count;
    return (cb - ca);
}

// Converte em minúsculas e filtra só letras
void normalize(char *s) {
    char *p = s, *q = s;
    while (*p) {
        if (isalpha((unsigned char)*p)) {
            *q++ = tolower((unsigned char)*p);
        } else if (*p == '\0') {
            break;
        } else {
            // delimita palavra
            *q++ = ' ';
        }
        p++;
    }
    *q = '\0';
}

int main(void) {
    char line[1024];
    int N;
    if (!fgets(line, sizeof(line), stdin) ||
        sscanf(line, "%d", &N) != 1)
    {
        fprintf(stderr, "Uso: programa <N> < texto.txt\n");
        return 1;
    }

    dynvec *v = dynvec_create(sizeof(WordCount));
    if (!v) { perror("malloc"); return 1; }

    while (fgets(line, sizeof(line), stdin)) {
        normalize(line);
        char *tok = strtok(line, " ");
        while (tok) {
            // procura existente
            size_t i;
            for (i = 0; i < dynvec_length(v); i++) {
                WordCount *wc = dynvec_get(v, i);
                if (strcmp(wc->word, tok) == 0) {
                    wc->count++;
                    break;
                }
            }
            if (i == dynvec_length(v)) {
                // nova palavra
                WordCount wc;
                wc.word = strdup(tok);
                wc.count = 1;
                dynvec_push(v, &wc);
            }
            tok = strtok(NULL, " ");
        }
    }

    // ordena alfabeticamente para agrupar iguais (já feito)...
    insertion_sort_dynvec(v, cmp_alpha);
    // agora ordena por contagem decrescente
    quicksort_dynvec(v, cmp_count_desc);

    // imprime top N
    size_t total = dynvec_length(v);
    size_t M = (N < (int)total ? N : total);
    for (size_t i = 0; i < M; i++) {
        WordCount *wc = dynvec_get(v, i);
        printf("%d %s\n", wc->count, wc->word);
    }

    // libera
    for (size_t i = 0; i < total; i++) {
        free(((WordCount*)dynvec_get(v,i))->word);
    }
    dynvec_free(v);
    return 0;
}
