#include <stdio.h>
#include <ncurses.h>
#include <string.h>

#include "screens.h"

char residences[2][50] = {
    "Test",
    "Test"
};

void dashboard_residence(int y, int x)
{
    const char *title[] = {
        "  __  __           _       _         _____          _     _                 _       ",
        " |  \\/  |         | |     | |       |  __ \\        (_)   | |               (_)      ",
        " | \\  / | ___   __| |_   _| | ___   | |__) |___ ___ _  __| | ___ _ __   ___ _  __ _ ",
        " | |\\/| |/ _ \\ / _` | | | | |/ _ \\  |  _  // _ \\ __| |/ _` |/ _ \\ '_ \\ / __| |/ _` |",
        " | |  | | (_) | (_| | |_| | | (_) | | | \\ \\  __\\__ \\ | (_| |  __/ | | | (__| | (_| |",
        " |_|  |_|\\___/ \\__,_|\\__,_|_|\\___/  |_|  \\_\\___|___/_|\\__,_|\\___|_| |_|\\___|_|\\__,_|",
    };

    const char *options[] = {
        "[1]   Criar Residência    ",
        "[2]   Ler Residência      ",
        "[3]   Atualizar Residência",
        "[4]   Excluir Residência  ",
        "[0]   Voltar"
    };

    int length_options = sizeof(options) / sizeof(options[0]);
    int length_title = sizeof(title) / sizeof(title[0]);

    char resp;

    do 
    {
        clear(); // limpa a tela

        // Função para imprimir a borda da tela
        draw_border('#', 0, 0);

        int h = 2;

        // Desenha o título centralizado
        for (int i = 0; i < length_title; i++)
        {
            mvprintw(h, (x - strlen(title[i])) / 2, "%s", title[i]);
            h += 1;
        }

        h = (y / 2) + 2; // espaço depois do título

        int width_options = strlen(options[0]);

        // Desenha as opções centralizadas
        for (int i = 0; i < length_options; i++)
        {
            mvprintw(h, ((x - width_options)/2) + i, "%s", options[i]);
            h += 2;
        }

        refresh(); // atualiza a tela

        resp = getch();

        switch (resp)
        {
            case '1':
                create_residence(y, x);
                break;

            case '2':
                read_residence(y, x, residences);
                break;

            case '3':
                update_residence(y, x, residences);
                break;
            
            case '4':
                delete_residence(y, x, residences);
                break;

            case '0':                
                break;
            
            default:
                break;
        }
    } 
    while (resp != '0');
}