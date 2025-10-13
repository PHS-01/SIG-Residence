#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "people.h"

// Função auxiliar para remover a quebra de linha ('\n') do final das strings.
static void trim_newline(char *s) {
    if (!s) return;
    size_t len = strlen(s);
    while (len > 0 && (s[len-1] == '\n' || s[len-1] == '\r')) {
        s[len-1] = '\0';
        len--;
    }
}

void create_people(Pessoa people[], int *count) {
    if (*count >= MAX_PEOPLE) {
        printf("Limite de pessoas atingido (%d).\n", MAX_PEOPLE);
        return;
    }

    Pessoa nova_pessoa;
    char buffer_idade[256]; // Buffer para ler idade como texto

    printf("\n=== Criar nova pessoa ===\n");

    printf("Nome: ");
    fgets(nova_pessoa.nome, sizeof(nova_pessoa.nome), stdin);
    trim_newline(nova_pessoa.nome);

    printf("Idade: ");
    fgets(buffer_idade, sizeof(buffer_idade), stdin);
    trim_newline(buffer_idade);
    nova_pessoa.idade = atoi(buffer_idade); // Converte a string para inteiro

    printf("CPF: ");
    fgets(nova_pessoa.cpf, sizeof(nova_pessoa.cpf), stdin);
    trim_newline(nova_pessoa.cpf);

    printf("Email: ");
    fgets(nova_pessoa.email, sizeof(nova_pessoa.email), stdin);
    trim_newline(nova_pessoa.email);

    // Adiciona pessoa ao array
    people[*count] = nova_pessoa;
    (*count)++;

    printf("\nPessoa '%s' adicionada com sucesso.\n", nova_pessoa.nome);
}