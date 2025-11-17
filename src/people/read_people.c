#include <stdio.h>
#include "people.h"
#include "terminal_control.h"
#include "controllers.h"
#include "config.h"

void read_people_ui() {
    int id;
    
    if (read_int_input("Digite o ID da pessoa: ", &id)) {
        printf("\n");
        set_search_id(id);
        People person;
        if (read_data(&person, sizeof(People), FILE_NAME_PEOPLE, match_people_by_id)) {
            print_people_detail(&person);
        } else {
            print_error("Pessoa com ID %d não encontrada ou está inativa.", id);
        }
    } else {
        print_error("ID inválido.");
    }
}