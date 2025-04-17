#ifndef DYNVEC_SEARCH_H
#define DYNVEC_SEARCH_H

#include "dynvec.h"

void* dynvec_lsearch(const dynvec *v, const void *key, int (*cmp)(const void*, const void*)) {
    for(size_t i = 0; i < v->length; i++) {
        void *elem = (char*)v->data + (i * v->elem_size);
        if(cmp(elem, key) == 0) return elem;
    }
    return NULL;
}

void* dynvec_bsearch(const dynvec *v, const void *key, int (*cmp)(const void*, const void*)) {
    size_t esq = 0, dir = v->length - 1;
    
    while(esq <= dir) {
        size_t meio = esq + (dir - esq)/2;
        void *elem = (char*)v->data + (meio * v->elem_size);
        int comparacao = cmp(elem, key);

        if(comparacao == 0) return elem;
        if(comparacao < 0) esq = meio + 1;
        else dir = meio - 1;
    }
    return NULL;
}

#endif
