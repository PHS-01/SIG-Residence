#include <stdio.h>
#include <string.h>

void update_people(char people[4][50]) {
    int index;
    char buffer[50];

    printf("\nAtualizar Pessoa\n");
    for (int i = 0; i < 4; i++) {
        if (people[i][0] == '\0' || strcmp(people[i], "Vazio") == 0) {
            printf(" [%d] (vazio)\n", i + 1);
        } else {
            printf(" [%d] %s\n", i + 1, people[i]);
        }
    }

    printf("Escolha o número da pessoa a atualizar (1-4): ");
    if (scanf("%d", &index) != 1) {
        while (getchar() != '\n'); // limpar stdin
        printf("Entrada inválida.\n");
        return;
    }
    while (getchar() != '\n'); // limpar \n do buffer

    if (index < 1 || index > 4) {
        printf("Opção inválida.\n");
        return;
    }

    if (people[index-1][0] == '\0' || strcmp(people[index-1], "Vazio") == 0) {
        printf("Essa posição está vazia, não é possível atualizar.\n");
        return;
    }

    printf("Digite o novo nome: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';

    if (strlen(buffer) == 0) {
        printf("Nome vazio, atualização cancelada.\n");
        return;
    }

    strncpy(people[index-1], buffer, 49);
    people[index-1][49] = '\0';

    printf("Pessoa atualizada para '%s'.\n", people[index-1]);
}
