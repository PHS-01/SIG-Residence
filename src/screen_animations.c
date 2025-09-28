#include <stdio.h>
#include <unistd.h>
#include <string.h>

// Variáveis globais do projeto
#include "config.h"
// Funções para controle do terminal, e manipulação do texto
#include "terminal_control.h"

void fade_animation(const char *type) {
    const char *fadeIn_chars[]  = { "#", "+", ".", " " };
    const char *fadeOut_chars[] = { " ", ".", "+", "#" };

    int rows = 0, cols = 0;
    update_terminal_size(&rows, &cols);
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

        usleep(500000);  // Aguarda tempo fixo
    }
}