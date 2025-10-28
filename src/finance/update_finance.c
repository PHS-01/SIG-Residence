#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "finance.h"
#include "terminal_control.h"
#include "controllers.h"
#include "config.h"

void update_finance_ui() {
    Finance updated_finance;
    int id;

    printf("=== ATUALIZAR TRANSAÇÃO ===\n\n");
    
    if (!read_int_input("Digite o ID da transação que deseja atualizar: ", &id)) {
        printf("ID inválido.\n");
        return;
    }

    // Primeiro verifica se a transação existe
    set_search_finance_id(id);
    Finance existing_finance;
    if (!read(&existing_finance, sizeof(Finance), FILE_NAME_FINANCE, match_finance_by_id)) {
        printf("Transação com ID %d não encontrada ou está inativa.\n", id);
        return;
    }

    printf("\nDeixe em branco para manter o valor atual.\n\n");
    
    char temp[100];
    float temp_float;
    
    // Descrição
    printf("Descrição atual: %s\n", existing_finance.description);
    read_string_input("Nova descrição: ", temp, sizeof(temp));
    if (strlen(temp) > 0) {
        strcpy(updated_finance.description, temp);
    } else {
        strcpy(updated_finance.description, existing_finance.description);
    }
    
    // Valor
    printf("Valor atual: %.2f\n", existing_finance.value);
    if (read_float_input("Novo valor: ", &temp_float)) {
        updated_finance.value = temp_float;
    } else {
        updated_finance.value = existing_finance.value;
    }
    
    // Data
    printf("Data atual: %s\n", existing_finance.date);
    read_string_input("Nova data: ", temp, sizeof(temp));
    if (strlen(temp) > 0) {
        strcpy(updated_finance.date, temp);
    } else {
        strcpy(updated_finance.date, existing_finance.date);
    }
    
    // Categoria
    printf("Categoria atual: %s\n", existing_finance.category);
    read_string_input("Nova categoria: ", temp, sizeof(temp));
    if (strlen(temp) > 0) {
        strcpy(updated_finance.category, temp);
    } else {
        strcpy(updated_finance.category, existing_finance.category);
    }
    
    // Tipo
    printf("Tipo atual: %c\n", existing_finance.type);
    char type[2];
    read_string_input("Novo tipo (R para Receita, D para Despesa): ", type, sizeof(type));
    if (type[0] == 'R' || type[0] == 'r' || type[0] == 'D' || type[0] == 'd') {
        updated_finance.type = type[0];
    } else {
        updated_finance.type = existing_finance.type;
    }

    updated_finance.id = id;
    updated_finance.status = true;

    printf("\n");
    set_search_finance_id(id);
    if (update(&updated_finance, sizeof(Finance), FILE_NAME_FINANCE,match_finance_by_id)) {
        printf("Transação atualizada com sucesso!\n");
    } else {
        printf("Erro ao atualizar transação.\n");
    }
}