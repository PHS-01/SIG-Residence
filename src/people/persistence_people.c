#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "people.h"

// utilitário
static void trim_newline(char *s) {
    if (!s) return;
    size_t len = strlen(s);
    while (len > 0 && (s[len-1] == '\n' || s[len-1] == '\r')) {
        s[len-1] = '\0';
        len--;
    }
}

void save_people(const char *filename, Pessoa people[], int count) {
    FILE *f = fopen(filename, "w");
    if (!f) {
        perror("save_people: fopen");
        return;
    }

    for (int i = 0; i < count; ++i) {
        // Garante ausência de nova linha nos campos
        trim_newline(people[i].nome);
        trim_newline(people[i].cpf);
        trim_newline(people[i].email);
        fprintf(f, "%s;%d;%s;%s\n", people[i].nome, people[i].idade, people[i].cpf, people[i].email);
    }

    fclose(f);
}

void load_people(const char *filename, Pessoa people[], int *count) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        // Arquivo não existe -> inicializa vazio
        *count = 0;
        return;
    }

    char line[512];
    int idx = 0;
    while (fgets(line, sizeof(line), f) && idx < MAX_PEOPLE) {
        trim_newline(line);
        if (line[0] == '\0') continue;

        char *tok;
        char *saveptr = NULL;

        tok = strtok_r(line, ";", &saveptr);
        if (!tok) continue;
        strncpy(people[idx].nome, tok, NAME_LEN-1);
        people[idx].nome[NAME_LEN-1] = '\0';

        tok = strtok_r(NULL, ";", &saveptr);
        if (!tok) { people[idx].idade = 0; }
        else { people[idx].idade = atoi(tok); }

        tok = strtok_r(NULL, ";", &saveptr);
        if (!tok) people[idx].cpf[0] = '\0';
        else { strncpy(people[idx].cpf, tok, CPF_LEN-1); people[idx].cpf[CPF_LEN-1] = '\0'; }

        tok = strtok_r(NULL, ";", &saveptr);
        if (!tok) people[idx].email[0] = '\0';
        else { strncpy(people[idx].email, tok, EMAIL_LEN-1); people[idx].email[EMAIL_LEN-1] = '\0'; }

        idx++;
    }

    *count = idx;
    fclose(f);
}
