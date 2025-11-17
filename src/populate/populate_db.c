#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "people.h"
#include "finance.h"
#include "residence.h"
#include "config.h"
#include "controllers.h"
#include "validations.h"
#include "populate_db.h"

// Função simples de print para o populador (sem cores)
void print_msg(const char* message) {
    printf("%s\n", message);
}

void print_success_msg(const char* message) {
    printf("✓ %s\n", message);
}

void print_error_msg(const char* message) {
    printf("✗ %s\n", message);
}

void print_info_msg(const char* message) {
    printf("ℹ %s\n", message);
}

// Função para gerar uma data aleatória nos últimos 5 anos
void generate_random_date(char *buffer, size_t size) {
    time_t now = time(NULL);
    // Últimos 5 anos em segundos
    long five_years_ago = now - (5 * 365 * 24 * 60 * 60);
    
    // Gera um tempo aleatório nos últimos 5 anos
    long random_time = five_years_ago + (rand() % (5 * 365 * 24 * 60 * 60));
    
    struct tm *timeinfo = localtime(&random_time);
    snprintf(buffer, size, "%02d/%02d/%04d", 
             timeinfo->tm_mday, timeinfo->tm_mon + 1, timeinfo->tm_year + 1900);
}

// Função para gerar um telefone aleatório
void generate_random_phone(char *buffer, size_t size) {
    const char *prefixes[] = {"11", "21", "31", "41", "51", "61", "71", "81", "91"};
    const char *prefix = prefixes[rand() % 9];
    int number = 900000000 + (rand() % 100000000);
    snprintf(buffer, size, "(%s)9%08d", prefix, number);
}

// Popular dados de pessoas
void populate_people_data(void) {

    People people[] = {
        {true, 0, "João Silva Santos", "15/03/1985", "joao.silva@email.com", ""},
        {true, 0, "Maria Oliveira Souza", "22/07/1990", "maria.oliveira@email.com", ""},
        {true, 0, "Pedro Costa Lima", "08/11/1978", "pedro.costa@email.com", ""},
        {true, 0, "Ana Pereira Rodrigues", "30/01/1995", "ana.pereira@email.com", ""},
        {true, 0, "Carlos Almeida Ferreira", "14/06/1982", "carlos.almeida@email.com", ""},
        {true, 0, "Juliana Martins Barbosa", "25/09/1988", "juliana.martins@email.com", ""},
        {true, 0, "Ricardo Carvalho Gomes", "03/12/1975", "ricardo.carvalho@email.com", ""},
        {true, 0, "Fernanda Santos Rocha", "19/04/1992", "fernanda.santos@email.com", ""},
        {true, 0, "Bruno Lima Oliveira", "07/08/1987", "bruno.lima@email.com", ""},
        {true, 0, "Camila Souza Costa", "12/10/1993", "camila.souza@email.com", ""},
        {true, 0, "Rafael Mendes Torres", "05/12/1980", "rafael.mendes@email.com", ""},
        {true, 0, "Patricia Alves Castro", "18/02/1989", "patricia.alves@email.com", ""},
        {true, 0, "Lucas Ribeiro Cardoso", "29/11/1991", "lucas.ribeiro@email.com", ""},
        {true, 0, "Amanda Dias Freitas", "14/07/1994", "amanda.dias@email.com", ""},
        {true, 0, "Marcos Oliveira Silva", "23/03/1983", "marcos.oliveira@email.com", ""}
    };
    
    int count = sizeof(people) / sizeof(people[0]);
    int success_count = 0;
    
    for (int i = 0; i < count; i++) {
        people[i].id = generate_people_id();
        generate_random_phone(people[i].phone, sizeof(people[i].phone));
        
        if (create(&people[i], sizeof(People), FILE_NAME_PEOPLE)) {
            success_count++;
        }
    }
    
    print_success_msg("Dados de pessoas populados:");
    printf("  %d de %d registros adicionados com sucesso\n", success_count, count);
}

// Popular dados de residências
void populate_residence_data(void) {

    Residence residences[] = {
        {true, 0, "Rua das Flores", "Jardim Paulista", "São Paulo", "SP", 123, "Apto 101", "01234-567"},
        {true, 0, "Avenida Brasil", "Centro", "Rio de Janeiro", "RJ", 456, "", "20000-000"},
        {true, 0, "Praça da Liberdade", "Savassi", "Belo Horizonte", "MG", 789, "Sala 2", "30140-010"},
        {true, 0, "Rua da Paz", "Boa Viagem", "Recife", "PE", 321, "Casa", "51020-000"},
        {true, 0, "Avenida Paulista", "Bela Vista", "São Paulo", "SP", 1000, "Conjunto 50", "01310-100"},
        {true, 0, "Rua Uruguai", "Centro", "Porto Alegre", "RS", 654, "Loja 5", "90010-140"},
        {true, 0, "Alameda Santos", "Cerqueira César", "São Paulo", "SP", 200, "Apto 1501", "01418-000"},
        {true, 0, "Rua 25 de Março", "Centro", "São Paulo", "SP", 777, "Galeria", "01021-000"},
        {true, 0, "Avenida Beira Mar", "Praia do Futuro", "Fortaleza", "CE", 888, "Casa de Praia", "60165-121"},
        {true, 0, "Rua Chile", "Centro", "Brasília", "DF", 999, "Bloco A", "70000-000"}
    };
    
    int count = sizeof(residences) / sizeof(residences[0]);
    int success_count = 0;
    
    for (int i = 0; i < count; i++) {
        residences[i].id = generate_residence_id();
        
        if (create(&residences[i], sizeof(Residence), FILE_NAME_RESIDENCE)) {
            success_count++;
        }
    }
    
    print_success_msg("Dados de residências populados:");
    printf("  %d de %d registros adicionados com sucesso\n", success_count, count);
}

