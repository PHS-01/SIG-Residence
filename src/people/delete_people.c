#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "people.h"

void delete_people(Pessoa people[], int *count) {
    if (*count == 0) {
        printf("Nenhuma pessoa para deletar.\n");
        return;
    }

    read_people(people, *count);
    char buf[32];
    int idx = 0;
    printf("Escolha o número da pessoa a deletar (1-%d): ", *count);
    if (!fgets(buf, sizeof(buf), stdin)) return;
    idx = atoi(buf);
    if (idx < 1 || idx > *count) {
        printf("Índice inválido.\n");
        return;
    }
    idx -= 1; // zero-based

    // shift left
    for (int i = idx; i < (*count) - 1; ++i) {
        people[i] = people[i + 1];
    }
    // limpa último
    memset(&people[*count - 1], 0, sizeof(Pessoa));
    (*count)--;

    printf("Pessoa removida.\n");
}
