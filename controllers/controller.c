#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Variáveis globais do projeto
#include "config.h"
#include "people.h"
#include "finance.h"
#include "residence.h"

// Cria ou adiciona dados ao arquivo
int create(const void* data, size_t size, const char* file_name) {
    FILE* file = fopen(file_name, "ab");  // Abre o arquivo para escrita binária (append)
    if (!file) {
        perror("Erro ao abrir arquivo");  // Se falhar, exibe erro
        return 0;  // Retorna 0 em caso de falha
    } else {
        fwrite(data, size, 1, file);  // Escreve os dados no arquivo
    }
    fclose(file);  // Fecha o arquivo
    return 1;  // Retorna 1 em caso de sucesso
}

// Lê dados do arquivo e verifica se há correspondência com a função `match`
int read_data(void *output, size_t size, const char* file_name, int (*match)(const void *)) {
    FILE *file = fopen(file_name, "rb");
    if (!file) {
        perror("Erro ao abrir arquivo");
        return 0;
    } else {
        void *buffer = malloc(size);
        while (fread(buffer, size, 1, file)) {
            if (match(buffer)) {
                memcpy(output, buffer, size);
                free(buffer);
                fclose(file);
                return 1;
            }
        }
        free(buffer);
    }
    fclose(file);
    return 0;
}

// Lista todos os registros
void list_records(size_t size, void (*print)(const void *), int (*match)(const void *), const char* filename) {
    FILE *file = fopen(filename, "rb");
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

// Atualiza dados no arquivo, se encontrar uma correspondência
int update(const void *new_data, size_t size,const char* file_name, int (*match)(const void *)) {
    FILE *file = fopen(file_name, "r+b");  // Abre o arquivo para leitura e escrita binária
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
int delete(size_t size, const char* file_name,int (*match)(const void *)) {
    FILE *file = fopen(file_name, "r+b");  // Abre o arquivo para leitura e escrita binária
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

// Exclusão física - remove completamente o registro do arquivo
int physical_delete(size_t size, int (*match)(const void *), const char* filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Erro ao abrir arquivo");
        return 0;
    }
    
    // Criar arquivo temporário
    char temp_file[256];
    snprintf(temp_file, sizeof(temp_file), "%s.tmp", filename);
    
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
        if (remove(filename) != 0) {
            perror("Erro ao remover arquivo original");
            remove(temp_file);
            return 0;
        }
        
        if (rename(temp_file, filename) != 0) {
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