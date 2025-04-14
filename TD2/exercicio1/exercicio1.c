#include <stdio.h>
#include <stdlib.h>

// Funções de transformação
int dobrar(int x)       {return x * 2;}

int triplicar(int x)    {return x * 3;}

int quadrado(int x)     {return x * x;}

int main(void){
    
    // Vetor de apontadores para funções
    int (*vetor_funcoes[3])(int) = {
        dobrar, 
        triplicar, 
        quadrado
    };

    int opcao;
    int valor;
    int tamanho = 0;
    int capacidade = 10; // Capacidade inicial do vetor
    int *vetor = malloc(capacidade * sizeof(int));

    if (vetor == NULL){
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    // Lê valores até encontrar uma entrada inválida
    printf("Digite os elementos do vetor (digite um valor não inteiro para parar):\n");
    while (scanf("%d", &valor) == 1){
        // Se o vetor estiver cheio, aumenta a capacidade
        if (tamanho >= capacidade){
            capacidade *= 2;
            vetor = realloc(vetor, capacidade * sizeof(int));
            if (vetor == NULL){
                printf("Erro ao realocar memória!\n");
                return 1;
            }
        }
        vetor[tamanho++] = valor;
    }

    // Redimensiona o vetor para o tamanho exato
    vetor = realloc(vetor, tamanho * sizeof(int));
    if (vetor == NULL && tamanho > 0){
        printf("Erro ao redimensionar memória!\n");
        return 1;
    }

    // Limpa o buffer de entrada para evitar problemas com a próxima leitura
    while (getchar() != '\n') ;

    // Menu de opções
    printf("\nEscolha uma transformação:\n");
    printf("1 - Dobrar o valor\n");
    printf("2 - Triplicar o valor\n");
    printf("3 - Elevar o valor ao quadrado\n");
    printf("Opção: ");
    scanf("%d", &opcao);

    // Valida a opção escolhida
    if (opcao < 1 || opcao > 3){
        printf("Opção inválida!\n");
        free(vetor);
        return 1;
    }

    // Aplica a transformação escolhida a cada elemento do vetor
    for (int i = 0; i < tamanho; i++){
        vetor[i] = vetor_funcoes[opcao - 1](vetor[i]);
    }

    // Exibe o vetor transformado
    printf("\nVetor transformado:\n");
    for (int i = 0; i < tamanho; i++){
        printf("%d ", vetor[i]);
    }
    printf("\n");
    
    // Libera a memória alocada para o vetor
    free(vetor);

    return 0;
}