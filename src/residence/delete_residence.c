#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "residence.h"
#include "terminal_control.h"
#include "controllers.h"
#include "config.h"

void delete_residence_ui() {
    int id;
    char confirm[3];

    printf("=== EXCLUIR RESIDÊNCIA ===\n\n");
    
    if (!read_int_input("Digite o ID da residência a ser excluída: ", &id)) {
        printf("ID inválido.\n");
        return;
    }

    // Primeiro verifica se a residência existe
    set_search_residence_id(id);
    Residence residence;
    if (!read(&residence, sizeof(Residence), FILE_NAME_RESIDENCE, match_residence_by_id)) {
        printf("Residência com ID %d não encontrada ou já está inativa.\n", id);
        return;
    }

    printf("\nDados da residência:\n");
    print_residence(&residence);
    printf("\n");

    read_string_input("Tem certeza que deseja inativar esta residência? (s/N): ", confirm, sizeof(confirm));

    if (confirm[0] == 's' || confirm[0] == 'S') {
        set_search_residence_id(id);
        if (delete(sizeof(Residence), FILE_NAME_RESIDENCE, match_residence_by_id)) {
            printf("Residência inativada com sucesso.\n");
        } else {
            printf("Erro ao inativar residência.\n");
        }
    } else {
        printf("Operação cancelada.\n");
    }
}