#include <string.h>
#include <unistd.h>

// Variáveis globais do projeto
#include "config.h"
// Funções para controle do terminal, e manipulação do texto
#include "terminal_control.h"

void draw_border(int rows, int cols) {
    // Canto superior esquerdo
    ansi_print(0, 0, "┌");

    // Canto superior direito
    ansi_print(0, cols - 1, "┐");

    // Canto inferior esquerdo
    ansi_print(rows - 1, 0, "└");

    // Canto inferior direito
    ansi_print(rows - 1, cols - 1, "┘");

    // Bordas horizontais (superior e inferior)
    for (int x = 2; x < cols - 1; x++) {
        ansi_print(0, x, "─");             // linha horizontal superior
        ansi_print(rows - 1, x, "─");      // linha horizontal inferior
    }

    // Bordas verticais (laterais esquerda e direita)
    for (int y = 2; y < rows - 1; y++) {
        ansi_print(y, 0, "│");             // linha lateral esquerda
        ansi_print(y, cols - 1, "│");      // linha lateral direita
    }
}

// Função para desenhar as opções do menu
void draw_menu_options(int rows, int cols, char *options[], int length_options) {
    // Calcular a maior string para ajustar a posição horizontal
    int max_width = 0;
    for (size_t i = 0; i < length_options; i++) {
        int option_length = strlen(options[i]);
        if (option_length > max_width) {
            max_width = option_length;
        }
    }

    // Posição horizontal alinhada à esquerda (baseada na maior string)
    int horizontal_pos = (cols - max_width) / 2;  // Ajuste conforme necessário para o alinhamento

    // Cálculo do espaço disponível (somente a metade inferior da tela)
    int start_y = rows / 2;  // Começar na metade inferior
    int vertical_spacing = 1;

    // Imprimir as opções na metade inferior da tela com efeito de escada
    for (size_t i = 0; i < length_options; i++) {
        // Calcular a posição vertical para distribuir as opções na metade inferior
        int vertical_pos = start_y + (i + 1) * vertical_spacing + i;  // Efeito de escada

        // Imprimir a opção na posição calculada
        ansi_print(vertical_pos, horizontal_pos + i, options[i]);
    }
}

// Função para desenhar a logo do projeto na parte superior
void draw_logo(int rows, int cols) {
    // Ajuste a posição vertical para a parte superior
    int start_y = 5;  // Um espaço livre no topo para a logo

    // Desenha a logo linha por linha
    for (int i = 0; i < LENGTH_ASCII_ART; i++) {
        // Posição horizontal: centraliza a logo
        int horizontal_pos = (cols - strlen(PROJECT_ASCII_ART[i])) / 2;
        
        // Imprime a linha da logo na posição calculada
        ansi_print(start_y + i, horizontal_pos, PROJECT_ASCII_ART[i]);
    }
}

// char draw_alert(const char *msg[], const int length_msg, int width, bool space) 
// {
//     int h = length_msg + 5;
//     int y = (LINES - h) / 2;
//     int x = (COLS - width) / 2;  
            
//     char resp;

//     WINDOW *alert = newwin(h, width, y, x);
//     box(alert, 0, 0);

//     h = 2;

//     // escreve a mensagem centralizada
//     for (int i = 0; i < length_msg; i++)
//     {
//         mvwprintw(alert, h, (width - (int)strlen(msg[i])) / 2, "%s", msg[i]);

//         if (space)
//         {
//             h += 2;
//         } else
//         {
//             h += 1;
//         }
//     }

//     wrefresh(alert);

//     // Espera uma até tecla ser digitada
//     resp = wgetch(alert);

//     // apaga a janela
//     werase(alert);
//     wrefresh(alert);
//     delwin(alert);

//     return resp;
// }

// // Função genérica para entrada de texto em caixa (window)
// void input_box(int width, const char *prompt, char *buffer, int max_len)
// {
//     int h = 5;
//     int y = (LINES - h) / 2;
//     int x = (COLS - width) / 2;

//     // Cria a janela
//     WINDOW *win = newwin(h, width, y, x);
//     box(win, 0, 0);
//     mvwprintw(win, h/2, 2, "%s ", prompt);
//     wrefresh(win);

//     // Habilita eco e lê entrada
//     echo();
//     wgetnstr(win, buffer, max_len - 1);
//     noecho();

//     // Remove a janela
//     delwin(win);
// }