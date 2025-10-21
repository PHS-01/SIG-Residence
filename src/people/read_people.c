#include <stdio.h>
#include "people.h"
#include "terminal_control.h"
#include "controllers.h"

void read_people_ui() {
    int id;
    
    printf("=== CONSULTAR PESSOA ===\n\n");
    
    if (read_int_input("Digite o ID da pessoa: ", &id)) {
        printf("\n");
        set_search_id(id);
        People test;
        if (read(&test, sizeof(People), match_people_by_id)) {
            /* code */
            print_people(&test);
        }
    } else {
        printf("ID inválido.\n");
    }
}