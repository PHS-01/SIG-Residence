#include <stdio.h>
#include <ncurses.h>
#include <string.h>

#include "screens.h"

void update_finance(int y, int x, char transactions[4][50], char type)
{
    // Define título da ação conforme tipo
    const char *type_title = (type == 'r' || type == 'R') ? "Receita" : "Despesa";

    const char *title[] = {                                                                    
        "                        ##                        ",
        "                ##################                ",
        "                ##################                ",
        "                  ##############                  ",
        "                                                  ",
        "                                                  ",
        "                  ################                ",
        "                ####################              ",
        "              ########################            ",
        "            ############    ############          ",
        "          ############        ############        ",
        "          ##########            ##########        ",
        "        ############    ####    ############      ",
        "        ############          ##############      ",
        "       ################          ############     ", 
        "       ##############    ####    ############     ", 
        "      ##############            ##############    ",
        "      ################        ################    ",
        "       ##################    ################     ",
        "        ####################################      ",
        "          ################################        ",
        "              ########################            ",                                               
    };

    const char *options[] = {
        "[1]   Descrição",   
        "[2]   Valor",     
        "[3]   Data", 
        "[4]   Categoria",
        "",
        "[0]   Cancelar"
    };
    
    int length_options = sizeof(options) / sizeof(options[0]);
    int length_title = sizeof(title) / sizeof(title[0]);

    char resp;

    do
    {
        clear();

        // Função para imprimir a borda da tela
        draw_border('#', 0, 0);

        int h = 2;

        // Desenha o título centralizado
        for (int i = 0; i < length_title; i++)
        {
            mvprintw(h, (x - strlen(title[i])) / 2, "%s", title[i]);
            h += 1;
        }

        // Escreve o tipo no centro
        mvprintw(h + 2, (x - strlen(type_title)) / 2, "%s", type_title);

        h = (y / 2) + 6;

        // Desenha as opções e os valores já preenchidos
        for (int i = 0; i < length_options; i++)
        {
            int col = (x - 40) / 2;
            if (i < 4) // os 4 campos de dados
                mvprintw(h, col, "%s: %s", options[i], transactions[i]);
            else
                mvprintw(h, (x - strlen(options[i])) / 2, "%s", options[i]); // opção Cancelar
            h += 2;
        }

        refresh();

        resp = getch();

        switch (resp)
        {
            case '1': // Descrição
                input_box(40, "Digite a Descrição:", transactions[0], 50);
                break;

            case '2': // Valor
                input_box(40, "Digite o Valor:", transactions[1], 50);
                break;

            case '3': // Data
                input_box(40, "Digite a Data (dd/mm/aaaa):", transactions[2], 50);
                break;

            case '4': // Categoria
                input_box(40, "Digite a Categoria:", transactions[3], 50);
                break;

            case '0': // Cancelar
                break;

            default:
                break;
        }
    } while (resp != '0');
}
