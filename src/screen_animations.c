#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>     // ✅ Para wchar_t, wcslen, etc.

// Funções que desenha as telas
#include "screens.h"
// Variáveis globais do projeto
#include "config.h"
// Funções para controle do terminal, e manipulação do texto
#include "terminal_control.h"

void fade_animation(const char *type) {
    const char *fadeIn_chars[]  = { "#", "+", ".", " " };
    const char *fadeOut_chars[] = { " ", ".", "+", "#" };

    int rows = 0, cols = 0;
    update_terminal_size(&rows, &cols);

    system("clear");
    clear_screen();

    for (int f = 0; f < 4; f++) {
        for (int y = 0; y < rows; y++) {
            for (int x = 0; x < cols; x++) {
                const char *symbol;

                if (strcmp(type, "out") == 0) {
                    symbol = fadeOut_chars[f];
                } else {
                    symbol = fadeIn_chars[f];
                }

                ansi_print(y + 1, x + 1, symbol);
            }
        }

        usleep(300000);  // Aguarda tempo fixo
    }

    system("clear");
    clear_screen();
}

// Função que anima a logo com cores do arco-íris
void draw_rainbow_logo(int rows, int cols) {
    // Cores do arco-íris usando o enum Color
    enum Color rainbow_colors[] = {
        COLOR_RED,           // Vermelho
        COLOR_YELLOW,        // Amarelo
        COLOR_GREEN,         // Verde
        COLOR_CYAN,          // Azul Claro
        COLOR_BLUE,          // Azul
        COLOR_MAGENTA,       // Magenta
        COLOR_LIGHT_MAGENTA  // Violeta (mais claro)
    };

    // Atualiza o tamanho do terminal
    update_terminal_size(&rows, &cols);

    // Fazendo a animação para a logo com mudança de cores
    for (int frame = 0; frame < 7; frame++) {  // 7 frames (um para cada cor)
        clear_screen();
        system("clear");
        
        set_text_color(rainbow_colors[frame]);

        draw_logo(rows, cols);

        fflush(stdout);
        usleep(300000);  // Delay entre frames
    }

    // Reseta para a cor normal após a animação
    reset_text_color();
}