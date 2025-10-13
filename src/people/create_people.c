#include <stdio.h>
#include <string.h>
#include "people.h"
#include "config.h"
#include "terminal_control.h"

void create_people_ui() {
    People new_person;

    printf("=== CADASTRO DE PESSOA ===\n\n");
    
    new_person.id = 0;
    
    read_string_input("Nome: ", new_person.name, sizeof(new_person.name));
    read_string_input("Data de nascimento (dd/mm/aaaa): ", new_person.birth_date, sizeof(new_person.birth_date));
    read_string_input("Email: ", new_person.email, sizeof(new_person.email));
    read_string_input("Telefone: ", new_person.phone, sizeof(new_person.phone));

    new_person.status = true;

    printf("\n");
    create_people(new_person);
}