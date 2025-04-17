#include <stdio.h>

int primeiro_indice(int arr[], int n, int chave) {
    int esq = 0, dir = n-1, res = -1;
    while(esq <= dir) {
        int meio = esq + (dir - esq)/2;
        if(arr[meio] >= chave) dir = meio-1;
        else esq = meio+1;
        
        if(arr[meio] == chave) res = meio;
    }
    return res;
}

int ultimo_indice(int arr[], int n, int chave) {
    int esq = 0, dir = n-1, res = -1;
    while(esq <= dir) {
        int meio = esq + (dir - esq)/2;
        if(arr[meio] <= chave) esq = meio+1;
        else dir = meio-1;
        
        if(arr[meio] == chave) res = meio;
    }
    return res;
}

int main() {
    int arr[] = {2,4,6,8,8,8,10,12};
    int n = sizeof(arr)/sizeof(arr[0]);
    
    printf("Primeira ocorrência de 8: %d\n", primeiro_indice(arr, n, 8));
    printf("Última ocorrência de 8: %d\n", ultimo_indice(arr, n, 8));
    
    return 0;
}