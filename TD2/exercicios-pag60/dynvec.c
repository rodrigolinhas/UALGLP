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