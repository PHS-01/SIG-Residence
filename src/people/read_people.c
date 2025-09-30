#include <stdio.h>
#include <string.h>

void read_people(char people[4][50]) {
    printf("\nLista de Pessoas:\n");

    int vazias = 0;
    for (int i = 0; i < 4; i++) {
        if (people[i][0] == '\0' || strcmp(people[i], "Vazio") == 0) {
            printf(" [%d] (vazio)\n", i + 1);
            vazias++;
        } else {
            printf(" [%d] %s\n", i + 1, people[i]);
        }
    }

    if (vazias == 4) {
        printf("Nenhuma pessoa cadastrada ainda.\n");
    }

    printf("\n");
}
