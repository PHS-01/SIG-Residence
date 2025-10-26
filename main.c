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