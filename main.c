#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>
#include <string.h>

// Funções que desenha as telas
#include <screens.h>
// Variaveis globais do projeto
#include <config.h>

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
    fade_animation("in", 250000);

    int WIDTH_ASCII_ART = strlen(PROJECT_ASCII_ART[0]);

    // Função de animação da logo
    animation_logo_staircase(2, ((COLS - WIDTH_ASCII_ART)/2), 150000);

    // Função de animação da borda
    animation_building_border('#',0, 0, 5000);

    char resp = '\n';
    bool loop = 1;
    while (loop)
    {
        // Limpar a tela
        clear();

        // Função para imprimir a bordar da tela
        draw_border('#',0, 0);

        // Função para imprimir a tela home
        home(LINES, ((COLS - WIDTH_ASCII_ART)/2));
        
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
    fade_animation("out", 250000);
    
    // Finaliza ncurses
    endwin();

    return 0;
}