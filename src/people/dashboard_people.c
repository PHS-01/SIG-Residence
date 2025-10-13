#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "screens.h"
#include "people.h"
#include "terminal_control.h"

void dashboard_people() {
    int opcao;
    char input[10];

    do {
        printf("\n=== MENU DE PESSOAS ===\n");
        printf("1 - Cadastrar nova pessoa\n");
        printf("2 - Consultar pessoa\n");
        printf("3 - Listar todas as pessoas\n");
        printf("4 - Listar pessoas ativas\n");
        printf("5 - Atualizar pessoa\n");
        printf("6 - Excluir pessoa (inativar)\n");
        printf("0 - Voltar\n");
        printf("Escolha uma opção: ");
        
        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("Erro na leitura da opção.\n");
            continue;
        }
        
        if (sscanf(input, "%d", &opcao) != 1) {
            printf("Opção inválida. Digite um número.\n");
            continue;
        }

        switch (opcao) {
            case 1:
                create_people_ui();
                break;
            case 2:
                read_people_ui();
                break;
            case 3:
                list_people();
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
            case 0:
                printf("Retornando ao menu principal...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }

        if (opcao != 0) {
            printf("\nPressione Enter para continuar...");
            getchar();
        }

    } while (opcao != 0);
}