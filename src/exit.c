#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>

int sair(int y, int x, char resp) {
    // Primeira tela - confirmação
    clear();
    mvprintw(y/2 - 4, (x/2) - 15, "Você realmente deseja sair?");
    mvprintw(y/2 - 2, (x/2) - 15, "Aperte duas vezes para comfirmar!");
    mvprintw(y/2,     (x/2) - 10, "[S] Sim   [N] Não");
    refresh();

    // Espera resposta do usuário
    while (1) {
        resp = getch();
        if (resp == 's' || resp == 'S') {
            // Tela de despedida
            clear();
            mvprintw(y/2 - 4, (x/2) - 15, "Obrigado por usar o SIG-Residence!");
            mvprintw(y/2 - 2,     (x/2) - 12, "Até breve! :)");
            mvprintw(y/2, (x/2) - 15, "pressione qualquer tecla para comtinua!");
            refresh();
            usleep(2000000); // espera 2 segundos
            return 0;
            break;
        } else if (resp == 'n' || resp == 'N') {
            // Cancela saída
            return 1;
            break;
        }
    }
}