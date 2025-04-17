#include <stdio.h>

int upper_bound(int arr[], int n, int chave) {
    int esq = 0, dir = n-1, res = -1;
    while(esq <= dir) {
        int meio = esq + (dir - esq)/2;
        if(arr[meio] <= chave) {
            res = meio;
            esq = meio+1;
        } else {
            dir = meio-1;
        }
    }
    return res;
}

int main() {
    int arr[] = {2,4,6,8,10,12,14};
    int n = sizeof(arr)/sizeof(arr[0]);
    
    printf("Upper bound para 9: %d\n", upper_bound(arr, n, 9));
    printf("Upper bound para 10: %d\n", upper_bound(arr, n, 10));
    
    return 0;
}