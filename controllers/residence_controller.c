#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "residence.h"
#include "config.h"

static int search_id = -1;  // Variável global para armazenar o ID de pesquisa

// Define o ID de pesquisa
void set_search_residence_id(int id) {
    search_id = id;
}

// Verifica se o ID da residência é igual ao de pesquisa
int match_residence_by_id(const void *data) {
    Residence *r = (Residence *)data;
    return (r->id == search_id);
}

// Match para listar apenas residências ativas
int match_active_residence(const void *data) {
    Residence *r = (Residence *)data;
    return (r->status == true);
}

// Match para listar todas as residências (independente do status)
int match_all_residence(const void *data) {
    (void)data;
    return 1;
}

// Imprime os dados da residência
void print_residence(const void *data) {
    Residence *r = (Residence *)data;
    printf("ID: %d, Endereço: %s, %d, %s, %s - %s, CEP: %s, Status: %s\n",
        r->id, r->address, r->number, r->complement, r->city, r->state, r->cep,
        r->status ? "Ativo" : "Inativo");
}

// Gera um novo ID automaticamente
int generate_residence_id(void) {
    FILE *file = fopen(FILE_NAME_RESIDENCE, "rb");
    int max_id = 0;
    
    if (file != NULL) {
        Residence residence;
        while (fread(&residence, sizeof(Residence), 1, file)) {
            if (residence.id > max_id) {
                max_id = residence.id;
            }
        }
        fclose(file);
    }
    
    return max_id + 1;
}

// Lista todas as residências
void list_all_residence(void) {
    printf("=== TODAS AS RESIDÊNCIAS ===\n\n");
    FILE *file = fopen(FILE_NAME_RESIDENCE, "rb");
    if (!file) {
        printf("Erro ao abrir arquivo ou nenhum dado cadastrado.\n");
        return;
    }
    
    Residence residence;
    while (fread(&residence, sizeof(Residence), 1, file)) {
        print_residence(&residence);
    }
    fclose(file);
}

// Lista apenas residências ativas
void list_active_residence(void) {
    printf("=== RESIDÊNCIAS ATIVAS ===\n\n");
    FILE *file = fopen(FILE_NAME_RESIDENCE, "rb");
    if (!file) {
        printf("Erro ao abrir arquivo ou nenhum dado cadastrado.\n");
        return;
    }
    
    Residence residence;
    int count = 0;
    while (fread(&residence, sizeof(Residence), 1, file)) {
        if (residence.status) {
            print_residence(&residence);
            count++;
        }
    }
    
    if (count == 0) {
        printf("Nenhuma residência ativa encontrada.\n");
    }
    fclose(file);
}