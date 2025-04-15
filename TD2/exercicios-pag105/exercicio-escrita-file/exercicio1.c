/**
 * fopen("exemplo.txt", "w")
 * fprintf, fwrite, fputs
 * fclose
 */
#include <stdio.h>

int main(void) {
    printf("Escreva uma frase:\n");
    FILE *fp = fopen("saida.txt", "w"); // Abre o ficheiro para escrita
    if (fp == NULL) {
        perror("Erro ao abrir o ficheiro");
        return 1;
    }
    char frase[100];
    fgets(frase, sizeof(frase), stdin); // Lê a frase do utilizador
    fprintf(fp, "%s", frase); // Escreve a frase no ficheiro
    fclose(fp); // Fecha o ficheiro
    printf("Dados escritos com sucesso em saida.txt\n");
    return 0;
}


/*#include <stdio.h>
int main() {
    FILE *fp = fopen("exemplo.txt", "w"); // Abre o ficheiro para escrita
    if (fp == NULL) {
        perror("Erro ao abrir o ficheiro");
        return 1;
    }
    fprintf(fp, "Olá, este é um exemplo de escrita em
    ficheiro.\n");
    fclose(fp); // Fecha o ficheiro
    printf("Dados escritos com sucesso em exemplo.txt\n");
    return 0;
}*/