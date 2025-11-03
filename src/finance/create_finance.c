#include <stdio.h>
#include <string.h>
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

    // ID_people - com validação individual
    do {
        if (!read_int_input("ID de Pessoa: ", &new_finance.people_id)) {
            print_error("ID de Pessoa inválido.");
        }
    } while (!is_valid_people_id(new_finance.people_id));
    
    // Descrição - com validação individual
    do {
        read_string_input("Descrição: ", new_finance.description, sizeof(new_finance.description));
        if (!is_valid_string(new_finance.description, sizeof(new_finance.description))) {
            print_error("Descrição não pode estar vazia e deve ter até 99 caracteres.");
        }
    } while (!is_valid_string(new_finance.description, sizeof(new_finance.description)));
    
    // Valor - com validação individual
    do {
        if (!read_float_input("Valor: R$ ", &new_finance.value)) {
            print_error("Valor inválido. Digite um número válido.");
            new_finance.value = -1; // Forçar repetição
        } else if (!is_valid_value(new_finance.value)) {
            print_error("Valor não pode ser negativo.");
        }
    } while (!is_valid_value(new_finance.value));
    
    // Data - com validação individual
    do {
        read_string_input("Data (dd/mm/aaaa): ", new_finance.date, sizeof(new_finance.date));
        if (!validation_date(new_finance.date)) {
            print_error("Data inválida! Use o formato dd/mm/aaaa e insira uma data real.");
        }
    } while (!validation_date(new_finance.date));
    
    // Categoria - com validação individual
    do {
        read_string_input("Categoria: ", new_finance.category, sizeof(new_finance.category));
        if (!is_valid_string(new_finance.category, sizeof(new_finance.category))) {
            print_error("Categoria não pode estar vazia e deve ter até 49 caracteres.");
        }
    } while (!is_valid_string(new_finance.category, sizeof(new_finance.category)));
    
    // Tipo: receita ou despesa - com validação individual
    char type_input[2];
    do {
        read_string_input("Tipo (R para Receita, D para Despesa): ", type_input, sizeof(type_input));
        new_finance.type = type_input[0];
        
        if (new_finance.type != 'R' && new_finance.type != 'r' && 
            new_finance.type != 'D' && new_finance.type != 'd') {
            print_error("Tipo inválido! Use 'R' para Receita ou 'D' para Despesa.");
        }
    } while (new_finance.type != 'R' && new_finance.type != 'r' && 
             new_finance.type != 'D' && new_finance.type != 'd');

    // Converter para maiúscula
    if (new_finance.type == 'r') new_finance.type = 'R';
    if (new_finance.type == 'd') new_finance.type = 'D';

    new_finance.status = true;

    printf("\n");
    create(&new_finance, sizeof(Finance), FILE_NAME_FINANCE);
    
    printf("\n");
    print_success("Transação cadastrada com sucesso!");
    printf(COLOR_CYAN "ID da transação: %d" COLOR_RESET "\n", new_finance.id);
}