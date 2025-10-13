#include <stdio.h>
#include "people.h"
#include "terminal_control.h"

void read_people_ui() {
    int id;
    
    printf("=== CONSULTAR PESSOA ===\n\n");
    
    if (read_int_input("Digite o ID da pessoa: ", &id)) {
        printf("\n");
        read_people(id);
    } else {
        printf("ID inválido.\n");
    }
}