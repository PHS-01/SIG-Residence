#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "residence.h"
#include "config.h"
#include "menu_borders.h"
#include "terminal_control.h"

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

// Imprime os dados completos de uma residência (para consulta individual)
void print_residence_detail(const void *data) {
    Residence *r = (Residence *)data;
    
    const char *status_text = r->status ? "Ativo" : "Inativo";
    
    printf("╔══════════════════════════════════════════════════════════════╗\n");
    printf("║                    DETALHES DA RESIDENCIA                    ║\n");
    printf("╠══════════════════════════════════════════════════════════════╣\n");
    printf("║ ID: %-56d ║\n", r->id);
    printf("║ Endereço: %-50s ║\n", r->address);
    printf("║ Número: %-52d ║\n", r->number);
    printf("║ Complemento: %-47s ║\n", r->complement);
    printf("║ Bairro: %-52s ║\n", r->neighborhood);
    printf("║ Cidade: %-52s ║\n", r->city);
    printf("║ Estado: %-52s ║\n", r->state);
    printf("║ CEP: %-55s ║\n", r->cep);
    printf("║ Status: %-52s ║\n", status_text);
    printf("╚══════════════════════════════════════════════════════════════╝\n");
}

// Imprime os dados da residência em formato de tabela
void print_residence_table(const void *data) {
    Residence *r = (Residence *)data;
    
    const char *status_text = r->status ? "Ativo" : "Inativo";
    
    printf("║ %-4d ║ %-20s ║ %-6d ║ %-12s ║ %-12s ║ %-12s ║ %-6s ║ %-10s ║ %-8s ║\n",
           r->id, r->address, r->number, r->complement, r->neighborhood, 
           r->city, r->state, r->cep, status_text);
}

void list_all_residence(void) {
    printf("╔════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                             R E L A T Ó R I O     D E     R E S I D E N C I A S                                    ║\n");
    printf("║                                                                                                                    ║\n");
    printf("╠══════╦══════════════════════╦════════╦══════════════╦══════════════╦══════════════╦════════╦════════════╦══════════╣\n");
    printf("║  ID  ║ Endereço             ║ Número ║ Complemento  ║ Bairro       ║ Cidade       ║ Estado ║ CEP        ║ Status   ║\n");
    printf("╠══════╬══════════════════════╬════════╬══════════════╬══════════════╬══════════════╬════════╬════════════╬══════════╣\n");

    FILE *file = fopen(FILE_NAME_RESIDENCE, "rb");
    if (!file) {
        printf("╚══════╩══════════════════════╩════════╩══════════════╩══════════════╩══════════════╩════════╩════════════╩══════════╝\n");
        print_error("Nenhum dado cadastrado ou erro ao abrir arquivo.");
        return;
    }
    
    Residence residence;
    int count = 0;
    while (fread(&residence, sizeof(Residence), 1, file)) {
        print_residence_table(&residence);
        count++;
    }
    
    printf("╚══════╩══════════════════════╩════════╩══════════════╩══════════════╩══════════════╩════════╩════════════╩══════════╝\n");
    printf("Total de registros: %d\n", count);
    
    fclose(file);
}

// Lista apenas residências ativas
void list_active_residence(void) {
    printf("╔════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                           R E L A T Ó R I O    D E    R E S I D E N C I A S    A T I V A S                         ║\n");
    printf("║                                                                                                                    ║\n");
    printf("╠══════╦══════════════════════╦════════╦══════════════╦══════════════╦══════════════╦════════╦════════════╦══════════╣\n");
    printf("║  ID  ║ Endereço             ║ Número ║ Complemento  ║ Bairro       ║ Cidade       ║ Estado ║ CEP        ║ Status   ║\n");
    printf("╠══════╬══════════════════════╬════════╬══════════════╬══════════════╬══════════════╬════════╬════════════╬══════════╣\n");
    
    FILE *file = fopen(FILE_NAME_RESIDENCE, "rb");
    if (!file) {
        printf("╚══════╩══════════════════════╩════════╩══════════════╩══════════════╩══════════════╩════════╩════════════╩══════════╝\n");
        print_error("Nenhum dado cadastrado ou erro ao abrir arquivo.");
        return;
    }
    
    Residence residence;
    int count = 0;
    while (fread(&residence, sizeof(Residence), 1, file)) {
        if (residence.status) {
            print_residence_table(&residence);
            count++;
        }
    }
    
    printf("╚══════╩══════════════════════╩════════╩══════════════╩══════════════╩══════════════╩════════╩════════════╩══════════╝\n");
    printf("Total de registros ativos: %d\n", count);
    
    fclose(file);
}