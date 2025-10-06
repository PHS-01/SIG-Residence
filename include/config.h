#ifndef CONFIG_H
#define CONFIG_H

// Declaração das variaveis
extern const char *PROJECT_VERSION;
extern const char *PROJECT_ASCII_ART[];
extern const int LENGTH_ASCII_ART;

// Configuração do Banco de dados
void create_database(void);
int database_exists(void);

#endif