#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>
#include <home.h>

const char *PROJECT_VERSION = "0.1-dev";
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
        usleep(500000); // espera 0.1s
    }

    // Função de animação da borda
    draw_building_border('#', 50, 0);

    char resp = '\n';
    while (resp != '0')
    {
        int height, width;

        // Pega altura e largura do terminal
        getmaxyx(stdscr, height, width);

        // Limpar a tela
        clear();

        // Função para imprimir a bordar da tela
        draw_border('#', 50, 0);

        // Função para imprimir a tela home
        home(height, width, resp);
        
        mvprintw((height-3), (width-63), "v %s", PROJECT_VERSION);

        // Atualizar a tela
        refresh();

        switch (resp)
        {
            case '\n':
                mvprintw(0, 0, "%s", "Enter");
                break;
            case '1':
                mvprintw(0, 0, "%s", "1");
                refresh(); 
                break;
            case '2':
                mvprintw(0, 0, "%s", "2");
                refresh();
                break;
            case '0':
                mvprintw(0, 0, "%s", "0");
                refresh();
                break;
            default:
                clear();
                mvprintw(0, 0, "%s", "default");
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
    int height, width;

    // Pega altura e largura do terminal
    getmaxyx(stdscr, height, width);

    // Desenha borda superior e inferior
    for (int x = border_margin_left_right; x < (width - border_margin_left_right); x++) {
        mvaddch(border_margin_top_bottom, x, style);                              // borda cima
        mvaddch(height - 1- border_margin_top_bottom, x, style);                  // borda baixo
    }

    // Desenha borda esquerda e direita
    for (int y = border_margin_top_bottom; y < (height - border_margin_top_bottom); y++) {
        mvaddch(y, border_margin_left_right, style);               // borda esquerda
        mvaddch(y, width - 1 - border_margin_left_right, style);   // borda direita
    }
}

void draw_building_border(char style, int border_margin_left_right, int border_margin_top_bottom)
{
    int height, width;
    getmaxyx(stdscr, height, width);

    // Desenha topo gradualmente
    for(int x = border_margin_left_right; x < width - border_margin_left_right; x++) {
        mvaddch(border_margin_top_bottom, x, style);
        refresh();
        usleep(15000); // pausa para animação
    }

    // Desenha direita gradualmente
    for(int y = border_margin_top_bottom + 1; y < height - border_margin_top_bottom; y++) {
        mvaddch(y, width - 1 - border_margin_left_right, style);
        refresh();
        usleep(15000);
    }

    // Desenha base gradualmente
    for(int x = width - 2 - border_margin_left_right; x >= border_margin_left_right; x--) {
        mvaddch(height - 1 - border_margin_top_bottom, x, style);
        refresh();
        usleep(15000);
    }

    // Desenha esquerda gradualmente
    for(int y = height - 2 - border_margin_top_bottom; y > border_margin_top_bottom; y--) {
        mvaddch(y, border_margin_left_right, style);
        refresh();
        usleep(15000);
    }
}