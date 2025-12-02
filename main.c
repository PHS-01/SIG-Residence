#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>
#include "screens.h"
#include "config.h"
#include "terminal_control.h"
#include "controllers.h"
#include "people.h"
#include "finance.h"

// Função de saída do programa
void exit_program(void) {
    free_people_list(); // Limpa a memória RAM antes de matar o processo
    free_finance_list();
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
    // Carrega listas dinâmicas na RAM
    load_people_list();
    finance_load_file();

    
    bool loop = true;
    int rows = 0, cols = 0;

    clear_screen();
    setlocale(LC_ALL, "");
    hide_cursor();  // Esconde o cursor enquanto o menu está sendo exibido

    fade_animation("in");
    draw_rainbow_logo(rows, cols);

    do {
        // Atualiza o tamanho do terminal
        update_terminal_size(&rows, &cols);
        clear_screen();

        // Funções para desenhar a tela
        loop = home();

    } while(loop);

    fade_animation("out");
    exit_program(); // Função para limpar e restaurar o terminal

    return 0;
}