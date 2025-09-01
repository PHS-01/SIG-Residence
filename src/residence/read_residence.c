#include <stdio.h>
#include <ncurses.h>
#include <string.h>

#include "screens.h"

void read_residence(int y, int x, char residence[2][50])
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
        "Número",  
        "Endereço", 
        "",
        "",
        "[1]   Deletar    "
        "[2]   Atualizar    "
        "[0]   Voltar"
    };

    int length_options = sizeof(options) / sizeof(options[0]);
    int length_title = sizeof(title) / sizeof(title[0]);

    char resp;

    do
    {
        clear();

        draw_border('#', 0, 0);

        int h = 2;

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
                mvprintw(h, (x - strlen(options[i])) / 2, "%s", options[i]);
            h += 2;
        }

        refresh();
        
        resp = getch();

        switch (resp)
        {
            case '1':
                delete_residence(y, x, residence);
                break;

            case '2':
                // update_residence(y, x, residence);
                break;

            case '0':                
                break;
            
            default:
                break;
        }

    } while (resp != '0');
}