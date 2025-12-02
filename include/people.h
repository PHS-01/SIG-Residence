#ifndef PEOPLE_H
#define PEOPLE_H

#include <stdbool.h>

// Definindo a estrutura People
typedef struct {
    bool status;             // Status: false (apagado logicamente) ou true (ativo)
    int id;                  // Identificador único
    char name[100];          // Nome da pessoa
    char birth_date[11];     // Data de nascimento (formato: dd/mm/yyyy)
    char email[100];         // Email
    char phone[20];          // Telefone
} People;

// Nó para listas encadeadas de People
typedef struct PeopleNode {
    People data;
    struct PeopleNode *next; // Ponteiro para o próximo nó
} PeopleNode;

// Variável Global Externa
extern PeopleNode *head_people; 

// FUNÇÕES DE GERENCIAMENTO DE LISTAGEM DINÂMICA INVERTIDA (CRUD EM MEMÓRIA)
void load_people_list(void);              // Carrega do arquivo para RAM
void save_people_list(void);              // Salva da RAM para arquivo
void free_people_list(void);               // Libera a memória da lista
int create_person(People new_person);     // Insere na lista e salva
int remove_person_from_list(int id);      // Remove da lista e salva
People* find_person_by_id(int id);        // Busca ponteiro na RAM pelo ID

// FUNÇÕES DE SUPORTE E UTILITÁRIOS
void set_search_id(int id);
int match_people_by_id(const void *data);
int match_active_people(const void *data);
int match_all_people(const void *data);

// Função de impressão
void print_people_detail(const void *data);
void print_people_table(const void *data);

// Geração de ID (Agora deve olhar a lista na RAM)
int generate_people_id(void);

// RELATÓRIOS
void list_people_paginated(bool active_only);
void list_birthdays_by_month(void);
void list_birthdays_by_year(void);

// INTERFACES DE USUÁRIO (UI)
void create_people_ui();
void read_people_ui();
void update_people_ui();
void delete_people_ui();
void physical_delete_people_ui();

#endif