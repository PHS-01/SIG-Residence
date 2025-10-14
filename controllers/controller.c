#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Variáveis globais do projeto
#include "config.h"

#include "controllers.h"

void create(const void* data, size_t size) {
    FILE* file = fopen(FILE_NAME, "ab");
    if (!file) {
        perror("Erro ao abrir arquivo");
        return;
    } else {
        fwrite(data, size, 1, file);
    }
    fclose(file);
}

int read(void *output, size_t size, int (*match)(const void *)) {
    FILE *file = fopen(FILE_NAME, "rb");
    if (!file) {
        perror("Erro ao abrir arquivo");
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

int update(const void *new_data, size_t size, int (*match)(const void *)) {
    FILE *file = fopen(FILE_NAME, "r+b");
    if (!file) {
        perror("Erro ao abrir arquivo");
    } else {
        void *buffer = malloc(size);
        while (fread(buffer, size, 1, file)) {
            if (match(buffer)) {
                fseek(file, -((long)size), SEEK_CUR);
                fwrite(new_data, size, 1, file);
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

int delete(size_t size, int (*match)(const void *)) {
    FILE *file = fopen(FILE_NAME, "r+b");
    if (!file) {
        perror("Erro ao abrir arquivo");
    } else {
        void *buffer = malloc(size);
        while (fread(buffer, size, 1, file)) {
            if (match(buffer)) {
                // Assume que há um campo `status` como `int` no início da struct
                fseek(file, -((long)size), SEEK_CUR);
                int false_status = 0;
                memcpy(buffer, &false_status, sizeof(int)); // status = false
                fwrite(buffer, size, 1, file);
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