#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "residence.h"
#include "terminal_control.h"
#include "controllers.h"
#include "config.h"

void delete_residence_ui() {
    int id;
    char confirm[3];
    
    if (!read_int_input("Digite o ID da residência a ser excluída: ", &id)) {
        print_error("ID inválido.");
        return;
    }

    // Busca na memória
    Residence *residence = find_residence_by_id(id);

    // Verifica se existe e se já não está inativo
    if (residence == NULL || residence->status == false) {
        print_error("Residência com ID %d não encontrada ou já está inativa.", id);
        return;
    }

    printf("\n");
    print_residence_detail(residence);
    printf("\n");

    read_string_input("Tem certeza que deseja inativar esta residência? (s/N): ", confirm, sizeof(confirm));

    if (confirm[0] == 's' || confirm[0] == 'S') {
        residence->status = false; // Atualiza na RAM
        save_residence_list();     // Persiste no arquivo
        print_success("Residência inativada com sucesso.");
    } else {
        print_warning("Operação cancelada.");
    }
}