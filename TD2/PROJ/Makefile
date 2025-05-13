CC = gcc
CFLAGS = -Wall -Wextra
DEBUG_FLAG = -DDEBUG_ON
CUNIT_LIB = -lcunit

.PHONY: all run test debug clean

all: TDfinal Test 

# Compila o programa principal
TDfinal:
	@cd main && $(CC) TDfinal.c $(CFLAGS) -o TDfinal.exe 

# Compila os testes
Test:
	@cd main && $(CC) Test.c $(CFLAGS) $(CUNIT_LIB) -o Test.exe 

# Executa o programa principal com input interativo
run:
	@echo "Digite o nome do arquivo de input (ex: main/input.txt):"; \
	read filename; \
	./main/TDfinal.exe < $$filename

# Executa os testes unitários
test:
	@cd test && ./Test.exe

# Compila em modo debug e executa
debug:
	$(CC) main/TDfinal.c -o main/TDfinal.exe $(CFLAGS) $(DEBUG_FLAG)
	@echo "Debug ativado"
	@echo "Digite o nome do arquivo de input (ex: main/input.txt):"; \
	read filename; \
	./main/TDfinal.exe < $$filename

# Remove executáveis e arquivos temporários
clean:
	rm -f main/TDfinal.exe main/Test.exe test/tmp*.txt test/temp_output*.txt