#include <stdio.h>
#include <string.h>

#include "people.h"
#include "config.h"
#include "terminal_control.h"
#include "controllers.h"
#include "validations.h"

void create_people_ui() {
    People new_person;
    
    // Gera ID automaticamente
    new_person.id = generate_people_id();

    do {
        clear_screen();
        read_string_input("Nome: ", new_person.name, sizeof(new_person.name));
        read_string_input("Data de nascimento (dd/mm/aaaa): ", new_person.birth_date, sizeof(new_person.birth_date));
        read_string_input("Email: ", new_person.email, sizeof(new_person.email));
        read_string_input("Telefone: ", new_person.phone, sizeof(new_person.phone));
        
        if (!is_valid_people(&new_person)) {
            printf("Dados inválidos! Por favor, tente novamente.\n");
        } else {
            printf("Dados Validos! Por favor, precione qualquer tecla.\n");
        }

        getchar();

    } while (!is_valid_people(&new_person));

    new_person.status = true;

    printf("\n");
    create(&new_person, sizeof(People), FILE_NAME_PEOPLE);
    
    printf("\n");
    print_success("Pessoa cadastrada com sucesso!");
    printf(COLOR_CYAN "ID da pessoa: %d" COLOR_RESET "\n", new_person.id);
}