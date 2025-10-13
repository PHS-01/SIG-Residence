#include <stdio.h>
#include "people.h"

void read_people_ui() {
    int id;
    printf("=== CONSULTAR PESSOA ===\n");
    printf("Digite o ID da pessoa: ");
    scanf("%d", &id);
    getchar();

    read_people(id);
}