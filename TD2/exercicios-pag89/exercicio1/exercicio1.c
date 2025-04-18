#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include "dynvec.h"

// Comparator for integers
int cmp_int(const void* a, const void* b) {
    int ai = *(const int*)a;
    int bi = *(const int*)b;
    return (ai > bi) - (ai < bi);
}

// Auxiliar para print_dynvec
void print_elem(void* elem) {
    printf("%d ", *(int*)elem);
}

// Print helper para dynvec de inteiros
void print_dynvec(const dynvec* v) {
    dynvec_map((dynvec*)v, print_elem);  // cast seguro porque print_elem não altera os dados
    printf("\n");
}

int main(void) {
    int arr[] = {5, 3, 8, 1, 2, 7, 4, 6};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    int arr1[] = {7, 45, 12, 9, 0, 98, 110, 5, 63, 96, 70, 1, 36};
    size_t n1 = sizeof(arr1) / sizeof(arr1[0]);
    int arr2[] = {7, 6, 3, 25, 110, 7, 9, 0, 2, 18, 69, 1, 36, 72, 4, 5};
    size_t n2 = sizeof(arr2) / sizeof(arr2[0]);
    int arr3[] = {1, 8, 4, 5, 9, 7, 3, 2, 0, 9, 10, 6, 11, 12, 13, 14, 15, 16, 17, 18, 19};
    size_t n3 = sizeof(arr3) / sizeof(arr3[0]);

    dynvec* v = dynvec_create(sizeof(int));
    for (size_t i = 0; i < n; ++i) {
        dynvec_push(v, &arr[i]);
    }
    dynvec* v1 = dynvec_create(sizeof(int));
    for (size_t i = 0; i < n1; ++i) {
        dynvec_push(v1, &arr1[i]);
    }
    dynvec* v2 = dynvec_create(sizeof(int));
    for (size_t i = 0; i < n2; ++i) {
        dynvec_push(v2, &arr2[i]);
    }
    dynvec* v3 = dynvec_create(sizeof(int));
    for (size_t i = 0; i < n3; ++i) {
        dynvec_push(v3, &arr3[i]);
    }
    
    printf("\n");
    printf("QUICKSORT:\n");
    printf("\n");
    printf("Original: ");
    print_dynvec(v);
    quicksort_dynvec(v, cmp_int);
    printf("Ordenado: ");
    print_dynvec(v);
    printf("Está ordenado? %s\n", dynvec_is_sorted(v, cmp_int) ? "true" : "false");
    dynvec_free(v);

    printf("\n");
    printf("MERGESORT:\n");
    printf("Original: ");
    print_dynvec(v1);
    mergesort_dynvec(v1, cmp_int);
    printf("Ordenado: ");
    print_dynvec(v1);
    printf("Está ordenado? %s\n", dynvec_is_sorted(v1, cmp_int) ? "true" : "false");
    dynvec_free(v1);
    printf("\n");

    printf("HEAPSORT:\n");
    printf("Original: ");
    print_dynvec(v2);
    heapsort_dynvec(v2, cmp_int);
    printf("Ordenado: ");
    print_dynvec(v2);
    printf("Está ordenado? %s\n", dynvec_is_sorted(v2, cmp_int) ? "true" : "false");
    dynvec_free(v2);
    printf("\n");

    printf("INSERTION SORT:\n");
    printf("Original: ");
    print_dynvec(v3);
    insertion_sort_dynvec(v3, cmp_int);
    printf("Ordenado: ");
    print_dynvec(v3);
    printf("Está ordenado? %s\n", dynvec_is_sorted(v3, cmp_int) ? "true" : "false");
    dynvec_free(v3);

    printf("\n");

    return 0;
}
