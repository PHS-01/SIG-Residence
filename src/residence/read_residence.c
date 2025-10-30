#include <stdio.h>
#include "residence.h"
#include "terminal_control.h"
#include "controllers.h"
#include "config.h"

void read_residence_ui() {
    int id;
    
    if (read_int_input("Digite o ID da residência: ", &id)) {
        printf("\n");
        set_search_residence_id(id);
        Residence residence;
        if (read(&residence, sizeof(Residence), FILE_NAME_RESIDENCE, match_residence_by_id)) {
            print_residence_detail(&residence);
        } else {
            print_error("Residência com ID %d não encontrada ou está inativa.");
        }
    } else {
        print_error("ID inválido.");
    }
}