#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Funções que desenha as telas
#include "screens.h"
// Funções para controle do terminal, e manipulação do texto
#include "terminal_control.h"

bool confirm_exit(void) {
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

    int cols = 0, rows = 0;
    update_terminal_size(&rows, &cols);

    char resp;

    do {
        resp = draw_alert(msg_alert, length_msg, 50);
    } while (resp != 's' && resp != 'S' && resp != 'n' && resp != 'N');

    if (resp == 's' || resp == 'S') {
        system("clear");
        clear_screen();
        
        int start_y = (rows - (length_msg_final * 2 - 1)) / 2;

        for (int i = 0; i < length_msg_final; i++) {
            int len = strlen(msg[i]);
            int pos_x = (cols - len) / 2;
            int pos_y = start_y + i * 2;  // espaçamento de 1 linha entre mensagens

            ansi_print(pos_y, pos_x, msg[i]);
        }

        get_keypress();  // Espera uma tecla
        return false;  // encerra
    } else {
        return true;  // continua
    }
}