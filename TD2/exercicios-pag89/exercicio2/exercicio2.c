#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "dynvec.h"

// Comparator for integers
int cmp_int(const void* a, const void* b) {
    int ai = *(const int*)a;
    int bi = *(const int*)b;
    return (ai > bi) - (ai < bi);
}

// Print each element (assumes int)
void print_elem(void *elem) {printf("%d ", *(int*)elem);}

// Test harness for a given quicksort variant
void test_qsort(const char *name, void (*sort_func)(dynvec*, int (*)(const void*, const void*)),
                    int data[], size_t n) {
    dynvec *v = dynvec_create(sizeof(int));
    for (size_t i = 0; i < n; i++) {
        dynvec_push(v, &data[i]);
    }
    printf("--- %s ---\n", name);
    printf("Before: "); 
    dynvec_map(v, print_elem); 
    printf("\n");
    sort_func(v, cmp_int);
    printf("After:  "); 
    dynvec_map(v, print_elem); 
    printf("\n");
    printf("Sorted? %s\n\n", dynvec_is_sorted(v, cmp_int) ? "yes" : "no");
    dynvec_free(v);
}

int main(void) {
    int sample[] = {5, 3, 8, 1, 2, 7, 4, 6};
    size_t n = sizeof(sample) / sizeof(sample[0]);

    test_qsort("quicksort_dynvec", quicksort_dynvec, sample, n);
    test_qsort("quicksort_lomuto", quicksort_lomuto, sample, n);
    test_qsort("quicksort_median_of_three", quicksort_median_of_three, sample, n);
    test_qsort("quicksort_randomized", quicksort_randomized, sample, n);
    test_qsort("quicksort_three_way", quicksort_three_way, sample, n);

    // Edge cases
    int empty[] = {};
    printf("--- Edge Case: Empty Vector ---\n");
    dynvec *ve = dynvec_create(sizeof(int));
    quicksort_dynvec(ve, cmp_int);
    printf("Sorted empty? %s\n\n", dynvec_is_sorted(ve, cmp_int) ? "yes" : "no");
    dynvec_free(ve);

    int single = 42;
    printf("--- Edge Case: Single Element ---\n");
    dynvec *vs = dynvec_create(sizeof(int));
    dynvec_push(vs, &single);
    quicksort_dynvec(vs, cmp_int);
    printf("Sorted single? %s\n", dynvec_is_sorted(vs, cmp_int) ? "yes" : "no");
    dynvec_free(vs);

    return 0;
}
