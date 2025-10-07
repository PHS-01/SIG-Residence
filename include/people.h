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

void read_people(int);

// Função para criar uma nova pessoa no arquivo
void create_people(People new_person);
// Função para listar as pessoas do arquivo
void list_people(void);
// Função para atualizar os dados de uma pessoa no arquivo
void update_people(int id, People updated_person);
// Função para excluir uma pessoa do arquivo
void delete_people(int id);

#endif