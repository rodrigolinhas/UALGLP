#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
//REVER
//Assuma que o tamanho máximo de um texto é definido via uma macro MAXTXT com o valor 4096
#define MAXTXT 4096
//Assuma que o número máximo de escolhas é definido via uma macro MAXCHOICE com o valor 10
#define MAXCHOICE 10

typedef enum {NORMAL, WON, FAILED} TipoCena;

typedef struct Cena {
    char *descritivo;
    TipoCena tipo;
    int nopcoes;
    char **vopcoes;
} Cena;


typedef struct no {
    Cena *cena;             // Apontador para a cena
    struct no **vizinhos;   // Vetor de apontadores para vizinhos
    int nvizinhos;          // Número de vizinhos
} No;

/*
Considere o tipo estrutural historia que tem dois campos. O primeiro campo é um
apontador para o nó que arquiva a cena inicial da história. O segundo campo é um
apontador para o nó que contem a cena atualmente ativa da história a decorrer.
Define o tipo historia 
*/
typedef struct historia {
    No *cena_inicial;  // Apontador para a cena inicial
    No *cena_ativa;    // Apontador para a cena atualmente ativa
    int  n_cenas;      // Número total de cenas
    Cena **cenas;      // Apontador para o vetor de cenas
    No   **nos;        // Apontador para o vetor de nós
} historia;
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

/*
que cria um nó com o conteúdo a apontar para a cena que está no endereço c e
que terá nvizinhos vizinhos. As células do vetor de vizinhos é inicializado,
nesta função, com o valor NULL 
*/
No *criaNo(Cena *c, int nvizinhos){
    if (c == NULL || nvizinhos < 0 || (c->tipo == NORMAL && nvizinhos != c->nopcoes)) {
        #ifdef DEBUG
        errno = EINVAL;
        perror("Erro: Parâmetros inválidos para criar nó.\n");
        #endif
        return NULL;
    }

    No *novoNo = (No *)malloc(sizeof(No));
    if (novoNo == NULL) {
        #ifdef DEBUG
        errno = ENOMEM; // Define o erro como falta de memória
        perror("Erro: Falha ao alocar memória para o novo nó.\n");
        #endif
        return NULL; // Retorna NULL se a alocação falhar
    }

    novoNo->cena = c;
    novoNo->nvizinhos = nvizinhos;
    novoNo->vizinhos = (No **)malloc(nvizinhos * sizeof(No *));
    
    if (novoNo->vizinhos == NULL) {
        free(novoNo);
        #ifdef DEBUG
        errno = ENOMEM; // Define o erro como falta de memória
        perror("Erro: Falha ao alocar memória para os vizinhos do nó.\n");
        #endif
        return NULL; // Retorna NULL se a alocação falhar
    }

    for (int i = 0; i < nvizinhos; i++) {
        novoNo->vizinhos[i] = NULL; // Inicializa os vizinhos com NULL
    }

    return novoNo; // Retorna o apontador para o novo nó criado
}

/*
que coloca a posição pos do vetor de vizinhos do nó no a apontar para v 
*/
void juntaVizinhoNo(No *no, int pos, No* v){
    if (no == NULL || pos < 0 || pos >= no->nvizinhos) {
        #ifdef DEBUG
        errno = EINVAL; // Define o erro como argumento inválido
        perror("Erro: Nó inválido ou posição inválida.\n");
        #endif
        return; // Retorna se o nó ou a posição forem inválidos
    }

    no->vizinhos[pos] = v; // Junta o vizinho na posição especificada
}

/*
que devolve a referência do nó que corresponde à escolha escolha tendo em
conta às opções possíveis propostas pela cena contida no no_ativo . Em caso de
anomalia (como o de uma escolha inválida), o programa deverá reagir de forma
adequada, garantindo a robustez da execução.
*/
No *proximoNo(No *no_ativo, int escolha) {
    if (no_ativo == NULL || no_ativo->cena == NULL || no_ativo->nvizinhos != no_ativo->cena->nopcoes) {
        #ifdef DEBUG
        errno = EINVAL;
        perror("Erro: Nó ativo inválido ou inconsistência entre opções e vizinhos.\n");
        #endif
        return NULL;
    }
    if (escolha < 0 || escolha >= no_ativo->nvizinhos) {
        #ifdef DEBUG
        errno = EINVAL;
        perror("Erro: Escolha inválida.\n");
        #endif
        return NULL;
    }
    return no_ativo->vizinhos[escolha];
}


//Mostra a informação da cena (o seu descritivo, etc.) contida no nó no .
void mostraCenaNo(No *no){
    if (no == NULL) {
        #ifdef DEBUG
        errno = EINVAL; // Define o erro como argumento inválido
        perror("Erro: Nó inválido.\n");
        #endif
        return; // Retorna se o nó for inválido
    }

    mostrarCena(no->cena); // Mostra a cena contida no nó
}

/*
Que informa do tipo de cena contida no nó no .
*/
TipoCena estadoCenaNo(No *no) {
    if (no == NULL || no->cena == NULL) {
        #ifdef DEBUG
        errno = EINVAL;
        perror("Erro: Nó inválido.\n");
        #endif
        return FAILED; // Valor padrão em caso de erro
    }
    return no->cena->tipo;
}

