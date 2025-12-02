#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "people.h"
#include "finance.h"
#include "config.h"
#include "menu_borders.h"
#include "terminal_control.h"

FinanceNode *finance_list = NULL;

void finance_list_insert(Finance f) {
    FinanceNode *node = malloc(sizeof(FinanceNode));
    node->data = f;
    node->next = NULL;

    if (finance_list == NULL) {
        finance_list = node;
        return;
    }

    FinanceNode *aux = finance_list;
    while (aux->next != NULL)
        aux = aux->next;

    aux->next = node;
}

void finance_load_file() {
    FILE *file = fopen(FILE_NAME_FINANCE, "rb");
    if (!file) return;

    Finance f;
    while (fread(&f, sizeof(Finance), 1, file))
        finance_list_insert(f);

    fclose(file);
}

void finance_save_file() {
    FILE *file = fopen(FILE_NAME_FINANCE, "wb");
    if (!file) return;

    FinanceNode *aux = finance_list;
    while (aux) {
        fwrite(&aux->data, sizeof(Finance), 1, file);
        aux = aux->next;
    }

    fclose(file);
}

FinanceNode *finance_list_find(int (*match)(const void *)) {
    FinanceNode *node = finance_list;

    while (node) {
        if (match(&node->data))
            return node;
        node = node->next;
    }

    return NULL;
}


void finance_list_print(int (*match)(const void *)) {
    FinanceNode *node = finance_list;

    while (node) {
        if (match(&node->data)) {
            Finance f = node->data;
            printf("%d - %s - %.2f\n", f.id, f.description, f.value);
        }
        node = node->next;
    }
}
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
    
    // Para o valor, formatando com R$
    char value_str[30];
    snprintf(value_str, sizeof(value_str), "R$ %.2f", f->value);
    
    printf("╔══════════════════════════════════════════════════════════════╗\n");
    printf("║                    DETALHES DA TRANSAÇÃO                     ║\n");
    printf("╠══════════════════════════════════════════════════════════════╣\n");
    
    print_detail_line_int("ID:", f->id, 3, 56);
    print_detail_line_int("ID de Pessoa:", f->people_id, 13, 46);
    print_detail_line("Descrição:", f->description, 11, 48);
    print_detail_line("Valor:", value_str, 7, 52);
    print_detail_line("Data:", f->date, 6, 53);
    print_detail_line("Categoria:", f->category, 11, 48);
    print_detail_line("Tipo:", type_text, 6, 53);
    print_detail_line("Status:", status_text, 8, 51);
    
    printf("╚══════════════════════════════════════════════════════════════╝\n");
}

// Imprime os dados da transação em formato de tabela
void print_finance_table(const void *data) {
    Finance *f = (Finance *)data;
    
    const char *type_text = (f->type == 'R' || f->type == 'r') ? "Receita" : "Despesa";
    const char *status_text = f->status ? "Ativo" : "Inativo";
    
    printf("║ ");
    printf("%-4d ║ ", f->id);
    printf("%-9d ║ ", f->people_id);
    print_padded_string(f->description, 23);
    printf(" ║ ");
    printf("%-10.2f ║ ", f->value);
    print_padded_string(f->date, 12);
    printf(" ║ ");
    print_padded_string(f->category, 20);
    printf(" ║ ");
    print_padded_string(type_text, 9);
    printf(" ║ ");
    print_padded_string(status_text, 9);
    printf(" ║\n");
}

