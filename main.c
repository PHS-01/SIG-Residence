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
    if (!database_exists()) {
        create_database();
    }

    // // Teste de criação de pessoas
    // People p1 = {true, 1, "João", "01/01/1990", "joao@example.com", "123456789"};
    // People p2 = {true, 2, "Teste", "02/01/1990", "test@example.com", "123123132"};
    // People p3 = {true, 3, "Marias", "03/01/1990", "marias@example.com", "020202020"};

    // create(&p1, sizeof(People));
    // create(&p2, sizeof(People));
    // create(&p3, sizeof(People));
    
    // getchar();

    // set_search_id(1);
    // People test;
    // if (read(&test, sizeof(People), match_people_by_id)) {
    //     /* code */
    //     print_people(&test);
    // }


    // getchar();

    // // Atualizar pessoa
    // set_search_id(1);
    // People updated = {true,1, "João Silva", "01/01/1990", "joao.silva@example.com", "987654321"};
    // update(&updated, sizeof(People), match_people_by_id);

    // set_search_id(1);
    // if (read(&test, sizeof(People), match_people_by_id)) {
    //     /* code */
    //     print_people(&test);
    // }
    
    // getchar();

    // set_search_id(1);
    // delete(sizeof(People), match_people_by_id);

    // if (read(&test, sizeof(People), match_people_by_id)) {
    //     /* code */
    //     print_people(&test);
    // } else {
    //     printf("Pessoa deletada");
    // }

    bool loop = true;
    int rows = 0, cols = 0;

    system("clear");
    clear_screen();

    setlocale(LC_ALL, "");

    hide_cursor();  // Esconde o cursor enquanto o menu está sendo exibido

    fade_animation("in");

    draw_rainbow_logo(rows, cols);

    do {

        // Atualiza o tamanho do terminal
        update_terminal_size(&rows, &cols);

        system("clear");
        clear_screen();

        // Funções para desenhar a tela
        loop = home();

    } while(loop);

    fade_animation("out");

    exit_program(); // Função para limpar e restaurar o terminal

    return 0;
}