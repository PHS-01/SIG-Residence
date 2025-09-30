#include <stdio.h>
#include <string.h>

void delete_people(char people[4][50]) {
    int index;

    printf("\nDeletar Pessoa\n");
    for (int i = 0; i < 4; i++) {
        if (people[i][0] == '\0' || strcmp(people[i], "Vazio") == 0) {
            printf(" [%d] (vazio)\n", i + 1);
        } else {
            printf(" [%d] %s\n", i + 1, people[i]);
        }
    }

    printf("Escolha o número da pessoa a deletar (1-4): ");
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
        printf("Essa posição já está vazia.\n");
        return;
    }

    strcpy(people[index-1], "Vazio");
    printf("Pessoa na posição %d removida.\n", index);
}
