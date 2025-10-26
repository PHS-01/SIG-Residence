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

    printf("=== EXCLUIR TRANSAÇÃO (LÓGICA) ===\n\n");
    
    if (!read_int_input("Digite o ID da transação a ser excluída: ", &id)) {
        printf("ID inválido.\n");
        return;
    }

    // Primeiro verifica se a transação existe
    set_search_finance_id(id);
    Finance finance;
    if (!read(&finance, sizeof(Finance), match_finance_by_id, FILE_NAME_FINANCE)) {
        printf("Transação com ID %d não encontrada ou já está inativa.\n", id);
        return;
    }

    printf("\nDados da transação:\n");
    print_finance(&finance);
    printf("\n");

    read_string_input("Tem certeza que deseja inativar esta transação? (s/N): ", confirm, sizeof(confirm));

    if (confirm[0] == 's' || confirm[0] == 'S') {
        set_search_finance_id(id);
        if (delete(sizeof(Finance), match_finance_by_id, FILE_NAME_FINANCE)) {
            printf("Transação inativada com sucesso.\n");
        } else {
            printf("Erro ao inativar transação.\n");
        }
    } else {
        printf("Operação cancelada.\n");
    }
}