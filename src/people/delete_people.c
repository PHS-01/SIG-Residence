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

    printf("=== EXCLUIR PESSOA ===\n\n");
    
    if (!read_int_input("Digite o ID da pessoa a ser excluída: ", &id)) {
        printf("ID inválido.\n");
        return;
    }

    // Primeiro verifica se a pessoa existe
    set_search_id(id);
    People person;
    if (!read(&person, sizeof(People), match_people_by_id, FILE_NAME_PEOPLE)) {
        printf("Pessoa com ID %d não encontrada ou já está inativa.\n", id);
        return;
    }

    printf("\nDados da pessoa:\n");
    print_people(&person);
    printf("\n");

    read_string_input("Tem certeza que deseja inativar esta pessoa? (s/N): ", confirm, sizeof(confirm));

    if (confirm[0] == 's' || confirm[0] == 'S') {
        set_search_id(id);
        if (delete(sizeof(People), match_people_by_id, FILE_NAME_PEOPLE)) {
            printf("Pessoa inativada com sucesso.\n");
        } else {
            printf("Erro ao inativar pessoa.\n");
        }
    } else {
        printf("Operação cancelada.\n");
    }
}