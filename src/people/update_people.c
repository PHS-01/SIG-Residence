#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "people.h"
#include "terminal_control.h"
#include "controllers.h"
#include "config.h"
#include "validations.h"

void update_people_ui() {
    int id;
    
    if (!read_int_input("Digite o ID da pessoa que deseja atualizar: ", &id)) {
        print_error("ID inválido.");
        return;
    }

    // Busca o ponteiro
    People *existing_person = find_person_by_id(id);

    if (existing_person == NULL || existing_person->status == false) {
        print_error("Pessoa com ID %d não encontrada ou está inativa.", id);
        return;
    }

    printf("\n");
    print_people_detail(existing_person);
    printf("\n");

    print_info("Deixe em branco para manter o valor atual.\n");
    
    char temp[100];
    
    // Nome - com validação
    printf("Nome atual: %s\n", existing_person->name);
    read_string_input("Novo nome: ", temp, sizeof(temp));
    if (strlen(temp) > 0) {
        do {
            if (!is_valid_name(temp)) {
                print_error("Nome inválido! Deve conter:");
                print_error("  - Pelo menos nome e sobrenome");
                print_error("  - Apenas letras, espaços, hífens e apóstrofos");
                print_error("  - Entre 2 e 100 caracteres");
                print_error("  - Não pode ter espaços consecutivos");
                print_error("  - Não pode começar ou terminar com espaço");
                read_string_input("Novo nome: ", temp, sizeof(temp));
            } else {
                break;
            }
        } while (1);
        strcpy(existing_person->name, temp); // Atualiza direto na RAM
    } // Senão mantém o atual
    
    // Data de nascimento - com validação
    printf("Data de nascimento atual: %s\n", existing_person->birth_date);
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
        strcpy(existing_person->birth_date, temp);
    } 

    // Email - com validação
    printf("Email atual: %s\n", existing_person->email);
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
        strcpy(existing_person->email, temp);
    }
    
    // Telefone - com validação
    printf("Telefone atual: %s\n", existing_person->phone);
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
        strcpy(existing_person->phone, temp);
    }

    printf("\n");
    update_person(*existing_person); // Salva as alterações no arquivo
    print_success("Pessoa atualizada com sucesso!");
}