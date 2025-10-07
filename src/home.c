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

bool home(void) {

    char resp;
    bool test = true;

    int cols = 0, rows = 0;
    update_terminal_size(&rows, &cols);

    char *options[] = {
        "[1]   Módulo Pessoas",
        "[2]   Módulo Residência",
        "[3]   Módulo Financia",
        "[4]   Sobre",
        "[5]   Créditos",
        "[0]   Sair"
    };

    int length_options = sizeof(options) / sizeof(options[0]);

    // Desenha uma borda ao redor da tela toda
    draw_box(1, 1, rows, cols);
    // Chama a função para desenhar a logo na parte superior
    draw_logo(rows, cols);
    
    enable_bold();

    // Chama a função para desenhar o menu
    draw_menu_options(rows, cols, options, length_options);

    // Desenha na tela a versão do projeto
    ansi_print(rows - 2 , cols - 15, PROJECT_VERSION);

    disable_bold();

    fflush(stdout);

    resp = get_keypress();  // Obtém a tecla pressionada

    system("clear");
    clear_screen();

    // Lógica de navegação no menu
    switch (resp) {
        case '1':
            // Chama a função do dashboard
            // dashboard_people();
            break;

        case '2':
            ansi_print(3, 3, (const char[]){resp, '\0'});
            break;

        case '3':
            ansi_print(3, 3, (const char[]){resp, '\0'});
            break;

        case '4':
            about();
            break;

        case '5':
            credits();
            break;

        case '0':
            test = confirm_exit();
            break;

        default:
            ansi_print(3, 3, "default");
            break;
    }

    return test;
}