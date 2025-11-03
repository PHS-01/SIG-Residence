#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "people.h"
#include "terminal_control.h"
#include "controllers.h"
#include "config.h"
#include "validations.h"

void update_people_ui() {
    People updated_person;
    int id;
    
    if (!read_int_input("Digite o ID da pessoa que deseja atualizar: ", &id)) {
        print_error("ID inválido.");
        return;
    }

    // Primeiro verifica se a pessoa existe
    set_search_id(id);
    People existing_person;
    if (!read(&existing_person, sizeof(People), FILE_NAME_PEOPLE, match_people_by_id)) {
        print_error("Pessoa com ID %d não encontrada ou está inativa.");
        return;
    }

    printf("\n");
    print_people_detail(&existing_person);
    printf("\n");

    print_info("Deixe em branco para manter o valor atual.\n");
    
    char temp[100];
    
    // Nome - com validação
    printf("Nome atual: %s\n", existing_person.name);
    read_string_input("Novo nome: ", temp, sizeof(temp));
    if (strlen(temp) > 0) {
        do {
            if (!is_valid_string(temp, sizeof(updated_person.name))) {
                print_error("Nome não pode estar vazio e deve ter até 99 caracteres.");
                read_string_input("Novo nome: ", temp, sizeof(temp));
            } else {
                break;
            }
        } while (1);
        strcpy(updated_person.name, temp);
    } else {
        strcpy(updated_person.name, existing_person.name);
    }
    
    // Data de nascimento - com validação
    printf("Data de nascimento atual: %s\n", existing_person.birth_date);
    read_string_input("Nova data de nascimento: ", temp, sizeof(temp));
    if (strlen(temp) > 0) {
        do {
            if (!validation_date(temp)) {
                print_error("Data inválida! Use o formato dd/mm/aaaa e insira uma data real.");
                read_string_input("Nova data de nascimento: ", temp, sizeof(temp));
            } else {
                break;
            }
        } while (1);
        strcpy(updated_person.birth_date, temp);
    } else {
        strcpy(updated_person.birth_date, existing_person.birth_date);
    }
    
    // Email - com validação
    printf("Email atual: %s\n", existing_person.email);
    read_string_input("Novo email: ", temp, sizeof(temp));
    if (strlen(temp) > 0) {
        do {
            if (!is_valid_email(temp)) {
                print_error("Email inválido! Certifique-se de que contém '@' e '.' e está no formato correto.");
                read_string_input("Novo email: ", temp, sizeof(temp));
            } else {
                break;
            }
        } while (1);
        strcpy(updated_person.email, temp);
    } else {
        strcpy(updated_person.email, existing_person.email);
    }
    
    // Telefone - com validação
    printf("Telefone atual: %s\n", existing_person.phone);
    read_string_input("Novo telefone: ", temp, sizeof(temp));
    if (strlen(temp) > 0) {
        do {
            if (!is_valid_phone(temp)) {
                print_error("Telefone inválido! Use apenas números, '+' e '-', com 9 a 20 caracteres.");
                read_string_input("Novo telefone: ", temp, sizeof(temp));
            } else {
                break;
            }
        } while (1);
        strcpy(updated_person.phone, temp);
    } else {
        strcpy(updated_person.phone, existing_person.phone);
    }

    updated_person.id = id;
    updated_person.status = true;

    printf("\n");
    set_search_id(id);
    if (update(&updated_person, sizeof(People), FILE_NAME_PEOPLE, match_people_by_id)) {
        print_success("Pessoa atualizada com sucesso!");
    } else {
        print_error("Erro ao atualizar pessoa.");
    }
}