#include <stdio.h>
#include <ncurses.h>
#include <string.h>

// Variaveis globais do projeto
#include "config.h"

void home(int y, int x)
{
    char *options[] = {
    "[1]   Módulo Pessoas    ",
    "[2]   Módulo Residência    ",
    "[3]   Sobre    ",
    "[4]   Créditos    ",
    "[0]   Sair    "
};

    
    int length_options = sizeof(options) / sizeof(options[0]);

    int h = 2;
    
    // Desenha a arte ASCII
    for (int i = 0; i < LENGTH_ASCII_ART; i++)
    {
        /* code */
        mvprintw(h, x + i, "%s", PROJECT_ASCII_ART[i]);
        h += 1;
    }
    
    h = (y / 2) + 2;

    int width_options = strlen(options[0]);

    // Desenha as opções
    for (int i = 0; i < length_options; i++)
    {
        mvprintw(h, ((COLS - width_options)/2) + i, "%s", options[i]);
        h += 2;
    }
}