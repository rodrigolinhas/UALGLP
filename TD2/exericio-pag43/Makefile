# Compilador
CC = gcc

# Flags de compilação padrão
CFLAGS = -Wall -Wextra -std=c11 -I.

# Flags para modo debug
DEBUG_CFLAGS = -DDEBUG_ON -g

# Nome do executável
TARGET = main.exe

# Arquivos objeto
OBJS = dynvec.o main.o

# Capacidade inicial do vetor (consistente com TD1)
DYNVEC_INIT_CAPACITY = 4

# Regra padrão
all: $(TARGET)

# Modo debug
debug: CFLAGS += $(DEBUG_CFLAGS)
debug: clean $(TARGET)

# Compilar o executável
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Regra para arquivos objeto
%.o: %.c dynvec.h
	$(CC) $(CFLAGS) -DDYNVEC_INIT_CAPACITY=$(DYNVEC_INIT_CAPACITY) -c -o $@ $<

# Limpar arquivos gerados
clean:
	rm -f $(TARGET) $(OBJS)

# Executar o programa
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run debug