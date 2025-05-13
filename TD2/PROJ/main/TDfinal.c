#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <errno.h>

#ifndef DYNVEC_INIT_CAPACITY
#define DYNVEC_INIT_CAPACITY 4
#endif

typedef struct Dynvec {
    void *data;          // apontador para a sequencia dos elementos
    size_t elem_size;    // tamanho dos elementos de datat (em bytes)
    size_t capacity;     // capacidade total da sequência data
    size_t length;       // quantidade atual dos elementos arquivados
} dynvec;

// Cria um vetor dinâmico genérico
dynvec* dynvec_create(size_t elem_size) {
    dynvec *v = malloc(sizeof(dynvec));
    if (!v) {
        errno = ENOMEM;
        #ifdef DEBUG_ON
        perror("Create. Erro ao alocar memória para estrutura");
        #endif
        return NULL;
    }

    v->elem_size = elem_size;
    v->capacity = DYNVEC_INIT_CAPACITY;
    v->length = 0;
    v->data = malloc(v->capacity * elem_size);
    
    if (!v->data) {
        errno = ENOMEM;
        #ifdef DEBUG_ON
        perror("Create. Erro ao alocar memória para dados");
        #endif
        free(v);
        return NULL;
    }
    return v;
}

// Adiciona um elemento ao vetor
void dynvec_push(dynvec *v, const void *elem) {
    if (v->length >= v->capacity) {
        v->capacity *= 2;
        v->data = realloc(v->data, v->capacity * v->elem_size);
    }
    memcpy((char*)v->data + (v->length * v->elem_size), elem, v->elem_size);
    v->length++;
}

// Libera a memória do vetor
void dynvec_free(dynvec *v) {
    if (v) {
        free(v->data);
        free(v);
    }
}

// Obtém um elemento do vetor
void* dynvec_get(const dynvec *v, size_t index) {
    if (index >= v->length) {
        return NULL;
    }
    return (char*)v->data + (index * v->elem_size);
}

// Define um elemento no vetor
void dynvec_set(dynvec *v, size_t index, const void *elem) {
    if (index < v->length)
        memcpy((char*)v->data + (index * v->elem_size), elem, v->elem_size);
}

// Retorna o número de elementos
size_t dynvec_length(const dynvec *v)   {return v->length;}

// Retorna os elementos do vetor
void dynvec_map(dynvec *v, void (*processo)(void *)) {
    if (!v || !processo) return;
    for (size_t i = 0; i < v->length; i++) {
        processo((char *)v->data + (i * v->elem_size));
    }
}

// Verifica se um elemento existe no vetor
bool dynvec_contains(const dynvec *v, const void *elem, int (*cmp)(const void*, const void*)) {
    for (size_t i = 0; i < v->length; i++) {
        const void *current = (char*)v->data + (i * v->elem_size);
        if (cmp(current, elem) == 0) return true;
    }
    return false;
}

// Retorna o índice do elemento (ou -1 se não encontrado)
size_t dynvec_index(const dynvec *v, const void *elem, int (*cmp)(const void*, const void*)) {
    for (size_t i = 0; i < v->length; i++) {
        const void *current = (char*)v->data + (i * v->elem_size);
        if (cmp(current, elem) == 0) return i;
    }
    return (size_t)-1;
}

// Aplica uma função acumuladora a todos os elementos
void dynvec_fold_left(const dynvec *v, void *acc, void (*func)(void *acc, const void *elem)) {
    for (size_t i = 0; i < v->length; i++) {
        const void *elem = (char*)v->data + (i * v->elem_size);
        func(acc, elem);
    }
}

// Verifica se todos os elementos satisfazem um predicado
bool dynvec_forall(const dynvec *v, bool (*predicate)(const void *elem)) {
    for (size_t i = 0; i < v->length; i++) {
        const void *elem = (char*)v->data + (i * v->elem_size);
        if (!predicate(elem)) return false;
    }
    return true;
}

// Verifica se pelo menos um elemento satisfaz um predicado
bool dynvec_exists(const dynvec *v, bool (*predicate)(const void *elem)) {
    for (size_t i = 0; i < v->length; i++) {
        const void *elem = (char*)v->data + (i * v->elem_size);
        if (predicate(elem)) return true;
    }
    return false;
}

// Retorna o índice do primeiro elemento que satisfaz o predicado
size_t dynvec_exists_index(const dynvec *v, bool (*predicate)(const void *elem)) {
    for (size_t i = 0; i < v->length; i++) {
        const void *elem = (char*)v->data + (i * v->elem_size);
        if (predicate(elem)) return i;
    }
    return (size_t)-1;
}

// Filtra elementos com base em um predicado
dynvec* dynvec_filter(const dynvec *v, bool (*predicate)(const void *elem)) {
    dynvec *filtered = dynvec_create(v->elem_size);
    for (size_t i = 0; i < v->length; i++) {
        const void *elem = (char*)v->data + (i * v->elem_size);
        if (predicate(elem)) {
            dynvec_push(filtered, elem);
        }
    }
    return filtered;
}
//---------------------------------------------------------------------novos---------------------------------------------------------------------------------------

