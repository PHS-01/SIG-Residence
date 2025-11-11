#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "finance.h"
#include "terminal_control.h"
#include "controllers.h"
#include "config.h"

void delete_finance_ui() {
    int id;
    char confirm[3];
    
    if (!read_int_input("Digite o ID da transação a ser excluída: ", &id)) {
        print_error("ID inválido.");
        return;
    }

    // Primeiro verifica se a transação existe
    set_search_finance_id(id);
    Finance finance;
    if (!read(&finance, sizeof(Finance), FILE_NAME_FINANCE, match_finance_by_id)) {
        print_error("Transação com ID %d não encontrada ou já está inativa.", id);
        return;
    }

    printf("\n");
    print_finance_detail(&finance);
    printf("\n");

    read_string_input("Tem certeza que deseja inativar esta transação? (s/N): ", confirm, sizeof(confirm));

    if (confirm[0] == 's' || confirm[0] == 'S') {
        set_search_finance_id(id);
        if (delete(sizeof(Finance), FILE_NAME_FINANCE, match_finance_by_id)) {
            print_success("Transação inativada com sucesso.");
        } else {
            print_error("Erro ao inativar transação.");
        }
    } else {
        print_warning("Operação cancelada.");
    }
}