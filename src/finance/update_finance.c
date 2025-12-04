#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "finance.h"
#include "terminal_control.h"
#include "controllers.h"
#include "config.h"
#include "validations.h"

void update_finance_ui() {
    int id;
    
    if (!read_int_input("Digite o ID da transação que deseja atualizar: ", &id)) {
        print_error("ID inválido.");
        return;
    }
    
    Finance *existing_finance = finance_list_find(id);
    
    // Primeiro verifica se a transação existe
    if (existing_finance == NULL || existing_finance->status == false) { 
        print_error("Transação com ID %d não encontrada ou está inativa.", id);
        return;
    }

    printf("\n");
    print_finance_detail(existing_finance);
    printf("\n");

    print_info("Deixe em branco para manter o valor atual.\n");
    
    char temp[100];
    float temp_float;
    
    // Descrição - com validação
    printf("Descrição atual: %s\n", existing_finance->description);
    read_string_input("Nova descrição: ", temp, sizeof(temp));
    if (strlen(temp) > 0) {
        do {
            if (!is_valid_string(temp, sizeof(existing_finance->description))) {
                print_error("Descrição não pode estar vazia e deve ter até 99 caracteres.");
                read_string_input("Nova descrição: ", temp, sizeof(temp));
            } else {
                break;
            }
        } while (1);
        strcpy(existing_finance->description, temp);
    } 
    
    // Valor - com validação
    printf("Valor atual: R$ %.2f\n", existing_finance->value);
    if (read_float_input("Novo valor: R$ ", &temp_float)) {
        do {
            if (!is_valid_value(temp_float)) {
                print_error("Valor não pode ser negativo.");
                if (!read_float_input("Novo valor: R$ ", &temp_float)) {
                    temp_float = existing_finance->value;
                    break;
                }
            } else {
                break;
            }
        } while (1);
        existing_finance->value = temp_float;
    }
    
    // Data - com validação
    printf("Data atual: %s\n", existing_finance->date);
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
        strcpy(existing_finance->date, temp);
    }
    
    // Categoria - com validação
    printf("Categoria atual: %s\n", existing_finance->category);
    read_string_input("Nova categoria: ", temp, sizeof(temp));
    if (strlen(temp) > 0) {
        do {
            if (!is_valid_string(temp, sizeof(existing_finance->category))) {
                print_error("Categoria não pode estar vazia e deve ter até 49 caracteres.");
                read_string_input("Nova categoria: ", temp, sizeof(temp));
            } else {
                break;
            }
        } while (1);
        strcpy(existing_finance->category, temp); 
    }
    
    // Tipo - com validação (agora usando inteiro diretamente)
    printf("Tipo atual: %s\n", existing_finance->type == FINANCE_RECEITA ? "Receita" : "Despesa");
    
    // Pergunta pelo tipo
    int new_type = -1;
    printf("Deseja alterar o tipo? (s/N): ");
    char resposta[3];
    read_string_input("", resposta, sizeof(resposta));
    
    if (resposta[0] == 's' || resposta[0] == 'S') {
        while (true) {
            if (read_int_input("Novo tipo (1 para Receita, 2 para Despesa): ", &new_type)) {
                if (new_type == FINANCE_RECEITA || new_type == FINANCE_DESPESA) {
                    existing_finance->type = (FinanceType)new_type;
                    break;
                } else {
                    print_error("Tipo inválido! Digite 1 para Receita ou 2 para Despesa.");
                }
            } else {
                print_error("Entrada inválida. Digite 1 para Receita ou 2 para Despesa.");
            }
        }
    }

    existing_finance->id = id;
    existing_finance->status = true;

    finance_save_file();
    print_success("Transação atualizada com sucesso!");
}