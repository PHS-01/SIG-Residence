#include <stdio.h>
#include <string.h>

// Variáveis globais do projeto
#include "config.h"

#include "people.h"

// Função para criar uma nova pessoa no arquivo CSV
void create_people(People new_person) {
    FILE *file = fopen(FILE_NAME, "a");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    // Escreve os dados no formato CSV: id,name,birth_date,email,phone
    fprintf(file, "%d,%s,%s,%s,%s\n", 
            new_person.id, new_person.name, new_person.birth_date, new_person.email, new_person.phone);
    fclose(file);
}

// Função para listar todas as pessoas do arquivo CSV
void list_people(void) {
    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }
    fclose(file);
}

// Função para atualizar os dados de uma pessoa no arquivo CSV
void update_people(int id, People updated_person) {
    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    // Abre o arquivo temporário para escrever as alterações
    FILE *temp_file = fopen("temp.csv", "w");
    if (temp_file == NULL) {
        printf("Erro ao criar arquivo temporário.\n");
        fclose(file);
        return;
    }

    char line[1024];
    int found = 0;

    while (fgets(line, sizeof(line), file)) {
        int file_id;
        char name[100], birth_date[11], email[100], phone[20];

        // Lê os dados do arquivo CSV (id,name,birth_date,email,phone)
        sscanf(line, "%d,%99[^,],%10[^,],%99[^,],%19[^\n]", &file_id, name, birth_date, email, phone);

        // Se o ID da pessoa corresponder ao ID informado, substituímos os dados
        if (file_id == id) {
            fprintf(temp_file, "%d,%s,%s,%s,%s\n", 
                    updated_person.id, updated_person.name, updated_person.birth_date, updated_person.email, updated_person.phone);
            found = 1;  // Marca que o ID foi encontrado e atualizado
            continue;  // Pula para a próxima linha
        }

        // Caso contrário, apenas copia a linha original para o arquivo temporário
        fputs(line, temp_file);
    }

    fclose(file);
    fclose(temp_file);

    if (found) {
        // Se encontrou e atualizou, substitui o arquivo original
        remove(FILE_NAME);
        rename("temp.csv", FILE_NAME);
        printf("Pessoa atualizada.\n");
    } else {
        // Caso contrário, exclui o arquivo temporário
        remove("temp.csv");
        printf("Pessoa não encontrada.\n");
    }
}

// Função para excluir uma pessoa do arquivo CSV
void delete_people(int id) {
    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    // Abre o arquivo temporário para escrever as alterações
    FILE *temp_file = fopen("temp.csv", "w");
    if (temp_file == NULL) {
        printf("Erro ao criar arquivo temporário.\n");
        fclose(file);
        return;
    }

    char line[1024];
    int found = 0;

    while (fgets(line, sizeof(line), file)) {
        int file_id;
        char name[100], birth_date[11], email[100], phone[20];

        // Lê os dados do arquivo CSV (id,name,birth_date,email,phone)
        sscanf(line, "%d,%99[^,],%10[^,],%99[^,],%19[^\n]", &file_id, name, birth_date, email, phone);

        // Se o ID não for o que estamos procurando, copia a linha para o arquivo temporário
        if (file_id != id) {
            fputs(line, temp_file);
        } else {
            found = 1;  // Marca que encontrou o ID para deletar
        }
    }

    fclose(file);
    fclose(temp_file);

    if (found) {
        // Se encontrou e excluiu, substitui o arquivo original
        remove(FILE_NAME);
        rename("temp.csv", FILE_NAME);
        printf("Pessoa excluída.\n");
    } else {
        // Caso contrário, exclui o arquivo temporário
        remove("temp.csv");
        printf("Pessoa não encontrada.\n");
    }
}