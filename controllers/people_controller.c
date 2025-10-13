#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Variáveis globais do projeto
#include "config.h"

#include "people.h"

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


// Função para listar todas as pessoas do arquivo CSV
void list_people(void) {
    FILE *file = fopen(FILE_NAME, "rb");

    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    } else {
        People* person = (People*)malloc(sizeof(People));
        while (fread(person, sizeof(People), 1, file)) {
            // Exibe os dados lidos
            printf("ID: %d, Name: %s, Birth Date: %s, Email: %s, Phone: %s, Status: %d\n",
                person->id, person->name, person->birth_date, person->email, person->phone, person->status);
        }
    }

    fclose(file);
}

// Função para atualizar os dados de uma pessoa no arquivo CSV
void update_people(int id, People updated_person) {
    FILE *file = fopen(FILE_NAME, "r+b");

    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    } else {
        People* person = (People*)malloc(sizeof(People));
        while (fread(person, sizeof(People), 1, file)) {
            if (person->id == id) {
                // Move o ponteiro de volta para a posição do registro encontrado
                fseek(file, -sizeof(People), SEEK_CUR);
                // Escreve o novo registro no lugar
                fwrite(&updated_person, sizeof(People), 1, file);
                printf("Pessoa atualizada com sucesso.\n");
            }
        }
    }


   fclose(file);
}

// Função para excluir uma pessoa do arquivo CSV
void delete_people(int id) {
    FILE *file = fopen(FILE_NAME, "r+b");

    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    } else {
        People* person = (People*)malloc(sizeof(People));
        while (fread(person, sizeof(People), 1, file)) {
            if (person->id == id) {
                // Move o ponteiro de volta para a posição do registro encontrado
                fseek(file, -sizeof(People), SEEK_CUR);
                person->status = false;
                // Escreve o novo registro no lugar
                fwrite(person, sizeof(People), 1, file);
                printf("Pessoa excluida com sucesso.\n");
            }
        }
    }
}