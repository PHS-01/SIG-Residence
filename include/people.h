#ifndef PEOPLE_H
#define PEOPLE_H

#include <stdbool.h>

// Definindo a estrutura People
typedef struct {
    int id;                  // Identificador único
    char name[100];          // Nome da pessoa
    char birth_date[11];     // Data de nascimento (formato: dd/mm/yyyy)
    char email[100];         // Email
    char phone[20];          // Telefone
    bool status;
    // char role[50];           // Papel ou função (ex: chefe de família, responsável pelas finanças)
    // float participation;     // Percentual de participação nas despesas compartilhadas (0.0 a 1.0)
    // int expense_type;        // Tipo de despesa (Pessoal ou Compartilhada)
} People;

// Funções CRUD
void create_people(People new_person);
void read_people(int id);
void list_people(void);
void update_people(int id, People updated_person);
void delete_people(int id);  // Exclusão lógica (inativa)

// Funções de interface do usuário
void create_people_ui(void);
void read_people_ui(void);
void update_people_ui(void);
void delete_people_ui(void);

// Nova função para gerar ID automático
int generate_people_id(void);
// Função para listar apenas pessoas ativas
void list_active_people(void);

#endif