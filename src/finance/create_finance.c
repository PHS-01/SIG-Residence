#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "screens.h"
#include "finance.h"
#include "config.h"
#include "terminal_control.h"
#include "controllers.h"
#include "validations.h"

void create_finance_ui() {
    Finance new_finance;
    
    // Gera ID automaticamente
    new_finance.id = generate_finance_id();

    // ID_people - Padrão while(true) com break
    while (true) {
        if (!read_int_input("ID de Pessoa: ", &new_finance.people_id)) {
            print_error("ID de Pessoa inválido (formato incorreto).");
        } else if (!is_valid_people_id(new_finance.people_id)) {
            print_error("ID de Pessoa não encontrado ou logicamente inválido.");
        } else {
            break; // Sucesso
        }
    }
    
    // Descrição - Padrão while(true) com break
    while (true) {
        read_string_input("Descrição: ", new_finance.description, sizeof(new_finance.description));
        if (!is_valid_string(new_finance.description, sizeof(new_finance.description))) {
            print_error("Descrição não pode estar vazia e deve ter até 99 caracteres.");
        } else {
            break; // Sucesso
        }
    }
    
    // Valor - Padrão while(true) com break
    while (true) {
        if (!read_float_input("Valor: R$ ", &new_finance.value)) {
            print_error("Valor inválido. Digite um número válido (ex: 123.45).");
        } else if (!is_valid_value(new_finance.value)) {
            print_error("Valor não pode ser negativo.");
        } else {
            break; // Sucesso
        }
    }
    
    // Data - Padrão while(true) com break
    // while (true) {
    //     read_string_input("Data (dd/mm/aaaa): ", new_finance.date, sizeof(new_finance.date));
    //     if (!validation_date(new_finance.date)) {
    //         print_error("Data inválida! Use o formato dd/mm/aaaa e insira uma data real.");
    //     } else {
    //         break; // Sucesso
    //     }
    // }
    
    // By Gemini
    // Obtém o tempo atual 
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    // Buffer maior (40 bytes) para satisfazer o compilador que calcula o pior caso dos inteiros
    char temp_date[40];

    // Formata no buffer temporário
    snprintf(temp_date, sizeof(temp_date), "%02d/%02d/%04d", 
             tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);

    // Copia para a struct limitando ao tamanho exato (10 chars + \0)
    strncpy(new_finance.date, temp_date, sizeof(new_finance.date) - 1);
    new_finance.date[sizeof(new_finance.date) - 1] = '\0'; // Garante null-termination

    // Exibe para o usuário saber qual data foi registrada
    printf("Data atual registrada automaticamente: %s\n", new_finance.date);

    // Categoria - Padrão while(true) com break
    while (true) {
        read_string_input("Categoria: ", new_finance.category, sizeof(new_finance.category));
        if (!is_valid_string(new_finance.category, sizeof(new_finance.category))) {
            print_error("Categoria não pode estar vazia e deve ter até 49 caracteres.");
        } else {
            break; // Sucesso
        }
    }
    
    // Tipo: receita ou despesa - Agora usando inteiro diretamente
    while (true) {
        int tipo_input;
        if (read_int_input("Tipo (1 para Receita, 2 para Despesa): ", &tipo_input)) {
            if (tipo_input == FINANCE_RECEITA || tipo_input == FINANCE_DESPESA) {
                new_finance.type = (FinanceType)tipo_input;
                break;
            } else {
                print_error("Tipo inválido! Use 1 para Receita ou 2 para Despesa.");
            }
        } else {
            print_error("Entrada inválida. Digite 1 para Receita ou 2 para Despesa.");
        }
    }

    new_finance.status = true;

    printf("\n");
    if (finance_list_insert(new_finance)) {
        print_success("Transação cadastrada com sucesso!");
        printf(COLOR_CYAN "ID da transação: %d" COLOR_RESET "\n", new_finance.id);
    } else {
        print_error("Erro ao cadastrar Transação.");
    }
}