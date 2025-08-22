#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>
#include <string.h>

#include "screens.h"

int confirm_exit(int y, int x) 
{
    const char *msg_alert[] = {
        "Você realmente deseja sair ?",
        "[S] Sim    [N] Não"
    };

    const char *msg[] = {
        "Obrigado por usar o SIG-Residence!",
        "Até breve! :)",
        "Pressione qualquer tecla para continuar..."
    };

    int length_msg = sizeof(msg_alert) / sizeof(msg_alert[0]);
    int length_msg_final = sizeof(msg) / sizeof(msg[0]);
    
    char resp;

    do 
    {
       resp = draw_alert(msg_alert, length_msg, 50, 1);
    } 
    while (resp != 's' && resp != 'S' && resp != 'n' && resp != 'N');

    // Espera resposta do usuário
    if(resp == 's' || resp == 'S') {
        clear();
        
        int h = 0;

        for (int i = 0; i < length_msg_final; i++)
        {
            mvprintw( (y - length_msg_final) / 2 + h, (x - (int)strlen(msg[i])) / 2, "%s", msg[i]);

            h += 2;
        }
        refresh();
        getch();
        return 0; // encerra loop
    } else {
        return 1;
    }
}