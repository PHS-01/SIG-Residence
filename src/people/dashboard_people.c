#include <stdio.h>
#include <string.h>
#include "screens.h"
#include "people.h"

Pessoa people[MAX_PEOPLE];
int people_count = 0;

void dashboard_people(void) {
    // carrega ao iniciar
    load_people("people.txt", people, &people_count);

    int option = -1;
    char buf[32];

    while (1) {
        // limpa tela (usando ANSI; se você tem função clear_screen(), use-a)
        printf("\033[2J\033[H");

        // mostra lista e opções
        read_people(people, people_count);

        printf("\nOpções:\n");
        printf(" [1] Criar Pessoa\n");
        printf(" [2] Atualizar Pessoa\n");
        printf(" [3] Deletar Pessoa\n");
        printf(" [0] Voltar\n");

        printf("\nEscolha uma opção: ");
        if (!fgets(buf, sizeof(buf), stdin)) break;
        option = atoi(buf);

        switch (option) {
            case 1:
                create_people(people, &people_count);
                save_people("people.txt", people, people_count);
                break;
            case 2:
                update_people(people, people_count);
                save_people("people.txt", people, people_count);
                break;
            case 3:
                delete_people(people, &people_count);
                save_people("people.txt", people, people_count);
                break;
            case 0:
                // salvar antes de sair da tela, só por segurança
                save_people("people.txt", people, people_count);
                return;
            default:
                printf("Opção inválida.\n");
                break;
        }

        printf("\nPressione ENTER para continuar...");
        fgets(buf, sizeof(buf), stdin);
    }
}