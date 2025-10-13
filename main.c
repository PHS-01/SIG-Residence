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

#include "controllers.h"
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
    People p1 = {1, 1, "João", "01/01/1990", "joao@example.com", "123456789", true};
    People p2 = {1, 2, "Teste", "02/01/1990", "test@example.com", "123123132", true};
    People p3 = {1, 3, "Marias", "03/01/1990", "marias@example.com", "020202020", true};

    create(&p1, sizeof(People));
    create(&p2, sizeof(People));
    create(&p3, sizeof(People));
    
    getchar();

    read_people(2);

    // getchar();

    // // Listar pessoas
    // list_people();

    // // Atualizar pessoa
    // People pupdate = {1, "João Silva", "01/01/1990", "joao.silva@example.com", "987654321", true};
    // update_people(1, pupdate);

    // read_people(1);

    // getchar();

    // // Excluir pessoa
    // delete_people(1);

    // // Listar pessoas
    // list_people();

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