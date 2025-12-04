#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "people.h"
#include "terminal_control.h"
#include "controllers.h"
#include "config.h"

void delete_people_ui() {
    int id;
    char confirm[3];
    
    if (!read_int_input("Digite o ID da pessoa a ser excluída: ", &id)) {
        print_error("ID inválido.");
        return;
    }

    People *person = find_person_by_id(id);

    if (person == NULL || person->status == false) {
        print_error("Pessoa com ID %d não encontrada ou já está inativa.", id);
        return;
    }

    printf("\n");
    print_people_detail(person);
    printf("\n");

    read_string_input("Tem certeza que deseja inativar esta pessoa? (s/N): ", confirm, sizeof(confirm));

    if (confirm[0] == 's' || confirm[0] == 'S') {
        person->status = false; // Muda na RAM
        save_people_list();     // Salva no Disco
        print_success("Pessoa inativada com sucesso.");
    } else {
        print_warning("Operação cancelada.");
    }
}