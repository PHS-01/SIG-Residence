#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>

// Funções que desenha as telas
#include "screens.h"
// Variáveis globais do projeto
#include "config.h"
// Funções para controle do terminal, e manipulação do texto
#include "terminal_control.h"

#include "people.h"

// Função de saída do programa
void exit_program(void) {
    clear_screen();
    disable_raw_mode();
    show_cursor();
    restore_terminal();
}

int main(void) {
    // Verifica se o banco de dados já existe
    if (database_exists()) {
        printf("O banco de dados já existe.\n");
    } else {
        printf("O banco de dados não existe. Criando o banco...\n");
        create_database();  // Chama a função para criar o banco se não existir
    }

    // Teste de criação de pessoas
    People p1 = {1, "João", "01/01/1990", "joao@example.com", "123456789"};
    create_people(p1);

    // Listar pessoas
    list_people();

    // Atualizar pessoa
    People p2 = {1, "João Silva", "01/01/1990", "joao.silva@example.com", "987654321"};
    update_people(1, p2);

    // Listar pessoas
    list_people();

    // Excluir pessoa
    delete_people(1);

    // bool loop = true;
    // int rows = 0, cols = 0;

    // system("clear");
    // clear_screen();

    // setlocale(LC_ALL, "");

    // hide_cursor();  // Esconde o cursor enquanto o menu está sendo exibido

    // fade_animation("in");

    // draw_rainbow_logo(rows, cols);

    // do {

    //     // Atualiza o tamanho do terminal
    //     update_terminal_size(&rows, &cols);

    //     system("clear");
    //     clear_screen();

    //     // Funções para desenhar a tela
    //     loop = home();

    // } while (loop);

    // fade_animation("out");

    // exit_program(); // Função para limpar e restaurar o terminal

    return 0;
}