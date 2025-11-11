#include <stdio.h>
#include <string.h>
#include <ctype.h> // Adicionado para toupper()
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
    while (true) {
        read_string_input("Data (dd/mm/aaaa): ", new_finance.date, sizeof(new_finance.date));
        if (!validation_date(new_finance.date)) {
            print_error("Data inválida! Use o formato dd/mm/aaaa e insira uma data real.");
        } else {
            break; // Sucesso
        }
    }
    
    // Categoria - Padrão while(true) com break
    while (true) {
        read_string_input("Categoria: ", new_finance.category, sizeof(new_finance.category));
        if (!is_valid_string(new_finance.category, sizeof(new_finance.category))) {
            print_error("Categoria não pode estar vazia e deve ter até 49 caracteres.");
        } else {
            break; // Sucesso
        }
    }
    
    // Tipo: receita ou despesa - Padrão while(true) com break
    char type_input[2];
    while (true) {
        read_string_input("Tipo (R para Receita, D para Despesa): ", type_input, sizeof(type_input));
        
        // Normaliza o input *antes* de validar
        new_finance.type = toupper(type_input[0]);
        
        if (new_finance.type == 'R' || new_finance.type == 'D') {
            break; // Sucesso
        } else {
            print_error("Tipo inválido! Use 'R' para Receita ou 'D' para Despesa.");
        }
    }

    new_finance.status = true;

    printf("\n");
    create(&new_finance, sizeof(Finance), FILE_NAME_FINANCE);
    
    printf("\n");
    print_success("Transação cadastrada com sucesso!");
    printf(COLOR_CYAN "ID da transação: %d" COLOR_RESET "\n", new_finance.id);
}