#include <stdio.h>

int binaria_recursiva(int arr[], int esq, int dir, int chave) {
    if (esq > dir) return -1;
    
    int meio = esq + (dir - esq)/2;
    
    if(arr[meio] == chave) return meio;
    if(arr[meio] < chave)
        return binaria_recursiva(arr, meio+1, dir, chave);
    else
        return binaria_recursiva(arr, esq, meio-1, chave);
}

int main() {
    int arr[] = {2,4,6,8,10,12,14};
    int n = sizeof(arr)/sizeof(arr[0]);
    int chave = 8;
    
    int resultado = binaria_recursiva(arr, 0, n-1, chave);
    
    if(resultado != -1)
        printf("Elemento %d encontrado na posição %d\n", chave, resultado);
    else
        printf("Elemento não encontrado\n");
        
    return 0;
}