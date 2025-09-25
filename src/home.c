#include <stdio.h>
#include <string.h>

// Funções que desenha as telas
#include "screens.h"
// Variaveis globais do projeto
#include "config.h"
// Funções para controle do terminal, e manipulação do texto
#include "terminal_control.h"

void home(int rows, int cols) {
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
    
    // Chama a função para desenhar o menu
    draw_menu_options(rows, cols, options, length_options);
}