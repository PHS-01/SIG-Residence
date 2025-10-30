#include <stdio.h>
#include <string.h>
#include "residence.h"
#include "config.h"
#include "terminal_control.h"
#include "controllers.h"

void create_residence_ui() {
    Residence new_residence;
    
    // Gera ID automaticamente
    new_residence.id = generate_residence_id();
    
    printf("\n");
    
    // Campos de entrada
    read_string_input("Endereço (logradouro): ", new_residence.address, sizeof(new_residence.address));
    read_int_input("Número: ", &new_residence.number);
    read_string_input("Complemento: ", new_residence.complement, sizeof(new_residence.complement));
    read_string_input("Bairro: ", new_residence.neighborhood, sizeof(new_residence.neighborhood));
    read_string_input("Cidade: ", new_residence.city, sizeof(new_residence.city));
    read_string_input("Estado: ", new_residence.state, sizeof(new_residence.state));
    read_string_input("CEP (12345-678): ", new_residence.cep, sizeof(new_residence.cep));

    new_residence.status = true;

    printf("\n");
    create(&new_residence, sizeof(Residence), FILE_NAME_RESIDENCE);
    
    printf("\n");
    print_success("Residência cadastrada com sucesso!");
    printf(COLOR_CYAN "ID da residência: %d" COLOR_RESET "\n", new_residence.id);
}