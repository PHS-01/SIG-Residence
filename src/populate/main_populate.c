#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "populate_db.h"
#include "config.h"

int main(int argc, char *argv[]) {
    printf("=== POPULADOR DE BANCO DE DADOS ===\n");
    
    // Inicializar random seed
    srand(time(NULL));

    // Cria banco de dados se não existir
    create_database();
    
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