#include <stdio.h>
#include <string.h>
#include "people.h"

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

    Pessoa p;
    char buf[256];

    printf("\n=== Criar nova pessoa ===\n");

    /* Nome */
    printf("Nome: ");
    if (!fgets(p.nome, sizeof(p.nome), stdin)) {
        printf("Entrada falhou.\n");
        return;
    }
    trim_newline(p.nome);
    if (p.nome[0] == '\0') {
        printf("Nome vazio. Operação cancelada.\n");
        return;
    }

    /* Idade (validação simples) */
    while (1) {
        printf("Idade: ");
        if (!fgets(buf, sizeof(buf), stdin)) return;
        trim_newline(buf);
        if (buf[0] == '\0') {
            printf("Idade vazia. Operação cancelada.\n");
            return;
        }
        int idade = atoi(buf);
        if (idade <= 0) {
            printf("Idade inválida. Digite um número maior que 0.\n");
            continue;
        }
        p.idade = idade;
        break;
    }

    /* CPF */
    printf("CPF: ");
    if (!fgets(p.cpf, sizeof(p.cpf), stdin)) return;
    trim_newline(p.cpf);

    /* Email (novo atributo) */
    printf("Email: ");
    if (!fgets(p.email, sizeof(p.email), stdin)) return;
    trim_newline(p.email);

    /* adiciona */
    people[*count] = p;
    (*count)++;

    printf("Pessoa '%s' adicionada com sucesso.\n", p.nome);
}