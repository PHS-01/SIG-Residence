#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>
#include <string.h>

#include "screens.h"

void delete_finance(int y, int x, char transactions[4][50], char type) 
{
    // Define título e mensagens conforme tipo
    const char *type_title = (type == 'r' || type == 'R') ? "Receita" : "Despesa";

    char msg_alert_1[100];
    snprintf(msg_alert_1, sizeof(msg_alert_1), "Deseja realmente excluir esta %s?", type_title);

    char msg_final_1[100];
    snprintf(msg_final_1, sizeof(msg_final_1), "%s excluída com sucesso!", type_title);

    const char *msg_alert[] = {
        msg_alert_1,
        "[S] Sim    [N] Não"
    };

    const char *msg[] = {
        msg_final_1,
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
