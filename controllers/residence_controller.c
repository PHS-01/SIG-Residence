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
    
    print_detail_line_int("ID:", r->id, 3, 56);
    print_detail_line("Endereço:", r->address, 10, 49);
    print_detail_line_int("Número:", r->number, 8, 51);
    print_detail_line("Complemento:", r->complement, 13, 46);
    print_detail_line("Bairro:", r->neighborhood, 8, 51);
    print_detail_line("Cidade:", r->city, 8, 51);
    print_detail_line("Estado:", r->state, 8, 51);
    print_detail_line("CEP:", r->cep, 5, 54);
    print_detail_line("Status:", status_text, 8, 51);
    
    printf("╚══════════════════════════════════════════════════════════════╝\n");
}

// Imprime os dados da residência em formato de tabela
void print_residence_table(const void *data) {
    Residence *r = (Residence *)data;
    
    const char *status_text = r->status ? "Ativo" : "Inativo";
    
    printf("║ ");
    printf("%-4d ║ ", r->id);
    print_padded_string(r->address, 20);
    printf(" ║ ");
    printf("%-6d ║ ", r->number);
    print_padded_string(r->complement, 12);
    printf(" ║ ");
    print_padded_string(r->neighborhood, 12);
    printf(" ║ ");
    print_padded_string(r->city, 12);
    printf(" ║ ");
    print_padded_string(r->state, 6);
    printf(" ║ ");
    print_padded_string(r->cep, 10);
    printf(" ║ ");
    print_padded_string(status_text, 8);
    printf(" ║\n");
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

// Função para listar residências por estado
void list_residence_by_state(void) {
    char estado[30];
    
    printf("Digite a sigla do estado (ex: SP, RJ, MG): ");
    read_string_input("", estado, sizeof(estado));
    
    // Converter para maiúsculas
    for (int i = 0; estado[i]; i++) {
        estado[i] = toupper(estado[i]);
    }

    printf("╔════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                  RELATORIO DE RESIDENCIAS POR ESTADO: %-2s                                          ║\n", estado);
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
        if (!residence.status) continue;

        char estado_residencia[30];
        strcpy(estado_residencia, residence.state);
        for (int i = 0; estado_residencia[i]; i++) {
            estado_residencia[i] = toupper(estado_residencia[i]);
        }

        if (strcmp(estado_residencia, estado) == 0) {
            print_residence_table(&residence);
            count++;
        }
    }

    printf("╚══════╩══════════════════════╩════════╩══════════════╩══════════════╩══════════════╩════════╩════════════╩══════════╝\n");
    printf("Total de residências no estado '%s': %d\n", estado, count);

    fclose(file);
}
