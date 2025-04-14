#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

#define MAX_COMMAND_LEN 30

// Estrutura para mapear os comandos com funções
typedef struct {
    char *name;
    void (*func)(Stack *, char *); // repare na assinatura!
} Command;

// Protótipos das funções
void handle_push(Stack *s, char *arg);
void handle_pop(Stack *s);
void handle_top(Stack *s);

// Implementação das funções
void handle_push(Stack *s, char *arg) {
  // se nenhum argumento foi extraido, assinalar o erro
  if (arg == NULL) {
      printf("Error: No value provided for push.\n");
      return;
  }
  
  // transformar o argumento de uma string para um inteiro
  int value = atoi(arg);
  push(s, value);
}

void handle_pop(Stack *s) {
  // nada por preprocessar, chamamos directamente
  // a função associada
  pop(s);
}

void handle_top(Stack *s) {
  // nada por preprocessar, chamamos directamente
  // a função associada
  top(s);
}

// vetor que mapeia comandos a funções concretas
Command commands[] = {
  {"push", handle_push},
  {"pop", handle_pop},
  {"top", handle_top},
  // Nenhum comando adicional necessário
};


// uma macro para assinalar o número de elementos no vector 
// commands: tamanho do vetor na sua globalidade dividida pelo tamanho
// dos seus elementos (aqui command[0]). Temos assim o número de elementos.
#define COMMAND_COUNT (sizeof(commands) / sizeof(commands[0]))

int main(void) {
  Stack stack;
  init( & stack);
  char input[MAX_COMMAND_LEN];

  // ciclo principal: lê até encontrar EOF
  while (fgets(input, MAX_COMMAND_LEN, stdin) != NULL) {
    // Remove o caractere de nova linha
    input[strcspn(input, "\n")] = '\0';
    // Divide a entrada em comando e argumento
    char * command = strtok(input, " ");
    char * arg = strtok(NULL, " ");
    // Ignora linhas vazias
    if (command == NULL) {
      continue;
    }
    // Procura o comando na lista de funções possíveis
    int found = 0;
    for (int i = 0; i < COMMAND_COUNT; i++) {
      if (strcmp(command, commands[i].name) == 0) {
        // Encontrei! O comando está na lista!
        commands[i].func(&stack, arg); // Executa a função
        // ---> executar a respectiva função com o rspectivo
        //argumento (args)
        // ....
        found = 1; // assinalar que o comando foi encontrado
        break;
      }
    }
    if (!found) { // o comando assinalado não existe!
      printf("Comando desconhecido: %s\n", command);
    }
  }
  return 0;
}