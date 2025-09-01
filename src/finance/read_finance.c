#include <stdio.h>
#include <ncurses.h>
#include <string.h>

#include "screens.h"

void read_finance(int y, int x, char transactions[4][50], char type)
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
        "Descrição",   
        "Valor",     
        "Data", 
        "Categoria",
        "",
        "[1]   Deletar    [2]   Atualizar    [0]   Voltar"
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

        // Desenha o título ASCII
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
                mvprintw(h, (x - strlen(options[i])) / 2, "%s", options[i]);
            h += 2;
        }

        refresh();

        resp = getch();

        switch (resp)
        {
            case '1':
                // delete_transaction(y, x, transactions, type);
                break;

            case '2':
                // update_transaction(y, x, transactions, type);
                break;

            case '0':                
                break;
            
            default:
                break;
        }

    } while (resp != '0');
}