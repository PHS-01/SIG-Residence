#include <stdio.h>
#include <ncurses.h>
#include <string.h>

#include "screens.h"

char transaction[4][50] = {
    "Vazio",        // Descrição
    "0.00",         // Valor
    "00/00/0000",   // Data
    "Sem categoria" // Categoria
};

void dashboard_finance(int y, int x)
{
    const char *title[] = {
        "  ______ _                        _            ",
        " |  ____(_)                      (_)           ",
        " | |__   _ _ __   __ _ _ __   ___ _  __ _ ___  ",
        " |  __| | | '_ \\ / _` | '_ \\ / __| |/ _` / __| ",
        " | |    | | | | | (_| | | | | (__| | (_| \\__ \\ ",
        " |_|    |_|_| |_|\\__,_|_| |_|\\___|_|\\__,_|___/ "
    };


    const char *options[] = {
        "[1]   Criar Receita/Despesa     ",
        "[2]   Ler Receita/Despesa       ",
        "[3]   Atualizar Receita/Despesa ",
        "[4]   Excluir Receita/Despesa   ",
        "[0]   Voltar"
    };

    const char *msg_alert[] = {
        "[R] Receita    [D] Despesa"
    };

    int length_options = sizeof(options) / sizeof(options[0]);
    int length_title = sizeof(title) / sizeof(title[0]);
    int length_msg = sizeof(msg_alert) / sizeof(msg_alert[0]);

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
                do 
                {
                    resp = draw_alert(msg_alert, length_msg, 50, 0);
                } 
                while (resp != 'r' && resp != 'R' && resp != 'd' && resp != 'D');
                create_finance(y, x, resp); // criar nova receita/despesa
                break;

            case '2':
                do 
                {
                    resp = draw_alert(msg_alert, length_msg, 50, 0);
                } 
                while (resp != 'r' && resp != 'R' && resp != 'd' && resp != 'D');
                read_finance(y, x, transaction, resp); // listar lançamentos
                break;

            case '3':
                do 
                {
                    resp = draw_alert(msg_alert, length_msg, 50, 0);
                } 
                while (resp != 'r' && resp != 'R' && resp != 'd' && resp != 'D');
                // update_transaction(y, x, transactions); // atualizar
                break;

            case '4':
                do 
                {
                    resp = draw_alert(msg_alert, length_msg, 50, 0);
                } 
                while (resp != 'r' && resp != 'R' && resp != 'd' && resp != 'D');
                // delete_transaction(y, x, transactions); // excluir
                break;

            case '0':
                break;

            default:
                break;
        }
    }
    while (resp != '0');
}
