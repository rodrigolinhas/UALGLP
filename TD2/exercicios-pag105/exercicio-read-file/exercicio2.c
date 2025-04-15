/**
 * fopen("exemplo.txt", "r")
 * fscanf, fgets, fread
 * fclose
 */


#include <stdio.h>
#include <string.h>
int main(void) {
    char str[100];
    int counter = 0;
    FILE *fp = fopen("entrada.txt", "r"); // Abre o ficheiro para leitura
    if (fp == NULL) {
        perror("Erro ao abrir o ficheiro");
        return 1;
    }
    // Lê a string do ficheiro
    while (fgets(str, sizeof(str), fp) != NULL) {
        counter++;
    }    
    printf("O número de linhas lidas é: %d\n", counter);
    fclose(fp); // Fecha o ficheiro
    return 0;
}
 /*#include <stdio.h>
int main() {
    char linha[256];
    FILE *fp = fopen("exemplo.txt", "r"); // Abre o ficheiro para leitura
    if (fp == NULL) {
        perror("Erro ao abrir o ficheiro");
        return 1;
    }
// Lê e imprime cada linha do ficheiro
    while (fgets(linha, sizeof(linha), fp) != NULL) {
        printf("%s", linha);
    }
    fclose(fp);
    return 0;
}*/