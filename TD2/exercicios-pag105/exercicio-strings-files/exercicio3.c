/**
 * Combine os conhecimentos de strings e ficheiros. Escreva um programa que:
 * Leia uma string do utilizador.
 * Grave essa string num ficheiro.
 * Leia o conteúdo do ficheiro e, usando funções da biblioteca string.h, 
 * conte quantas vezes uma determinada palavra (também fornecida pelo utilizador)
 * aparece na string lida do ficheiro.
 */

#include <stdio.h>
#include <string.h>

int main(void) {
    char frase[1000], palavra[100], conteudo[1000];
    FILE *arquivo;
    int contador = 0;

    // Ler a string do utilizador
    printf("Digite uma string: ");
    fgets(frase, sizeof(frase), stdin);
    frase[strcspn(frase, "\n")] = '\0'; // Remove a quebra de linha

    // Escrever no ficheiro
    arquivo = fopen("arquivo.txt", "w");
    if (arquivo == NULL) {
        perror("Erro ao criar arquivo");
        return 1;
    }
    fprintf(arquivo, "%s", frase);
    fclose(arquivo);

    // Ler conteúdo do ficheiro
    arquivo = fopen("arquivo.txt", "r");
    if (arquivo == NULL) {
        perror("Erro ao ler arquivo");
        return 1;
    }
    size_t bytes_lidos = fread(conteudo, 1, sizeof(conteudo) - 1, arquivo);
    conteudo[bytes_lidos] = '\0';
    fclose(arquivo);

    // Ler palavra a procurar
    printf("Digite a palavra a ser contada: ");
    fgets(palavra, sizeof(palavra), stdin);
    palavra[strcspn(palavra, "\n")] = '\0';

    // evitar contagem de palavras semelhantes e simbolos indesejados
    // Exemplo: "cachorro" e não contar "cachorros" ou "cahorro!"
    char *token;
    const char *delimitadores = " \t\n\r.,;:!?()";

    token = strtok(conteudo, delimitadores);
    while (token != NULL) {
        if (strcmp(token, palavra) == 0) contador++;
        token = strtok(NULL, delimitadores);
    }

    printf("A palavra '%s' aparece %d vezes.\n", palavra, contador);
    return 0;
}