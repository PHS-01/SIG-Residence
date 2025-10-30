#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "finance.h"
#include "terminal_control.h"
#include "controllers.h"
#include "config.h"

void physical_delete_finance_ui() {
    int id;
    char confirm[4];
    
    if (!read_int_input("Digite o ID da transação a ser excluída fisicamente: ", &id)) {
        print_error("ID inválido.");
        return;
    }

    // Primeiro verifica se a transação existe
    set_search_finance_id(id);
    Finance finance;
    if (!read(&finance, sizeof(Finance), FILE_NAME_FINANCE, match_finance_by_id)) {
        print_error("Transação com ID %d não encontrada.");
        return;
    }

    printf("\nDados da transação que será excluída FISICAMENTE:\n");
    print_finance_detail(&finance);
    printf("\n");
    print_warning("ATENÇÃO: Esta operação é IRREVERSÍVEL!");

    clear_input_buffer();

    read_string_input("Confirma a exclusão física? (digite 'sim' para confirmar): ", confirm, sizeof(confirm));

    if (strcmp(confirm, "sim") == 0) {
        set_search_finance_id(id);
        if (physical_delete(sizeof(Finance), match_finance_by_id, FILE_NAME_FINANCE)) {
            print_success("Transação excluída fisicamente com sucesso.");
        } else {
            print_error("Erro ao excluir transação fisicamente.");
        }
    } else {
        print_warning("Operação cancelada.");
    }
}