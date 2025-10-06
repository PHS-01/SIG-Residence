#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Variáveis constantes para o banco de dados (Nome do arquivo/banco de dados, Tipo do arquivo)
const char* DATABASE_NAME = "database";
const char* FILE_TYPE = "json"; // (dat, csv, json)

void create_database(void) {
    // Variável para armazenar o nome completo do arquivo
    char file_name[100];  // Tamanho suficiente para o nome do arquivo

    // Monta o nome do arquivo com a extensão
    snprintf(file_name, sizeof(file_name), "%s.%s", DATABASE_NAME, FILE_TYPE);

    // Cria o arquivo com o nome completo
    FILE *arquivo = fopen(file_name, "w"); // 'w' para criar o arquivo de texto
    if (arquivo == NULL) {
        exit(EXIT_FAILURE);
    } else {
        fclose(arquivo);
    }
}

// Função para verificar se o arquivo de banco de dados existe
int database_exists(void) {
    // Variável para armazenar o nome completo do arquivo
    char database_name[100];

    // Monta o nome do arquivo com a extensão
    snprintf(database_name, sizeof(database_name), "%s.%s", DATABASE_NAME, FILE_TYPE);

    // Tenta abrir o arquivo no modo de leitura
    FILE *arquivo = fopen(database_name, "r"); // 'r' para verificar a existência do arquivo
    if (arquivo == NULL) {
        // Se o arquivo não existir, retorna 0 (não existe)
        return 0;
    } else {
        // Se o arquivo existir, fecha o arquivo e retorna 1 (existe)
        fclose(arquivo);
        return 1;
    }
}