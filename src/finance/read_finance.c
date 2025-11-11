#include <stdio.h>
#include "finance.h"
#include "terminal_control.h"
#include "controllers.h"
#include "people.h"
#include "config.h"

void read_finance_ui() {
    int id;
    
    if (read_int_input("Digite o ID da transação: ", &id)) {
        printf("\n");
        set_search_finance_id(id);
        Finance finance;
        if (read(&finance, sizeof(Finance), FILE_NAME_FINANCE, match_finance_by_id)) {
            print_finance_detail(&finance);

            // Buscar e exibir dados da pessoa associada
            if (finance.people_id > 0) {
                printf("\n");
                print_info("================= DADOS DA PESSOA ASSOCIADA ===================");
                People person;
                set_search_id(finance.people_id);
                
                if (read(&person, sizeof(People), FILE_NAME_PEOPLE, match_people_by_id)) {
                    print_people_detail(&person);
                } else {
                    print_error("Pessoa com ID %d não encontrada ou está inativa.", finance.people_id);
                }
            } else {
                print_info("Esta transação não está associada a nenhuma pessoa.");
            }
        } else {
            print_error("Transação com ID %d não encontrada ou está inativa.", id);
        }
    } else {
        print_error("ID inválido.");
    }
}