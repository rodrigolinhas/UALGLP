CC = gcc
CFLAGS = -Wall -Wextra -std=c11

EXECUTAVEIS = \
	exercicio1/exercicio1.exe \
	exercicio2/exercicio2.exe \
	exercicio3/exercicio3-1-a.exe \
	exercicio3/exercicio3-1-b.exe \
	exercicio4/exercicio4.exe \
	exercicio4/exercicio4-corrigido.exe \
	exercicio5/exercicio5.exe

all: $(EXECUTAVEIS)

# Regra genérica para exercícios simples (1, 2, 5)
%.exe: %.c
	$(CC) $(CFLAGS) -o $@ $<

# Regras específicas para exercício 3
exercicio3/exercicio3-1-a.exe: exercicio3/exercicio3-1-a.c
	$(CC) $(CFLAGS) -o $@ $<

exercicio3/exercicio3-1-b.exe: exercicio3/exercicio3-1-b.c
	$(CC) $(CFLAGS) -o $@ $<

# Regras específicas para exercício 4
exercicio4/exercicio4.exe: exercicio4/exercicio4.c
	$(CC) $(CFLAGS) -o $@ $<

exercicio4/exercicio4-corrigido.exe: exercicio4/exercicio4-corrigido.c
	$(CC) $(CFLAGS) -o $@ $<

# Regras de execução
run1: exercicio1/exercicio1.exe
	@echo "Executando exercício 1:"
	@cd exercicio1 && ./exercicio1.exe

run2: exercicio2/exercicio2.exe
	@echo "Executando exercício 2:"
	@cd exercicio2 && ./exercicio2.exe

run3a: exercicio3/exercicio3-1-a.exe
	@echo "Executando exercício 3a:"
	@cd exercicio3 && ./exercicio3-1-a.exe

run3b: exercicio3/exercicio3-1-b.exe
	@echo "Executando exercício 3b:"
	@cd exercicio3 && ./exercicio3-1-b.exe

run4: exercicio4/exercicio4.exe
	@echo "Executando exercício 4:"
	@cd exercicio4 && ./exercicio4.exe

run4c: exercicio4/exercicio4-corrigido.exe
	@echo "Executando exercício 4 corrigido:"
	@cd exercicio4 && ./exercicio4-corrigido.exe

run5: exercicio5/exercicio5.exe
	@echo "Executando exercício 5:"
	@cd exercicio5 && ./exercicio5.exe

clean:
	rm -f $(EXECUTAVEIS)

.PHONY: all clean run1 run2 run3a run3b run4 run4c run5