// Troca dois elementos de posição
void dynvec_swap(dynvec *v, size_t i, size_t j) {
    if (i == j) return;
    
    void *temp = malloc(v->elem_size);
    void *ptr_i = dynvec_get(v, i);
    void *ptr_j = dynvec_get(v, j);
    
    memcpy(temp, ptr_i, v->elem_size);
    memcpy(ptr_i, ptr_j, v->elem_size);
    memcpy(ptr_j, temp, v->elem_size);
    
    free(temp);
}

void insertion_sort_dynvec(dynvec *v, int (*cmp)(const void*, const void*)) {
    for (size_t i = 1; i < v->length; i++) {
        size_t j = i;
        void *key = dynvec_get(v, i);
        char key_buffer[v->elem_size];
        memcpy(key_buffer, key, v->elem_size);
        
        while (j > 0 && cmp(dynvec_get(v, j-1), key_buffer) > 0) {
            dynvec_set(v, j, dynvec_get(v, j-1));
            j--;
        }
        dynvec_set(v, j, key_buffer);
    }
}

static int partition(dynvec *v, int (*cmp)(const void*, const void*), int low, int high) {
    if (low > high || high >= (int)v->length) return -1;
    void *pivot = dynvec_get(v, high);
    int i = low;
    
    for (int j = low; j < high; j++) {
        if (cmp(dynvec_get(v, j), pivot) < 0) {
            dynvec_swap(v, i, j);
            i++;
        }
    }
    dynvec_swap(v, i, high);
    return i;
}

static void quicksort_rec(dynvec *v, int (*cmp)(const void*, const void*), int low, int high) {
    if (low < high) {
        int pi = partition(v, cmp, low, high);
        if (pi == -1) return;
        quicksort_rec(v, cmp, low, pi - 1);
        quicksort_rec(v, cmp, pi + 1, high);
    }
}

void quicksort_dynvec(dynvec *v, int (*cmp)(const void*, const void*)) {
    if (v->length == 0) return;
    quicksort_rec(v, cmp, 0, (int)v->length - 1);
}

bool dynvec_is_sorted(dynvec *v, int (*cmp)(const void *, const void *)) {
    for (size_t i = 1; i < v->length; ++i) {
        void *prev = (char*)v->data + (i - 1) * v->elem_size;
        void *curr = (char*)v->data + i * v->elem_size;
        if (cmp(prev, curr) > 0) return false;
    }
    return true;
}
//---------------------------------------------------------------------TD2---------------------------------------------------------------------------------------

typedef struct word_count {
    char *word;
    int count;
} WordCount;

int compare_words_alpha(const void *a, const void *b) {
    const WordCount *wc_a = a;
    const WordCount *wc_b = b;
    return strcmp(wc_a->word, wc_b->word);
}

int compare_counts_desc(const void *a, const void *b) {
    const WordCount *wc_a = a;
    const WordCount *wc_b = b;
    if (wc_a->count > wc_b->count) return -1;
    if (wc_a->count < wc_b->count) return 1;
    return strcmp(wc_a->word, wc_b->word); // critério secundário
}

int main(void) {
    int N;
    char buffer[1024];

    // Ler número de palavras do ranking
    if (fgets(buffer, sizeof(buffer), stdin) == NULL || sscanf(buffer, "%d", &N) != 1) {
        errno = ENOMEM;
        #ifdef DEBUG_ON
        perror("Erro ao ler o número de palavras");
        #endif
        return 1;
    }
  
    dynvec *words = dynvec_create(sizeof(WordCount));
    const char *delimiters = " \t\n\r.,;:!?()[]{}<>|/";

    // Processar entrada linha a linha
    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0'; // Remove newline
        
        // Salta linhas vazias
        if (strlen(buffer) == 0) continue;
        
        char *token = strtok(buffer, delimiters);
        while (token != NULL) {
            // Ignorar strings vazias
            if (strlen(token) == 0) {
                token = strtok(NULL, delimiters);
                continue;
            }

            // Procura palavra no vetor
            bool found = false;
            for (size_t i = 0; i < dynvec_length(words); i++) {
                WordCount *wc = dynvec_get(words, i);
                if (strcmp(wc->word, token) == 0) {
                    wc->count++;
                    found = true;
                    break;
                }
            }

            // Adicionar nova palavra se não foi encontrada
            if (!found) {
                WordCount new_wc = {
                    .word = strdup(token),
                    .count = 1
                };
                if (!new_wc.word) {
                    errno = ENOMEM;
                    #ifdef DEBUG_ON
                    perror("Create. Erro ao alocar memória para estrutura");
                    #endif
                    dynvec_free(words);
                    return 1;
                }
                dynvec_push(words, &new_wc);
            }

            token = strtok(NULL, delimiters);
        }
    }
    // 1) Ordenação alfabética
    insertion_sort_dynvec(words, compare_words_alpha);
    
    // 2) Ordenação por contagem decrescente
    //qsort(words->data, words->length, sizeof(WordCount), compare_counts_desc);
    quicksort_dynvec(words, compare_counts_desc);

    // Impressão dos top N
    size_t limit = N < dynvec_length(words) ? N : dynvec_length(words);
    for (size_t i = 0; i < limit; i++) {
        WordCount *wc = dynvec_get(words, i);
        printf("%d %s\n", wc->count, wc->word);
        free(wc->word);
    }

    // Liberar memória das palavras restantes (se N > limit)
    for (size_t i = limit; i < dynvec_length(words); i++) {
        WordCount *wc = dynvec_get(words, i);
        free(wc->word);
    }

    dynvec_free(words);
    return 0;
}