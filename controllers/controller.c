#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Variáveis globais do projeto
#include "config.h"
#include "people.h"

// Cria ou adiciona dados ao arquivo
void create(const void* data, size_t size) {
    FILE* file = fopen(FILE_NAME, "ab");
    if (!file) {
        perror("Erro ao abrir arquivo");
        return;
    }
    fwrite(data, size, 1, file);
    fclose(file);
}

// Lê dados do arquivo e verifica se há correspondência com a função `match`
int read(void *output, size_t size, int (*match)(const void *)) {
    FILE *file = fopen(FILE_NAME, "rb");
    if (!file) {
        perror("Erro ao abrir arquivo");
        return 0;
    }
    
    void *buffer = malloc(size);
    int found = 0;
    
    while (fread(buffer, size, 1, file)) {
        if (match(buffer)) {
            memcpy(output, buffer, size);
            found = 1;
            break;
        }
    }
    
    free(buffer);
    fclose(file);
    return found;
}

// Lista todos os registros
void list_records(size_t size, void (*print)(const void *), int (*match)(const void *)) {
    FILE *file = fopen(FILE_NAME, "rb");
    if (!file) {
        perror("Erro ao abrir arquivo");
        return;
    }
    
    void *buffer = malloc(size);
    
    while (fread(buffer, size, 1, file)) {
        if (match == NULL || match(buffer)) {
            print(buffer);
        }
    }
    
    free(buffer);
    fclose(file);
}

// Atualiza dados no arquivo
int update(const void *new_data, size_t size, int (*match)(const void *)) {
    FILE *file = fopen(FILE_NAME, "r+b");
    if (!file) {
        perror("Erro ao abrir arquivo");
        return 0;
    }
    
    void *buffer = malloc(size);
    int found = 0;
    
    while (fread(buffer, size, 1, file)) {
        if (match(buffer)) {
            fseek(file, -((long)size), SEEK_CUR);
            fwrite(new_data, size, 1, file);
            found = 1;
            break;
        }
    }
    
    free(buffer);
    fclose(file);
    return found;
}

// Marca o registro como deletado (mudando o status para falso) - CORRIGIDA
int delete(size_t size, int (*match)(const void *)) {
    FILE *file = fopen(FILE_NAME, "r+b");
    if (!file) {
        perror("Erro ao abrir arquivo");
        return 0;
    }
    
    void *buffer = malloc(size);
    int found = 0;
    
    while (fread(buffer, size, 1, file)) {
        if (match(buffer)) {
            // Para a estrutura People, precisamos preservar todos os dados
            // apenas alterando o status para false
            People *person = (People *)buffer;
            person->status = false;
            
            fseek(file, -((long)size), SEEK_CUR);
            fwrite(buffer, size, 1, file);
            found = 1;
            break;
        }
    }
    
    free(buffer);
    fclose(file);
    return found;
}