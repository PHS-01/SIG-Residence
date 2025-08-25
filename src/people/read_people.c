#include <stdio.h>
#include <ncurses.h>
#include <string.h>

void read_people(int y, int x, char people[4][50])
{
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
        "Nome",   
        "Matricula",     
        "Telefone", 
        "Email",
        "",
        "",
        "[0]   Voltar"
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
    } while (resp != '0');
}