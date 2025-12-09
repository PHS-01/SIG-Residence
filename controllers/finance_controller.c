#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "people.h"
#include "finance.h"
#include "config.h"
#include "menu_borders.h"
#include "terminal_control.h"

FinanceNode *head_finance = NULL;

// FUNÇÕES DE GERENCIAMENTO DA LISTA

// Carrega do arquivo para a RAM
void finance_load_file(void) {
    // Se a lista já está carregada, não recarregar
    if (head_finance != NULL) return;

    FILE *file = fopen(FILE_NAME_FINANCE, "rb");
    if (!file) return;  // Arquivo não existe → OK, lista vazia

    // --- Verificação: arquivo vazio ---
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    if (size == 0) {
        fclose(file);
        return;  // Arquivo vazio → lista permanece vazia
    }
    rewind(file); // Volta para o início para leitura
    // ------------------------------------

    Finance temp_data;
    FinanceNode *ultimo = NULL;

    // Lê cada registro do arquivo e monta a lista
    while (fread(&temp_data, sizeof(Finance), 1, file)) {
        FinanceNode *novo =(FinanceNode*) malloc(sizeof(FinanceNode));
        if (!novo) {
            fclose(file);
            return;
        }

        novo->data = temp_data;
        novo->next = NULL;

        if (head_finance == NULL){
            head_finance = novo;
        }
        else{
            ultimo->next = novo;
        }

        ultimo = novo;
    }

    fclose(file);
}

void finance_save_append(FinanceNode *novo_no) {
    if (!novo_no) return;

    FILE *file = fopen(FILE_NAME_FINANCE, "ab");
    if (!file) return;

    fwrite(&novo_no->data, sizeof(Finance), 1, file);

    fclose(file);
}
// Salva da RAM para o Arquivo
void finance_save_file(void) {
    FILE *file = fopen(FILE_NAME_FINANCE, "wb");
    if (!file) return;

    FinanceNode *atual = head_finance;
    while (atual != NULL) {
        fwrite(&atual->data, sizeof(Finance), 1, file);
        atual = atual->next;
    }
    fclose(file);
}

// Adiciona uma transação na lista (inserção no final) e salva
int finance_list_insert(Finance new_finance) {
    // Cria o nó na memória
    FinanceNode *novo = (FinanceNode*) malloc(sizeof(FinanceNode));
    if (!novo) {
        return 0; // Falha na alocação
    }
    
    novo->data = new_finance;
    novo->next = NULL;

    // Se a lista está vazia, insere no início
    if (head_finance == NULL) {
        head_finance = novo;
    } else {
        // Encontra o último nó
        FinanceNode *atual = head_finance;
        while (atual->next != NULL) {
            atual = atual->next;
        }
        // Insere no final
        atual->next = novo;
    }

    finance_save_append(novo);
    return 1; // Sucesso
}

// Busca uma transação na lista pelo ID
Finance *finance_list_find(int id) {
    FinanceNode *atual = head_finance;
    
    while (atual != NULL) {
        if (atual->data.id == id) {
            return &atual->data;  // Retorna endereço do dado dentro do nó
        }
        atual = atual->next;
    }

    return NULL; // Não encontrado
}

// Remove fisicamente um nó da lista
int finance_list_remove(int id) {
    FinanceNode *atual = head_finance;
    FinanceNode *anterior = NULL;

    while (atual != NULL) {
        if (atual->data.id == id) {
            // Caso 1: removendo o primeiro nó
            if (anterior == NULL) {
                head_finance = atual->next;
            }
            // Caso 2: removendo nó do meio/fim
            else {
                anterior->next = atual->next;
            }

            free(atual);               // libera o nó da lista dinâmica
            finance_save_file();       // reescreve o arquivo atualizado
            return 1;                  // sucesso
        }

        // avança ponteiros
        anterior = atual;
        atual = atual->next;
    }

    return 0; // não encontrou
}

// Libera toda a memória alocada para a lista
void free_finance_list(void) {
    FinanceNode *atual = head_finance;

    while (atual != NULL) {
        FinanceNode *temp = atual;
        atual = atual->next;
        free(temp); // libera o nó atual da lista
    }

    head_finance = NULL; // zera o ponteiro global
}

