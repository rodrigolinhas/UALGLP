/*
-- To shuffle an array a of n elements (indices 0..n-1):
for i from n−1 down to 1 do
j ← random integer such that 0 ≤ j ≤ i
exchange a[j] and a[i]
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void knuth_shuffle(int arr[], int n) {
    // Inicializa a semente do gerador de números aleatórios
    srand(time(NULL));
    for (int i = n - 1; i > 0; i--) {
        // Escolhe um índice aleatório entre 0 e i
        int j = rand() % (i + 1);
        // Troca arr[i] e arr[j]
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

void print_array(int arr[], int n) {
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
        printf("\\n");
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Array original:\\n");
    print_array(arr, n);
    // misturar com justiça, usando Knuth Shuffle
    knuth_shuffle(arr, n);
    printf("Array misturado:\\n");
    print_array(arr, n);
    return 0;
}

/*
A mistura de Knuth
É fácil de escrever
Tem complexidade O(n)
Gera cada uma das n! permutações com a mesma probabilidade
*/