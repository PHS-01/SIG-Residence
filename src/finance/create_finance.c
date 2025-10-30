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

    do {
        clear_screen();
        read_string_input("Descrição: ", new_finance.description, sizeof(new_finance.description));
    
        // Para valor, usamos read_float_input
        float value;
        if (read_float_input("Valor: ", &value)) {
            new_finance.value = value;
        } else {
            printf("Valor inválido. Definindo como 0.0.\n");
            new_finance.value = 0.0;
        }
        
        read_string_input("Data (dd/mm/aaaa): ", new_finance.date, sizeof(new_finance.date));
        read_string_input("Categoria: ", new_finance.category, sizeof(new_finance.category));
        
        // Tipo: receita ou despesa
        char type;
        do {
            read_string_input("Tipo (R para Receita, D para Despesa): ", &type, 2);
        } while (type != 'R' && type != 'r' && type != 'D' && type != 'd');
        
        new_finance.type = type;
        
        if (!is_valid_finance(&new_finance)) {
            printf("Dados inválidos! Por favor, tente novamente.\n");
        } else {
            printf("Dados Validos! Por favor, precione qualquer tecla.\n");
        }

        getchar();

    } while (!is_valid_finance(&new_finance));
    
    new_finance.status = true;

    printf("\n");
    create(&new_finance, sizeof(Finance), FILE_NAME_FINANCE);
    
    printf("\n");
    print_success("Transação cadastrada com sucesso!");
    printf(COLOR_CYAN "ID da transação: %d" COLOR_RESET "\n", new_finance.id);
}