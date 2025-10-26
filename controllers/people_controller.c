#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Include de dados e funções da entidade People
#include "people.h"
#include "config.h"

static int search_id = -1;  // Variável global para armazenar o ID de pesquisa

// Define o ID de pesquisa
void set_search_id(int id) {
    search_id = id;
}

// Verifica se o ID da pessoa é igual ao de pesquisa
int match_people_by_id(const void *data) {
    People *p = (People *)data;
    return (p->id == search_id);
}

// Match para listar apenas pessoas ativas
int match_active_people(const void *data) {
    People *p = (People *)data;
    return (p->status == true);
}

// Match para listar todas as pessoas (independente do status)
int match_all_people(const void *data) {
    (void)data;  // Marcar parâmetro como usado para evitar warning
    return 1; // Sempre retorna verdadeiro
}

// Imprime os dados da pessoa
void print_people(const void *data) {
    People *p = (People *)data;
    printf("ID: %d, Nome: %s, Data: %s, Email: %s, Telefone: %s, Status: %s\n",
        p->id, p->name, p->birth_date, p->email, p->phone, 
        p->status ? "Ativo" : "Inativo");
}

// Gera um novo ID automaticamente
int generate_people_id(void) {
    FILE *file = fopen(FILE_NAME_PEOPLE, "rb");
    int max_id = 0;
    
    if (file != NULL) {
        People person;
        while (fread(&person, sizeof(People), 1, file)) {
            if (person.id > max_id) {
                max_id = person.id;
            }
        }
        fclose(file);
    }
    
    return max_id + 1;
}

// Lista todas as pessoas
void list_all_people(void) {
    printf("=== TODAS AS PESSOAS ===\n\n");
    FILE *file = fopen(FILE_NAME_PEOPLE, "rb");
    if (!file) {
        printf("Erro ao abrir arquivo ou nenhum dado cadastrado.\n");
        return;
    }
    
    People person;
    while (fread(&person, sizeof(People), 1, file)) {
        print_people(&person);
    }
    fclose(file);
}

// Lista apenas pessoas ativas
void list_active_people(void) {
    printf("=== PESSOAS ATIVAS ===\n\n");
    FILE *file = fopen(FILE_NAME_PEOPLE, "rb");
    if (!file) {
        printf("Erro ao abrir arquivo ou nenhum dado cadastrado.\n");
        return;
    }
    
    People person;
    int count = 0;
    while (fread(&person, sizeof(People), 1, file)) {
        if (person.status) {
            print_people(&person);
            count++;
        }
    }
    
    if (count == 0) {
        printf("Nenhuma pessoa ativa encontrada.\n");
    }
    fclose(file);
}