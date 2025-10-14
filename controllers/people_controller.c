#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Include de dados é funções do modelo/entidade People
#include "people.h"

static int search_id = -1;  // Variável global para armazenar o ID de pesquisa

// Define o ID de pesquisa
void set_search_id(int id) {
    search_id = id;
}

// Verifica se o ID da pessoa é igual ao de pesquisa e se está ativa
int match_people_by_id(const void *data) {
    People *p = (People *)data;
    return (p->id == search_id && p->status == 1);
}

// Imprime os dados da pessoa, se ela estiver ativa
void print_people(const void *data) {
    People *p = (People *)data;
    if (p->status == 1) {
        printf("ID: %d, Name: %s, Birth Date: %s, Email: %s, Phone: %s\n",
            p->id, p->name, p->birth_date, p->email, p->phone);
    }

    fclose(file);
}