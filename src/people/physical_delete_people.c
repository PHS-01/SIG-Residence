#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "people.h"
#include "terminal_control.h"
#include "controllers.h"
#include "config.h"
#include "finance.h"

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
        print_error("Pessoa com ID %d não encontrada.", id);
        return;
    }

    printf("\nDados da pessoa que será excluída FISICAMENTE:\n");
    print_people_detail(&person);
    
    // Verificar e listar finanças associadas
    int finance_count = count_finance_by_people_id(id);
    
    if (finance_count > 0) {
        printf("\n");
        list_finance_by_people_id(id);
        printf("\n");
        print_warning("Esta pessoa possui %d transação(ões) financeira(s) associada(s).", finance_count);
        print_warning("TODAS as transações financeiras desta pessoa também serão excluídas FISICAMENTE!");
    }
    
    printf("\n");
    print_warning("ATENÇÃO: Esta operação é IRREVERSÍVEL!");
    print_warning("Todos os dados da pessoa e suas transações serão PERDIDOS PERMANENTEMENTE!");

    clear_input_buffer();

    read_string_input("Confirma a exclusão física? (digite 'sim' para confirmar): ", confirm, sizeof(confirm));

    if (strcmp(confirm, "sim") == 0) {
        // Primeiro excluir todas as finanças associadas
        int deleted_finances = 0;
        if (finance_count > 0) {
            deleted_finances = delete_finance_by_people_id(id);
            if (deleted_finances > 0) {
                print_success("%d transação(ões) financeira(s) excluída(s) com sucesso.", deleted_finances);
            } else {
                print_error("Erro ao excluir transações financeiras associadas.");
                // Perguntar se deseja continuar mesmo assim
                read_string_input("Deseja continuar excluindo apenas a pessoa? (digite 'sim' para continuar): ", confirm, sizeof(confirm));
                if (strcmp(confirm, "sim") != 0) {
                    print_warning("Operação cancelada.");
                    return;
                }
            }
        }
        
        // Agora excluir a pessoa
        set_search_id(id);
        if (physical_delete(sizeof(People), match_people_by_id, FILE_NAME_PEOPLE)) {
            if (deleted_finances > 0) {
                print_success("Pessoa e %d transação(ões) financeira(s) excluída(s) fisicamente com sucesso.", deleted_finances);
            } else {
                print_success("Pessoa excluída fisicamente com sucesso.");
            }
        } else {
            print_error("Erro ao excluir pessoa fisicamente.");
        }
    } else {
        print_warning("Operação cancelada.");
    }
}