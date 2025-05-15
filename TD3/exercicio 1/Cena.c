#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "Cena.h"
//REVER
/*
que aloca dinamicamente uma Cena com malloc , preencha os seus campos
textuais com recurso à função strcpy e a partir dos parâmetros passados
( descritivo , tipo , nopcoes , vopcoes ). A função deverá verificar que uma
cena de tipo NORMAL tem pelo menos uma opção possível de continuação
( nopcoes >0 e o vetor vopcoes contém exactamente nopcoes descrições textuais
das opções possíveis). Deverá também verificar as cenas de tipo WON ou FAILED
não têm nenhuma opção de continuação ( nopcoes é 0). Em caso de erro, poderá
usar os recursos da biblioteca errno.h e deverá devolver o apontador NULL
*/
Cena *criaCena(char *descritivo, TipoCena tipo, int nopcoes, char **vopcoes) {
    // Verifica se o número de opções é válido
    if ((tipo == NORMAL && nopcoes <= 0) || (tipo != NORMAL && nopcoes != 0)) {
        #ifdef DEBUG
        errno = EINVAL; // Define o erro como argumento inválido
        perror("Erro: Cena de tipo NORMAL deve ter pelo menos uma opção.\n");
        #endif
        return NULL; // Retorna NULL em caso de erro
    }

    // Aloca memória para a nova cena
    Cena *novaCena = (Cena *)malloc(sizeof(Cena));
    if (novaCena == NULL) {
        #ifdef DEBUG
        errno = ENOMEM; // Define o erro como falta de memória
        perror("Erro: Falha ao alocar memória para a nova cena.\n");
        #endif
        return NULL; // Retorna NULL se a alocação falhar
    }

    // Preenche os campos da nova cena
    novaCena->tipo = tipo;
    novaCena->nopcoes = nopcoes;
    novaCena->descritivo = (char *)malloc(MAXTXT*sizeof(char));
    
    if (novaCena->descritivo == NULL) {
        #ifdef DEBUG
        errno = ENOMEM; // Define o erro como falta de memória
        perror("Erro: Falha ao alocar memória para o descritivo.\n");
        #endif
        free(novaCena);
        return NULL; // Retorna NULL se a alocação falhar
    }
    strcpy(novaCena->descritivo, descritivo);

    // Verificar se vopcoes é NULL quando necessário
    if (tipo == NORMAL && (nopcoes <= 0 || vopcoes == NULL)) {
        #ifdef DEBUG
        errno = EINVAL;
        perror("Erro: Cena de tipo NORMAL deve ter opções válidas.\n");
        #endif
        return NULL;
    }

    // Aloca memória para as opções de continuação
    novaCena->vopcoes = (char **)malloc(nopcoes * sizeof(char *));
    if (novaCena->vopcoes == NULL) {
        #ifdef DEBUG
        errno = ENOMEM; // Define o erro como falta de memória
        perror("Erro: Falha ao alocar memória para as opções.\n");
        #endif
        free(novaCena->descritivo);
        free(novaCena);
        return NULL; // Retorna NULL se a alocação falhar
    }

    // Preenche as opções de continuação
    for (int i = 0; i < nopcoes; i++) {
        novaCena->vopcoes[i] = (char *)malloc(strlen(vopcoes[i]) + 1);
        if (novaCena->vopcoes[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(novaCena->vopcoes[j]);
            }
            free(novaCena->vopcoes);
            free(novaCena->descritivo);
            free(novaCena);
            return NULL; // Retorna NULL se a alocação falhar
        }
        strcpy(novaCena->vopcoes[i], vopcoes[i]);
    }

    return novaCena; // Retorna o apontador para a nova cena criada
}

/*
que imprime na saída standard o conteúdo da cena c , à semelhança dos
exemplos acima descritos. As opções consideradas são sempre numeradas 'a' ,
'b' , 'c' etc...
*/
void mostrarCena(Cena *c) {
    if (c == NULL) {
        #ifdef DEBUG
        errno = EINVAL; // Define o erro como argumento inválido
        perror("Erro: Cena inválida.\n");
        #endif
        return;
    }

    // Formato: [ID] (ID não está na estrutura, omitido aqui)
    printf("<<<\n%s\n>>>", c->descritivo);
    
    // Adicionar tipo/número de opções
    if (c->tipo == NORMAL) {
        printf("<%d>\n", c->nopcoes);
        printf("***\n");
        for (int i = 0; i < c->nopcoes; i++) {
            printf("+ %c. %s\n", 'a' + i, c->vopcoes[i]);
        }
        printf("***\n");
    } else {
        printf("<%s>\n", (c->tipo == WON) ? "WON" : "FAILED");
        printf("***\n");
    }
}
/*
que liberta a memória apontada por c assim como a dos seus campos.
*/
void libertaCena(Cena *c) {
    if (c == NULL) {
        #ifdef DEBUG
        errno = EINVAL; // Define o erro como argumento inválido
        perror("Erro: Cena inválida.\n");
        #endif
        return; // Verifica se a cena é válida
    }

    free(c->descritivo); // Libera a memória da descritivo
    for (int i = 0; i < c->nopcoes; i++) {
        free(c->vopcoes[i]); // Libera a memória de cada opção
    }
    free(c->vopcoes); // Libera a memória do vetor de opções
    free(c); // Libera a memória da cena
}