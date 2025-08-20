# Variáveis
CC = gcc
CFLAGS = -Iinclude -lncurses -Wall

# Arquivos do projeto
SRC = main.c config.c $(wildcard src/*.c)
OUT = test.exe

# Regra padrão
all:
	$(CC) $(SRC) -o $(OUT) $(CFLAGS)

# Atalho para compilar e rodar
run: all
	./$(OUT)

# Limpa o executável
clean:
	rm -f $(OUT)
