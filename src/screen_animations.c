#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>
#include <string.h>

void fade_animation(char *type)
{
    // Caracteres para a animação
    char *fadeIn_chars[] = {"#", "+", ".", " "};
    char *fadeOut_chars[] = {" ", ".", "+", "#"};

    clear();

    // Desenha os quatro chars da animção, por toda tela
    for(int f = 0; f < 4; f++) 
    {
        for(int y = 0; y < LINES; y++) 
        {
            for(int x = 0; x < COLS; x++) 
            { 
                if (strcmp(type, "out"))
                {
                    mvprintw(y, x, "%s", fadeIn_chars[f]);
                } else
                {
                    mvprintw(y, x, "%s", fadeOut_chars[f]);
                }
                
            }
        }
        refresh();
        // Trava o terminal por alguns s/ms
        usleep(500000);
    }
}

void draw_building_border(char style, int border_margin_left_right, int border_margin_top_bottom)
{
    clear();
    
    // Desenha topo gradualmente
    for(int x = border_margin_left_right; x < COLS - border_margin_left_right; x++) 
    {
        mvaddch(border_margin_top_bottom, x, style);
        refresh();
        usleep(15000);
    }

    // Desenha direita gradualmente
    for(int y = border_margin_top_bottom + 1; y < LINES - border_margin_top_bottom; y++) 
    {
        mvaddch(y, COLS - 1 - border_margin_left_right, style);
        refresh();
        usleep(15000);
    }

    // Desenha base gradualmente
    for(int x = COLS - 2 - border_margin_left_right; x >= border_margin_left_right; x--) 
    {
        mvaddch(LINES - 1 - border_margin_top_bottom, x, style);
        refresh();
        usleep(15000);
    }

    // Desenha esquerda gradualmente
    for(int y = LINES - 2 - border_margin_top_bottom; y > border_margin_top_bottom; y--) 
    {
        mvaddch(y, border_margin_left_right, style);
        refresh();
        usleep(15000);
    }
}