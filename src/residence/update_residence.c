#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "residence.h"
#include "terminal_control.h"
#include "controllers.h"
#include "config.h"

void update_residence_ui() {
    Residence updated_residence;
    int id;

    printf("=== ATUALIZAR RESIDÊNCIA ===\n\n");
    
    if (!read_int_input("Digite o ID da residência que deseja atualizar: ", &id)) {
        printf("ID inválido.\n");
        return;
    }

    // Primeiro verifica se a residência existe
    set_search_residence_id(id);
    Residence existing_residence;
    if (!read(&existing_residence, sizeof(Residence), FILE_NAME_RESIDENCE, match_residence_by_id)) {
        printf("Residência com ID %d não encontrada ou está inativa.\n", id);
        return;
    }

    printf("\nDeixe em branco para manter o valor atual.\n\n");
    
    char temp[100];
    int temp_int;
    
    // Endereço
    printf("Endereço atual: %s\n", existing_residence.address);
    read_string_input("Novo endereço: ", temp, sizeof(temp));
    if (strlen(temp) > 0) {
        strcpy(updated_residence.address, temp);
    } else {
        strcpy(updated_residence.address, existing_residence.address);
    }
    
    // Número
    printf("Número atual: %d\n", existing_residence.number);
    if (read_int_input("Novo número: ", &temp_int)) {
        updated_residence.number = temp_int;
    } else {
        updated_residence.number = existing_residence.number;
    }
    
    // Complemento
    printf("Complemento atual: %s\n", existing_residence.complement);
    read_string_input("Novo complemento: ", temp, sizeof(temp));
    if (strlen(temp) > 0) {
        strcpy(updated_residence.complement, temp);
    } else {
        strcpy(updated_residence.complement, existing_residence.complement);
    }
    
    // Bairro
    printf("Bairro atual: %s\n", existing_residence.neighborhood);
    read_string_input("Novo bairro: ", temp, sizeof(temp));
    if (strlen(temp) > 0) {
        strcpy(updated_residence.neighborhood, temp);
    } else {
        strcpy(updated_residence.neighborhood, existing_residence.neighborhood);
    }
    
    // Cidade
    printf("Cidade atual: %s\n", existing_residence.city);
    read_string_input("Nova cidade: ", temp, sizeof(temp));
    if (strlen(temp) > 0) {
        strcpy(updated_residence.city, temp);
    } else {
        strcpy(updated_residence.city, existing_residence.city);
    }
    
    // Estado
    printf("Estado atual: %s\n", existing_residence.state);
    read_string_input("Novo estado: ", temp, sizeof(temp));
    if (strlen(temp) > 0) {
        strcpy(updated_residence.state, temp);
    } else {
        strcpy(updated_residence.state, existing_residence.state);
    }
    
    // CEP
    printf("CEP atual: %s\n", existing_residence.cep);
    read_string_input("Novo CEP: ", temp, sizeof(temp));
    if (strlen(temp) > 0) {
        strcpy(updated_residence.cep, temp);
    } else {
        strcpy(updated_residence.cep, existing_residence.cep);
    }

    updated_residence.id = id;
    updated_residence.status = true;

    printf("\n");
    set_search_residence_id(id);
    if (update(&updated_residence, sizeof(Residence), FILE_NAME_RESIDENCE, match_residence_by_id)) {
        printf("Residência atualizada com sucesso!\n");
    } else {
        printf("Erro ao atualizar residência.\n");
    }
}