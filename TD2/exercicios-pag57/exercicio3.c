#include <stdio.h>

int binaria_contagem(int arr[], int n, int chave, int *comp) {
    *comp = 0;
    int esq = 0, dir = n-1;
    while(esq <= dir) {
        int meio = esq + (dir - esq)/2;
        (*comp)++;
        
        if(arr[meio] == chave) return meio;
        if(arr[meio] < chave) esq = meio+1;
        else dir = meio-1;
    }
    return -1;
}

int main() {
    int arr[] = {2,4,6,8,10,12,14};
    int n = sizeof(arr)/sizeof(arr[0]);
    int comparacoes;
    
    int chave = 12;
    int resultado = binaria_contagem(arr, n, chave, &comparacoes);
    
    if(resultado != -1)
        printf("Encontrado em %d posições (Comparações: %d)\n", resultado, comparacoes);
    else
        printf("Não encontrado (Comparações: %d)\n", comparacoes);
    
    return 0;
}