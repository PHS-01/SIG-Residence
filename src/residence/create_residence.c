#include <stdio.h>
#include <string.h>
#include "residence.h"
#include "config.h"
#include "terminal_control.h"
#include "controllers.h"
#include "validations.h"

void create_residence_ui() {
    Residence new_residence;
    
    // Gera ID automaticamente
    new_residence.id = generate_residence_id();
    
    // Campos de entrada com validação individual
    do {
        read_string_input("Endereço (logradouro): ", new_residence.address, sizeof(new_residence.address));
        if (!is_valid_string(new_residence.address, sizeof(new_residence.address))) {
            print_error("Endereço não pode estar vazio e deve ter até 99 caracteres.");
        }
    } while (!is_valid_string(new_residence.address, sizeof(new_residence.address)));
    
    do {
        if (!read_int_input("Número: ", &new_residence.number)) {
            print_error("Número inválido. Digite um número inteiro.");
            new_residence.number = -1; // Forçar repetição
        } else if (!is_valid_residence_number(new_residence.number)) {
            print_error("Número da residência deve ser positivo.");
        }
    } while (!is_valid_residence_number(new_residence.number));
    
    // Complemento pode ser vazio
    read_string_input("Complemento: ", new_residence.complement, sizeof(new_residence.complement));
    if (strlen(new_residence.complement) >= sizeof(new_residence.complement)) {
        print_error("Complemento muito longo.");
        return;
    }
    
    do {
        read_string_input("Bairro: ", new_residence.neighborhood, sizeof(new_residence.neighborhood));
        if (!is_valid_string(new_residence.neighborhood, sizeof(new_residence.neighborhood))) {
            print_error("Bairro não pode estar vazio e deve ter até 49 caracteres.");
        }
    } while (!is_valid_string(new_residence.neighborhood, sizeof(new_residence.neighborhood)));
    
    do {
        read_string_input("Cidade: ", new_residence.city, sizeof(new_residence.city));
        if (!is_valid_string(new_residence.city, sizeof(new_residence.city))) {
            print_error("Cidade não pode estar vazia e deve ter até 49 caracteres.");
        }
    } while (!is_valid_string(new_residence.city, sizeof(new_residence.city)));
    
    do {
        read_string_input("Estado (sigla 2 letras): ", new_residence.state, sizeof(new_residence.state));
        if (!is_valid_state(new_residence.state)) {
            print_error("Estado inválido! Use uma sigla de 2 letras válida (ex: SP, RJ, MG).");
        }
    } while (!is_valid_state(new_residence.state));
    
    do {
        read_string_input("CEP (12345-678): ", new_residence.cep, sizeof(new_residence.cep));
        if (!is_valid_cep(new_residence.cep)) {
            print_error("CEP inválido! Use o formato 12345-678 ou 12345678.");
        }
    } while (!is_valid_cep(new_residence.cep));

    new_residence.status = true;

    printf("\n");
    create(&new_residence, sizeof(Residence), FILE_NAME_RESIDENCE);
    
    printf("\n");
    print_success("Residência cadastrada com sucesso!");
    printf(COLOR_CYAN "ID da residência: %d" COLOR_RESET "\n", new_residence.id);
}