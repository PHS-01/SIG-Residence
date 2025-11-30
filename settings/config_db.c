#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"

// Variáveis constantes para o banco de dados
const char* DATABASE_NAME = "database";
const char* FILE_TYPE = "dat";

char FILE_NAME_PEOPLE[100];
char FILE_NAME_FINANCE[100];
char FILE_NAME_RESIDENCE[100];

// Função para criar o nome completo do arquivo de pessoas
void create_file_name_people(void) {
    snprintf(FILE_NAME_PEOPLE, sizeof(FILE_NAME_PEOPLE), "%s_people.%s", DATABASE_NAME, FILE_TYPE);
}

void create_file_name_finance(void) {
    snprintf(FILE_NAME_FINANCE, sizeof(FILE_NAME_FINANCE), "%s_finance.%s", DATABASE_NAME, FILE_TYPE);
}

void create_file_name_residence(void) {
    snprintf(FILE_NAME_RESIDENCE, sizeof(FILE_NAME_RESIDENCE), "%s_residence.%s", DATABASE_NAME, FILE_TYPE);
}

void create_database(void) {
    create_file_name_people();
    create_file_name_finance();
    create_file_name_residence();
    
    // Cria o arquivo de pessoas
    FILE *arquivo = fopen(FILE_NAME_PEOPLE, "ab");
    if (arquivo == NULL) {
        printf("Erro ao criar banco de dados de pessoas.\n");
        exit(EXIT_FAILURE);
    } else {
        fclose(arquivo);
    }

    // Cria o arquivo de finanças
    arquivo = fopen(FILE_NAME_FINANCE, "ab");
    if (arquivo == NULL) {
        printf("Erro ao criar banco de dados de finanças.\n");
        exit(EXIT_FAILURE);
    } else {
        fclose(arquivo);
    }

    arquivo = fopen(FILE_NAME_RESIDENCE, "ab");
    if (arquivo == NULL) {
        printf("Erro ao criar banco de dados de residências.\n");
        exit(EXIT_FAILURE);
    } else {
        fclose(arquivo);
    }
}

// Função para verificar se o arquivo de banco de dados de pessoas existe
int database_exists(void) {
    create_file_name_people();
    create_file_name_finance();
    create_file_name_residence();
    
    FILE *arquivo_people = fopen(FILE_NAME_PEOPLE, "rb");
    FILE *arquivo_finance = fopen(FILE_NAME_FINANCE, "rb");
    FILE *arquivo_residence = fopen(FILE_NAME_RESIDENCE, "rb");
    int exists = (arquivo_people != NULL) && (arquivo_finance != NULL) && (arquivo_residence != NULL);
    
    if (arquivo_people) fclose(arquivo_people);
    if (arquivo_finance) fclose(arquivo_finance);
    if (arquivo_residence) fclose(arquivo_residence);
    
    return exists;
}