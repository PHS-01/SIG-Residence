#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "people.h"
#include "terminal_control.h"
#include "controllers.h"

void update_people_ui() {
    People updated_person;
    int id;

    printf("=== ATUALIZAR PESSOA ===\n\n");
    
    if (!read_int_input("Digite o ID da pessoa que deseja atualizar: ", &id)) {
        printf("ID inválido.\n");
        return;
    }

    printf("\n");
    
    read_string_input("Novo nome: ", updated_person.name, sizeof(updated_person.name));
    read_string_input("Nova data de nascimento (dd/mm/aaaa): ", updated_person.birth_date, sizeof(updated_person.birth_date));
    read_string_input("Novo email: ", updated_person.email, sizeof(updated_person.email));
    read_string_input("Novo telefone: ", updated_person.phone, sizeof(updated_person.phone));

    updated_person.id = id;
    updated_person.status = true;

    printf("\n");
    // Atualizar pessoa
    set_search_id(id);
    update(&updated_person, sizeof(People), match_people_by_id);
}