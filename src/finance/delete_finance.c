#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "finance.h"
#include "terminal_control.h"

void delete_finance_ui() {
    int id;
    char confirm[3];
    
    if (!read_int_input("Digite o ID da transação a ser excluída: ", &id)) {
        print_error("ID inválido.");
        return;
    }

    // Busca a transação na lista dinâmica
    Finance *finance = finance_list_find(id);
    
    if (finance == NULL || !finance->status) {
        print_error("Transação com ID %d não encontrada ou já está inativa.", id);
        return;
    }

    printf("\n");
    print_finance_detail(finance);
    printf("\n");

    read_string_input("Tem certeza que deseja inativar esta transação? (s/N): ", confirm, sizeof(confirm));

    if (confirm[0] == 's' || confirm[0] == 'S') {
        // Inativa a transação na lista
        finance->status = false;
        // Salva a lista no arquivo
        finance_save_file();
        print_success("Transação inativada com sucesso.");
    } else {
        print_warning("Operação cancelada.");
    }
}