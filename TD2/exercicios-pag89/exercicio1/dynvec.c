#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
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

static void merge(dynvec *v, int (*cmp)(const void*, const void*), 
                 size_t l, size_t m, size_t r, void *tmp) {
    size_t i = l, j = m, k = 0;
    
    while (i < m && j < r) {
        if (cmp(dynvec_get(v, i), dynvec_get(v, j)) <= 0) {
            memcpy((char*)tmp + (k++ * v->elem_size), dynvec_get(v, i++), v->elem_size);
        } else {
            memcpy((char*)tmp + (k++ * v->elem_size), dynvec_get(v, j++), v->elem_size);
        }
    }
    
    while (i < m) memcpy((char*)tmp + (k++ * v->elem_size), dynvec_get(v, i++), v->elem_size);
    while (j < r) memcpy((char*)tmp + (k++ * v->elem_size), dynvec_get(v, j++), v->elem_size);
    
    memcpy((char*)v->data + (l * v->elem_size), tmp, k * v->elem_size);
}

static void mergesort_rec(dynvec *v, int (*cmp)(const void*, const void*), 
                         size_t l, size_t r, void *tmp) {
    if (r - l <= 1) return;
    
    size_t m = l + (r - l) / 2;
    mergesort_rec(v, cmp, l, m, tmp);
    mergesort_rec(v, cmp, m, r, tmp);
    merge(v, cmp, l, m, r, tmp);
}

void mergesort_dynvec(dynvec *v, int (*cmp)(const void*, const void*)) {
    void *tmp = malloc(v->length * v->elem_size);
    mergesort_rec(v, cmp, 0, v->length, tmp);
    free(tmp);
}

static void heapify(dynvec *v, int (*cmp)(const void*, const void*), size_t n, size_t i) {
    size_t largest = i;
    size_t left = 2 * i + 1;
    size_t right = 2 * i + 2;

    if (left < n && cmp(dynvec_get(v, left), dynvec_get(v, largest)) > 0) {
        largest = left;
    }

    if (right < n && cmp(dynvec_get(v, right), dynvec_get(v, largest)) > 0) {
        largest = right;
    }

    if (largest != i) {
        dynvec_swap(v, i, largest);
        heapify(v, cmp, n, largest);
    }
}

void heapsort_dynvec(dynvec *v, int (*cmp)(const void*, const void*)) {
    // Build heap
    for (int i = v->length / 2 - 1; i >= 0; i--) {
        heapify(v, cmp, v->length, i);
    }

    // Extract elements
    for (int i = v->length - 1; i > 0; i--) {
        dynvec_swap(v, 0, i);
        heapify(v, cmp, i, 0);
    }
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

void quicksort_dynvec(dynvec *v, int (*cmp)(const void*, const void*))  {quicksort_rec(v, cmp, 0, v->length - 1);}

bool dynvec_is_sorted(dynvec *v, int (*cmp)(const void *, const void *)) {
    for (size_t i = 1; i < v->length; ++i) {
        void *prev = (char*)v->data + (i - 1) * v->elem_size;
        void *curr = (char*)v->data + i * v->elem_size;
        if (cmp(prev, curr) > 0) return false;
    }
    return true;
}
