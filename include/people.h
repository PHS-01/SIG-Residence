#ifndef PEOPLE_H
#define PEOPLE_H

#include <stddef.h>

#define MAX_PEOPLE 100
#define NAME_LEN 50
#define CPF_LEN 16
#define EMAIL_LEN 100

typedef struct {
    char nome[NAME_LEN];
    int idade;
    char cpf[CPF_LEN];
    char email[EMAIL_LEN];
} Pessoa;

void create_people(Pessoa people[], int *count);
void read_people(Pessoa people[], int count);
void update_people(Pessoa people[], int count);
void delete_people(Pessoa people[], int *count);

// Persistência de dados
void save_people(const char *filename, Pessoa people[], int count);
void load_people(const char *filename, Pessoa people[], int *count);

#endif