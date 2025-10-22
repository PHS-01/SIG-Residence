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

// Exclusão física - remove completamente o registro do arquivo
int physical_delete(size_t size, int (*match)(const void *)) {
    FILE *file = fopen(FILE_NAME, "rb");
    if (!file) {
        perror("Erro ao abrir arquivo");
        return 0;
    }
    
    // Criar arquivo temporário com nome único
    char temp_file[256];  // Aumentado para 256 bytes
    const char *base_name = FILE_NAME;
    const char *ext = strrchr(base_name, '.');
    
    if (ext != NULL) {
        // Se o arquivo tem extensão, insere .tmp antes da extensão
        size_t base_len = ext - base_name;
        snprintf(temp_file, sizeof(temp_file), "%.*s.tmp%s", (int)base_len, base_name, ext);
    } else {
        // Se não tem extensão, apenas adiciona .tmp
        snprintf(temp_file, sizeof(temp_file), "%s.tmp", FILE_NAME);
    }
    
    FILE *temp = fopen(temp_file, "wb");
    if (!temp) {
        perror("Erro ao criar arquivo temporário");
        fclose(file);
        return 0;
    }
    
    void *buffer = malloc(size);
    int found = 0;
    int count = 0;
    
    // Copiar todos os registros, exceto o que será excluído
    while (fread(buffer, size, 1, file)) {
        if (match(buffer)) {
            found = 1;  // Registro encontrado, não copia (exclui)
        } else {
            fwrite(buffer, size, 1, temp);
            count++;
        }
    }
    
    free(buffer);
    fclose(file);
    fclose(temp);
    
    if (found) {
        // Substituir arquivo original pelo temporário
        if (remove(FILE_NAME) != 0) {
            perror("Erro ao remover arquivo original");
            remove(temp_file);
            return 0;
        }
        
        if (rename(temp_file, FILE_NAME) != 0) {
            perror("Erro ao renomear arquivo temporário");
            return 0;
        }
        
        printf("Registro excluído fisicamente. %d registros restantes.\n", count);
        return 1;
    } else {
        // Se não encontrou, remove o arquivo temporário
        remove(temp_file);
        printf("Registro não encontrado para exclusão física.\n");
        return 0;
    }
}