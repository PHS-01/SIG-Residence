#include <stdio.h>
#include <ncurses.h>

void home(int y, int x)
{
    char *ascii_art[] = {
        "  #####  ###  #####        ######                                                     ",
        " #     #  #  #     #       #     # ######  ####  # #####  ###### #    #  ####  ###### ",
        " #        #  #             #     # #      #      # #    # #      ##   # #    # #      ",
        "  #####   #  #  #### ##### ######  #####   ####  # #    # #####  # #  # #      #####  ",
        "       #  #  #     #       #   #   #           # # #    # #      #  # # #      #      ",
        " #     #  #  #     #       #    #  #      #    # # #    # #      #   ## #    # #      ",
        "  #####  ###  #####        #     # ######  ####  # #####  ###### #    #  ####  ###### "
    };                                                                           

    char *options[] = {
        "[1] Sobre",
        "[2] Créditos",
        "[0] Sair"
    };

    int length_ascii_art = sizeof(ascii_art) / sizeof(ascii_art[0]);
    int length_options = sizeof(options) / sizeof(options[0]);

    int h = 2;
    
    // Desenha a arte ASCII
    for (int i = 0; i < length_ascii_art; i++)
    {
        /* code */
        mvprintw(h, ((x/2)-44), "%s", ascii_art[i]);
        h += 1;
    }
    
    h = (y / 2) + 2;


    // Desenha as opções
    for (int i = 0; i < length_options; i++)
    {
        mvprintw(h, ((x/2)-5), "%s", options[i]);
        h += 2;
    }
}