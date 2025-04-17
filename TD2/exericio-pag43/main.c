#include <stdio.h>
#include "dynvec.h"

void print_int(void *elem) {
    printf("%d ", *(int *)elem);
}

// Função de comparação para inteiros
int int_cmp(const void *a, const void *b) {
    int x = *(const int*)a;
    int y = *(const int*)b;
    return (x > y) - (x < y);
}

// Predicado: verifica se o número é par
bool is_even(const void *elem) {
    return (*(const int*)elem) % 2 == 0;
}

// Acumulador para soma (usado em fold_left)
void sum_acc(void *acc, const void *elem) {
    *(int*)acc += *(const int*)elem;
}

void double_value(void *elem) {
    *(int*)elem *= 2;
}

int main(void) {
    // Cria um vetor de inteiros
    dynvec *v = dynvec_create(sizeof(int));
    int nums[] = {1, 2, 3, 4, 5, 6};
    for (size_t i = 0; i < 6; i++) {
        dynvec_push(v, &nums[i]);
    }

    printf("Valores originais: ");
    dynvec_map(v, print_int);    
    printf("\n");


    // Testa dynvec_contains
    int target = 3;
    printf("Contém 3? %s\n", dynvec_contains(v, &target, int_cmp) ? "Sim" : "Não");

    // Testa dynvec_index
    printf("Índice de 3: %zu\n", dynvec_index(v, &target, int_cmp));

    // Testa dynvec_fold_left (soma)
    int total = 0;
    dynvec_fold_left(v, &total, sum_acc);
    printf("Soma total: %d\n", total);

    // Testa dynvec_forall (todos pares?)
    printf("Todos pares? %s\n", dynvec_forall(v, is_even) ? "Sim" : "Não");

    // Testa dynvec_exists (existe par?)
    printf("Existe par? %s\n", dynvec_exists(v, is_even) ? "Sim" : "Não");
    
    // Testa dynvec_exists_index (índice do primeiro par)
    printf("Índice do primeiro par: %zu\n", dynvec_exists_index(v, is_even));

    // Testa dynvec_filter (filtra pares)
    dynvec *filtered = dynvec_filter(v, is_even);
    printf("Elementos filtrados (pares): ");
    for (size_t i = 0; i < filtered->length; i++) {
        printf("%d ", *(int*)((char*)filtered->data + (i * filtered->elem_size)));
    }

    printf("\nTeste dynvec_map (dobrar valores):\n");
    printf("Antes de map: ");
    dynvec_map(v, print_int);    
    printf("\n");

    dynvec_map(v, double_value);
    printf("Depois do map: ");
    dynvec_map(v, print_int);    
    printf("\n");

    // Libera memória
    dynvec_free(v);
    dynvec_free(filtered);

    return 0;
}