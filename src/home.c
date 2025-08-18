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

    for (int i = 0; i < length_ascii_art; i++)
    {
        /* code */
        mvprintw(h, 53, "%s", ascii_art[i]);
        h += 1;
    }
    
    h = (y / 2) + 2;

    for (int i = 0; i < length_options; i++)
    {
        mvprintw(h, ((x/2)-6), "%s", options[i]);
        h += 2;
    }
}