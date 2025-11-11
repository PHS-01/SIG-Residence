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

// Função para contar quantas finanças uma pessoa possui
int count_finance_by_people_id(int people_id) {
    if (people_id <= 0) {
        return 0;
    }
    
    FILE *file = fopen(FILE_NAME_FINANCE, "rb");
    if (!file) {
        return 0;
    }
    
    Finance finance;
    int count = 0;
    
    while (fread(&finance, sizeof(Finance), 1, file)) {
        if (finance.people_id == people_id) {
            count++;
        }
    }
    
    fclose(file);
    return count;
}

// Função para excluir fisicamente todas as finanças de uma pessoa (versão melhorada)
int delete_finance_by_people_id(int people_id) {
    if (people_id <= 0) {
        return 0;
    }
    
    FILE *file = fopen(FILE_NAME_FINANCE, "rb");
    if (!file) {
        return 0; // Nenhum arquivo, nada para excluir
    }
    
    // Verificar primeiro se há registros para excluir
    Finance finance;
    int records_to_delete = 0;
    while (fread(&finance, sizeof(Finance), 1, file)) {
        if (finance.people_id == people_id) {
            records_to_delete++;
        }
    }
    
    if (records_to_delete == 0) {
        fclose(file);
        return 0; // Nada para excluir
    }
    
    // Voltar ao início do arquivo
    rewind(file);
    
    // Criar arquivo temporário
    FILE *temp_file = fopen("temp_finance.dat", "wb");
    if (!temp_file) {
        fclose(file);
        return 0;
    }
    
    int deleted_count = 0;
    int error_occurred = 0;
    
    // Copiar todos os registros exceto os da pessoa especificada
    while (fread(&finance, sizeof(Finance), 1, file)) {
        if (finance.people_id != people_id) {
            if (fwrite(&finance, sizeof(Finance), 1, temp_file) != 1) {
                error_occurred = 1;
                break;
            }
        } else {
            deleted_count++;
        }
    }
    
    fclose(file);
    fclose(temp_file);
    
    if (error_occurred) {
        remove("temp_finance.dat");
        return 0;
    }
    
    // Substituir arquivo original pelo temporário
    if (remove(FILE_NAME_FINANCE) != 0) {
        remove("temp_finance.dat");
        return 0;
    }
    
    if (rename("temp_finance.dat", FILE_NAME_FINANCE) != 0) {
        // Tentar restaurar do backup se houver
        // rename(backup_name, FILE_NAME_FINANCE);
        return 0;
    }
    
    return deleted_count;
}

// Função para listar finanças de uma pessoa específica
void list_finance_by_people_id(int people_id) {
    if (people_id <= 0) {
        return;
    }
    
    FILE *file = fopen(FILE_NAME_FINANCE, "rb");
    if (!file) {
        return;
    }
    
    Finance finance;
    int count = 0;
    
    printf("\n╔══════════════════════════════════════════════════════════════╗\n");
    printf("║               TRANSAÇÕES FINANCEIRAS ASSOCIADAS              ║\n");
    printf("╠══════════════════════════════════════════════════════════════╣\n");
    
    while (fread(&finance, sizeof(Finance), 1, file)) {
        if (finance.people_id == people_id) {
            count++;
            const char *type_text = (finance.type == 'R') ? "Receita" : "Despesa";
            printf("║ %-4d | %-25s | R$ %8.2f | %-11s ║\n", 
                   finance.id, finance.description, finance.value, type_text);
        }
    }
    
    if (count == 0) {
        printf("║           Nenhuma transação encontrada              ║\n");
    }
    
    printf("╚══════════════════════════════════════════════════════════════╝\n");
    printf("Total de transações: %d\n", count);
    
    fclose(file);
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
    printf("║ ID de Pessoa: %-46d ║\n", f->people_id);
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
    printf("║ %-4d ║ %-9d ║ %-23s ║ %-10.2f ║ %-12s ║ %-20s ║ %-9s ║ %-9s ║\n",
           f->id, f->people_id, f->description, f->value, f->date, f->category, type_text, status_text);
}

void list_all_finance(void) {
    printf("╔═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                        R E L A T Ó R I O    F I N A N C E I R O                                       ║\n");
    printf("║                                                                                                                       ║\n");
    printf("╠══════╦═══════════╦═════════════════════════╦════════════╦══════════════╦══════════════════════╦═══════════╦═══════════╣\n");
    printf("║  ID  ║ ID Pessoa ║ Descrição               ║ Valor      ║ Data         ║ Categoria            ║ Tipo      ║ Status    ║\n");
    printf("╠══════╬═══════════╬═════════════════════════╬════════════╬══════════════╬══════════════════════╬═══════════╬═══════════╣\n");

    FILE *file = fopen(FILE_NAME_FINANCE, "rb");
    if (!file) {
        printf("╚══════╩═══════════╩═════════════════════════╩════════════╩══════════════╩══════════════════════╩═══════════╩═══════════╝\n");
        print_error("Nenhum dado cadastrado ou erro ao abrir arquivo.");
        return;
    }
    
    Finance finance;
    int count = 0;
    while (fread(&finance, sizeof(Finance), 1, file)) {
        print_finance_table(&finance);
        count++;
    }
    
    printf("╚══════╩═══════════╩═════════════════════════╩════════════╩══════════════╩══════════════════════╩═══════════╩═══════════╝\n");
    printf("Total de registros: %d\n", count);
    
    fclose(file);
}

// Lista apenas transações ativas
void list_active_finance(void) {
    printf("╔═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                        R E L A T Ó R I O    F I N A N C E I R O                                       ║\n");
    printf("║                                                                                                                       ║\n");
    printf("╠══════╦═══════════╦═════════════════════════╦════════════╦══════════════╦══════════════════════╦═══════════╦═══════════╣\n");
    printf("║  ID  ║ ID Pessoa ║ Descrição               ║ Valor      ║ Data         ║ Categoria            ║ Tipo      ║ Status    ║\n");
    printf("╠══════╬═══════════╬═════════════════════════╬════════════╬══════════════╬══════════════════════╬═══════════╬═══════════╣\n");
    
    FILE *file = fopen(FILE_NAME_FINANCE, "rb");
    if (!file) {
        printf("╚══════╩═══════════╩═════════════════════════╩════════════╩══════════════╩══════════════════════╩═══════════╩═══════════╝\n");
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
    
    printf("╚══════╩═══════════╩═════════════════════════╩════════════╩══════════════╩══════════════════════╩═══════════╩═══════════╝\n");
    printf("Total de registros ativos: %d\n", count);
    
    fclose(file);
}