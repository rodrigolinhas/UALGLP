CC = gcc
CFLAGS = -Wall -Wextra -std=c11

EXECUTAVEIS = \
	exercicio-escrita-file/exercicio1.exe \
	exercicio-read-file/exercicio2.exe \
	exercicio-strings-files/exercicio3.exe

all: $(EXECUTAVEIS)

# Regra genérica para compilação
%.exe: %.c
	$(CC) $(CFLAGS) -o $@ $<

# Regras de execução
run1: exercicio-escrita-file/exercicio1.exe
	@echo "Executando exercício 1:"
	@cd exercicio-escrita-file && ./exercicio1.exe

run2: exercicio-read-file/exercicio2.exe
	@echo "Executando exercício 2:"
	@cd exercicio-read-file && ./exercicio2.exe

run3: exercicio-strings-files/exercicio3.exe
	@echo "Executando exercício 3:"
	@cd exercicio-strings-files && ./exercicio3.exe

clean:
	rm -f $(EXECUTAVEIS)
	rm -f exercicio-escrita-file/saida.txt
	rm -f exercicio-strings-files/arquivo.txt

.PHONY: all clean run1 run2 run3