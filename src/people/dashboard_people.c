#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "screens.h"
#include "people.h"
#include "terminal_control.h"

void dashboard_people() {
    int opcao;

    do {
        printf("\n=== MENU DE PESSOAS ===\n");
        printf("1 - Cadastrar nova pessoa\n");
        printf("2 - Consultar pessoa\n");
        printf("3 - Listar todas as pessoas\n");
        printf("4 - Listar pessoas ativas\n");
        printf("5 - Atualizar pessoa\n");
        printf("6 - Exclusão lógica (inativar)\n");
        printf("7 - Exclusão física (permanente)\n");
        printf("0 - Voltar\n");
        
        if (!read_int_input("Escolha uma opção: ", &opcao)) {
            printf("Opção inválida. Digite um número.\n");
            clear_input_buffer(); // Limpa buffer em caso de erro
            wait_for_enter();
            system("clear");
            continue;
        }

        system("clear");

        switch (opcao) {
            case 1:
                create_people_ui();
                break;
            case 2:
                read_people_ui();
                break;
            case 3:
                list_all_people();
                break;
            case 4:
                list_active_people();
                break;
            case 5:
                update_people_ui();
                break;
            case 6:
                delete_people_ui();
                break;
            case 7:
                physical_delete_people_ui();
                break;
            case 0:
                printf("Retornando ao menu principal...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }

        // Para opções que não são voltar, pausa apenas se não houve erro de input
        if (opcao != 0 && opcao >= 1 && opcao <= 7) {
            wait_for_enter();
            system("clear");
        }

    } while (opcao != 0);
}