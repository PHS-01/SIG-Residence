#include <stdio.h>
#include <ncurses.h>
#include <string.h>

#include "screens.h"

void update_residence(int y, int x, char residence [2][50])
{
    const char *title[] = {                        
                                
        "            ##	     	   ",
        "          ###### 	       ",
        "        ##########   	   ",
        "      ##############      ",
        "    ##################    ",
        "  ######################  ",
        "##########################",
        " ######################## ",
        " ######################## ",
        " #######          ####### ",
        " #######          ####### ",
        " #######          ####### ",
        " #######          ####### ",
    };
    const char *options[] = {
        "[1]   Número",   
        "[2]   Endereço", 
        "",
        "",
        "[0]   Cancelar"
    };

    int length_options = sizeof(options) / sizeof(options[0]);
    int length_title = sizeof(title) / sizeof(title[0]);

    char resp;

    do
    { 
        clear();

        // Função para imprimir a bordar da tela
        draw_border('#', 0, 0);

        int h = 2;

        // Desenha o título centralizado
        for (int i = 0; i < length_title; i++)
        {
            mvprintw(h, (x - strlen(title[i])) / 2, "%s", title[i]);
            h += 1;
        }

        h = (y / 2) + 1;

        for (int i = 0; i < length_options; i++)
        {
            int col = (x - 40) / 2;
            if (i < 2)
                mvprintw(h, col, "%s: %s", options[i], residence[i]);
            else
                mvprintw(h, (x - strlen(options[i])) / 2, "%s", options[i]); // opção Cancelar
            h += 2;
        }

        refresh();

        resp = getch();

        switch (resp)
        {
            case '1': // Número
                input_box(40, "Número da Residência:", residence[0], 50);
                break;

            case '2': // Endereço
                input_box(60, "Endereço da Residência:", residence[1], 50);
                break;

            case '0': // Cancelar
                break;

            default:
                break;
        }
    } while (resp != '0');
}
