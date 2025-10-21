#ifndef PEOPLE_H
#define PEOPLE_H

#include <stdbool.h>

// Definindo a estrutura People
typedef struct {
    bool status;             // Dado que amazenar o status da entidade entre apagado ou não (false ou true)
    // int type_id;          // Indentificador de type de dado
    int id;                  // Identificador único
    char name[100];          // Nome da pessoa
    char birth_date[11];     // Data de nascimento (formato: dd/mm/yyyy)
    char email[100];         // Email
    char phone[20];          // Telefone
    // char role[50];        // Papel ou função (ex: chefe de família, responsável pelas finanças)
    // float participation;  // Percentual de participação nas despesas compartilhadas (0.0 a 1.0)
    // int expense_type;     // Tipo de despesa (Pessoal ou Compartilhada)
} People;

// Funções auxiliares
void set_search_id(int id);     
int match_people_by_id(const void *data);
int match_active_people(const void *data);
int match_all_people(const void *data);
void print_people(const void *data);

// Novas funções
int generate_people_id(void);
void list_all_people(void);
void list_active_people(void);

#endif