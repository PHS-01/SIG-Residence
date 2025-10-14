#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Variáveis globais do projeto
#include "config.h"

// Cria ou adiciona dados ao arquivo
void create(const void* data, size_t size) {
    FILE* file = fopen(FILE_NAME, "ab");  // Abre o arquivo para escrita binária (append)
    if (!file) {
        perror("Erro ao abrir arquivo");  // Se falhar, exibe erro
        return;
    } else {
        fwrite(data, size, 1, file);  // Escreve os dados no arquivo
    }
    fclose(file);  // Fecha o arquivo
}

// Lê dados do arquivo e verifica se há correspondência com a função `match`
int read(void *output, size_t size, int (*match)(const void *)) {
    FILE *file = fopen(FILE_NAME, "rb");  // Abre o arquivo para leitura binária
    if (!file) {
        perror("Erro ao abrir arquivo");  // Se falhar, exibe erro
    } else {
        void *buffer = malloc(size);  // Aloca buffer para armazenar os dados lidos
        while (fread(buffer, size, 1, file)) {  // Lê os dados do arquivo
            if (match(buffer)) {  // Se encontrar uma correspondência
                memcpy(output, buffer, size);  // Copia os dados para o `output`
                free(buffer);  // Libera o buffer
                fclose(file);  // Fecha o arquivo
                return 1;  // Retorna 1 se encontrar a correspondência
            }
        }
        free(buffer);  // Libera o buffer se não encontrar correspondência
    }
    fclose(file);  // Fecha o arquivo
    return 0;  // Retorna 0 se não encontrar a correspondência
}

// Função comentada para listar registros
// void list_records(size_t size, const char *filename, void (*print)(const void *)) {
//     FILE *file = fopen(filename, "rb");
//     if (!file) {
//         perror("Erro ao abrir arquivo");
//         return;
//     }
//     void *buffer = malloc(size);
//     while (fread(buffer, size, 1, file)) {
//         print(buffer);
//     }
//     free(buffer);
//     fclose(file);
// }

// Atualiza dados no arquivo, se encontrar uma correspondência
int update(const void *new_data, size_t size, int (*match)(const void *)) {
    FILE *file = fopen(FILE_NAME, "r+b");  // Abre o arquivo para leitura e escrita binária
    if (!file) {
        perror("Erro ao abrir arquivo");  // Se falhar, exibe erro
    } else {
        void *buffer = malloc(size);  // Aloca buffer para os dados lidos
        while (fread(buffer, size, 1, file)) {  // Lê o arquivo
            if (match(buffer)) {  // Se encontrar correspondência
                fseek(file, -((long)size), SEEK_CUR);  // Volta para sobrescrever os dados
                fwrite(new_data, size, 1, file);  // Escreve os novos dados
                free(buffer);  // Libera o buffer
                fclose(file);  // Fecha o arquivo
                return 1;  // Retorna 1 se for bem-sucedido
            }
        }
        free(buffer);  // Libera o buffer se não encontrar correspondência
    }
    fclose(file);  // Fecha o arquivo
    return 0;  // Retorna 0 se não encontrar correspondência
}

// Marca o registro como deletado (mudando o status para 0)
int delete(size_t size, int (*match)(const void *)) {
    FILE *file = fopen(FILE_NAME, "r+b");  // Abre o arquivo para leitura e escrita binária
    if (!file) {
        perror("Erro ao abrir arquivo");  // Se falhar, exibe erro
    } else {
        void *buffer = malloc(size);  // Aloca buffer para os dados lidos
        while (fread(buffer, size, 1, file)) {  // Lê o arquivo
            if (match(buffer)) {  // Se encontrar correspondência
                fseek(file, -((long)size), SEEK_CUR);  // Volta para sobrescrever os dados
                int false_status = 0;  // Marca o status como 0 (inativo)
                memcpy(buffer, &false_status, sizeof(int));  // Substitui o status no buffer
                fwrite(buffer, size, 1, file);  // Escreve os dados modificados de volta
                free(buffer);  // Libera o buffer
                fclose(file);  // Fecha o arquivo
                return 1;  // Retorna 1 se a exclusão for bem-sucedida
            }
        }
        free(buffer);  // Libera o buffer se não encontrar correspondência
    }
    fclose(file);  // Fecha o arquivo
    return 0;  // Retorna 0 se não encontrar correspondência
}