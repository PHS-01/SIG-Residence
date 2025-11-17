#include <stdio.h>
#include <string.h>

// Funções que desenha as telas
#include "screens.h"
// Funções para controle do terminal, e manipulação do texto
#include "terminal_control.h"

void credits(void) {
    const char *logo[] = {
        "  ___  ____  ____  ____  __  ____  __   ____ ",
        " / __)(  _ \\(  __)(    \\(  )(_  _)/  \\ / ___)",
        "( (__  )   / ) _)  ) D ( )(   )( (  O )\\___ \\",
        " \\___)(__\\_)(____)(____/(__) (__) \\__/ (____/"
    };

    const char *text[] = {
        "A U T O R E S",
        "Pedro Henrique da Silva",
        "Gleydson Henrique Dantas da Silva",
        "Paulo André Alves de Moura",
        "Nikcael Gidalte Lopes da Silva",
        "",
        "O R I E N T A D O R",
        "Flavius da Luz e Gorgônio",
        "",
        "I N S T I T U I Ç Ã O",
        "UNIVERSIDADE FEDERAL DO RIO GRANDE DO NORTE",
        "",
        "F E R R A M E N T A S",
        "Github and Git",
        "Linguagem: C",
        "",
        "P R O J E T O",
        "https://github.com/PHS-01/SIG-Residence.git",
        "",
        "[0] Voltar"
    };

    int rows = 0, cols = 0;
    update_terminal_size(&rows, &cols);

    int logo_lines = sizeof(logo) / sizeof(logo[0]);
    int text_lines = sizeof(text) / sizeof(text[0]);

    // Cálculo da largura da caixa com base na maior linha
    int max_width = strlen(logo[0]);

    int box_width = max_width + 10;
    int box_height = logo_lines + text_lines + 6;

    int x = (cols - box_width) / 2;
    int y = (rows - box_height) / 2;

    clear_screen();
    draw_box(y, x, box_height, box_width);

    // Exibe a logo
    int current_y = y + 2;
    for (int i = 0; i < logo_lines; i++) {
        int padding = (box_width - strlen(logo[i])) / 2;
        ansi_print(current_y++, x + padding, logo[i]);
    }

    current_y++; // espaço entre logo e conteúdo

    // Exibe o restante do conteúdo
    for (int i = 0; i < text_lines; i++) {
        int padding = (box_width - strlen(text[i])) / 2;
        ansi_print(current_y++, x + padding, text[i]);
    }

    fflush(stdout);

    // Espera o usuário pressionar '0' para voltar
    char key;
    do {
        key = get_keypress();
    } while (key != '0');
}