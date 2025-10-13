#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "people.h"

void update_people_ui() {
    People updated_person;
    int id;

    printf("=== ATUALIZAR PESSOA ===\n");
    printf("Digite o ID da pessoa que deseja atualizar: ");
    scanf("%d", &id);
    getchar();

    printf("Novo nome: ");
    fgets(updated_person.name, sizeof(updated_person.name), stdin);
    updated_person.name[strcspn(updated_person.name, "\n")] = '\0';

    printf("Nova data de nascimento (dd/mm/aaaa): ");
    fgets(updated_person.birth_date, sizeof(updated_person.birth_date), stdin);
    updated_person.birth_date[strcspn(updated_person.birth_date, "\n")] = '\0';

    printf("Novo email: ");
    fgets(updated_person.email, sizeof(updated_person.email), stdin);
    updated_person.email[strcspn(updated_person.email, "\n")] = '\0';

    printf("Novo telefone: ");
    fgets(updated_person.phone, sizeof(updated_person.phone), stdin);
    updated_person.phone[strcspn(updated_person.phone, "\n")] = '\0';

    updated_person.id = id;
    updated_person.status = true;

    update_people(id, updated_person);
}