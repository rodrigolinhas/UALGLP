/*
-- To shuffle an array a of n elements (indices 0..n-1):
for i from 0 to n−2 do
j ← random integer such that i ≤ j ≤ n-1
exchange a[i] and a[j]
*/
//Está certo o código abaixo?
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void knuth_shuffle(int arr[], int n) {
    // Inicializa a semente do gerador de números aleatórios
    srand(time(NULL));
    for (int i = 0; i < n - 1; i++) {
        // Escolhe um índice aleatório entre i e n-i
        int j = i + rand() % (n - i);
        // Troca arr[i] e arr[j]
        int temp = arr[j];
        arr[j] = arr[i];
        arr[i] = temp;
    }
}

void print_array(int arr[], int n) {
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
        printf("\n");
}

int main(void) {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Array original:\n");
    print_array(arr, n);
    // misturar com justiça, usando Knuth Shuffle
    knuth_shuffle(arr, n);
    printf("Array misturado:\n");
    print_array(arr, n);
    return 0;
}
