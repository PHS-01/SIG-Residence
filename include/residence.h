#ifndef RESIDENCE_H
#define RESIDENCE_H

#include <stdbool.h>

typedef struct {
    bool status;        // ativo ou inativo
    int id;
    char address[100];
    char neighborhood[50];
    char city[50];
    char state[30];
    int number;
    char complement[50];
    char cep[10];       // 12345-678
} Residence;

typedef struct ResidenceNode {
    Residence data;
    struct ResidenceNode *next;
} ResidenceNode;

// Variável Global Externa
extern ResidenceNode *head_residence;

// Funções de Gerenciamento da Lista (CRUD Memória)
void load_residence_list(void);                 // Carrega do arquivo para RAM ordenado
void save_residence_list(void);                 // Salva da RAM para arquivo
void free_residence_list(void);                 // Limpa memória
int insert_residence_sorted(Residence new_res); // Insere ORDENADO por endereço
int remove_residence_from_list(int id);         // Remove da lista e salva
Residence* find_residence_by_id(int id);        // Busca na RAM

// Funções de match
int match_residence_by_id(const void *data);

// Função de impressão
void print_residence_detail(const void *data);
void print_residence_table(const void *data);

// Geração de ID
int generate_residence_id(void);

// Listagens
void list_residence_paginated(bool active_only);
void list_residence_by_state(void);

// Função para definir ID de pesquisa
void set_search_residence_id(int id);

// Interfaces de usuário (UI)
void create_residence_ui();
void read_residence_ui();
void update_residence_ui();
void delete_residence_ui();
void physical_delete_residence_ui();

#endif