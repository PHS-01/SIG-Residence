#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "people.h"

static void trim_newline(char *s) {
    if (!s) return;
    size_t len = strlen(s);
    while (len > 0 && (s[len-1] == '\n' || s[len-1] == '\r')) {
        s[len-1] = '\0';
        len--;
    }
}

void update_people(Pessoa people[], int count) {
    if (count == 0) {
        printf("Nenhuma pessoa para atualizar.\n");
        return;
    }

    read_people(people, count);
    char buf[256];
    int idx = 0;

    printf("Escolha o número da pessoa a atualizar (1-%d): ", count);
    if (!fgets(buf, sizeof(buf), stdin)) return;
    trim_newline(buf);
    idx = atoi(buf);
    if (idx < 1 || idx > count) {
        printf("Índice inválido.\n");
        return;
    }
    idx -= 1; // zero-based

    printf("\nAtualizando [%d] %s\n", idx+1, people[idx].nome);
    printf("Deixe em branco e pressione ENTER para manter o valor atual.\n");

    /* Nome */
    printf("Novo nome (atual: %s): ", people[idx].nome);
    if (!fgets(buf, sizeof(buf), stdin)) return;
    trim_newline(buf);
    if (buf[0] != '\0') {
        strncpy(people[idx].nome, buf, NAME_LEN-1);
        people[idx].nome[NAME_LEN-1] = '\0';
    }

    /* Idade */
    printf("Nova idade (atual: %d): ", people[idx].idade);
    if (!fgets(buf, sizeof(buf), stdin)) return;
    trim_newline(buf);
    if (buf[0] != '\0') {
        int v = atoi(buf);
        if (v > 0) people[idx].idade = v;
        else printf("Idade inválida, manteve-se o valor anterior.\n");
    }

    /* CPF */
    printf("Novo CPF (atual: %s): ", people[idx].cpf);
    if (!fgets(buf, sizeof(buf), stdin)) return;
    trim_newline(buf);
    if (buf[0] != '\0') {
        strncpy(people[idx].cpf, buf, CPF_LEN-1);
        people[idx].cpf[CPF_LEN-1] = '\0';
    }

    /* Email */
    printf("Novo email (atual: %s): ", people[idx].email);
    if (!fgets(buf, sizeof(buf), stdin)) return;
    trim_newline(buf);
    if (buf[0] != '\0') {
        strncpy(people[idx].email, buf, EMAIL_LEN-1);
        people[idx].email[EMAIL_LEN-1] = '\0';
    }

    printf("Registro atualizado.\n");
}
