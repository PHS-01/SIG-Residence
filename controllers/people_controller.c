#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "people.h"
#include "config.h"
#include "menu_borders.h"
#include "terminal_control.h"

// VARIÁVEIS GLOBAIS
// A "cabeça" da lista fica aqui. Inicialmente vazia (NULL).
PeopleNode *head_people = NULL; 

static int search_id = -1;

// FUNÇÕES DE GERENCIAMENTO DA LISTA

// Carrega do arquivo para a RAM (Chamar no início do programa)
void load_people_list() {
    // Se a lista já estiver carregada, não faz nada (evita duplicação)
    if (head_people != NULL) return;

    FILE *file = fopen(FILE_NAME_PEOPLE, "rb");
    if (!file) return; 

    People temp_data;
    PeopleNode *ultimo = NULL;

    while (fread(&temp_data, sizeof(People), 1, file)) {
        PeopleNode *novo = (PeopleNode*) malloc(sizeof(PeopleNode));
        novo->data = temp_data;
        novo->next = NULL;

        if (head_people == NULL) {
            head_people = novo; // Primeiro da lista
        } else {
            ultimo->next = novo; // Liga o anterior ao novo
        }
        ultimo = novo;
    }
    
    fclose(file);
}

// Salva da RAM para o Arquivo
void save_people_list() {
    FILE *file = fopen(FILE_NAME_PEOPLE, "wb"); // "wb" zera o arquivo
    if (!file) return;

    PeopleNode *atual = head_people;
    while (atual != NULL) {
        fwrite(&atual->data, sizeof(People), 1, file);
        atual = atual->next;
    }
    fclose(file);
}

// Adiciona uma pessoa na lista e salva
int create_person(People new_person) {
    // Cria o nó na memória
    PeopleNode *novo = (PeopleNode*) malloc(sizeof(PeopleNode));
    novo->data = new_person;
    
    // Insere no INÍCIO 
    novo->next = head_people;
    head_people = novo;
    
    // Persiste no disco
    save_people_list();
    return 1; // Sucesso
}

// Busca uma pessoa na lista pelo ID e retorna ponteiro para os DADOS
People* find_person_by_id(int id) {
    PeopleNode *atual = head_people;
    while (atual != NULL) {
        if (atual->data.id == id) {
            return &atual->data; // Retorna o endereço do dado dentro do nó
        }
        atual = atual->next;
    }
    return NULL; // Não achou
}

// Gera ID baseado no maior ID da lista
int generate_people_id(void) {
    int max_id = 0;
    PeopleNode *atual = head_people;
    
    while (atual != NULL) {
        if (atual->data.id > max_id) {
            max_id = atual->data.id;
        }
        atual = atual->next;
    }
    return max_id + 1;
}

// Remove fisicamente um nó da lista e salva a alteração no disco
int remove_person_from_list(int id) {
    PeopleNode *atual = head_people;
    PeopleNode *anterior = NULL;

    while (atual != NULL) {
        if (atual->data.id == id) {
            if (anterior == NULL) {
                // Caso 1: O nó a ser apagado é a CABEÇA da lista
                head_people = atual->next;
            } else {
                // Caso 2: O nó está no meio ou no fim
                // O anterior pula o atual e aponta para o próximo
                anterior->next = atual->next;
            }
            
            free(atual);        // Libera a memória RAM
            save_people_list(); // Reescreve o arquivo sem esse dado
            return 1;           // Sucesso
        }
        
        // Avança os ponteiros
        anterior = atual;
        atual = atual->next;
    }
    
    return 0; // Não encontrou
}

void free_people_list(void) {
    PeopleNode *atual = head_people;
    while (atual != NULL) {
        PeopleNode *temp = atual;
        atual = atual->next;
        free(temp); // Libera o nó atual da memória
    }
    head_people = NULL; // Zera o ponteiro global
}

// FUNÇÕES DE HELPER / MATCH

void set_search_id(int id) {
    search_id = id;
}

int match_people_by_id(const void *data) {
    People *p = (People *)data;
    return (p->id == search_id);
}

// FUNÇÕES DE RELATÓRIO / VISUALIZAÇÃO

void print_people_detail(const void *data) {
    People *p = (People *)data;
    const char *status_text = p->status ? "Ativo" : "Inativo";
    
    printf("╔══════════════════════════════════════════════════════════════╗\n");
    printf("║                     DETALHES DA PESSOA                       ║\n");
    printf("╠══════════════════════════════════════════════════════════════╣\n");
    print_detail_line_int("ID:", p->id, 3, 56);
    print_detail_line("Nome:", p->name, 6, 53);
    print_detail_line("Data de Nascimento:", p->birth_date, 19, 40);
    print_detail_line("Email:", p->email, 7, 52);
    print_detail_line("Telefone:", p->phone, 10, 49);
    print_detail_line("Status:", status_text, 8, 51);
    printf("╚══════════════════════════════════════════════════════════════╝\n");
}

