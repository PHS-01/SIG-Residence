#include <stdio.h>
#include <string.h>

#include "people.h"
#include "config.h"
#include "terminal_control.h"
#include "validations.h"

void create_people_ui() {
    People new_person;
    
    // Gera ID automaticamente
    new_person.id = generate_people_id();
    
    // Nome - com validação individual
    do {
        read_string_input("Nome completo: ", new_person.name, sizeof(new_person.name));
        if (!is_valid_name(new_person.name)) {
            print_error("Nome inválido! Deve conter:");
            print_error("  - Pelo menos nome e sobrenome");
            print_error("  - Apenas letras, espaços, hífens e apóstrofos");
            print_error("  - Entre 2 e 100 caracteres");
            print_error("  - Não pode ter espaços consecutivos");
            print_error("  - Não pode começar ou terminar com espaço");
            print_error("Exemplo: João Silva ou Maria dos Santos");
        }
    } while (!is_valid_name(new_person.name));
    
    // Data de nascimento - com validação individual
    do {
        read_string_input("Data de nascimento (dd/mm/aaaa): ", new_person.birth_date, sizeof(new_person.birth_date));
        if (!validation_bith_date(new_person.birth_date)) {
            print_error("Data inválida! Use o formato dd/mm/aaaa e insira uma data real.");
        }
    } while (!validation_bith_date(new_person.birth_date));
    
    // Email - com validação individual
    do {
        read_string_input("Email: ", new_person.email, sizeof(new_person.email));
        if (!is_valid_email(new_person.email)) {
            print_error("Email inválido! Certifique-se de que contém '@' e '.' e está no formato correto.");
        }
    } while (!is_valid_email(new_person.email));
    
    // Telefone - com validação individual
    do {
        read_string_input("Telefone: ", new_person.phone, sizeof(new_person.phone));
        if (!is_valid_phone(new_person.phone)) {
            print_error("Telefone inválido! Use apenas números, '+' e '-', com 9 a 20 caracteres.");
        }
    } while (!is_valid_phone(new_person.phone));

    new_person.status = true;

    printf("\n");
    if (create_person(new_person)) {
        printf("\n");
        print_success("Pessoa cadastrada com sucesso!");
        printf(COLOR_CYAN "ID da pessoa: %d" COLOR_RESET "\n", new_person.id);
    } else {
        print_error("Erro ao cadastrar pessoa.");
    }
}