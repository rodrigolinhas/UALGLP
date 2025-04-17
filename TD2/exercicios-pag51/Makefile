# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11

# Nomes dos executáveis
TARGET1 = exercicio1.exe
TARGET2 = exercicio2.exe

# Regras principais
all: $(TARGET1) $(TARGET2)

# Compilação da versão 1 (contagem de comparações)
$(TARGET1): exercicio1.c
	$(CC) $(CFLAGS) -o $@ $<

# Compilação da versão 2 (múltiplas ocorrências)
$(TARGET2): exercicio2.c
	$(CC) $(CFLAGS) -o $@ $<

# Comandos de execução
run1: $(TARGET1)
	@echo "Executando versão 1 - Contagem de comparações:"
	@./$(TARGET1)

run2: $(TARGET2)
	@echo "Executando versão 2 - Múltiplas ocorrências:"
	@./$(TARGET2)

# Limpeza
clean:
	rm -f $(TARGET1) $(TARGET2) *.o

.PHONY: all run1 run2 clean