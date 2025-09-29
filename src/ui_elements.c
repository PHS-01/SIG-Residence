#include <stdio.h>
#include <stdlib.h>    // ✅ Para mbstowcs
#include <string.h>
#include <unistd.h>
#include <locale.h>
#include <wchar.h>     // ✅ Para wchar_t, wcslen, etc.

// Variáveis globais do projeto
#include "config.h"
// Funções para controle do terminal, e manipulação do texto
#include "terminal_control.h"

// Função para desenhar as opções do menu
void draw_menu_options(int rows, int cols, char *options[], int length_options) {
    // Calcular a maior string para ajustar a posição horizontal
    int max_width = 0;
    for (int i = 0; i < length_options; i++) {
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
    for (int i = 0; i < length_options; i++) {
        // Calcular a posição vertical para distribuir as opções na metade inferior
        int vertical_pos = start_y + (i + 1) * vertical_spacing + i;  // Efeito de escada

        // Imprimir a opção na posição calculada
        ansi_print(vertical_pos, horizontal_pos + i, options[i]);
    }
}

// Função que desenha a logo
void draw_logo(int rows, int cols) {

    int start_y = rows / 5;

    for (int i = 0; i < LENGTH_ASCII_ART; i++) {
        const char *utf8_str = PROJECT_ASCII_ART[i];

        // Buffer para wchar_t (tamanho máximo = strlen + 1, para garantir)
        wchar_t wide_str[512];
        mbstowcs(wide_str, utf8_str, sizeof(wide_str) / sizeof(wchar_t));

        // Calcula largura visível corretamente
        int width = wcslen(wide_str);
        int horizontal_pos = (cols - width) / 2;

        ansi_print(start_y + i, horizontal_pos, utf8_str);
    }
}

// Função que desenha uma caixa com tamanho e posição
void draw_box(int y, int x, int height, int width) {
    // Canto superior esquerdo
    ansi_print(y, x, "┌");

    // Canto superior direito
    ansi_print(y, x + width - 1, "┐");

    // Canto inferior esquerdo
    ansi_print(y + height - 1, x, "└");

    // Canto inferior direito
    ansi_print(y + height - 1, x + width - 1, "┘");

    // Linha superior e inferior
    for (int i = 1; i < width - 1; i++) {
        ansi_print(y, x + i, "─");                               // superior
        ansi_print(y + height - 1, x + i, "─");                  // inferior
    }

    // Lados verticais
    for (int i = 1; i < height - 1; i++) {
        ansi_print(y + i, x, "│");                               // esquerdo
        ansi_print(y + i, x + width - 1, "│");                   // direito
    }

    fflush(stdout);
}

char draw_alert(const char *msg[], const int length_msg, int width) {
    int rows = 0, cols = 0;
    update_terminal_size(&rows, &cols);

    int spacing = 2;

    // Altura da caixa = linhas da mensagem + espaçamentos + topo + base
    int content_lines = length_msg + (spacing - 1) * (length_msg - 1);
    int height = content_lines + 4;  // +2 para bordas, +2 para padding

    int x = (cols - width) / 2;
    int y = (rows - height) / 2;

    draw_box(y, x, height, width);

    // Centraliza mensagens no conteúdo da caixa
    int content_y = y + 2;
    for (int i = 0; i < length_msg; i++) {
        int msg_len = strlen(msg[i]);
        int padding = (width - 2 - msg_len) / 2;
        move_cursor(content_y, x + 1 + padding);
        printf("%s", msg[i]);
        content_y += spacing;
    }

    fflush(stdout);

    // Espera tecla do usuário
    char key = get_keypress();

    // Limpa a área do alerta com espaços
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            ansi_print(y + i, x + j, " ");
        }
    }

    fflush(stdout);
    return key;
}

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