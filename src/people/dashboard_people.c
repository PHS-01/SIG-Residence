#include <stdio.h>
#include <ncurses.h>
#include <string.h>

#include "screens.h"

char people[4][50] = {
    "Test",
    "Test",
    "Test",
    "Test"
};

void dashboard_people(int y, int x)
{
    const char *title[] = {
        "  __  __           _       _         _____                              ",
        " |  \\/  |         | |     | |       |  __ \\                             ",
        " | \\  / | ___   __| |_   _| | ___   | |__) |__ ___ ___  ___   __ _ ___  ",
        " | |\\/| |/ _ \\ / _` | | | | |/ _ \\  |  ___/ _ \\ __/ __|/ _ \\ / _` / __| ",
        " | |  | | (_) | (_| | |_| | | (_) | | |  |  __\\__ \\__ \\ (_) | (_| \\__ \\ ",
        " |_|  |_|\\___/ \\__,_|\\__,_|_|\\___/  |_|   \\___|___/___/\\___/ \\__,_|___/ "
    };


    const char *options[] = {
        "[1]   Criar Pessoa    ",   
        "[2]   Ler Pessoa      ",     
        "[3]   Atualizar Pessoa", 
        "[4]   Excluir Pessoa  ",
        "[0]   Voltar"
    };
    
    int length_options = sizeof(options) / sizeof(options[0]);
    int length_title = sizeof(title) / sizeof(title[0]);

    char resp;

    do 
    {
        clear(); // limpa a tela

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
                create_people(y, x);
                break;

            case '2':
                read_people(y, x, people);
                break;

            case '3':
                update_people(y, x, people);
                break;
            
            case '4':
                delete_people(y, x, people);
                break;

            case '0':                
                break;
            
            default:
                break;
        }
    } 
    while (resp != '0');
}