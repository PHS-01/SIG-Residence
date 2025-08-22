#include <stdio.h>
#include <ncurses.h>
#include <string.h>

#include "screens.h"

void about(int y, int x)
{
    const char *text[] = {
        "      ___           ___           ___           ___           ___      ",
        "     /\\  \\         /\\  \\         /\\  \\         /\\  \\         /\\  \\     ",
        "    /::\\  \\       /::\\  \\       /::\\  \\       /::\\  \\       /::\\  \\    ",
        "   /:/\\ \\  \\     /:/\\:\\  \\     /:/\\:\\  \\     /:/\\:\\  \\     /:/\\:\\  \\   ",
        "  _\\:\\~\\ \\  \\   /:/  \\:\\  \\   /::\\~\\:\\__\\   /::\\~\\:\\  \\   /::\\~\\:\\  \\  ",
        " /\\ \\:\\ \\ \\__\\ /:/__/ \\:\\__\\ /:/\\:\\ \\:|__| /:/\\:\\ \\:\\__\\ /:/\\:\\ \\:\\__\\ ",
        " \\:\\ \\:\\ \\/__/ \\:\\  \\ /:/  / \\:\\~\\:\\/:/  / \\/_|::\\/:/  / \\:\\~\\:\\ \\/__/ ",
        "  \\:\\ \\:\\__\\    \\:\\  /:/  /   \\:\\ \\::/  /     |:|::/  /   \\:\\ \\:\\__\\   ",
        "   \\:\\/:/  /     \\:\\/:/  /     \\:\\/:/  /      |:|\\/__/     \\:\\ \\/__/   ",
        "    \\::/  /       \\::/  /       \\::/__/       |:|  |        \\:\\__\\     ",
        "     \\/__/         \\/__/         ~~            \\|__|         \\/__/     ",
        "",
        "",
        "SIG-Residence é um sistema de gestão de despesas",
        "para repúblicas estudantis, desenvolvido em C.",
        "",
        "Permite registrar, organizar e acompanhar gastos",
        "de forma simples, por meio do terminal.",
        "",
        "O projeto prevê evolução futura para C++,",
        "com novos recursos e melhorias.",
        "",
        "",
        "",
        "",
        "[0] Voltar"   
    };

    int length_text = sizeof(text) / sizeof(text[0]);

    char resp;

    do 
    {
        resp = draw_alert(text, length_text, strlen(text[0]) + 2, 0);
    } 
    while (resp != '0');
}