// Popular dados financeiros
void populate_finance_data(void) {
    
    // Verifica quantas pessoas existem para associar as finanças
    FILE *people_file = fopen(FILE_NAME_PEOPLE, "rb");
    if (!people_file) {
        print_error_msg("Não existem pessoas cadastradas. Execute 'populate people' primeiro.");
        return;
    }
    
    // Contar pessoas
    People person;
    int people_count = 0;
    int people_ids[50]; // Array para armazenar IDs das pessoas
    
    while (fread(&person, sizeof(People), 1, people_file)) {
        if (person.status) {
            people_ids[people_count++] = person.id;
        }
    }
    fclose(people_file);
    
    if (people_count == 0) {
        print_error_msg("Nenhuma pessoa ativa encontrada. Execute 'populate people' primeiro.");
        return;
    }
    
    // Gerar transações financeiras
    const char *descriptions[] = {
        "Salário", "Aluguel", "Supermercado", "Luz", "Água", "Internet", 
        "Academia", "Transporte", "Restaurante", "Compras online",
        "Investimentos", "Freelance", "Consulta médica", "Farmácia", "Combustível",
        "Manutenção carro", "Presentes", "Vestuário", "Educação", "Streaming",
        "Seguro", "IPTU", "Condomínio", "Gás", "Celular"
    };
    
    const char *categories[] = {
        "Moradia", "Alimentação", "Transporte", "Saúde", "Lazer", 
        "Educação", "Investimentos", "Rendimentos", "Serviços", "Outros"
    };
    
    int transaction_count = 25; // Número de transações a criar
    int success_count = 0;
    
    srand(time(NULL)); // Seed para números aleatórios
    
    for (int i = 0; i < transaction_count; i++) {
        Finance finance;
        finance.id = generate_finance_id();
        
        // Associar a uma pessoa aleatória
        finance.people_id = people_ids[rand() % people_count];
        
        // Descrição aleatória
        strcpy(finance.description, descriptions[rand() % (sizeof(descriptions) / sizeof(descriptions[0]))]);
        
        // Valor aleatório entre R$ 10 e R$ 5000
        finance.value = (float)(100 + rand() % 490000) / 100.0f;
        
        // Data aleatória
        generate_random_date(finance.date, sizeof(finance.date));
        
        // Categoria aleatória
        strcpy(finance.category, categories[rand() % (sizeof(categories) / sizeof(categories[0]))]);
        
        // Tipo aleatório (70% despesas, 30% receitas)
        finance.type = (rand() % 100 < 70) ? 'D' : 'R';
        
        finance.status = true;
        
        if (create(&finance, sizeof(Finance), FILE_NAME_FINANCE)) {
            success_count++;
        }
    }
    
    print_success_msg("Dados financeiros populados:");
    printf("  %d de %d transações adicionadas com sucesso\n", success_count, transaction_count);
}

// Mostrar estatísticas do banco
void show_statistics(void) {
    printf("\n=== ESTATÍSTICAS DO BANCO DE DADOS ===\n");
    
    // Contar pessoas
    FILE *file = fopen(FILE_NAME_PEOPLE, "rb");
    int people_count = 0;
    if (file) {
        People p;
        while (fread(&p, sizeof(People), 1, file)) {
            if (p.status) people_count++;
        }
        fclose(file);
        printf("Pessoas cadastradas: %d\n", people_count);
    } else {
        printf("Pessoas cadastradas: 0 (arquivo não existe)\n");
    }
    
    // Contar residências
    file = fopen(FILE_NAME_RESIDENCE, "rb");
    int residence_count = 0;
    if (file) {
        Residence r;
        while (fread(&r, sizeof(Residence), 1, file)) {
            if (r.status) residence_count++;
        }
        fclose(file);
        printf("Residências cadastradas: %d\n", residence_count);
    } else {
        printf("Residências cadastradas: 0 (arquivo não existe)\n");
    }
    
    // Contar finanças
    file = fopen(FILE_NAME_FINANCE, "rb");
    int finance_count = 0;
    float total_receitas = 0, total_despesas = 0;
    if (file) {
        Finance f;
        while (fread(&f, sizeof(Finance), 1, file)) {
            if (f.status) {
                finance_count++;
                if (f.type == 'R') total_receitas += f.value;
                else total_despesas += f.value;
            }
        }
        fclose(file);
        printf("Transações financeiras: %d\n", finance_count);
        printf("Total de receitas: R$ %.2f\n", total_receitas);
        printf("Total de despesas: R$ %.2f\n", total_despesas);
        printf("Saldo: R$ %.2f\n", total_receitas - total_despesas);
    } else {
        printf("Transações financeiras: 0 (arquivo não existe)\n");
    }
}

// Popular todos os dados
void populate_all_data(void) {
    printf("=== POPULANDO BANCO DE DADOS COM DADOS DE TESTE ===\n\n");
    
    print_info_msg("Populando pessoas...");
    populate_people_data();
    
    print_info_msg("Populando residências...");
    populate_residence_data();
    
    print_info_msg("Populando transações financeiras...");
    populate_finance_data();
    
    printf("\n");
    print_success_msg("População do banco de dados concluída!");
    
    show_statistics();
}