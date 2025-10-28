#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "residence.h"
#include "terminal_control.h"
#include "controllers.h"
#include "config.h"

void physical_delete_residence_ui() {
    int id;
    char confirm[4];

    printf("=== EXCLUSÃO FÍSICA DE RESIDÊNCIA ===\n\n");
    
    if (!read_int_input("Digite o ID da residência a ser excluída fisicamente: ", &id)) {
        printf("ID inválido.\n");
        return;
    }

    // Primeiro verifica se a residência existe
    set_search_residence_id(id);
    Residence residence;
    if (!read(&residence, sizeof(Residence), FILE_NAME_RESIDENCE, match_residence_by_id)) {
        printf("Residência com ID %d não encontrada.\n", id);
        return;
    }

    printf("\nDados da residência que será excluída FISICAMENTE:\n");
    print_residence(&residence);
    printf("\nATENÇÃO: Esta operação é IRREVERSÍVEL!\n");

    clear_input_buffer();

    read_string_input("Confirma a exclusão física? (digite 'sim' para confirmar): ", confirm, sizeof(confirm));

    if (strcmp(confirm, "sim") == 0) {
        set_search_residence_id(id);
        if (physical_delete(sizeof(Residence), match_residence_by_id, FILE_NAME_RESIDENCE)) {
            printf("Residência excluída fisicamente com sucesso.\n");
        } else {
            printf("Erro ao excluir residência fisicamente.\n");
        }
    } else {
        printf("Operação cancelada.\n");
    }
}