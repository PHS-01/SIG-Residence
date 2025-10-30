#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "finance.h"
#include "config.h"
#include "menu_borders.h"
#include "terminal_control.h"

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

// Imprime os dados completos de uma transação (para consulta individual)
void print_finance_detail(const void *data) {
    Finance *f = (Finance *)data;
    
    const char *type_text = (f->type == 'R' || f->type == 'r') ? "Receita" : "Despesa";
    const char *status_text = f->status ? "Ativo" : "Inativo";
    
    printf("╔══════════════════════════════════════════════════════════════╗\n");
    printf("║                    DETALHES DA TRANSAÇÃO                     ║\n");
    printf("╠══════════════════════════════════════════════════════════════╣\n");
    printf("║ ID: %-56d ║\n", f->id);
    printf("║ Descrição: %-49s ║\n", f->description);
    printf("║ Valor: R$ %-50.2f ║\n", f->value);
    printf("║ Data: %-54s ║\n", f->date);
    printf("║ Categoria: %-49s ║\n", f->category);
    printf("║ Tipo: %-54s ║\n", type_text);
    printf("║ Status: %-52s ║\n", status_text);
    printf("╚══════════════════════════════════════════════════════════════╝\n");
}

// Imprime os dados da transação em formato de tabela
void print_finance_table(const void *data) {
    Finance *f = (Finance *)data;
    
    const char *type_text = (f->type == 'R' || f->type == 'r') ? "Receita" : "Despesa";
    const char *status_text = f->status ? "Ativo" : "Inativo";
    
    // Colunas ajustadas para tabela formatada
    printf("║ %-4d ║ %-27s ║ %-10.2f ║ %-12s ║ %-20s ║ %-9s ║ %-9s ║\n",
           f->id, f->description, f->value, f->date, f->category, type_text, status_text);
}

void list_all_finance(void) {
    printf("╔═══════════════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                  R E L A T Ó R I O    F I N A N C E I R O                                     ║\n");
    printf("║                                                                                                               ║\n");
    printf("╠══════╦═════════════════════════════╦════════════╦══════════════╦══════════════════════╦═══════════╦═══════════╣\n");
    printf("║  ID  ║ Descrição                   ║ Valor      ║ Data         ║ Categoria            ║ Tipo      ║ Status    ║\n");
    printf("╠══════╬═════════════════════════════╬════════════╬══════════════╬══════════════════════╬═══════════╬═══════════╣\n");

    FILE *file = fopen(FILE_NAME_FINANCE, "rb");
    if (!file) {
        printf("╚══════╩═════════════════════════════╩════════════╩══════════════╩══════════════════════╩═══════════╩═══════════╝\n");
        print_error("Nenhum dado cadastrado ou erro ao abrir arquivo.");
        return;
    }
    
    Finance finance;
    int count = 0;
    while (fread(&finance, sizeof(Finance), 1, file)) {
        print_finance_table(&finance);
        count++;
    }
    
    printf("╚══════╩═════════════════════════════╩════════════╩══════════════╩══════════════════════╩═══════════╩═══════════╝\n");
    printf("Total de registros: %d\n", count);
    
    fclose(file);
}

// Lista apenas transações ativas
void list_active_finance(void) {
    printf("╔═══════════════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                             R E L A T Ó R I O    F I N A N C E I R O    A T I V O S                           ║\n");
    printf("║                                                                                                               ║\n");
    printf("╠══════╦═════════════════════════════╦════════════╦══════════════╦══════════════════════╦═══════════╦═══════════╣\n");
    printf("║  ID  ║ Descrição                   ║ Valor      ║ Data         ║ Categoria            ║ Tipo      ║ Status    ║\n");
    printf("╠══════╬═════════════════════════════╬════════════╬══════════════╬══════════════════════╬═══════════╬═══════════╣\n");
    
    FILE *file = fopen(FILE_NAME_FINANCE, "rb");
    if (!file) {
        printf("╚══════╩═════════════════════════════╩════════════╩══════════════╩══════════════════════╩═══════════╩═══════════╝\n");
        print_error("Nenhum dado cadastrado ou erro ao abrir arquivo.");
        return;
    }
    
    Finance finance;
    int count = 0;
    while (fread(&finance, sizeof(Finance), 1, file)) {
        if (finance.status) {
            print_finance_table(&finance);
            count++;
        }
    }
    
    printf("╚══════╩═════════════════════════════╩════════════╩══════════════╩══════════════════════╩═══════════╩═══════════╝\n");
    printf("Total de registros ativos: %d\n", count);
    
    fclose(file);
}