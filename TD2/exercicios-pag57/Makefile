CC = gcc
CFLAGS = -Wall -Wextra -std=c11
TARGET1 = exercicio1.exe
TARGET2 = exercicio2.exe
TARGET3 = exercicio3.exe
TARGET4 = exercicio4.exe
TARGET5 = exercicio5.exe
EXECUTAVEIS = $(TARGET1) $(TARGET2) $(TARGET3) $(TARGET4) $(TARGET5)

all: $(EXECUTAVEIS)

$(TARGET1): exercicio1.c
	$(CC) $(CFLAGS) -o $@ $<

$(TARGET2): exercicio2.c
	$(CC) $(CFLAGS) -o $@ $<

$(TARGET3): exercicio3.c
	$(CC) $(CFLAGS) -o $@ $<

$(TARGET4): exercicio4.c
	$(CC) $(CFLAGS) -o $@ $<

$(TARGET5): exercicio5.c
	$(CC) $(CFLAGS) -o $@ $<

run1: $(TARGET1)
	@echo "Executando exercicio1 - Pesquisa Binaria Recursiva:"
	@./$(TARGET1)

run2: $(TARGET2)
	@echo "Executando exercicio2 - Primeiro e último índice de valor repetido:"
	@./$(TARGET2)

run3: $(TARGET3)
	@echo "Executando exercicio3 - Contagem de comparações:"
	@./$(TARGET3)

run4: $(TARGET4)
	@echo "Executando exercicio4 - Limite inferior (Lower Bound):"
	@./$(TARGET4)

run5: $(TARGET5)
	@echo "Executando exercicio5 - Limite superior (Upper Bound):"
	@./$(TARGET5)

clean:
	rm -f $(EXECUTAVEIS)

.PHONY: all run1 run2 run3 run4 run5 clean