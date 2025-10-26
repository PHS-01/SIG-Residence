#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "finance.h"
#include "config.h"

static int search_id = -1;  // Variável global para armazenar o ID de pesquisa

// Define o ID de pesquisa
void set_search_finance_id(int id) {
    search_id = id;
}

// Verifica se o ID da transação é igual ao de pesquisa
int match_finance_by_id(const void *data) {
    Finance *f = (Finance *)data;
    return (f->id == search_id);
}

// Match para listar apenas transações ativas
int match_active_finance(const void *data) {
    Finance *f = (Finance *)data;
    return (f->status == true);
}

// Match para listar todas as transações (independente do status)
int match_all_finance(const void *data) {
    (void)data;
    return 1;
}

// Imprime os dados da transação
void print_finance(const void *data) {
    Finance *f = (Finance *)data;
    printf("ID: %d, Descrição: %s, Valor: %.2f, Data: %s, Categoria: %s, Tipo: %s, Status: %s\n",
        f->id, f->description, f->value, f->date, f->category,
        (f->type == 'R' || f->type == 'r') ? "Receita" : "Despesa",
        f->status ? "Ativo" : "Inativo");
}

// Gera um novo ID automaticamente
int generate_finance_id(void) {
    FILE *file = fopen(FILE_NAME_FINANCE, "rb");
    int max_id = 0;
    
    if (file != NULL) {
        Finance finance;
        while (fread(&finance, sizeof(Finance), 1, file)) {
            if (finance.id > max_id) {
                max_id = finance.id;
            }
        }
        fclose(file);
    }
    
    return max_id + 1;
}

// Lista todas as transações
void list_all_finance(void) {
    printf("=== TODAS AS TRANSAÇÕES ===\n\n");
    FILE *file = fopen(FILE_NAME_FINANCE, "rb");
    if (!file) {
        printf("Erro ao abrir arquivo ou nenhum dado cadastrado.\n");
        return;
    }
    
    Finance finance;
    while (fread(&finance, sizeof(Finance), 1, file)) {
        print_finance(&finance);
    }
    fclose(file);
}

// Lista apenas transações ativas
void list_active_finance(void) {
    printf("=== TRANSAÇÕES ATIVAS ===\n\n");
    FILE *file = fopen(FILE_NAME_FINANCE, "rb");
    if (!file) {
        printf("Erro ao abrir arquivo ou nenhum dado cadastrado.\n");
        return;
    }
    
    Finance finance;
    int count = 0;
    while (fread(&finance, sizeof(Finance), 1, file)) {
        if (finance.status) {
            print_finance(&finance);
            count++;
        }
    }
    
    if (count == 0) {
        printf("Nenhuma transação ativa encontrada.\n");
    }
    fclose(file);
}