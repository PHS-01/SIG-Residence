#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Include de dados e funções da entidade People
#include "people.h"
#include "config.h"
#include "menu_borders.h"
#include "terminal_control.h"

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

// Imprime os dados completos de uma pessoa (para consulta individual)
void print_people_detail(const void *data) {
    People *p = (People *)data;
    
    const char *status_text = p->status ? "Ativo" : "Inativo";
    
    printf("╔══════════════════════════════════════════════════════════════╗\n");
    printf("║                     DETALHES DA PESSOA                       ║\n");
    printf("╠══════════════════════════════════════════════════════════════╣\n");
    printf("║ ID: %-56d ║\n", p->id);
    printf("║ Nome: %-54s ║\n", p->name);
    printf("║ Data de Nascimento: %-40s ║\n", p->birth_date);
    printf("║ Email: %-53s ║\n", p->email);
    printf("║ Telefone: %-50s ║\n", p->phone);
    printf("║ Status: %-52s ║\n", status_text);
    printf("╚══════════════════════════════════════════════════════════════╝\n");
}

// Imprime os dados da pessoa em formato de tabela
void print_people_table(const void *data) {
    People *p = (People *)data;
    
    const char *status_text = p->status ? "Ativo" : "Inativo";
    
    // Colunas ajustadas com larguras maiores para melhor alinhamento
    printf("║ %-4d ║ %-27s ║ %-12s ║ %-28s ║ %-16s ║ %-9s ║\n",
           p->id, p->name, p->birth_date, p->email, p->phone, status_text);
}

void list_all_people(void) {
    printf("╔══════╦═════════════════════════════╦══════════════╦══════════════════════════════╦══════════════════╦═══════════╗\n");
    printf("║  ID  ║ Nome                        ║  Nascimento  ║ Email                        ║ Telefone         ║ Status    ║\n");
    printf("╠══════╬═════════════════════════════╬══════════════╬══════════════════════════════╬══════════════════╬═══════════╣\n");

    FILE *file = fopen(FILE_NAME_PEOPLE, "rb");
    if (!file) {
        printf("║                                   Nenhum dado cadastrado ou erro ao abrir arquivo                                   ║\n");
        printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝\n");
        return;
    }
    
    People person;
    int count = 0;
    while (fread(&person, sizeof(People), 1, file)) {
        print_people_table(&person);
        count++;
    }
    
    printf("╚══════╩═════════════════════════════╩══════════════╩══════════════════════════════╩══════════════════╩═══════════╝\n");
    printf("Total de registros: %d\n", count);
    
    fclose(file);
}

// Lista apenas pessoas ativas
void list_active_people(void) {
    printf("╔══════╦═════════════════════════════╦══════════════╦══════════════════════════════╦══════════════════╦═══════════╗\n");
    printf("║  ID  ║ Nome                        ║  Nascimento  ║ Email                        ║ Telefone         ║ Status    ║\n");
    printf("╠══════╬═════════════════════════════╬══════════════╬══════════════════════════════╬══════════════════╬═══════════╣\n");
    
    FILE *file = fopen(FILE_NAME_PEOPLE, "rb");
    if (!file) {
        printf("║                                   Nenhum dado cadastrado ou erro ao abrir arquivo                                   ║\n");
        printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝\n");
        return;
    }
    
    People person;
    int count = 0;
    while (fread(&person, sizeof(People), 1, file)) {
        if (person.status) {
            print_people_table(&person);
            count++;
        }
    }
    
    printf("╚══════╩═════════════════════════════╩══════════════╩══════════════════════════════╩══════════════════╩═══════════╝\n");
    printf("Total de registros ativos: %d\n", count);
    
    fclose(file);
}