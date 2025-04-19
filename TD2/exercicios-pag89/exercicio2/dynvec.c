#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include "dynvec.h"

#ifndef DYNVEC_INIT_CAPACITY
#define DYNVEC_INIT_CAPACITY 4
#endif

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

static size_t partition(dynvec *v, int (*cmp)(const void*, const void*), size_t low, size_t high) {
    void *pivot = dynvec_get(v, high);
    size_t i = low;
    
    for (size_t j = low; j < high; j++) {
        if (cmp(dynvec_get(v, j), pivot) < 0) {
            dynvec_swap(v, i, j);
            i++;
        }
    }
    dynvec_swap(v, i, high);
    return i;
}

static void quicksort_rec(dynvec *v, int (*cmp)(const void*, const void*), size_t low, size_t high) {
    if (low < high) {
        size_t pi = partition(v, cmp, low, high);
        if (pi > 0) quicksort_rec(v, cmp, low, pi - 1);
        quicksort_rec(v, cmp, pi + 1, high);
    }
}

void quicksort_dynvec(dynvec *v, int (*cmp)(const void*, const void*)) {
    if (v->length < 2) return;
    quicksort_rec(v, cmp, 0, v->length - 1);
}

//-----------------------------------------------------------
// Função auxiliar para verificar se o vetor está ordenado
//-----------------------------------------------------------
bool dynvec_is_sorted(dynvec *v, int (*cmp)(const void *, const void *)) {
    for (size_t i = 1; i < v->length; i++) {
        if (cmp(dynvec_get(v, i-1), dynvec_get(v, i)) > 0) {
            return false;
        }
    }
    return true;
}

//-----------------------------------------------------------
// Implementação das variantes do Quicksort
//-----------------------------------------------------------

//================= LOMUTO PARTITION ========================
static size_t partition_lomuto(dynvec *v, int (*cmp)(const void*, const void*), size_t low, size_t high) {
    void *pivot = dynvec_get(v, high);
    size_t i = low;
    
    for (size_t j = low; j < high; j++) {
        if (cmp(dynvec_get(v, j), pivot) < 0) {
            dynvec_swap(v, i, j);
            i++;
        }
    }
    dynvec_swap(v, i, high);
    return i;
}

static void qs_lomuto(dynvec *v, int (*cmp)(const void*, const void*), size_t low, size_t high) {
    if (low < high) {
        size_t p = partition_lomuto(v, cmp, low, high);
        if (p > 0) qs_lomuto(v, cmp, low, p-1);
        qs_lomuto(v, cmp, p+1, high);
    }
}

void quicksort_lomuto(dynvec *v, int (*cmp)(const void *, const void *)) {
    if (v->length < 2 || dynvec_is_sorted(v, cmp)) return;
    qs_lomuto(v, cmp, 0, v->length-1);
}

//============= MEDIAN OF THREE PARTITION ===================
static void median_of_three(dynvec *v, int (*cmp)(const void*, const void*), size_t a, size_t b, size_t c) {
    void *x = dynvec_get(v, a);
    void *y = dynvec_get(v, b);
    void *z = dynvec_get(v, c);
    
    if (cmp(x, y) > 0) dynvec_swap(v, a, b);
    if (cmp(y, z) > 0) dynvec_swap(v, b, c);
    if (cmp(x, y) > 0) dynvec_swap(v, a, b);
}

static size_t partition_mot(dynvec *v, int (*cmp)(const void*, const void*), size_t low, size_t high) {
    size_t mid = low + (high - low)/2;
    median_of_three(v, cmp, low, mid, high);
    return partition_lomuto(v, cmp, low, high);
}

static void qs_mot(dynvec *v, int (*cmp)(const void*, const void*), size_t low, size_t high) {
    if (high > low) {
        size_t p = partition_mot(v, cmp, low, high);
        if (p > 0) qs_mot(v, cmp, low, p-1);
        qs_mot(v, cmp, p+1, high);
    }
}

void quicksort_median_of_three(dynvec *v, int (*cmp)(const void *, const void *)) {
    if (v->length < 2 || dynvec_is_sorted(v, cmp)) return;
    qs_mot(v, cmp, 0, v->length-1);
}

//================= RANDOMIZED PARTITION ====================
static size_t partition_random(dynvec *v, int (*cmp)(const void*, const void*), size_t low, size_t high) {
    size_t random_idx = low + rand() % (high - low + 1);
    dynvec_swap(v, random_idx, high);
    return partition_lomuto(v, cmp, low, high);
}

static void qs_random(dynvec *v, int (*cmp)(const void*, const void*), size_t low, size_t high) {
    if (low < high) {
        size_t p = partition_random(v, cmp, low, high);
        if (p > 0) qs_random(v, cmp, low, p-1);
        qs_random(v, cmp, p+1, high);
    }
}

void quicksort_randomized(dynvec *v, int (*cmp)(const void *, const void *)) {
    if (v->length < 2 || dynvec_is_sorted(v, cmp)) return;
    srand(time(NULL));
    qs_random(v, cmp, 0, v->length-1);
}

//================= THREE WAY PARTITION =====================
static void partition_three_way(dynvec *v, int (*cmp)(const void*, const void*), size_t low, size_t high, size_t *lt, size_t *gt) {
    // Escolhe um pivô aleatório e troca com o elemento em 'low'
    size_t random_pivot = low + rand() % (high - low + 1);
    dynvec_swap(v, low, random_pivot); 
    
    void *pivot = dynvec_get(v, low);
    *lt = low;
    *gt = high;
    size_t i = low + 1;

    while (i <= *gt) {
        int res = cmp(dynvec_get(v, i), pivot);
        if (res < 0) {
            dynvec_swap(v, (*lt)++, i++);
        } else if (res > 0) {
            dynvec_swap(v, i, (*gt)--);
        } else {
            i++;
        }
    }
}

static void qs_three_way(dynvec *v, int (*cmp)(const void*, const void*), size_t low, size_t high) {
    if (high <= low) return;

    size_t lt, gt;
    partition_three_way(v, cmp, low, high, &lt, &gt);

    if (lt > low)
        qs_three_way(v, cmp, low, lt - 1);
    if (gt < high)
        qs_three_way(v, cmp, gt + 1, high);
}

void quicksort_three_way(dynvec *v, int (*cmp)(const void *, const void *)) {
    if (v->length < 2) return;
    qs_three_way(v, cmp, 0, v->length - 1);
}
