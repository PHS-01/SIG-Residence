#include <stdio.h>
#include "finance.h"
#include "terminal_control.h"
#include "controllers.h"
#include "config.h"

void read_finance_ui() {
    int id;
    
    printf("=== CONSULTAR TRANSAÇÃO ===\n\n");
    
    if (read_int_input("Digite o ID da transação: ", &id)) {
        printf("\n");
        set_search_finance_id(id);
        Finance finance;
        if (read(&finance, sizeof(Finance), FILE_NAME_FINANCE, match_finance_by_id)) {
            print_finance(&finance);
        } else {
            printf("Transação com ID %d não encontrada ou está inativa.\n", id);
        }
    } else {
        printf("ID inválido.\n");
    }
}