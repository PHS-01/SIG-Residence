#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>
#include <string.h>

#include "screens.h"

void delete_people(int y, int x, char people[4][50]) 
{
    const char *msg_alert[] = {
        "Deseja realmente excluir esta pessoa?",
        "[S] Sim    [N] Não"
    };

    const char *msg[] = {
        "Pessoa excluída com sucesso!",
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
        
        draw_alert(msg, length_msg_final, 50, 1);

        refresh();
    }
}