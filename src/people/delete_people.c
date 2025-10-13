#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "people.h"

void delete_people_ui() {
    int id;
    char confirm;

    printf("=== EXCLUIR PESSOA ===\n");
    printf("Digite o ID da pessoa a ser excluída: ");
    scanf("%d", &id);
    getchar();

    printf("Tem certeza que deseja inativar a pessoa com ID %d? (s/N): ", id);
    scanf("%c", &confirm);

    if (confirm == 's' || confirm == 'S') {
        delete_people(id);
    } else {
        printf("Operação cancelada.\n");
    }
}