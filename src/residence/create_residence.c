#include <stdio.h>
#include <ncurses.h>
#include <string.h>

#include "screens.h"

void create_residence(int y, int x)
{
    char residence[4][50] = {
        "Vazio",
        "Vazio",
        "Vazio",
        "Vazio"
    };

    const char *msg[] = {
        "Residência criada com sucesso!",
        "Pressione qualquer tecla para continuar..."
    };

    const char *title[] = {                        
                                
        "            ##	     	   ",
        "          ###### 	       ",
        "        ##########   	   ",
        "      ##############      ",
        "    ##################    ",
        "  ######################  ",
        "##########################",
        " ######################## ",
        " ######################## ",
        " #######          ####### ",
        " #######          ####### ",
        " #######          ####### ",
        " #######          ####### ",
    };
    const char *options[] = {
        "[1]   Número",   // Número de identificação da residência
        "[2]   Endereço", // Localização 
        "[3]   Capacidade", // Vagas da residência, capacidade de pessoas basicamente
        "[4]   Gestão", // Coodernação/Pessoa responsável pela residência
        "",
        "",
        "[C]   Criar    "
        "[0]   Cancelar"
    };

    int length_options = sizeof(options) / sizeof(options[0]);
    int length_title = sizeof(title) / sizeof(title[0]);

    char resp;

    do
    {
    // COMANDOS DE CREATE_PEOPLE
        clear();

        draw_border('#', 50, 0);

        int h = 2;

        for (int i = 0; i < length_title; i++)
        {
            mvprintw(h, (x - strlen(title[i])) / 2, "%s", title[i]);
            h += 1;
        }

        h = (y / 2) + 1;

        for (int i = 0; i < length_options; i++)
        {
            int col = (x - 40) / 2;
            if (i < 4)
                mvprintw(h, col, "%s: %s", options[i], residence[i]);
            else
                mvprintw(h, (x - strlen(options[i])) / 2, "%s", options[i]);
            h += 2;
        }

        refresh();
        
        resp = getch();

        switch (resp)
        {
            case '1': // Número
                input_box(40, "Número da Residência:", residence[0], 50);
                break;

            case '2': // Endereço
                input_box(40, "Endereço da Residência:", residence[1], 50);
                break;

            case '3': // Capacidade
                input_box(40, "Capacidade da Residência: ", residence[2], 50);
                break;

            case '4': // Gestão
                input_box(40, "Gestão da Residência: ", residence[3], 50);
                break;
        
            case 'c':
                int length_msg_final = sizeof(msg) / sizeof(msg[0]);
                clear();
                draw_alert(msg, length_msg_final, 50, 1);
                refresh();
                break;

            case '0':
                break;

            default:
                break;
        }
    } while (resp != '0');
}