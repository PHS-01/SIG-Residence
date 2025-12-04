#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "residence.h"
#include "terminal_control.h"
#include "controllers.h"
#include "config.h"
#include "validations.h"

void update_residence_ui() {
    int id;
    if (!read_int_input("Digite o ID da residência que deseja atualizar: ", &id)) {
        print_error("ID inválido.");
        return;
    }

    // Busca ponteiro na memória
    Residence *existing_residence = find_residence_by_id(id);

    if (existing_residence == NULL || existing_residence->status == false) {
        print_error("Residência com ID %d não encontrada ou está inativa.", id);
        return;
    }

    // Fazemos uma cópia para editar. Se salvar, copiamos de volta.
    Residence temp_res = *existing_residence;

    printf("\n");
    print_residence_detail(existing_residence);
    printf("\n");
    
    print_info("Deixe em branco para manter o valor atual.\n");
    
    char temp[100];
    int temp_int;
    bool address_changed = false;
    
    // Endereço (Verifica se mudou para reordenar)
    printf("Endereço atual: %s\n", existing_residence->address);
    read_string_input("Novo endereço: ", temp, sizeof(temp));
    if (strlen(temp) > 0) {
        do {
            if (!is_valid_string(temp, sizeof(temp_res.address))) {
                print_error("Endereço inválido.");
                read_string_input("Novo endereço: ", temp, sizeof(temp));
            } else { break; }
        } while (1);
        
        if (strcmp(temp, existing_residence->address) != 0) {
            strcpy(temp_res.address, temp);
            address_changed = true;
        }
    }
    
    // Número
    printf("Número atual: %d\n", existing_residence->number);
    if (read_int_input("Novo número: ", &temp_int)) {
        // Validação simples
        if (is_valid_residence_number(temp_int)) temp_res.number = temp_int;
    }
    
    // Complemento
    printf("Complemento atual: %s\n", existing_residence->complement);
    read_string_input("Novo complemento: ", temp, sizeof(temp));
    if (strlen(temp) > 0) strcpy(temp_res.complement, temp);

    // Bairro
    printf("Bairro atual: %s\n", existing_residence->neighborhood);
    read_string_input("Novo bairro: ", temp, sizeof(temp));
    if (strlen(temp) > 0) strcpy(temp_res.neighborhood, temp);
    
    // Cidade
    printf("Cidade atual: %s\n", existing_residence->city);
    read_string_input("Nova cidade: ", temp, sizeof(temp));
    if (strlen(temp) > 0) strcpy(temp_res.city, temp);
    
    // Estado
    printf("Estado atual: %s\n", existing_residence->state);
    read_string_input("Novo estado: ", temp, sizeof(temp));
    if (strlen(temp) > 0) {
         if (is_valid_state(temp)) strcpy(temp_res.state, temp);
    } 
    
    // CEP
    printf("CEP atual: %s\n", existing_residence->cep);
    read_string_input("Novo CEP: ", temp, sizeof(temp));
    if (strlen(temp) > 0) {
        if (is_valid_cep(temp)) strcpy(temp_res.cep, temp);
    }

    // LÓGICA DE SALVAMENTO
    if (address_changed) {
        // Se mudou o endereço, a ordem alfabética pode mudar.
        // Removemos o antigo e inserimos o novo (que vai achar seu lugar sozinho)
        int old_id = existing_residence->id;
        
        // Remove fisicamente o nó antigo (mas sem salvar no disco ainda para performance, ou salva direto)
        remove_residence_from_list(old_id);
        
        // Garante que o ID se mantém o mesmo
        temp_res.id = old_id;
        
        // Insere ordenado
        insert_residence_sorted(temp_res);
        
        print_success("Residência atualizada e reordenada com sucesso!");
    } else {
        // Se não mudou endereço, apenas atualiza a RAM no lugar e salva
        *existing_residence = temp_res;
        save_residence_list();
        print_success("Residência atualizada com sucesso!");
    }
}