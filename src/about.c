#include <stdio.h>
#include <string.h>

// Funções que desenha as telas
#include "screens.h"
// Funções para controle do terminal, e manipulação do texto
#include "terminal_control.h"

void about(void) {
    const char *logo[] = {
        "      ___           ___           ___           ___           ___      ",
        "     /\\  \\         /\\  \\         /\\  \\         /\\  \\         /\\  \\     ",
        "    /::\\  \\       /::\\  \\       /::\\  \\       /::\\  \\       /::\\  \\    ",
        "   /:/\\ \\  \\     /:/\\:\\  \\     /:/\\:\\  \\     /:/\\:\\  \\     /:/\\:\\  \\   ",
        "  _\\:\\~\\ \\  \\   /:/  \\:\\  \\   /::\\~\\:\\__\\   /::\\~\\:\\  \\   /::\\~\\:\\  \\  ",
        " /\\ \\:\\ \\ \\__\\ /:/__/ \\:\\__\\ /:/\\:\\ \\:|__| /:/\\:\\ \\:\\__\\ /:/\\:\\ \\:\\__\\ ",
        " \\:\\ \\:\\ \\/__/ \\:\\  \\ /:/  / \\:\\~\\:\\/:/  / \\/_|::\\/:/  / \\:\\~\\:\\ \\/__/ ",
        "  \\:\\ \\:\\__\\    \\:\\  /:/  /   \\:\\ \\::/  /     |:|::/  /   \\:\\ \\:\\__\\   ",
        "   \\:\\/:/  /     \\:\\/:/  /     \\:\\/:/  /      |:|\\/__/     \\:\\ \\/__/   ",
        "    \\::/  /       \\::/  /       \\::/__/       |:|  |        \\:\\__\\     ",
        "     \\/__/         \\/__/         ~~            \\|__|         \\/__/     "
    };

    const char *text[] = {
        "SIG-Residence é um sistema de gestão de despesas",
        "para repúblicas estudantis, desenvolvido em C.",
        "",
        "Permite registrar, organizar e acompanhar gastos",
        "de forma simples, por meio do terminal.",
        "",
        "O projeto prevê evolução futura para C++,",
        "com novos recursos e melhorias.",
        "",
        "[0] Voltar"
    };

    int rows = 0, cols = 0;
    update_terminal_size(&rows, &cols);
    clear_screen();

    int logo_lines = sizeof(logo) / sizeof(logo[0]);
    int text_lines = sizeof(text) / sizeof(text[0]);

    // Define largura e altura da caixa com margem
    int width = strlen(logo[0]) + 6;
    int height = logo_lines + text_lines + 6;

    int y = (rows - height) / 2;
    int x = (cols - width) / 2;

    // Desenha a caixa
    draw_box(y, x, height, width);

    // Exibe a logo
    int current_y = y + 2;
    for (int i = 0; i < logo_lines; i++) {
        int padding = (width - strlen(logo[i])) / 2;
        ansi_print(current_y++, x + padding, logo[i]);
    }

    current_y++; // espaço entre logo e conteúdo

    // Exibe o restante do conteúdo
    for (int i = 0; i < text_lines; i++) {
        int padding = (width - strlen(text[i])) / 2;
        ansi_print(current_y++, x + padding, text[i]);
    }

    fflush(stdout);

    // Espera o usuário pressionar 0
    char resp;
    do {
        resp = get_keypress();
    } while (resp != '0');
}