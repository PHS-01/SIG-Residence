#include <stdio.h>
#include "people.h"
#include "terminal_control.h"
#include "config.h"

void read_people_ui() {
    int id;
    
    if (read_int_input("Digite o ID da pessoa: ", &id)) {
        printf("\n");

        People *person = find_person_by_id(id);

        if (person != NULL) {
            print_people_detail(person);
        } else {
            print_error("Pessoa com ID %d não encontrada.", id);
        }
    } else {
        print_error("ID inválido.");
    }
}