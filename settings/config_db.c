#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Variáveis constantes para o banco de dados (Nome do arquivo/banco de dados, Tipo do arquivo)
const char* DATABASE_NAME = "database";
const char* FILE_TYPE = "csv"; // (dat, csv, json)
char FILE_NAME[100];

// Função para criar o nome completo do arquivo
void create_file_name(void) {
    // Monta o nome do arquivo com a extensão e preenche o array FILE_NAME
    snprintf(FILE_NAME, sizeof(FILE_NAME), "%s.%s", DATABASE_NAME, FILE_TYPE);
}

void create_database(void) {
    create_file_name();

    // Cria o arquivo com o nome completo
    FILE *arquivo = fopen(FILE_NAME, "w"); // 'w' para criar o arquivo de texto
    if (arquivo == NULL) {
        exit(EXIT_FAILURE);
    } else {
        fclose(arquivo);
    }
}

// Função para verificar se o arquivo de banco de dados existe
int database_exists(void) {
    create_file_name();
    
    // Tenta abrir o arquivo no modo de leitura
    FILE *arquivo = fopen(FILE_NAME, "r"); // 'r' para verificar a existência do arquivo
    if (arquivo == NULL) {
        // Se o arquivo não existir, retorna 0 (não existe)
        return 0;
    } else {
        // Se o arquivo existir, fecha o arquivo e retorna 1 (existe)
        fclose(arquivo);
        return 1;
    }
}