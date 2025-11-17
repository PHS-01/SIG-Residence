#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "populate_db.h"
#include "config.h"

void show_help(void) {
    printf("\n=== POPULADOR DE BANCO DE DADOS - AJUDA ===\n");
    printf("Uso: populate [comando]\n\n");
    printf("Comandos disponíveis:\n");
    printf("  all           - Popula todos os dados (pessoas, residências, finanças)\n");
    printf("  people        - Popula apenas dados de pessoas\n");
    printf("  residence     - Popula apenas dados de residências\n");
    printf("  finance       - Popula apenas dados financeiros\n");
    printf("  stats         - Mostra estatísticas atuais do banco\n");
    printf("  help          - Mostra esta mensagem de ajuda\n");
    printf("\nExemplos:\n");
    printf("  ./populate all\n");
    printf("  ./populate people\n");
    printf("  ./populate stats\n");
}

int main(int argc, char *argv[]) {
    printf("=== POPULADOR DE BANCO DE DADOS ===\n");
    
    // Inicializar random seed
    srand(time(NULL));

    // Cria banco de dados se não existir
    create_database();
    
    if (argc != 2) {
        show_help();
        return 1;
    }
    
    if (strcmp(argv[1], "all") == 0) {
        populate_all_data();
    }
    else if (strcmp(argv[1], "people") == 0) {
        printf("=== POPULANDO DADOS DE PESSOAS ===\n");
        populate_people_data();
        show_statistics();
    }
    else if (strcmp(argv[1], "residence") == 0) {
        printf("=== POPULANDO DADOS DE RESIDÊNCIAS ===\n");
        populate_residence_data();
        show_statistics();
    }
    else if (strcmp(argv[1], "finance") == 0) {
        printf("=== POPULANDO DADOS FINANCEIROS ===\n");
        populate_finance_data();
        show_statistics();
    }
    else if (strcmp(argv[1], "stats") == 0) {
        show_statistics();
    }
    else if (strcmp(argv[1], "help") == 0) {
        show_help();
    }
    else {
        printf("Comando desconhecido: %s\n", argv[1]);
        show_help();
        return 1;
    }
    
    return 0;
}