void print_people_table(const void *data) {
    People *p = (People *)data;
    const char *status_text = p->status ? "Ativo" : "Inativo";
    
    printf("║ ");
    printf("%-4d ║ ", p->id);
    print_padded_string(p->name, 27);
    printf(" ║ ");
    print_padded_string(p->birth_date, 12);
    printf(" ║ ");
    print_padded_string(p->email, 28);
    printf(" ║ ");
    print_padded_string(p->phone, 16);
    printf(" ║ ");
    print_padded_string(status_text, 9);
    printf(" ║\n");
}

// Listagem Paginada usando a LISTA DINÂMICA
void list_people_paginated(bool active_only) {
    if (head_people == NULL) {
        print_warning("Nenhum registro encontrado (Lista Vazia).");
        // wait_for_enter();
        return;
    }

    // Conta registros (Na RAM)
    int total_records = 0;
    PeopleNode *atual = head_people;
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
        const char* title = active_only ? "RELATORIO DE PESSOAS (ATIVAS)" : "RELATORIO DE PESSOAS (TODAS)";
        printf("╔═════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
        printf("║ %-111s ║\n", title);
        printf("║ Página %d de %d - Total de registros: %-75d ║\n", current_page, total_pages, total_records);
        printf("╠══════╦═════════════════════════════╦══════════════╦══════════════════════════════╦══════════════════╦═══════════╣\n");
        printf("║  ID  ║ Nome                        ║  Nascimento  ║ Email                        ║ Telefone         ║ Status    ║\n");
        printf("╠══════╬═════════════════════════════╬══════════════╬══════════════════════════════╬══════════════════╬═══════════╣\n");

        // 2. Navegar até a página atual
        atual = head_people;
        int skipped = 0;
        int printed = 0;
        int start_index = (current_page - 1) * ITEMS_PER_PAGE;

        while (atual != NULL && printed < ITEMS_PER_PAGE) {
            if (!active_only || atual->data.status) {
                if (skipped < start_index) {
                    skipped++;
                } else {
                    print_people_table(&atual->data);
                    printed++;
                }
            }
            atual = atual->next;
        }

        printf("╚══════╩═════════════════════════════╩══════════════╩══════════════════════════════╩══════════════════╩═══════════╝\n");
        printf("\n[A] Anterior  [P] Próxima  [0] Sair\n");
        
        option = get_keypress();

        if ((option == 'p' || option == 'P') && current_page < total_pages) current_page++;
        else if ((option == 'a' || option == 'A') && current_page > 1) current_page--;

    } while (option != '0');
}

// Aniversariantes por Mês (Usando a Lista Dinâmica)
void list_birthdays_by_month(void) {
    int month;
    printf("Digite o mês (1-12): ");
    
    // Pequena correção para ler int de forma segura
    if (!read_int_input(NULL, &month)) {
         print_error("Entrada inválida.");
         return;
    }

    if (month < 1 || month > 12) {
        print_error("Mês inválido. Digite um número entre 1 e 12.");
        return;
    }

    printf("╔═════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                   R E L A T Ó R I O   P O R   M Ê S                                             ║\n");
    printf("╠═════════════════════════════════════════════════════════════════════════════════════════════════════════════════╣\n");

    PeopleNode *atual = head_people;
    int count = 0;

    // Varre a lista na RAM
    while (atual != NULL) {
        if (atual->data.status) {
            int d, m, y;
            sscanf(atual->data.birth_date, "%d/%d/%d", &d, &m, &y);
            
            if (m == month) {
                print_people_table(&atual->data);
                count++;
            }
        }
        atual = atual->next;
    }
    printf("╚═════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("Total: %d\n", count);
    wait_for_enter(); // Pausa para ver o resultado
}

// Aniversariantes por Ano (Usando a Lista Dinâmica)
void list_birthdays_by_year(void) {
    int year;
    printf("Digite o ano de nascimento: ");
    
    if (!read_int_input(NULL, &year)) return;

    printf("╔═════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                   R E L A T Ó R I O   P O R   A N O                                             ║\n");
    printf("╠═════════════════════════════════════════════════════════════════════════════════════════════════════════════════╣\n");

    PeopleNode *atual = head_people;
    int count = 0;

    while (atual != NULL) {
        if (atual->data.status) {
            int d, m, y;
            sscanf(atual->data.birth_date, "%d/%d/%d", &d, &m, &y);
            
            if (y == year) {
                print_people_table(&atual->data);
                count++;
            }
        }
        atual = atual->next;
    }
    printf("╚═════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("Total: %d\n", count);
    wait_for_enter();
}