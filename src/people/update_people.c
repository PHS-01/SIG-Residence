#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "people.h"
#include "terminal_control.h"
#include "controllers.h"
#include "config.h"

void update_people_ui() {
    People updated_person;
    int id;

    printf("=== ATUALIZAR PESSOA ===\n\n");
    
    if (!read_int_input("Digite o ID da pessoa que deseja atualizar: ", &id)) {
        printf("ID inválido.\n");
        return;
    }

    // Primeiro verifica se a pessoa existe
    set_search_id(id);
    People existing_person;
    if (!read(&existing_person, sizeof(People), FILE_NAME_PEOPLE,match_people_by_id)) {
        printf("Pessoa com ID %d não encontrada ou está inativa.\n", id);
        return;
    }

    printf("\nDeixe em branco para manter o valor atual.\n\n");
    
    char temp[100];
    
    // Nome
    printf("Nome atual: %s\n", existing_person.name);
    read_string_input("Novo nome: ", temp, sizeof(temp));
    if (strlen(temp) > 0) {
        strcpy(updated_person.name, temp);
    } else {
        strcpy(updated_person.name, existing_person.name);
    }
    
    // Data de nascimento
    printf("Data de nascimento atual: %s\n", existing_person.birth_date);
    read_string_input("Nova data de nascimento: ", temp, sizeof(temp));
    if (strlen(temp) > 0) {
        strcpy(updated_person.birth_date, temp);
    } else {
        strcpy(updated_person.birth_date, existing_person.birth_date);
    }
    
    // Email
    printf("Email atual: %s\n", existing_person.email);
    read_string_input("Novo email: ", temp, sizeof(temp));
    if (strlen(temp) > 0) {
        strcpy(updated_person.email, temp);
    } else {
        strcpy(updated_person.email, existing_person.email);
    }
    
    // Telefone
    printf("Telefone atual: %s\n", existing_person.phone);
    read_string_input("Novo telefone: ", temp, sizeof(temp));
    if (strlen(temp) > 0) {
        strcpy(updated_person.phone, temp);
    } else {
        strcpy(updated_person.phone, existing_person.phone);
    }

    updated_person.id = id;
    updated_person.status = true;

    printf("\n");
    set_search_id(id);
    if (update(&updated_person, sizeof(People), FILE_NAME_PEOPLE,match_people_by_id)) {
        printf("Pessoa atualizada com sucesso!\n");
    } else {
        printf("Erro ao atualizar pessoa.\n");
    }
}