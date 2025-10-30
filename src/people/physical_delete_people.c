#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "people.h"
#include "terminal_control.h"
#include "controllers.h"
#include "config.h"

void physical_delete_people_ui() {
    int id;
    char confirm[4];
    
    if (!read_int_input("Digite o ID da pessoa a ser excluída fisicamente: ", &id)) {
        print_error("ID inválido.");
        return;
    }

    // Primeiro verifica se a pessoa existe
    set_search_id(id);
    People person;
    if (!read(&person, sizeof(People), FILE_NAME_PEOPLE, match_people_by_id)) {
        print_error("Pessoa com ID %d não encontrada.");
        return;
    }

    printf("\nDados da pessoa que será excluída FISICAMENTE:\n");
    print_people_detail(&person);
    printf("\n");
    print_warning("ATENÇÃO: Esta operação é IRREVERSÍVEL!");

    clear_input_buffer();

    read_string_input("Confirma a exclusão física? (digite 'sim' para confirmar): ", confirm, sizeof(confirm));

    if (strcmp(confirm, "sim") == 0) {
        set_search_id(id);
        if (physical_delete(sizeof(People), match_people_by_id, FILE_NAME_PEOPLE)) {
            print_success("Pessoa excluída fisicamente com sucesso.");
        } else {
            print_error("Erro ao excluir pessoa fisicamente.");
        }
    } else {
        print_warning("Operação cancelada.");
    }
}