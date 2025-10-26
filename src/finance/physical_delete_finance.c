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

    printf("=== EXCLUSÃO FÍSICA DE TRANSAÇÃO ===\n\n");
    
    if (!read_int_input("Digite o ID da transação a ser excluída fisicamente: ", &id)) {
        printf("ID inválido.\n");
        return;
    }

    // Primeiro verifica se a transação existe
    set_search_finance_id(id);
    Finance finance;
    if (!read(&finance, sizeof(Finance), match_finance_by_id, FILE_NAME_FINANCE)) {
        printf("Transação com ID %d não encontrada.\n", id);
        return;
    }

    printf("\nDados da transação que será excluída FISICAMENTE:\n");
    print_finance(&finance);
    printf("\nATENÇÃO: Esta operação é IRREVERSÍVEL!\n");

    clear_input_buffer();

    read_string_input("Confirma a exclusão física? (digite 'sim' para confirmar): ", confirm, sizeof(confirm));

    if (strcmp(confirm, "sim") == 0) {
        set_search_finance_id(id);
        if (physical_delete(sizeof(Finance), match_finance_by_id, FILE_NAME_FINANCE)) {
            printf("Transação excluída fisicamente com sucesso.\n");
        } else {
            printf("Erro ao excluir transação fisicamente.\n");
        }
    } else {
        printf("Operação cancelada.\n");
    }
}