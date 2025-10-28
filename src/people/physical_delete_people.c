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

    printf("=== EXCLUSÃO FÍSICA DE PESSOA ===\n\n");
    
    if (!read_int_input("Digite o ID da pessoa a ser excluída fisicamente: ", &id)) {
        printf("ID inválido.\n");
        return;
    }

    // Primeiro verifica se a pessoa existe
    set_search_id(id);
    People person;
    if (!read(&person, sizeof(People), FILE_NAME_PEOPLE,match_people_by_id)) {
        printf("Pessoa com ID %d não encontrada.\n", id);
        return;
    }

    printf("\nDados da pessoa que será excluída FISICAMENTE:\n");
    print_people(&person);
    printf("\nATENÇÃO: Esta operação é IRREVERSÍVEL!\n");

    clear_input_buffer();

    read_string_input("Confirma a exclusão física? (digite 'sim' para confirmar): ", confirm, sizeof(confirm));

    if (strcmp(confirm, "sim") == 0) {
        set_search_id(id);
        if (physical_delete(sizeof(People), match_people_by_id, FILE_NAME_PEOPLE)) {
            printf("Pessoa excluída fisicamente com sucesso.\n");
        } else {
            printf("Erro ao excluir pessoa fisicamente.\n");
        }
    } else {
        printf("Operação cancelada.\n");
    }
}