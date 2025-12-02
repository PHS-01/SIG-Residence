#ifndef FINANCE_H
#define FINANCE_H

#include <stdbool.h>

typedef enum {
    FINANCE_RECEITA = 1,
    FINANCE_DESPESA = 2
} FinanceType;

typedef struct {
    bool status;    // ativo ou inativo
    int id;
    int people_id;           // Identificador único de pessoa (1:N)
    char description[100];
    float value;
    char date[11];           // dd/mm/aaaa
    char category[50];      // todo: Fazer enum e relatorio para categorias     
    FinanceType type;               // 'R' para receita, 'D' para despesa
} Finance;

typedef struct FinanceNode {
    Finance data;
    struct FinanceNode *next;   // aponta para o próximo nó
} FinanceNode;
// Variável Global Externa
extern FinanceNode *head_finance;

// FUNÇÕES DE GERENCIAMENTO DE LISTAGEM DINÂMICA DIRETA (CRUD EM MEMÓRIA)
int finance_list_insert(Finance f);             // Insere na lista em RAM
int finance_list_remove(int id);              // Remove da lista em RAM 
void finance_load_file(void);                        // Carrega do arquivo para RAM
void free_finance_list(void);                     // Libera a memória da lista
void finance_save_file(void);                       // Salva da RAM para arquivo
Finance *finance_list_find(int id);  // Busca nó na RAM pelo critério
void finance_list_print(int (*match)(const void *)); // Imprime lista conforme critério

// Funções de match
int match_finance_by_id(const void *data);
int match_active_finance(const void *data);
int match_all_finance(const void *data);

// Função de impressão
void print_finance_detail(const void *data);
void print_finance_table(const void *data);

// Geração de ID
int generate_finance_id(void);

// Listagens
void list_finance_paginated(bool active_only);
// void list_all_finance(void);
// void list_active_finance(void);
void list_finance_by_people_id(int people_id);
void list_finance_by_category(void);
void list_finance_by_person(void);

// Função para definir ID de pesquisa
void set_search_finance_id(int id);

// Contagem de finanças por people_id
int count_finance_by_people_id(int people_id);

// Exclusão de finanças por people_id
int delete_finance_by_people_id(int people_id);


// Interfaces de usuário (UI)
void create_finance_ui();
void read_finance_ui();
void update_finance_ui();
void delete_finance_ui();
void physical_delete_finance_ui();

#endif