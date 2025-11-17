#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "finance.h"
#include "terminal_control.h"
#include "controllers.h"
#include "config.h"
#include "validations.h"

void update_finance_ui() {
    Finance updated_finance;
    int id;
    
    if (!read_int_input("Digite o ID da transação que deseja atualizar: ", &id)) {
        print_error("ID inválido.");
        return;
    }

    // Primeiro verifica se a transação existe
    set_search_finance_id(id);
    Finance existing_finance;
    if (!read_data(&existing_finance, sizeof(Finance), FILE_NAME_FINANCE, match_finance_by_id)) {
        print_error("Transação com ID %d não encontrada ou está inativa.");
        return;
    }

    printf("\n");
    print_finance_detail(&existing_finance);
    printf("\n");

    print_info("Deixe em branco para manter o valor atual.\n");
    
    char temp[100];
    float temp_float;
    
    // Descrição - com validação
    printf("Descrição atual: %s\n", existing_finance.description);
    read_string_input("Nova descrição: ", temp, sizeof(temp));
    if (strlen(temp) > 0) {
        do {
            if (!is_valid_string(temp, sizeof(updated_finance.description))) {
                print_error("Descrição não pode estar vazia e deve ter até 99 caracteres.");
                read_string_input("Nova descrição: ", temp, sizeof(temp));
            } else {
                break;
            }
        } while (1);
        strcpy(updated_finance.description, temp);
    } else {
        strcpy(updated_finance.description, existing_finance.description);
    }
    
    // Valor - com validação
    printf("Valor atual: R$ %.2f\n", existing_finance.value);
    if (read_float_input("Novo valor: R$ ", &temp_float)) {
        do {
            if (!is_valid_value(temp_float)) {
                print_error("Valor não pode ser negativo.");
                if (!read_float_input("Novo valor: R$ ", &temp_float)) {
                    temp_float = existing_finance.value;
                    break;
                }
            } else {
                break;
            }
        } while (1);
        updated_finance.value = temp_float;
    } else {
        updated_finance.value = existing_finance.value;
    }
    
    // Data - com validação
    printf("Data atual: %s\n", existing_finance.date);
    read_string_input("Nova data: ", temp, sizeof(temp));
    if (strlen(temp) > 0) {
        do {
            if (!validation_date(temp)) {
                print_error("Data inválida! Use o formato dd/mm/aaaa e insira uma data real.");
                read_string_input("Nova data: ", temp, sizeof(temp));
            } else {
                break;
            }
        } while (1);
        strcpy(updated_finance.date, temp);
    } else {
        strcpy(updated_finance.date, existing_finance.date);
    }
    
    // Categoria - com validação
    printf("Categoria atual: %s\n", existing_finance.category);
    read_string_input("Nova categoria: ", temp, sizeof(temp));
    if (strlen(temp) > 0) {
        do {
            if (!is_valid_string(temp, sizeof(updated_finance.category))) {
                print_error("Categoria não pode estar vazia e deve ter até 49 caracteres.");
                read_string_input("Nova categoria: ", temp, sizeof(temp));
            } else {
                break;
            }
        } while (1);
        strcpy(updated_finance.category, temp);
    } else {
        strcpy(updated_finance.category, existing_finance.category);
    }
    
    // Tipo - com validação
    printf("Tipo atual: %c\n", existing_finance.type);
    char type_input[2];
    read_string_input("Novo tipo (R para Receita, D para Despesa): ", type_input, sizeof(type_input));
    if (strlen(type_input) > 0) {
        char new_type = type_input[0];
        do {
            if (new_type != 'R' && new_type != 'r' && new_type != 'D' && new_type != 'd') {
                print_error("Tipo inválido! Use 'R' para Receita ou 'D' para Despesa.");
                read_string_input("Novo tipo (R para Receita, D para Despesa): ", type_input, sizeof(type_input));
                new_type = type_input[0];
            } else {
                break;
            }
        } while (1);
        
        // Converter para maiúscula
        if (new_type == 'r') new_type = 'R';
        if (new_type == 'd') new_type = 'D';
        updated_finance.type = new_type;
    } else {
        updated_finance.type = existing_finance.type;
    }

    updated_finance.id = id;
    updated_finance.status = true;

    printf("\n");
    set_search_finance_id(id);
    if (update(&updated_finance, sizeof(Finance), FILE_NAME_FINANCE, match_finance_by_id)) {
        print_success("Transação atualizada com sucesso!");
    } else {
        print_error("Erro ao atualizar transação.");
    }
}