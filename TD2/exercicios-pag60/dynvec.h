#ifndef DYNVEC_H
#define DYNVEC_H

#include <stddef.h>
#include <stdbool.h>

typedef struct Dynvec {
    void *data;          // apontador para a sequencia dos elementos
    size_t elem_size;    // tamanho dos elementos de datat (em bytes)
    size_t capacity;     // capacidade total da sequência data
    size_t length;       // quantidade atual dos elementos arquivados
} dynvec;

// TD1
dynvec* dynvec_create       (size_t elem_size);
void    dynvec_push         (dynvec *v, const void *elem);
void    dynvec_free         (dynvec *v);

// novo
void    dynvec_map          (dynvec *v, void (*processo)(void *));
bool    dynvec_contains     (const dynvec *v, const void *elem, int (*cmp)(const void*, const void*));
size_t  dynvec_index        (const dynvec *v, const void *elem, int (*cmp)(const void*, const void*));
void    dynvec_fold_left    (const dynvec *v, void *acc, void (*func)(void *acc, const void *elem));
bool    dynvec_forall       (const dynvec *v, bool (*predicate)(const void *elem));
bool    dynvec_exists       (const dynvec *v, bool (*predicate)(const void *elem));
size_t  dynvec_exists_index (const dynvec *v, bool (*predicate)(const void *elem));
dynvec* dynvec_filter       (const dynvec *v, bool (*predicate)(const void *elem));

#endif