#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "reports.h"
#include "people.h"
#include "finance.h"
#include "residence.h"
#include "config.h"
#include "menu_borders.h"
#include "terminal_control.h"

void generate_people_report(bool active_only) {
    list_people_paginated(active_only);
}

void generate_finance_report(bool active_only) {
    list_finance_paginated(active_only);
}

void generate_residence_report(bool active_only) {
   list_residence_paginated(active_only);
}

void generate_birth_report(bool active_only) {
    if (active_only) {
        list_birthdays_by_month();
    } else {
        list_birthdays_by_year();
    }

}

void generate_residence_by_state(void) {
    list_residence_by_state();
}

void generate_finance_by_category(void) {
    list_finance_by_category();
}
void generate_finance_by_person(void) {
    list_finance_by_person();
}

// void generate_consolidated_report(void) {
//     // generate_people_report(false);
//     // printf("\n");
//     // generate_finance_report(false);
//     // printf("\n");
//     // generate_residence_report(false);
// }

// Funções de estatística
int count_active_people(void) {
    FILE *file = fopen(FILE_NAME_PEOPLE, "rb");
    int count = 0;
    
    if (file) {
        People person;
        while (fread(&person, sizeof(People), 1, file)) {
            if (person.status) count++;
        }
        fclose(file);
    }
    
    return count;
}

int count_active_finances(void) {
    FILE *file = fopen(FILE_NAME_FINANCE, "rb");
    int count = 0;
    
    if (file) {
        Finance finance;
        while (fread(&finance, sizeof(Finance), 1, file)) {
            if (finance.status) count++;
        }
        fclose(file);
    }
    
    return count;
}

int count_active_residences(void) {
    FILE *file = fopen(FILE_NAME_RESIDENCE, "rb");
    int count = 0;
    
    if (file) {
        Residence residence;
        while (fread(&residence, sizeof(Residence), 1, file)) {
            if (residence.status) count++;
        }
        fclose(file);
    }
    
    return count;
}

void show_system_statistics(void) {
    int total_people = count_active_people();
    int total_finances = count_active_finances();
    int total_residences = count_active_residences();
    
    printf("╔════════════════════════════════════════════════════════════════════╗\n");
    printf("║                      ESTATÍSTICAS DO SISTEMA                       ║\n");
    printf("╚════════════════════════════════════════════════════════════════════╝\n");
    
    printf("┌───────────────────┬──────────────┐\n");
    printf("│      Modulo       │   Registros  │\n");
    printf("├───────────────────┼──────────────┤\n");
    printf("│ Pessoas Ativas    │ %-12d │\n", total_people);
    printf("│ Transações Ativas │ %-12d │\n", total_finances);
    printf("│ Residências Ativas│ %-12d │\n", total_residences);
    printf("└───────────────────┴──────────────┘\n");
}