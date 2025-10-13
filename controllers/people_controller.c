#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Variáveis globais do projeto
#include "config.h"
#include "people.h"

// Função para gerar ID automático
int generate_people_id(void) {
    FILE *file = fopen(FILE_NAME, "rb");
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

// Função para criar uma nova pessoa no arquivo CSV
void create_people(People new_person) {
    FILE *file = fopen(FILE_NAME, "ab");

    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    } else {
        // Gera ID automático se não foi especificado
        if (new_person.id == 0) {
            new_person.id = generate_people_id();
        }
        
        // Escreve a estrutura 'People' diretamente no arquivo binário
        fwrite(&new_person, sizeof(People), 1, file);
        printf("Pessoa cadastrada com sucesso! ID: %d\n", new_person.id);
    }

    fclose(file);
}

void read_people(int id) {
    FILE *file = fopen(FILE_NAME, "rb");
    int found = 0;

    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    } else {
        People person;
        while (fread(&person, sizeof(People), 1, file)) {
            if (person.id == id) {
                printf("ID: %d\n", person.id);
                printf("Nome: %s\n", person.name);
                printf("Data de Nascimento: %s\n", person.birth_date);
                printf("Email: %s\n", person.email);
                printf("Telefone: %s\n", person.phone);
                printf("Status: %s\n", person.status ? "Ativo" : "Inativo");
                found = 1;
                break;
            }
        }
        
        if (!found) {
            printf("Pessoa com ID %d não encontrada.\n", id);
        }
    }

    fclose(file);
}

// Função para listar todas as pessoas do arquivo
void list_people(void) {
    FILE *file = fopen(FILE_NAME, "rb");
    int count = 0;

    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    } else {
        People person;
        printf("\n=== TODAS AS PESSOAS CADASTRADAS ===\n");
        while (fread(&person, sizeof(People), 1, file)) {
            printf("ID: %d, Nome: %s, Status: %s\n",
                person.id, person.name, person.status ? "Ativo" : "Inativo");
            count++;
        }
        
        if (count == 0) {
            printf("Nenhuma pessoa cadastrada.\n");
        } else {
            printf("Total: %d pessoa(s)\n", count);
        }
    }

    fclose(file);
}

// Função para listar apenas pessoas ativas
void list_active_people(void) {
    FILE *file = fopen(FILE_NAME, "rb");
    int count = 0;

    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    } else {
        People person;
        printf("\n=== PESSOAS ATIVAS ===\n");
        while (fread(&person, sizeof(People), 1, file)) {
            if (person.status) {
                printf("ID: %d, Nome: %s, Email: %s, Telefone: %s\n",
                    person.id, person.name, person.email, person.phone);
                count++;
            }
        }
        
        if (count == 0) {
            printf("Nenhuma pessoa ativa cadastrada.\n");
        } else {
            printf("Total: %d pessoa(s) ativa(s)\n", count);
        }
    }

    fclose(file);
}

// Função para atualizar os dados de uma pessoa no arquivo
void update_people(int id, People updated_person) {
    FILE *file = fopen(FILE_NAME, "r+b");
    int found = 0;

    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    } else {
        People person;
        while (fread(&person, sizeof(People), 1, file)) {
            if (person.id == id) {
                // Move o ponteiro de volta para a posição do registro encontrado
                fseek(file, -sizeof(People), SEEK_CUR);
                // Mantém o ID original e o status
                updated_person.id = id;
                updated_person.status = person.status;
                // Escreve o novo registro no lugar
                fwrite(&updated_person, sizeof(People), 1, file);
                printf("Pessoa atualizada com sucesso.\n");
                found = 1;
                break;
            }
        }
        
        if (!found) {
            printf("Pessoa com ID %d não encontrada.\n", id);
        }
    }

    fclose(file);
}

// Função para excluir uma pessoa (exclusão lógica - marca como inativa)
void delete_people(int id) {
    FILE *file = fopen(FILE_NAME, "r+b");
    int found = 0;

    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    } else {
        People person;
        while (fread(&person, sizeof(People), 1, file)) {
            if (person.id == id && person.status) {
                // Move o ponteiro de volta para a posição do registro encontrado
                fseek(file, -sizeof(People), SEEK_CUR);
                person.status = false;
                // Escreve o registro atualizado
                fwrite(&person, sizeof(People), 1, file);
                printf("Pessoa excluída com sucesso (marcada como inativa).\n");
                found = 1;
                break;
            }
        }
        
        if (!found) {
            printf("Pessoa com ID %d não encontrada ou já está inativa.\n", id);
        }
    }

    fclose(file);
}