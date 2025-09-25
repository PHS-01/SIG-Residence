#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/ioctl.h>
#include <termios.h>

// Funções que desenha as telas
#include "screens.h"
// Variáveis globais do projeto
#include "config.h"
// Funções para controle do terminal, e manipulação do texto
#include "terminal_control.h"

// Função de saída do programa
void exit_program(void) {
    clear_screen();
    disable_raw_mode();
    show_cursor();
    restore_terminal();
}

int main(void) {

    char resp;
    bool loop = true;
    int rows = 0, cols = 0;

    system("clear");
    clear_screen();

    do {

        // Atualiza o tamanho do terminal
        update_terminal_size(&rows, &cols);

        // Funções para desenhar a tela
        home(rows, cols);
        draw_border(rows, cols);

        fflush(stdout);

        hide_cursor();  // Esconde o cursor enquanto o menu está sendo exibido

        resp = get_keypress();  // Obtém a tecla pressionada

        system("clear");
        clear_screen();

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
                loop = false;  // Confirma saída do programa
                exit_program(); // Função para limpar e restaurar o terminal
                break;

            default:
                ansi_print(3, 3, "default");
                break;
        }

    } while (loop);

    return 0;
}