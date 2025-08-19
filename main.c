#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>
#include <home.h>
#include <credits.h>
#include <exit.h>

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
    
    /* code */
    // Caracteres para a animação
    char* fade_chars[] = {"#", "+", ".", " "}; // do mais escuro ao mais claro

    for(int f = 0; f < 4; f++) {
        for(int y = 0; y < LINES; y++) {
            for(int x = 0; x < COLS; x++) {
                mvprintw(y, x, "%s", fade_chars[f]);
            }
        }
        refresh();
        usleep(500000);
    }

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
                mvprintw(2, 2, "%s", "1");
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

void draw_building_border(char style, int border_margin_left_right, int border_margin_top_bottom)
{
    // Desenha topo gradualmente
    for(int x = border_margin_left_right; x < COLS - border_margin_left_right; x++) {
        mvaddch(border_margin_top_bottom, x, style);
        refresh();
        usleep(15000);
    }

    // Desenha direita gradualmente
    for(int y = border_margin_top_bottom + 1; y < LINES - border_margin_top_bottom; y++) {
        mvaddch(y, COLS - 1 - border_margin_left_right, style);
        refresh();
        usleep(15000);
    }

    // Desenha base gradualmente
    for(int x = COLS - 2 - border_margin_left_right; x >= border_margin_left_right; x--) {
        mvaddch(LINES - 1 - border_margin_top_bottom, x, style);
        refresh();
        usleep(15000);
    }

    // Desenha esquerda gradualmente
    for(int y = LINES - 2 - border_margin_top_bottom; y > border_margin_top_bottom; y--) {
        mvaddch(y, border_margin_left_right, style);
        refresh();
        usleep(15000);
    }
}