#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "people.h"
#include "terminal_control.h"
#include "controllers.h"

void delete_people_ui() {
    int id;
    char confirm[3];

    printf("=== EXCLUIR PESSOA ===\n\n");
    
    if (!read_int_input("Digite o ID da pessoa a ser excluída: ", &id)) {
        printf("ID inválido.\n");
        return;
    }

    read_string_input("Tem certeza que deseja inativar a pessoa? (s/N): ", confirm, sizeof(confirm));

    if (confirm[0] == 's' || confirm[0] == 'S') {
        set_search_id(id);
        delete(sizeof(People), match_people_by_id);
    } else {
        printf("Operação cancelada.\n");
    }
}