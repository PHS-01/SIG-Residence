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

    // Busca na Lista Dinâmica
    People *person = find_person_by_id(id);

    if (person == NULL) {
        print_error("Pessoa com ID %d não encontrada.", id);
        return;
    }

    printf("\nDados da pessoa que será excluída FISICAMENTE:\n");
    print_people_detail(person);
    
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
        // Exclui as finanças associadas primeiro
        int deleted_finances = 0;
        if (finance_count > 0) {
            deleted_finances = delete_finance_by_people_id(id);
            if (deleted_finances > 0) {
                print_success("%d transação(ões) financeira(s) excluída(s) com sucesso.", deleted_finances);
            } else {
                print_error("Erro ao excluir transações financeiras associadas.");
                // Pergunta de segurança
                read_string_input("Deseja continuar excluindo apenas a pessoa? (digite 'sim' para continuar): ", confirm, sizeof(confirm));
                if (strcmp(confirm, "sim") != 0) {
                    print_warning("Operação cancelada.");
                    return;
                }
            }
        }
        
        // Exclusão Física na Lista
        if (remove_person_from_list(id)) {
            if (deleted_finances > 0) {
                print_success("Pessoa e %d transação(ões) financeira(s) excluída(s) fisicamente.", deleted_finances);
            } else {
                print_success("Pessoa excluída fisicamente com sucesso.");
            }
        } else {
            print_error("Erro ao excluir pessoa fisicamente (não encontrada na lista).");
        }

    } else {
        print_warning("Operação cancelada.");
    }
}