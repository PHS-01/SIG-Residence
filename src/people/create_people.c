#include <stdio.h>
#include <ncurses.h>
#include <string.h>

#include "screens.h"

void create_people(int y, int x)
{
    char people[4][50] = {
        "Vazio",
        "Vazio",
        "Vazio",
        "Vazio"
    };

    const char *title[] = {                        
                                
        "        ##########        ",
        "      ##############      ",
        "      ##############      ",
        "      ##############      ",
        "      ##############      ",
        "      ##############      ",
        "        ##########        ",
        "    ####          ####    ",
        "  ######################  ",
        "##########################",
        "##########################",
        "##########################",
        " ######################## ",
    };

    const char *options[] = {
        "[1]   Nome",   
        "[2]   Matricula",     
        "[3]   Telefone", 
        "[4]   Email",
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

        int h = 2;

        // Desenha o título centralizado
        for (int i = 0; i < length_title; i++)
        {
            mvprintw(h, (x - strlen(title[i])) / 2, "%s", title[i]);
            h += 1;
        }

        h = (y / 2) + 1;

        // Desenha as opções e os valores já preenchidos
        for (int i = 0; i < length_options; i++)
        {
            int col = (x - 40) / 2;
            if (i < 4) // os 4 campos de dados
                mvprintw(h, col, "%s: %s", options[i], people[i]);
            else
                mvprintw(h, (x - strlen(options[i])) / 2, "%s", options[i]); // opção Cancelar
            h += 2;
        }

        refresh();

        resp = getch();

        switch (resp)
        {
            case '1': // Nome
                input_box(40, "Digite o Nome:", people[0], 50);
                break;

            case '2': // Matrícula
                input_box(40, "Digite a Matrícula:", people[1], 50);
                break;

            case '3': // Telefone
                input_box(40, "Digite o Telefone:", people[2], 50);
                break;

            case '4': // Email
                input_box(40, "Digite o Email:", people[3], 50);
                break;

            case '0': // Cancelar
                break;

            default:
                break;
        }
    } while (resp != '0');
}