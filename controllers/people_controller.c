#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Variáveis globais do projeto
#include "config.h"

#include "people.h"

static int search_id = -1;

void set_search_id(int id) {
    search_id = id;
}

int match_people_by_id(const void *data) {
    People *p = (People *)data;
    return (p->id == search_id && p->status == 1);
}

void print_people(const void *data) {
    People *p = (People *)data;
    if (p->status == 1) {
        printf("ID: %d, Name: %s, Birth Date: %s, Email: %s, Phone: %s\n",
            p->id, p->name, p->birth_date, p->email, p->phone);
    }
}

void read_people(int id) {
    FILE *file = fopen(FILE_NAME, "rb");

    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    } else {
        People* person = (People*)malloc(sizeof(People));
        while (fread(person, sizeof(People), 1, file)) {
            if (person->id == id && person->status == true) {
                // Exibe os dados lidos
                printf("ID: %d, Name: %s, Birth Date: %s, Email: %s, Phone: %s, Status: %d\n",
                person->id, person->name, person->birth_date, person->email, person->phone, person->status);
            }
        }
    }

    fclose(file);
}