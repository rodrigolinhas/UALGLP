CC = gcc
CFLAGS = -Wall -Wextra -std=c11
TARGET1 = exercicio1.exe
TARGET2 = exercicio2.exe
TARGET3 = exercicio3.exe
EXECUTAVEIS = $(TARGET1) $(TARGET2) $(TARGET3)

all: $(EXECUTAVEIS)

$(TARGET1): exercicio1.c plg.c plg.h
	$(CC) $(CFLAGS) -o $@ $< plg.c

$(TARGET2): exercicio2.c
	$(CC) $(CFLAGS) -o $@ $<

$(TARGET3): exercicio3.c dynvec.c plg.c plg.h
	$(CC) $(CFLAGS) -o $@ $< dynvec.c plg.c

run1: $(TARGET1)
	@echo "Executando exercicio1:"
	@./$(TARGET1)

run2: $(TARGET2)
	@echo "Executando exercicio2:"
	@./$(TARGET2)

run3: $(TARGET3)
	@echo "Executando exercicio3:"
	@./$(TARGET3)

clean:
	rm -f $(EXECUTAVEIS)

.PHONY: all run1 run2 run3 clean