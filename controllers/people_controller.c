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
    
    print_detail_line_int("ID:", p->id, 3, 56);
    print_detail_line("Nome:", p->name, 6, 53);
    print_detail_line("Data de Nascimento:", p->birth_date, 19, 40);
    print_detail_line("Email:", p->email, 7, 52);
    print_detail_line("Telefone:", p->phone, 10, 49);
    print_detail_line("Status:", status_text, 8, 51);
    
    printf("╚══════════════════════════════════════════════════════════════╝\n");
}

// Imprime os dados da pessoa em formato de tabela
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

void list_people_paginated(bool active_only) {
    FILE *file = fopen(FILE_NAME_PEOPLE, "rb");
    if (!file) {
        print_error("Nenhum dado cadastrado ou erro ao abrir arquivo.");
        wait_for_enter();
        return;
    }

    // 1. Contar total de registros válidos para o filtro
    int total_records = 0;
    People p;
    while (fread(&p, sizeof(People), 1, file)) {
        if (!active_only || p.status) {
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
        const char* title = active_only ? "RELATORIO DE PESSOAS (ATIVAS)" : "RELATORIO DE PESSOAS (TODAS)";
        printf("╔═════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
        printf("║ %-111s ║\n", title);
        printf("║ Página %d de %d - Total de registros: %-75d ║\n", current_page, total_pages, total_records);
        printf("╠══════╦═════════════════════════════╦══════════════╦══════════════════════════════╦══════════════════╦═══════════╣\n");
        printf("║  ID  ║ Nome                        ║  Nascimento  ║ Email                        ║ Telefone         ║ Status    ║\n");
        printf("╠══════╬═════════════════════════════╬══════════════╬══════════════════════════════╬══════════════════╬═══════════╣\n");

        // 2. Posicionar e ler registros da página atual
        rewind(file); // Volta ao inicio do arquivo
        int skipped = 0;
        int printed = 0;
        int start_index = (current_page - 1) * ITEMS_PER_PAGE;

        while (fread(&p, sizeof(People), 1, file) && printed < ITEMS_PER_PAGE) {
            // Aplica o filtro (ativo ou todos)
            if (!active_only || p.status) {
                // Pula os registros das páginas anteriores
                if (skipped < start_index) {
                    skipped++;
                    continue;
                }
                
                // Imprime o registro atual
                print_people_table(&p);
                printed++;
            }
        }

        printf("╚══════╩═════════════════════════════╩══════════════╩══════════════════════════════╩══════════════════╩═══════════╝\n");
        
        // Rodapé de Navegação
        printf("\n[A] Anterior  [P] Próxima  [0] Sair\n");
        
        option = get_keypress(); // Usa sua função de capturar tecla sem enter

        // Lógica de navegação
        if ((option == 'p' || option == 'P') && current_page < total_pages) {
            current_page++;
        } else if ((option == 'a' || option == 'A') && current_page > 1) {
            current_page--;
        }

    } while (option != '0');

    fclose(file);
}

// void list_all_people(void) {
//     printf("╔═════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
//     printf("║                                  R E L A T Ó R I O    D E    P E S S O A S                                      ║\n");
//     printf("║                                                                                                                 ║\n");
//     printf("╠══════╦═════════════════════════════╦══════════════╦══════════════════════════════╦══════════════════╦═══════════╣\n");
//     printf("║  ID  ║ Nome                        ║  Nascimento  ║ Email                        ║ Telefone         ║ Status    ║\n");
//     printf("╠══════╬═════════════════════════════╬══════════════╬══════════════════════════════╬══════════════════╬═══════════╣\n");

//     FILE *file = fopen(FILE_NAME_PEOPLE, "rb");
//     if (!file) {
//         printf("╚══════╩═════════════════════════════╩══════════════╩══════════════════════════════╩══════════════════╩═══════════╝\n");
//         print_error("Nenhum dado cadastrado ou erro ao abrir arquivo.");
//         return;
//     }
    
//     People person;
//     int count = 0;
//     while (fread(&person, sizeof(People), 1, file)) {
//         print_people_table(&person);
//         count++;
//     }
    
//     printf("╚══════╩═════════════════════════════╩══════════════╩══════════════════════════════╩══════════════════╩═══════════╝\n");
//     printf("Total de registros: %d\n", count);
    
//     fclose(file);
// }

// // Lista apenas pessoas ativas
// void list_active_people(void) {
//     printf("╔═════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
//     printf("║                             R E L A T Ó R I O   D E   P E S S O A S   A T I V A S                               ║\n");
//     printf("║                                                                                                                 ║\n");
//     printf("╠══════╦═════════════════════════════╦══════════════╦══════════════════════════════╦══════════════════╦═══════════╣\n");
//     printf("║  ID  ║ Nome                        ║  Nascimento  ║ Email                        ║ Telefone         ║ Status    ║\n");
//     printf("╠══════╬═════════════════════════════╬══════════════╬══════════════════════════════╬══════════════════╬═══════════╣\n");
    
//     FILE *file = fopen(FILE_NAME_PEOPLE, "rb");
//     if (!file) {
//         printf("╚══════╩═════════════════════════════╩══════════════╩══════════════════════════════╩══════════════════╩═══════════╝\n");
//         print_error("Nenhum dado cadastrado ou erro ao abrir arquivo.");
//         return;
//     }
    
//     People person;
//     int count = 0;
//     while (fread(&person, sizeof(People), 1, file)) {
//         if (person.status) {
//             print_people_table(&person);
//             count++;
//         }
//     }
    
//     printf("╚══════╩═════════════════════════════╩══════════════╩══════════════════════════════╩══════════════════╩═══════════╝\n");
//     printf("Total de registros ativos: %d\n", count);
    
//     fclose(file);
// }

void list_birthdays_by_month(void) {
    int month;

    printf("Digite o mês (1-12): ");
    scanf("%d", &month);
    clear_input_buffer(); // se você tiver essa função, ajuda com o \n pendente

    if (month < 1 || month > 12) {
        print_error("Mês inválido. Digite um número entre 1 e 12.");
        return;
    }
    printf("╔═════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                   R E L A T Ó R I O   P O R   M Ê S   D E                                       ║\n");
    printf("║                                            N A S C I M E N T O                                                  ║\n");
    printf("╠═════════════════════════════════════════════════════════════════════════════════════════════════════════════════╣\n");
    printf("║ Mês selecionado: %02d                                                                                             ║\n", month);
    printf("╠══════╦═════════════════════════════╦══════════════╦══════════════════════════════╦══════════════════╦═══════════╣\n");
    printf("║  ID  ║ Nome                        ║  Nascimento  ║ Email                        ║ Telefone         ║ Status    ║\n");
    printf("╠══════╬═════════════════════════════╬══════════════╬══════════════════════════════╬══════════════════╬═══════════╣\n");

    FILE *file = fopen(FILE_NAME_PEOPLE, "rb");
    if (!file) {
        printf("╚══════╩═════════════════════════════╩══════════════╩══════════════════════════════╩══════════════════╩═══════════╝\n");
        print_error("Nenhum dado cadastrado ou erro ao abrir arquivo.");
        return;
    }

    People person;
    int count = 0;

    while (fread(&person, sizeof(People), 1, file)) {
        if (!person.status) continue;

        int d, m, y;
        sscanf(person.birth_date, "%d/%d/%d", &d, &m, &y);

        if (m == month) {
            print_people_table(&person);
            count++;
        }
    }

    printf("╚══════╩═════════════════════════════╩══════════════╩══════════════════════════════╩══════════════════╩═══════════╝\n");
    printf("Total de aniversariantes no mês %02d: %d\n", month, count);

    fclose(file);
}
void list_birthdays_by_year() {
    int year;

    printf("Digite o ano de nascimento: ");
    scanf("%d", &year);
    clear_input_buffer(); // se existir no seu sistema

    if (year < 1900 || year > 2100) {
        print_error("Ano inválido! Digite um ano razoável (1900–2100).");
        return;
    }
    printf("╔═════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                   R E L A T Ó R I O   P O R   A N O   D E                                       ║\n");
    printf("║                                            N A S C I M E N T O                                                  ║\n");
    printf("╠═════════════════════════════════════════════════════════════════════════════════════════════════════════════════╣\n");
    printf("║ Ano selecionado: %-4d                                                                                           ║\n", year);
    printf("╠══════╦═════════════════════════════╦══════════════╦══════════════════════════════╦══════════════════╦═══════════╣\n");
    printf("║  ID  ║ Nome                        ║  Nascimento  ║ Email                        ║ Telefone         ║ Status    ║\n");
    printf("╠══════╬═════════════════════════════╬══════════════╬══════════════════════════════╬══════════════════╬═══════════╣\n");

    FILE *file = fopen(FILE_NAME_PEOPLE, "rb");
    if (!file) {
        printf("╚══════╩═════════════════════════════╩══════════════╩══════════════════════════════╩══════════════════╩═══════════╝\n");
        print_error("Nenhum dado cadastrado ou erro ao abrir arquivo.");
        return;
    }

    People person;
    int count = 0;

    while (fread(&person, sizeof(People), 1, file)) {
        if (!person.status) continue;  // Ignora registros inativos

        int d, m, y;
        sscanf(person.birth_date, "%d/%d/%d", &d, &m, &y);

        if (y == year) {
           print_people_table(&person);
            count++;
        }
    }

    printf("╚══════╩═════════════════════════════╩══════════════╩══════════════════════════════╩══════════════════╩═══════════╝\n");
    printf("Total de pessoas nascidas em %d: %d\n", year, count);

    fclose(file);
}