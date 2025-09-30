#include <stdio.h>
#include "people.h"

void read_people(Pessoa people[], int count) {
    printf("\n=== Lista de Pessoas (%d) ===\n", count);
    if (count == 0) {
        printf("Nenhuma pessoa cadastrada.\n");
        return;
    }
    for (int i = 0; i < count; ++i) {
        printf("[%d] Nome: %s | Idade: %d | CPF: %s | Email: %s\n",
            i + 1,
            people[i].nome[0] ? people[i].nome : "(sem nome)",
            people[i].idade,
            people[i].cpf[0] ? people[i].cpf : "(sem cpf)",
            people[i].email[0] ? people[i].email : "(sem email)");
    }
}