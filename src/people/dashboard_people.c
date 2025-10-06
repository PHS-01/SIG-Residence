#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "screens.h"
#include "people.h"
#include "terminal_control.h"

Pessoa people[MAX_PEOPLE];
int people_count = 0;

void dashboard_people(void) {
    // Carrega ao iniciar
    load_people("people.txt", people, &people_count);

    int option;
    char buf[32];

    do {
        clear_screen();

        // Mostra lista e opções
        read_people(people, people_count);

        printf("\nOpções:\n");
        printf(" [1] Criar Pessoa\n");
        printf(" [2] Atualizar Pessoa\n");
        printf(" [3] Deletar Pessoa\n");
        printf(" [0] Voltar\n");

        printf("\nEscolha uma opção: ");
        if (!fgets(buf, sizeof(buf), stdin)) {
            option = 0; // Em caso de erro de leitura, assume a opção de sair.
        } else {
            option = atoi(buf); // Converte a entrada para número (simples, sem validação).
        }

        switch (option) {
            case 1:
                create_people(people, &people_count);
                break;
            case 2:
                update_people(people, people_count);
                break;
            case 3:
                delete_people(people, &people_count);
                break;
            case 0:
                printf("Voltando ao menu principal...\n");
                break;
            default:
                printf("Opção inválida.\n");
                break;
        }

        // Pausa a tela para o usuário ver o resultado, a menos que ele queira sair.
        if (option != 0) {
            printf("\nPressione ENTER para continuar...");
            fgets(buf, sizeof(buf), stdin); // Apenas aguarda o Enter.
        }

    } while (option != 0);

    // Salva todas as alterações no arquivo uma única vez, ao sair da tela.
    save_people("people.txt", people, people_count);
}