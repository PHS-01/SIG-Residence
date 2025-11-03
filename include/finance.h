#ifndef FINANCE_H
#define FINANCE_H

#include <stdbool.h>

typedef struct {
    bool status;    // ativo ou inativo
    int id;
    int people_id;           // Identificador único de pessoa (1:N)
    char description[100];
    float value;
    char date[11];           // dd/mm/aaaa
    char category[50];        
    char type;               // 'R' para receita, 'D' para despesa
} Finance;

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
void list_all_finance(void);
void list_active_finance(void);

// Função para definir ID de pesquisa
void set_search_finance_id(int id);

// Interfaces de usuário (UI)
void create_finance_ui();
void read_finance_ui();
void update_finance_ui();
void delete_finance_ui();
void physical_delete_finance_ui();

#endif