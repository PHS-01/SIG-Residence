#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "finance.h"
#include "controllers.h"
#include "config.h"
#include "terminal_control.h"

void delete_finance_ui() {
    int id;
    char confirm[3];

    if (!read_int_input("Digite o ID da transação a ser excluída: ", &id)) {
        print_error("ID inválido.");
        return;
    }

    Finance *finance = finance_list_find(id);

    if (finance == NULL || !finance->status) {
        print_error("Transação com ID %d não encontrada ou já está inativa.", id);
        return;
    }

    printf("\n");
    print_finance_detail(finance);
    printf("\n");

    read_string_input("Tem certeza que deseja inativar esta transação? (s/N): ",
                      confirm, sizeof(confirm));

    if (confirm[0] != 's' && confirm[0] != 'S') {
        print_warning("Operação cancelada.");
        return;
    }

    finance->status = false;

    FILE *file = fopen(FILE_NAME_FINANCE, "r+b");
    if (!file) {
        print_error("Erro ao abrir arquivo de finanças.");
        return;
    }

    Finance f;
    long pos;
    int found = 0;

    while (1) {
        pos = ftell(file);

        if (fread(&f, sizeof(Finance), 1, file) != 1)
            break;

        if (f.id == id) {
            f.status = false;

            fseek(file, pos, SEEK_SET);
            fwrite(&f, sizeof(Finance), 1, file);

            found = 1;
            break;
        }
    }

    fclose(file);

    if (found)
        print_success("Transação inativada com sucesso.");
    else
        print_error("Erro: transação encontrada na memória mas não no arquivo.");
}

void physical_delete_finance_ui() {
    int id;
    char confirm[4];
    
    if (!read_int_input("Digite o ID da transação a ser excluída fisicamente: ", &id)) {
        print_error("ID inválido.");
        return;
    }

    // Primeiro verifica se a transação existe na lista
    Finance *finance = finance_list_find(id);
    if (finance == NULL) {
        print_error("Transação com ID %d não encontrada.", id);
        return;
    }

    printf("\nDados da transação que será excluída FISICAMENTE:\n");
    print_finance_detail(finance);
    printf("\n");
    print_warning("ATENÇÃO: Esta operação é IRREVERSÍVEL!");

    clear_input_buffer();

    read_string_input("Confirma a exclusão física? (digite 'sim' para confirmar): ", confirm, sizeof(confirm));

    if (strcmp(confirm, "sim") == 0) {
        // Remove da lista dinâmica
        if (finance_list_remove(id)) {
            print_success("Transação excluída fisicamente com sucesso.");
        } else {
            print_error("Erro ao excluir transação fisicamente.");
        }
    } else {
        print_warning("Operação cancelada.");
    }
}