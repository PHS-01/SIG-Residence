#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>
#include <string.h>

// Funções que desenha as telas
#include "screens.h"
// Variaveis globais do projeto
#include "config.h"

int main(void)
{
    // Inicia modo ncurses
    initscr();

    // Desabilita buffer de linha 
    // Captura teclas sem precisar de ENTER
    // Fechar a janela com ctrl + c
    cbreak();

    // Não mostrar teclas digitadas
    noecho();
    
    // Animação de entrada
    fade_animation("in", 250000);

    int WIDTH_ASCII_ART = strlen(PROJECT_ASCII_ART[0]);

    // Função de animação da logo
    animation_logo_staircase(2, ((COLS - WIDTH_ASCII_ART)/2), 150000);

    // Função de animação da borda
    animation_building_border('#',0, 0, 5000);

    char resp;

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

        resp = getch();

        switch (resp)
        {
            case '1':
                dashboard_people(LINES, COLS);
                break;

            case '2':
                dashboard_residence(LINES, COLS);
                break;

            case '3':
                clear();
                about(LINES, COLS);
                refresh(); 
                break;

            case '4':
                clear();
                credits(LINES, COLS);
                refresh(); 
                break;

            case '0':
                clear();
                loop = confirm_exit(LINES, COLS);
                refresh();
                break;

            default:
                refresh();
                break;
        }

    }

    // Animação de saida
    fade_animation("out", 250000);
    
    // Finaliza ncurses
    endwin();

    return 0;
}