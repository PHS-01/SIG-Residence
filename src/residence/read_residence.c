#include <stdio.h>
#include "residence.h"
#include "terminal_control.h"
#include "controllers.h"
#include "config.h"

void read_residence_ui() {
    int id;
    
    if (read_int_input("Digite o ID da residência: ", &id)) {
        printf("\n");
        
        // Busca na memória ao invés do arquivo
        Residence *residence = find_residence_by_id(id);

        if (residence != NULL) {
            print_residence_detail(residence);
        } else {
            print_error("Residência com ID %d não encontrada.", id);
        }
    } else {
        print_error("ID inválido.");
    }
}