# Variáveis
CC = gcc
CFLAGS = -Iinclude -Wall -Wextra

# Arquivos do projeto principal
SRC = main.c validations.c $(wildcard utils/*.c) $(wildcard settings/*.c) $(wildcard src/*.c) $(wildcard controllers/*.c) $(wildcard src/people/*.c) $(wildcard src/finance/*.c) $(wildcard src/residence/*.c) $(wildcard src/reports/*.c)
OUT = test.exe

# Arquivos do populador (apenas os específicos do populador)
POPULATE_SRC = $(wildcard src/populate/*.c)
POPULATE_OUT = populate.exe

# Regra padrão
all: $(OUT)

# Regra para o populador
populate: $(POPULATE_OUT)
	./$(POPULATE_OUT) all

$(OUT):
	$(CC) $(SRC) -o $(OUT) $(CFLAGS)

$(POPULATE_OUT):
	$(CC) $(POPULATE_SRC) $(filter-out main.c, $(SRC)) -o $(POPULATE_OUT) $(CFLAGS)

# Atalho para compilar e rodar
run: all
	./$(OUT)

# Atalho para compilar e usar o populador
run-populate: populate
	./$(POPULATE_OUT) help

# Limpa os executáveis
clean:
	rm -f $(OUT) $(POPULATE_OUT)

# Ajuda
help:
	@echo "Targets disponíveis:"
	@echo "  all          - Compila o projeto principal (padrão)"
	@echo "  populate     - Compila o populador de banco de dados"
	@echo "  run          - Compila e executa o projeto principal"
	@echo "  run-populate - Compila e executa o populador (mostra ajuda)"
	@echo "  clean        - Remove os executáveis"
	@echo "  help         - Mostra esta mensagem"