/*
Que permite ao utilizador escolher uma opção dentro das possíveis na
cena contida no nó no 
*/
int escolheCenaNo(No *no){
    if (no == NULL) {
        #ifdef DEBUG
        errno = EINVAL; // Define o erro como argumento inválido
        perror("Erro: Nó inválido.\n");
        #endif
        return -1; // Retorna -1 se o nó for inválido
    }

    int escolha;
    printf("Escolha uma opção (0-%d): ", no->cena->nopcoes - 1);
    scanf("%d", &escolha);

    if (escolha < 0 || escolha >= no->cena->nopcoes) {
        #ifdef DEBUG
        errno = EINVAL; // Define o erro como argumento inválido
        perror("Erro: Escolha inválida.\n");
        #endif
        return -1; // Retorna -1 se a escolha for inválida
    }

    return escolha; // Retorna a escolha válida do usuário
}

// Função auxiliar: lê bloco descritivo até ">>>", retornando parte após ">>>" se existir
static char *leBloco(FILE *in, char *buffer) {
    char line[512];
    buffer[0] = '\0';
    while (fgets(line, sizeof line, in)) {
        char *p = strstr(line, ">>>");
        if (p) {
            // tudo antes de >>> é descritivo
            *p = '\0';
            strncat(buffer, line, MAXTXT - strlen(buffer) - 1);
            p += 3;
            // pula espaços
            while (*p == ' ' || *p == '\t') p++;
            if (*p == '<') {
                // retorna tipo+opções numa string alocada
                return strdup(p);
            }
            return NULL; // tipo será lido separadamente
        }
        strncat(buffer, line, MAXTXT - strlen(buffer) - 1);
    }
    return NULL;
}

// Cria toda a história lendo da stdin
historia *criaHistoria(void) {
    int n;
    if (scanf("%d\n", &n) != 1 || n <= 0) {
        errno = EINVAL;
        return NULL;
    }

    Cena *cenas_arr[n];
    No   *nos_arr[n];
    int   targets[n][MAXCHOICE];
    char *vtxt[n][MAXCHOICE];
    char  *typeLine;
    char   descript[MAXTXT];

    for (int i = 0; i < n; i++) {
        // lê índice [i]
        char tmp[64];
        if (!fgets(tmp, sizeof tmp, stdin) || !strchr(tmp, '[')) {
            errno = EINVAL;
            return NULL;
        }
        // lê <<< e bloco até >>>, capturando tipoLine se após >>>
        typeLine = leBloco(stdin, descript);
        if (!typeLine) {
            // tipo e opções não na mesma linha
            typeLine = malloc(64);
            if (!fgets(typeLine, 64, stdin)) {
                free(typeLine);
                errno = EINVAL;
                return NULL;
            }
        }
        // parse tipo/num opções
        TipoCena tipo;
        int nopc = 0;
        if (strstr(typeLine, "WON")) tipo = WON;
        else if (strstr(typeLine, "FAILED")) tipo = FAILED;
        else if (sscanf(typeLine, "<%d>", &nopc) == 1) tipo = NORMAL;
        else {
            free(typeLine);
            errno = EINVAL;
            return NULL;
        }
        free(typeLine);
        
        // se NORMAL, lê opções
        if (tipo == NORMAL) {
            fgets(tmp, sizeof tmp, stdin); // "***"
            for (int j = 0; j < nopc; j++) {
                char line[512];
                fgets(line, sizeof line, stdin);
                int tgt;
                if (sscanf(line + 2, "%d.", &tgt) != 1) {
                    errno = EINVAL;
                    return NULL;
                }
                targets[i][j] = tgt;
                vtxt[i][j] = strdup(line + 2);
            }
            fgets(tmp, sizeof tmp, stdin); // "***"
        }
        // cria cena e nó
        cenas_arr[i] = criaCena(descript, tipo, nopc,
                                 (tipo == NORMAL) ? vtxt[i] : NULL);
        nos_arr[i]   = criaNo(cenas_arr[i], nopc);
        if (!cenas_arr[i] || !nos_arr[i]) {
            perror("Erro a criar cena/nó");
            return NULL;
        }
    }
    // Liga vizinhos
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < nos_arr[i]->nvizinhos; j++) {
            juntaVizinhoNo(nos_arr[i], j, nos_arr[ targets[i][j] ]);
        }
    }
    historia *H = malloc(sizeof *H);
    H->cena_inicial = nos_arr[0];
    H->cena_ativa   = nos_arr[0];
    H->n_cenas      = n;
    H->cenas        = malloc(n * sizeof(Cena*));
    H->nos          = malloc(n * sizeof(No*));
    memcpy(H->cenas, cenas_arr, n * sizeof(Cena*));
    memcpy(H->nos,   nos_arr,   n * sizeof(No*));
    return H;
}

int main(void) {
    historia *H = criaHistoria();
    if (!H) {
        perror("criaHistoria");
        return 1;
    }
    No *atual = H->cena_ativa;
    while (estadoCenaNo(atual) == NORMAL) {
        int escolha_id;
        if (scanf("%d", &escolha_id) != 1) {
            printf("WAITING\n");
            goto cleanup;
        }
        int idx = -1;
        for (int i = 0; i < atual->nvizinhos; i++) {
            int tgt;
            if (sscanf(atual->cena->vopcoes[i], "%d.", &tgt) == 1
                && tgt == escolha_id) {
                idx = i; break;
            }
        }
        if (idx < 0) {
            printf("WAITING\n");
            goto cleanup;
        }
        atual = proximoNo(atual, idx);
    }
    if (estadoCenaNo(atual) == WON)   printf("WON\n");
    else                               printf("FAILED\n");

cleanup:
    // Liberta memória
    for (int i = 0; i < H->n_cenas; i++) libertaCena(H->cenas[i]);
    for (int i = 0; i < H->n_cenas; i++) {
        free(H->nos[i]->vizinhos);
        free(H->nos[i]);
    }
    free(H->cenas);
    free(H->nos);
    free(H);
    return 0;
}