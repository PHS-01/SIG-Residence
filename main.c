#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>
#include "screens.h"

const char *PROJECT_VERSION = "1.0-alpha";

void draw_border(char style, int border_margin_left_right, int border_margin_top_bottom);
void draw_building_border(char style, int border_margin_left_right, int border_margin_top_bottom);

int main(void)
{
    // Inicia modo ncurses
    initscr();

    // Desabilita buffer de linha 
    // Captura teclas sem precisar de ENTER
    cbreak();

    // Não mostrar teclas digitadas
    noecho();

    // Fechar a janela com ctrl + c
    cbreak();
    
    // Animação de entrada
    fade_animation("in");

    // Função de animação da borda
    draw_building_border('#',0, 0);

    char resp = '\n';
    bool loop = 1;
    while (loop)
    {
        // Limpar a tela
        clear();

        // Função para imprimir a bordar da tela
        draw_border('#',0, 0);

        // Função para imprimir a tela home
        home(LINES, COLS);
        
        mvprintw((LINES-3), (COLS-16), "v %s", PROJECT_VERSION);

        // Atualizar a tela
        refresh();

        switch (resp)
        {
            case '\n':
                mvprintw(2, 2, "%s", "Enter");
                break;
            case '1':
                clear();
                mvprintw(2, 2, "%s", "1");
                about(LINES, COLS);
                refresh(); 
                break;
            case '2':
                clear();
                mvprintw(2, 2, "%s", "2");
                credits(LINES, COLS);
                refresh(); 
                break;
            case '0':
                mvprintw(2, 2, "%s", "0");
                refresh();
                break;
            case 27:
                clear();
                mvprintw(2, 2, "%s", "ESC");
                loop = sair(LINES, COLS, resp);
                refresh();
                break;
            default:
                mvprintw(2, 2, "%s", "default");
                refresh();
                break;
        }

        resp = getch();
    }

    // Animação de saida
    fade_animation("out");
    
    // Finaliza ncurses
    endwin();

    return 0;
}

void draw_border(char style, int border_margin_left_right, int border_margin_top_bottom)
{
    // Desenha borda superior e inferior
    for (int x = border_margin_left_right; x < (COLS - border_margin_left_right); x++) {
        mvaddch(border_margin_top_bottom, x, style);                              // borda cima
        mvaddch(LINES - 1- border_margin_top_bottom, x, style);                  // borda baixo
    }

    // Desenha borda esquerda e direita
    for (int y = border_margin_top_bottom; y < (LINES - border_margin_top_bottom); y++) {
        mvaddch(y, border_margin_left_right, style);               // borda esquerda
        mvaddch(y, COLS - 1 - border_margin_left_right, style);   // borda direita
    }
}