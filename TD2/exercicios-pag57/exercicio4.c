#include <stdio.h>

int lower_bound(int arr[], int n, int chave) {
    int esq = 0, dir = n-1, res = -1;
    while(esq <= dir) {
        int meio = esq + (dir - esq)/2;
        if(arr[meio] >= chave) {
            res = meio;
            dir = meio-1;
        } else {
            esq = meio+1;
        }
    }
    return res;
}

int main() {
    int arr[] = {2,4,6,8,10,12,14};
    int n = sizeof(arr)/sizeof(arr[0]);
    
    printf("Lower bound para 7: %d\n", lower_bound(arr, n, 7));
    printf("Lower bound para 8: %d\n", lower_bound(arr, n, 8));
    
    return 0;
}