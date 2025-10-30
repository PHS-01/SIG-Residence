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
    
    if (!read_int_input("Digite o ID da residência a ser excluída fisicamente: ", &id)) {
        print_error("ID inválido.");
        return;
    }

    // Primeiro verifica se a residência existe
    set_search_residence_id(id);
    Residence residence;
    if (!read(&residence, sizeof(Residence), FILE_NAME_RESIDENCE, match_residence_by_id)) {
        print_error("Residência com ID %d não encontrada.");
        return;
    }

    printf("\nDados da residência que será excluída FISICAMENTE:\n");
    print_residence_detail(&residence);
    printf("\n");
    print_warning("ATENÇÃO: Esta operação é IRREVERSÍVEL!");

    clear_input_buffer();

    read_string_input("Confirma a exclusão física? (digite 'sim' para confirmar): ", confirm, sizeof(confirm));

    if (strcmp(confirm, "sim") == 0) {
        set_search_residence_id(id);
        if (physical_delete(sizeof(Residence), match_residence_by_id, FILE_NAME_RESIDENCE)) {
            print_success("Residência excluída fisicamente com sucesso.");
        } else {
            print_error("Erro ao excluir residência fisicamente.");
        }
    } else {
        print_warning("Operação cancelada.");
    }
}