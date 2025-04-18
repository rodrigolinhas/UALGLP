CC = gcc
CFLAGS = -Wall -Wextra -std=c11

# Lista de executáveis com caminhos relativos
EXECUTAVEIS = \
	exercicio1/exercicio1.exe \
	exercicio2/exercicio2.exe \
	exercicio3/exercicio3.exe \
	exercicio4/exercicio4.exe \
	exercicio5/exercicio5.exe \
	exercicio6/exercicio6.exe \
	exercicio7/exercicio7-1.exe \
	exercicio7/exercicio7-2.exe \
	exercicio8/exercicio8.exe \
	exercicio9/exercicio9.exe

all: $(EXECUTAVEIS)

# Regra genérica para a maioria dos exercícios
%.exe: %.c
	$(CC) $(CFLAGS) -o $@ $<

# Regras de execução
run1: exercicio1/exercicio1.exe
	@echo "Executando exercício 1:"
	@./$<

run2: exercicio2/exercicio2.exe
	@echo "Executando exercício 2:"
	@./$<

run3: exercicio3/exercicio3.exe
	@echo "Executando exercício 3:"
	@./$<

run4: exercicio4/exercicio4.exe
	@echo "Executando exercício 4:"
	@./$<

run5: exercicio5/exercicio5.exe
	@echo "Executando exercício 5:"
	@./$<

run6: exercicio6/exercicio6.exe
	@echo "Executando exercício 6:"
	@./$<

run7-1: exercicio7/exercicio7-1.exe
	@echo "Executando exercício 7-1:"
	@./$<

run7-2: exercicio7/exercicio7-2.exe
	@echo "Executando exercício 7-2:"
	@./$<

run8: exercicio8/exercicio8.exe
	@echo "Executando exercício 8:"
	@./$<

run9: exercicio9/exercicio9.exe
	@echo "Executando exercício 9:"
	@./$<

clean:
	rm -f $(EXECUTAVEIS)

.PHONY: all clean run1 run2 run3 run4 run5 run6 run7-1 run7-2 run8 run9