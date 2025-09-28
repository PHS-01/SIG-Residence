# Variáveis
CC = gcc
CFLAGS = -Iinclude -Wall -Wextra

# Arquivos do projeto
SRC = main.c config.c termios_utils.c ansi_utils.c src/ui_elements.c src/home.c # $(wildcard src/*.c) $(wildcard src/people/*.c) $(wildcard src/residence/*.c) $(wildcard src/finance/*.c)
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