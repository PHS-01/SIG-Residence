#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <strings.h> // Para strcasecmp (Linux/Mac)

#include "residence.h"
#include "config.h"
#include "menu_borders.h"
#include "terminal_control.h"

// Cabeça da lista
ResidenceNode *head_residence = NULL;
static int search_id = -1;

// INSERÇÃO ORDENADA
int insert_residence_sorted(Residence new_residence) {
    ResidenceNode *novo = (ResidenceNode*) malloc(sizeof(ResidenceNode));
    if (!novo) return 0;
    
    novo->data = new_residence;
    novo->next = NULL;

    // Caso 1: Lista vazia ou o novo item é alfabeticamente menor que o primeiro (vem antes da cabeça)
    // strcasecmp retorna < 0 se o primeiro argumento for "menor" que o segundo
    if (head_residence == NULL || strcasecmp(new_residence.address, head_residence->data.address) < 0) {
        novo->next = head_residence;
        head_residence = novo;
    } else {
        // Caso 2: Percorrer a lista para encontrar a posição correta
        ResidenceNode *atual = head_residence;
        
        // Avança enquanto houver próximo E o endereço do próximo for "menor" que o novo
        while (atual->next != NULL && strcasecmp(atual->next->data.address, new_residence.address) < 0) {
            atual = atual->next;
        }
        
        // Insere o novo nó após o 'atual'
        novo->next = atual->next;
        atual->next = novo;
    }
    
    save_residence_list(); // Persiste no arquivo
    return 1;
}

// Carrega do arquivo inserindo ordenadamente
void load_residence_list(void) {
    if (head_residence != NULL) return; // Já carregado

    FILE *file = fopen(FILE_NAME_RESIDENCE, "rb");
    if (!file) return;

    Residence temp;
    while (fread(&temp, sizeof(Residence), 1, file)) {
        // Isso reordena caso o arquivo esteja bagunçado
        insert_residence_sorted(temp); 
    }
    fclose(file);
}

void save_residence_list(void) {
    FILE *file = fopen(FILE_NAME_RESIDENCE, "wb");
    if (!file) return;

    ResidenceNode *atual = head_residence;
    while (atual != NULL) {
        fwrite(&atual->data, sizeof(Residence), 1, file);
        atual = atual->next;
    }
    fclose(file);
}

Residence* find_residence_by_id(int id) {
    ResidenceNode *atual = head_residence;
    while (atual != NULL) {
        if (atual->data.id == id) {
            return &atual->data;
        }
        atual = atual->next;
    }
    return NULL;
}

void free_residence_list(void) {
    ResidenceNode *atual = head_residence;
    while (atual != NULL) {
        ResidenceNode *temp = atual;
        atual = atual->next;
        free(temp);
    }
    head_residence = NULL;
}

// Remove fisicamente um nó da lista e salva
int remove_residence_from_list(int id) {
    ResidenceNode *atual = head_residence;
    ResidenceNode *anterior = NULL;

    while (atual != NULL) {
        if (atual->data.id == id) {
            // Se for o primeiro
            if (anterior == NULL) {
                head_residence = atual->next;
            } else {
                anterior->next = atual->next;
            }
            
            free(atual);        // Libera RAM
            save_residence_list(); // Salva no arquivo sem o registro
            return 1;
        }
        anterior = atual;
        atual = atual->next;
    }
    return 0; // Não encontrou
}

// Gera ID baseado no maior ID da lista
int generate_residence_id(void) {
    int max_id = 0;
    ResidenceNode *atual = head_residence;
    while (atual != NULL) {
        if (atual->data.id > max_id) {
            max_id = atual->data.id;
        }
        atual = atual->next;
    }
    return max_id + 1;
}

// --- Funções Auxiliares e de Visualização ---

void set_search_residence_id(int id) {
    search_id = id;
}

int match_residence_by_id(const void *data) {
    Residence *r = (Residence *)data;
    return (r->id == search_id);
}

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

// Listagem Paginada usando a LISTA DINÂMICA
void list_residence_paginated(bool active_only) {
    if (head_residence == NULL) {
        print_warning("Nenhum registro encontrado.");
        wait_for_enter();
        return;
    }

    int total_records = 0;
    ResidenceNode *atual = head_residence;
    while (atual != NULL) {
        if (!active_only || atual->data.status) total_records++;
        atual = atual->next;
    }

    if (total_records == 0) {
        print_warning("Nenhum registro encontrado.");
        wait_for_enter();
        return;
    }

    const int ITEMS_PER_PAGE = 10;
    int total_pages = (total_records + ITEMS_PER_PAGE - 1) / ITEMS_PER_PAGE;
    int current_page = 1;
    char option;

    do {
        clear_screen();
        const char* title = active_only ? "RELATORIO DE RESIDENCIAS (ATIVAS)" : "RELATORIO DE RESIDENCIAS (TODAS)";
        printf("╔════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
        printf("║ %-114s ║\n", title);
        printf("║ Página %d de %d - Total de registros: %-78d ║\n", current_page, total_pages, total_records);
        printf("╠══════╦══════════════════════╦════════╦══════════════╦══════════════╦══════════════╦════════╦════════════╦══════════╣\n");
        printf("║  ID  ║ Endereço             ║ Número ║ Complemento  ║ Bairro       ║ Cidade       ║ Estado ║ CEP        ║ Status   ║\n");
        printf("╠══════╬══════════════════════╬════════╬══════════════╬══════════════╬══════════════╬════════╬════════════╬══════════╣\n");

        atual = head_residence;
        int skipped = 0;
        int printed = 0;
        int start_index = (current_page - 1) * ITEMS_PER_PAGE;

        while (atual != NULL && printed < ITEMS_PER_PAGE) {
            if (!active_only || atual->data.status) {
                if (skipped < start_index) {
                    skipped++;
                } else {
                    print_residence_table(&atual->data);
                    printed++;
                }
            }
            atual = atual->next;
        }

        printf("╚══════╩══════════════════════╩════════╩══════════════╩══════════════╩══════════════╩════════╩════════════╩══════════╝\n");
        printf("\n[A] Anterior  [P] Próxima  [0] Sair\n");
        
        option = get_keypress();
        if ((option == 'p' || option == 'P') && current_page < total_pages) current_page++;
        else if ((option == 'a' || option == 'A') && current_page > 1) current_page--;

    } while (option != '0');
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