void list_finance_paginated(bool active_only) {
    FILE *file = fopen(FILE_NAME_FINANCE, "rb");
    if (!file) {
        print_error("Nenhum dado cadastrado ou erro ao abrir arquivo.");
        wait_for_enter();
        return;
    }

    // Conta o total de registros válidos para o filtro
    int total_records = 0;
    Finance f;
    while (fread(&f, sizeof(Finance), 1, file)) {
        if (!active_only || f.status) {
            total_records++;
        }
    }

    if (total_records == 0) {
        fclose(file);
        print_warning("Nenhum registro encontrado.");
        wait_for_enter();
        return;
    }

    // Configurações da paginação
    const int ITEMS_PER_PAGE = 10;
    int total_pages = (total_records + ITEMS_PER_PAGE - 1) / ITEMS_PER_PAGE;
    int current_page = 1;
    char option;

    do {
        clear_screen();
        
        // Cabeçalho
        const char* title = active_only ? "RELATORIO DE FINANÇAS (ATIVAS)" : "RELATORIO DE FINANÇAS (TODAS)";
        printf("╔═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
        printf("║ %-118s ║\n", title);
        printf("║ Página %d de %d - Total de registros: %-81d ║\n", current_page, total_pages, total_records);
        printf("╠══════╦═══════════╦═════════════════════════╦════════════╦══════════════╦══════════════════════╦═══════════╦═══════════╣\n");
        printf("║  ID  ║ ID Pessoa ║ Descrição               ║ Valor      ║ Data         ║ Categoria            ║ Tipo      ║ Status    ║\n");
        printf("╠══════╬═══════════╬═════════════════════════╬════════════╬══════════════╬══════════════════════╬═══════════╬═══════════╣\n");


        // Posiciona e lê registros da página atual
        rewind(file); // Volta ao inicio do arquivo
        int skipped = 0;
        int printed = 0;
        int start_index = (current_page - 1) * ITEMS_PER_PAGE;

        while (fread(&f, sizeof(Finance), 1, file) && printed < ITEMS_PER_PAGE) {
            // Aplica o filtro (ativo ou todos)
            if (!active_only || f.status) {
                // Pula os registros das páginas anteriores
                if (skipped < start_index) {
                    skipped++;
                    continue;
                }
                
                // Imprime o registro atual
                print_finance_table(&f);
                printed++;
            }
        }

        printf("╚══════╩═══════════╩═════════════════════════╩════════════╩══════════════╩══════════════════════╩═══════════╩═══════════╝\n");
        
        // Rodapé de Navegação
        printf("\n[A] Anterior  [P] Próxima  [0] Sair\n");
        
        option = get_keypress(); // Usa função de capturar tecla sem enter

        // Lógica de navegação
        if ((option == 'p' || option == 'P') && current_page < total_pages) {
            current_page++;
        } else if ((option == 'a' || option == 'A') && current_page > 1) {
            current_page--;
        }

    } while (option != '0');

    fclose(file);
}

// void list_all_finance(void) {
//     printf("╔═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
//     printf("║                                        R E L A T Ó R I O    F I N A N C E I R O                                       ║\n");
//     printf("║                                                                                                                       ║\n");
//     printf("╠══════╦═══════════╦═════════════════════════╦════════════╦══════════════╦══════════════════════╦═══════════╦═══════════╣\n");
//     printf("║  ID  ║ ID Pessoa ║ Descrição               ║ Valor      ║ Data         ║ Categoria            ║ Tipo      ║ Status    ║\n");
//     printf("╠══════╬═══════════╬═════════════════════════╬════════════╬══════════════╬══════════════════════╬═══════════╬═══════════╣\n");

//     FILE *file = fopen(FILE_NAME_FINANCE, "rb");
//     if (!file) {
//         printf("╚══════╩═══════════╩═════════════════════════╩════════════╩══════════════╩══════════════════════╩═══════════╩═══════════╝\n");
//         print_error("Nenhum dado cadastrado ou erro ao abrir arquivo.");
//         return;
//     }
    
//     Finance finance;
//     int count = 0;
//     while (fread(&finance, sizeof(Finance), 1, file)) {
//         print_finance_table(&finance);
//         count++;
//     }
    
//     printf("╚══════╩═══════════╩═════════════════════════╩════════════╩══════════════╩══════════════════════╩═══════════╩═══════════╝\n");
//     printf("Total de registros: %d\n", count);
    
//     fclose(file);
// }

// // Lista apenas transações ativas
// void list_active_finance(void) {
//     printf("╔═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
//     printf("║                                        R E L A T Ó R I O    F I N A N C E I R O                                       ║\n");
//     printf("║                                                                                                                       ║\n");
//     printf("╠══════╦═══════════╦═════════════════════════╦════════════╦══════════════╦══════════════════════╦═══════════╦═══════════╣\n");
//     printf("║  ID  ║ ID Pessoa ║ Descrição               ║ Valor      ║ Data         ║ Categoria            ║ Tipo      ║ Status    ║\n");
//     printf("╠══════╬═══════════╬═════════════════════════╬════════════╬══════════════╬══════════════════════╬═══════════╬═══════════╣\n");
    
//     FILE *file = fopen(FILE_NAME_FINANCE, "rb");
//     if (!file) {
//         printf("╚══════╩═══════════╩═════════════════════════╩════════════╩══════════════╩══════════════════════╩═══════════╩═══════════╝\n");
//         print_error("Nenhum dado cadastrado ou erro ao abrir arquivo.");
//         return;
//     }
    
//     Finance finance;
//     int count = 0;
//     while (fread(&finance, sizeof(Finance), 1, file)) {
//         if (finance.status) {
//             print_finance_table(&finance);
//             count++;
//         }
//     }
    
//     printf("╚══════╩═══════════╩═════════════════════════╩════════════╩══════════════╩══════════════════════╩═══════════╩═══════════╝\n");
//     printf("Total de registros ativos: %d\n", count);
    
//     fclose(file);
// }

void list_finance_by_category(void) {
    char categoria[50];
    
    printf("Digite a categoria para filtrar: ");
    read_string_input("", categoria, sizeof(categoria));

    printf("╔═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                  RELATORIO FINANCEIRO POR CATEGORIA                                                   ║\n");
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
    float total = 0;

    while (fread(&finance, sizeof(Finance), 1, file)) {
        if (!finance.status) continue;

        if (strcasecmp(finance.category, categoria) == 0) {
            print_finance_table(&finance);
            count++;
            total += finance.value;
        }
    }

    printf("╚══════╩═══════════╩═════════════════════════╩════════════╩══════════════╩══════════════════════╩═══════════╩═══════════╝\n");
    printf("Total de transações na categoria '%s': %d\n", categoria, count);
    printf("Valor total: R$ %.2f\n", total);

    fclose(file);
}
void list_finance_by_person(void) {
    FILE *fp_people = fopen(FILE_NAME_PEOPLE, "rb");
    FILE *fp_fin = fopen(FILE_NAME_FINANCE, "rb");

    if (!fp_people || !fp_fin) {
        print_error("Erro ao abrir arquivos de dados.");
        if (fp_people) fclose(fp_people);
        if (fp_fin) fclose(fp_fin);
        return;
    }

    People p;
    Finance f;

 
    printf("╔═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                  RELATÓRIO DE FINANÇAS GERAIS POR PESSOA                                              ║\n");
    printf("║                                                                                                                       ║\n");
    printf("╠══════╦══════════════════════════════╦═════════════════════╦══════════════════════════╦════════════════════════════════╣\n");
    printf("║  ID  ║   Nome                       ║ Receitas            ║ Despesas                 ║ Saldo                          ║\n");
    printf("╠══════╬══════════════════════════════╬═════════════════════╬══════════════════════════╬════════════════════════════════╣\n");

    while (fread(&p, sizeof(People), 1, fp_people)) {
        if (!p.status) continue;

        float total_r = 0, total_d = 0;

        rewind(fp_fin);
        while (fread(&f, sizeof(Finance), 1, fp_fin)) {
            if (f.status && f.people_id == p.id) {
                if (f.type == FINANCE_RECEITA) total_r += f.value;
                else total_d += f.value;
            }
        }

        printf("║ %-4d ║ %-28s ║ %-19.2f ║ %-24.2f ║ %-30.2f ║\n",
               p.id, p.name, total_r, total_d, total_r - total_d);
    }
    printf("╚══════╩══════════════════════════════╩═════════════════════╩══════════════════════════╩════════════════════════════════╝\n");
    fclose(fp_people);
    fclose(fp_fin);
}
