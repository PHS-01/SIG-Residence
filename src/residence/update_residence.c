#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "residence.h"
#include "terminal_control.h"
#include "controllers.h"
#include "config.h"
#include "validations.h"

void update_residence_ui() {
    Residence updated_residence;
    int id;
    
    if (!read_int_input("Digite o ID da residência que deseja atualizar: ", &id)) {
        print_error("ID inválido.");
        return;
    }

    // Primeiro verifica se a residência existe
    set_search_residence_id(id);
    Residence existing_residence;
    if (!read(&existing_residence, sizeof(Residence), FILE_NAME_RESIDENCE, match_residence_by_id)) {
        print_error("Residência com ID %d não encontrada ou está inativa.");
        return;
    }

    printf("\n");
    print_residence_detail(&existing_residence);
    printf("\n");
    
    print_info("Deixe em branco para manter o valor atual.\n");
    
    char temp[100];
    int temp_int;
    
    // Endereço - com validação
    printf("Endereço atual: %s\n", existing_residence.address);
    read_string_input("Novo endereço: ", temp, sizeof(temp));
    if (strlen(temp) > 0) {
        do {
            if (!is_valid_string(temp, sizeof(updated_residence.address))) {
                print_error("Endereço não pode estar vazio e deve ter até 99 caracteres.");
                read_string_input("Novo endereço: ", temp, sizeof(temp));
            } else {
                break;
            }
        } while (1);
        strcpy(updated_residence.address, temp);
    } else {
        strcpy(updated_residence.address, existing_residence.address);
    }
    
    // Número - com validação
    printf("Número atual: %d\n", existing_residence.number);
    if (read_int_input("Novo número: ", &temp_int)) {
        do {
            if (!is_valid_residence_number(temp_int)) {
                print_error("Número da residência deve ser positivo.");
                if (!read_int_input("Novo número: ", &temp_int)) {
                    temp_int = existing_residence.number;
                    break;
                }
            } else {
                break;
            }
        } while (1);
        updated_residence.number = temp_int;
    } else {
        updated_residence.number = existing_residence.number;
    }
    
    // Complemento
    printf("Complemento atual: %s\n", existing_residence.complement);
    read_string_input("Novo complemento: ", temp, sizeof(temp));
    if (strlen(temp) > 0) {
        // Complemento pode ser vazio, mas se preenchido, verificar o tamanho
        if (strlen(temp) >= sizeof(updated_residence.complement)) {
            print_error("Complemento é muito longo (máximo 49 caracteres).");
            // Não vamos repetir a entrada, apenas mantemos o atual
            strcpy(updated_residence.complement, existing_residence.complement);
        } else {
            strcpy(updated_residence.complement, temp);
        }
    } else {
        strcpy(updated_residence.complement, existing_residence.complement);
    }
    
    // Bairro - com validação
    printf("Bairro atual: %s\n", existing_residence.neighborhood);
    read_string_input("Novo bairro: ", temp, sizeof(temp));
    if (strlen(temp) > 0) {
        do {
            if (!is_valid_string(temp, sizeof(updated_residence.neighborhood))) {
                print_error("Bairro não pode estar vazio e deve ter até 49 caracteres.");
                read_string_input("Novo bairro: ", temp, sizeof(temp));
            } else {
                break;
            }
        } while (1);
        strcpy(updated_residence.neighborhood, temp);
    } else {
        strcpy(updated_residence.neighborhood, existing_residence.neighborhood);
    }
    
    // Cidade - com validação
    printf("Cidade atual: %s\n", existing_residence.city);
    read_string_input("Nova cidade: ", temp, sizeof(temp));
    if (strlen(temp) > 0) {
        do {
            if (!is_valid_string(temp, sizeof(updated_residence.city))) {
                print_error("Cidade não pode estar vazia e deve ter até 49 caracteres.");
                read_string_input("Nova cidade: ", temp, sizeof(temp));
            } else {
                break;
            }
        } while (1);
        strcpy(updated_residence.city, temp);
    } else {
        strcpy(updated_residence.city, existing_residence.city);
    }
    
    // Estado - com validação
    printf("Estado atual: %s\n", existing_residence.state);
    read_string_input("Novo estado: ", temp, sizeof(temp));
    if (strlen(temp) > 0) {
        do {
            if (!is_valid_state(temp)) {
                print_error("Estado inválido! Use uma sigla de 2 letras válida (ex: SP, RJ, MG).");
                read_string_input("Novo estado: ", temp, sizeof(temp));
            } else {
                break;
            }
        } while (1);
        strcpy(updated_residence.state, temp);
    } else {
        strcpy(updated_residence.state, existing_residence.state);
    }
    
    // CEP - com validação
    printf("CEP atual: %s\n", existing_residence.cep);
    read_string_input("Novo CEP: ", temp, sizeof(temp));
    if (strlen(temp) > 0) {
        do {
            if (!is_valid_cep(temp)) {
                print_error("CEP inválido! Use o formato 12345-678 ou 12345678.");
                read_string_input("Novo CEP: ", temp, sizeof(temp));
            } else {
                break;
            }
        } while (1);
        strcpy(updated_residence.cep, temp);
    } else {
        strcpy(updated_residence.cep, existing_residence.cep);
    }

    updated_residence.id = id;
    updated_residence.status = true;

    printf("\n");
    set_search_residence_id(id);
    if (update(&updated_residence, sizeof(Residence), FILE_NAME_RESIDENCE, match_residence_by_id)) {
        print_success("Residência atualizada com sucesso!");
    } else {
        print_error("Erro ao atualizar residência.");
    }
}