void finance_list_print(int (*match)(const void *)) {
    FinanceNode *node = head_finance;

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

// Gera ID baseado no maior ID da lista
int generate_finance_id(void) {
    int max_id = 0;
    FinanceNode *atual = head_finance;
    
    while (atual != NULL) {
        if (atual->data.id > max_id) {
            max_id = atual->data.id;
        }
        atual = atual->next;
    }
    return max_id + 1;
}

// Função para contar quantas finanças uma pessoa possui
int count_finance_by_people_id(int people_id) {
    if (people_id <= 0) return 0;
    
    int count = 0;
    FinanceNode *atual = head_finance;
    
    while (atual != NULL) {
        if (atual->data.people_id == people_id && atual->data.status) {
            count++;
        }
        atual = atual->next;
    }
    
    return count;
}

int delete_finance_by_people_id(int people_id) {
    if (people_id <= 0) return 0;
    
    FinanceNode *atual = head_finance;
    FinanceNode *anterior = NULL;
    int deleted_count = 0;
    
    while (atual != NULL) {
        if (atual->data.people_id == people_id) {
            FinanceNode *to_delete = atual;
            
            if (anterior == NULL) {
                // Removendo do início
                head_finance = atual->next;
                atual = head_finance;
            } else {
                // Removendo do meio/fim
                anterior->next = atual->next;
                atual = anterior->next;
            }
            
            free(to_delete);
            deleted_count++;
        } else {
            anterior = atual;
            atual = atual->next;
        }
    }
    
    if (deleted_count > 0) {
        finance_save_file();
    }
    
    return deleted_count;
}

// Função para listar finanças de uma pessoa específica
void list_finance_by_people_id(int people_id) {
    if (people_id <= 0) return;
    
    FinanceNode *atual = head_finance;
    int count = 0;
    
    printf("\n╔══════════════════════════════════════════════════════════════╗\n");
    printf("║               TRANSAÇÕES FINANCEIRAS ASSOCIADAS              ║\n");
    printf("╠══════════════════════════════════════════════════════════════╣\n");
    
    while (atual != NULL) {
        if (atual->data.people_id == people_id) {
            count++;
            const char *type_text = (atual->data.type == FINANCE_RECEITA) ? "Receita" : "Despesa";
            printf("║ %-4d | %-25s | R$ %8.2f | %-11s ║\n", 
                   atual->data.id, atual->data.description, atual->data.value, type_text);
        }
        atual = atual->next;
    }
    
    if (count == 0) {
        printf("║           Nenhuma transação encontrada              ║\n");
    }
    
    printf("╚══════════════════════════════════════════════════════════════╝\n");
    printf("Total de transações: %d\n", count);
}

// Imprime os dados completos de uma transação (para consulta individual)
void print_finance_detail(const void *data) {
    Finance *f = (Finance *)data;
    
    const char *type_text = (f->type == FINANCE_RECEITA) ? "Receita" : "Despesa";
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
    
    const char *type_text = (f->type == FINANCE_RECEITA) ? "Receita" : "Despesa";
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

// LISTAGEM PAGINADA USANDO A LISTA DINÂMICA
void list_finance_paginated(bool active_only) {
    if (head_finance == NULL) {
        print_warning("Nenhum registro encontrado (Lista Vazia).");
        // wait_for_enter();
        return;
    }

    // Conta registros (Na RAM)
    int total_records = 0;
    FinanceNode *atual = head_finance;
    while (atual != NULL) {
        if (!active_only || atual->data.status) {
            total_records++;
        }
        atual = atual->next;
    }

    if (total_records == 0) {
        print_warning("Nenhum registro encontrado.");
        // wait_for_enter();
        return;
    }

    // Configuração Paginação
    const int ITEMS_PER_PAGE = 10;
    int total_pages = (total_records + ITEMS_PER_PAGE - 1) / ITEMS_PER_PAGE;
    int current_page = 1;
    char option;

    do {
        clear_screen();
        const char* title = active_only ? "RELATORIO DE FINANÇAS (ATIVAS)" : "RELATORIO DE FINANÇAS (TODAS)";
        printf("╔═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
        printf("║ %-118s ║\n", title);
        printf("║ Página %d de %d - Total de registros: %-81d ║\n", current_page, total_pages, total_records);
        printf("╠══════╦═══════════╦═════════════════════════╦════════════╦══════════════╦══════════════════════╦═══════════╦═══════════╣\n");
        printf("║  ID  ║ ID Pessoa ║ Descrição               ║ Valor      ║ Data         ║ Categoria            ║ Tipo      ║ Status    ║\n");
        printf("╠══════╬═══════════╬═════════════════════════╬════════════╬══════════════╬══════════════════════╬═══════════╬═══════════╣\n");

        // 2. Navegar até a página atual
        atual = head_finance;
        int skipped = 0;
        int printed = 0;
        int start_index = (current_page - 1) * ITEMS_PER_PAGE;

        while (atual != NULL && printed < ITEMS_PER_PAGE) {
            if (!active_only || atual->data.status) {
                if (skipped < start_index) {
                    skipped++;
                } else {
                    print_finance_table(&atual->data);
                    printed++;
                }
            }
            atual = atual->next;
        }

        printf("╚══════╩═══════════╩═════════════════════════╩════════════╩══════════════╩══════════════════════╩═══════════╩═══════════╝\n");
        printf("\n[A] Anterior  [P] Próxima  [0] Sair\n");
        
        option = get_keypress();

        if ((option == 'p' || option == 'P') && current_page < total_pages) current_page++;
        else if ((option == 'a' || option == 'A') && current_page > 1) current_page--;

    } while (option != '0');
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
    printf("╠══════╦═══════════╦═════════════════════════╦════════════╦══════════════╦══════════════════════╦═══════════╦═══════════╣\n");
    printf("║  ID  ║ ID Pessoa ║ Descrição               ║ Valor      ║ Data         ║ Categoria            ║ Tipo      ║ Status    ║\n");
    printf("╠══════╬═══════════╬═════════════════════════╬════════════╬══════════════╬══════════════════════╬═══════════╬═══════════╣\n");

    FinanceNode *atual = head_finance;
    int count = 0;
    float total = 0;

    while (atual != NULL) {
        if (atual->data.status && strcasecmp(atual->data.category, categoria) == 0) {
            print_finance_table(&atual->data);
            count++;
            total += atual->data.value;
        }
        atual = atual->next;
    }

    printf("╚══════╩═══════════╩═════════════════════════╩════════════╩══════════════╩══════════════════════╩═══════════╩═══════════╝\n");
    printf("Total de transações na categoria '%s': %d\n", categoria, count);
    printf("Valor total: R$ %.2f\n", total);
}

// Relatório de finanças por pessoa (saldo)
void list_finance_by_person(void) {
    if (head_finance == NULL) {
        print_error("Nenhuma transação cadastrada.");
        return;
    }

    printf("╔═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                  RELATÓRIO DE FINANÇAS GERAIS POR PESSOA                                              ║\n");
    printf("╠══════╦══════════════════════════════╦═════════════════════╦══════════════════════════╦════════════════════════════════╣\n");
    printf("║  ID  ║   Nome                       ║ Receitas            ║ Despesas                 ║ Saldo                          ║\n");
    printf("╠══════╬══════════════════════════════╬═════════════════════╬══════════════════════════╬════════════════════════════════╣\n");

    // Primeiro, precisamos obter a lista de pessoas
    // Vou assumir que você tem uma função para obter todas as pessoas ativas
    // Se não tiver, precisará carregar o arquivo de pessoas
    
    FILE *fp_people = fopen(FILE_NAME_PEOPLE, "rb");
    if (!fp_people) {
        print_error("Erro ao abrir arquivo de pessoas.");
        return;
    }
    
    People p;
    while (fread(&p, sizeof(People), 1, fp_people)) {
        if (!p.status) continue;

        float total_r = 0, total_d = 0;
        
        // Calcular totais para esta pessoa
        FinanceNode *atual = head_finance;
        while (atual != NULL) {
            if (atual->data.status && atual->data.people_id == p.id) {
                if (atual->data.type == FINANCE_RECEITA) {
                    total_r += atual->data.value;
                } else {
                    total_d += atual->data.value;
                }
            }
            atual = atual->next;
        }

        printf("║ %-4d ║ %-28s ║ %-19.2f ║ %-24.2f ║ %-30.2f ║\n",
               p.id, p.name, total_r, total_d, total_r - total_d);
    }
    
    printf("╚══════╩══════════════════════════════╩═════════════════════╩══════════════════════════╩════════════════════════════════╝\n");
    fclose(fp_people);
}
