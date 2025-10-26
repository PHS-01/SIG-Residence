#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "finance.h"
#include "terminal_control.h"

void dashboard_finance() {
    int opcao;

    do {
        printf("\n=== MENU DE FINANÇAS ===\n");
        printf("1 - Cadastrar nova transação\n");
        printf("2 - Consultar transação\n");
        printf("3 - Listar todas as transações\n");
        printf("4 - Listar transações ativas\n");
        printf("5 - Atualizar transação\n");
        printf("6 - Exclusão lógica (inativar)\n");
        printf("7 - Exclusão física (permanente)\n");
        printf("0 - Voltar\n");
        
        if (!read_int_input("Escolha uma opção: ", &opcao)) {
            printf("Opção inválida. Digite um número.\n");
            clear_input_buffer();
            wait_for_enter();
            system("clear");
            continue;
        }

        system("clear");

        switch (opcao) {
            case 1:
                create_finance_ui();
                break;
            case 2:
                read_finance_ui();
                break;
            case 3:
                list_all_finance();
                break;
            case 4:
                list_active_finance();
                break;
            case 5:
                update_finance_ui();
                break;
            case 6:
                delete_finance_ui();
                break;
            case 7:
                physical_delete_finance_ui();
                break;
            case 0:
                printf("Retornando ao menu principal...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }

        if (opcao != 0 && opcao >= 1 && opcao <= 7) {
            wait_for_enter();
            system("clear");
        }

    } while (opcao != 0);
}