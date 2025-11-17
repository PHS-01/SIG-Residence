#ifndef REPORTS_H
#define REPORTS_H

#include <stdbool.h>

// Funções de relatório
void generate_people_report(bool active_only);
void generate_finance_report(bool active_only);
void generate_residence_report(bool active_only);
void generate_consolidated_report(void);
void generate_birth_report(bool active_only);

// Estatísticas
void show_system_statistics(void);
int count_active_people(void);
int count_active_finances(void);
int count_active_residences(void);

#endif