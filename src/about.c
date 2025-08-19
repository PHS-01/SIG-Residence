#include <stdio.h>
#include <ncurses.h>
#include <string.h>

void about(int y, int x)
{
    char *titulo[] = {
        "####################################################",
        "-----                S O B R E                 -----",
        "####################################################",
        ""
    };

    char *texto[] = {
        "SIG-Residence é um sistema de gestão de despesas",
        "para repúblicas estudantis, desenvolvido em C.",
        "",
        "Permite registrar, organizar e acompanhar gastos",
        "de forma simples, por meio do terminal.",
        "",
        "O projeto prevê evolução futura para C++,",
        "com novos recursos e melhorias.",
        ""
    };

    int h = 2;

    // Mostrar título
    for (int i = 0; i < sizeof(titulo) / sizeof(titulo[0]); i++) {
        mvprintw(h, (x / 2) - (strlen(titulo[i]) / 2), "%s", titulo[i]);
        h++;
    }

    h += 1;

    // Mostrar texto
    for (int i = 0; i < sizeof(texto) / sizeof(texto[0]); i++) {
        mvprintw(h, (x / 2) - (strlen(texto[i]) / 2), "%s", texto[i]);
        h++;
    }

    // Rodapé com instrução
    mvprintw(y-3, 16, "[0] Voltar ao Menu");
}