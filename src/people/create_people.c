#include <stdio.h>
#include <string.h>

void create_people(char people[4][50]) {
    int slot = -1;

    // Procura posição livre
    for (int i = 0; i < 4; i++) {
        if (people[i][0] == '\0' || strcmp(people[i], "Vazio") == 0) {
            slot = i;
            break;
        }
    }

    if (slot == -1) {
        printf("Limite de pessoas atingido.\n");
        return;
    }

    char buffer[50];
    printf("Digite o nome da nova pessoa: ");
    fgets(buffer, sizeof(buffer), stdin);

    // remover \n
    buffer[strcspn(buffer, "\n")] = '\0';

    if (strlen(buffer) == 0) {
        printf("Nome vazio, operação cancelada.\n");
        return;
    }

    strncpy(people[slot], buffer, 49);
    people[slot][49] = '\0'; // garantir terminação

    printf("Pessoa '%s' criada com sucesso!\n", people[slot]);
}