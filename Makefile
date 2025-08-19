# Variáveis
CC = gcc
CFLAGS = -Iinclude -lncurses -Wall

# Arquivos do projeto
SRC = main.c src/home.c src/credits.c
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
