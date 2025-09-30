#include <stdio.h>
#include <string.h>

// Salva os dados em arquivo texto
void save_people(const char *filename, char people[4][50]) {
    FILE *f = fopen(filename, "w");
    if (!f) {
        perror("Erro ao abrir arquivo para salvar pessoas");
        return;
    }

    for (int i = 0; i < 4; i++) {
        if (people[i][0] == '\0') {
            fprintf(f, "Vazio\n");
        } else {
            fprintf(f, "%s\n", people[i]);
        }
    }

    fclose(f);
}

// Carrega os dados do arquivo texto
void load_people(const char *filename, char people[4][50]) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        // Se não existir, inicializa como vazio
        for (int i = 0; i < 4; i++) {
            strcpy(people[i], "Vazio");
        }
        return;
    }

    char buffer[50];
    int i = 0;
    while (fgets(buffer, sizeof(buffer), f) && i < 4) {
        buffer[strcspn(buffer, "\n")] = '\0'; // remove \n
        if (strlen(buffer) == 0) {
            strcpy(people[i], "Vazio");
        } else {
            strncpy(people[i], buffer, 49);
            people[i][49] = '\0';
        }
        i++;
    }

    // Se o arquivo tiver menos de 4 linhas, preenche o resto
    for (; i < 4; i++) {
        strcpy(people[i], "Vazio");
    }

    fclose(f);
}
