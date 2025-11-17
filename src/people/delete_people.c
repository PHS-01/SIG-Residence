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

    // Primeiro verifica se a pessoa existe
    set_search_id(id);
    People person;
    if (!read_data(&person, sizeof(People), FILE_NAME_PEOPLE, match_people_by_id)) {
        print_error("Pessoa com ID %d não encontrada ou já está inativa.", id);
        return;
    }

    printf("\n");
    print_people_detail(&person);
    printf("\n");

    read_string_input("Tem certeza que deseja inativar esta pessoa? (s/N): ", confirm, sizeof(confirm));

    if (confirm[0] == 's' || confirm[0] == 'S') {
        set_search_id(id);
        if (delete(sizeof(People), FILE_NAME_PEOPLE, match_people_by_id)) {
            print_success("Pessoa inativada com sucesso.");
        } else {
            print_error("Erro ao inativar pessoa.");
        }
    } else {
        print_warning("Operação cancelada.");
    }
}