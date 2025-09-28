#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Funções que desenha as telas
#include "screens.h"
// Variaveis globais do projeto
#include "config.h"
// Funções para controle do terminal, e manipulação do texto
#include "terminal_control.h"

bool home(int rows, int cols) {

    char resp;

    char *options[] = {
        "[1]   Módulo Pessoas",
        "[2]   Módulo Residência",
        "[3]   Módulo Financia",
        "[4]   Sobre",
        "[5]   Créditos",
        "[0]   Sair"
    };

    int length_options = sizeof(options) / sizeof(options[0]);

    // Chama a função para desenhar a logo na parte superior
    draw_logo(rows, cols);
    
    enable_bold();

    // Chama a função para desenhar o menu
    draw_menu_options(rows, cols, options, length_options);

    // Desenha na tela a versão do projeto
    ansi_print(rows - 3 , cols - 15, PROJECT_VERSION);

    disable_bold();

    fflush(stdout);

    hide_cursor();  // Esconde o cursor enquanto o menu está sendo exibido

    resp = get_keypress();  // Obtém a tecla pressionada

    system("clear");
    clear_screen();
    
    set_text_color(COLOR_RED);

    // Lógica de navegação no menu
    switch (resp) {
        case '1':
            ansi_print(3, 3, (const char[]){resp, '\0'});
            break;

        case '2':
            ansi_print(3, 3, (const char[]){resp, '\0'});
            break;

        case '3':
            ansi_print(3, 3, (const char[]){resp, '\0'});
            break;

        case '4':
            ansi_print(3, 3, (const char[]){resp, '\0'});
            break;

        case '5':
            ansi_print(3, 3, (const char[]){resp, '\0'});
            break;

        case '0':
            ansi_print(3, 3, (const char[]){resp, '\0'});
            return false;  // Confirma saída do programa
            break;

        default:
            ansi_print(3, 3, "default");
            break;
    }

    reset_text_color();

    return true;
}