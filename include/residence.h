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

// Funções de match
int match_residence_by_id(const void *data);
int match_active_residence(const void *data);
int match_all_residence(const void *data);

// Função de impressão
void print_residence_detail(const void *data);
void print_residence_table(const void *data);

// Geração de ID
int generate_residence_id(void);

// Listagens
void list_residence_paginated(bool active_only);
// void list_all_residence(void);
// void list_active_residence(void);
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