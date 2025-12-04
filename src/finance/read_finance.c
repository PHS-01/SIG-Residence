#include <stdio.h>
#include "finance.h"
#include "terminal_control.h"
#include "people.h"

void read_finance_ui() {
    int id;
    
    if (read_int_input("Digite o ID da transação: ", &id)) {
        printf("\n");
        
        // Busca a transação na lista dinâmica
        Finance *finance = finance_list_find(id);
        
        if (finance != NULL && finance->status) {
            print_finance_detail(finance);

            // Buscar e exibir dados da pessoa associada
            if (finance->people_id > 0) {
                printf("\n");
                print_info("================= DADOS DA PESSOA ASSOCIADA ===================");
                
                // Busca pessoa na lista dinâmica de pessoas
                People *person = find_person_by_id(finance->people_id);
                if (person != NULL && person->status) {
                    print_people_detail(person);
                } else {
                    print_error("Pessoa com ID %d não encontrada ou está inativa.", finance->people_id);
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