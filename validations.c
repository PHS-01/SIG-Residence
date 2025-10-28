#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include "people.h"
#include "finance.h"

// Função para verificar se uma string é um número válido no formato dd/mm/yyyy
bool validation_date(const char *date) {
    // Verificar se todos os numeros são digitos
    if (strlen(date) != 10) {
        return false;
    } else {
        for (int i = 0; i < 10; i++) {
            if (i == 2 || i == 5) {
                if (date[i] != '/') return false;
            } else if (!isdigit(date[i])) {
                return false;
            }
        }
    }
    
    // Verifica se a data é uma data válida
    int day, month, year;
    sscanf(date, "%d/%d/%d", &day, &month, &year);

    if (month < 1 || month > 12) {
        return false;
    } else if (day < 1 || day > 31) {
        return false;
    }
    
    // Ajuste simples para meses com menos de 31 dias (não considera anos bissextos)
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
        return false;
    } else if (month == 2 && day > 28) {
        return false;
    }
    
    return true;
}

// Valida o telefone (com ou sem código de país, apenas números e o formato correto)
bool is_valid_phone(const char *phone) {
    int len = strlen(phone);
    
    if (len < 10 || len > 20) {
        return false; // Comprimento do telefone inválido
    } else {
        for (int i = 0; i < len; i++) {
            if (!isdigit(phone[i]) && phone[i] != '+' && phone[i] != '-') {
                return false;
            }
        }
    }
    
    // Validando o formato padrão como: +55 99999-9999 ou 99999-9999
    if (phone[0] == '+' && len < 13) return false; // Se começar com '+' precisa ser código de país

    return true;
}

// Valida o email (forma básica)
bool is_valid_email(const char *email) {
    int len = strlen(email);
    
    if (len < 5 || len > 100) {
        return false;
    } else {
        bool at_found = false;
        bool dot_found = false;
        
        for (int i = 0; i < len; i++) {
            if (email[i] == '@') {
                at_found = true;
            } else if (email[i] == '.') {
                dot_found = true;
            } else if (!isalnum(email[i]) && email[i] != '.' && email[i] != '@') {
                return false;
            }
        }
        
        return at_found && dot_found;
    }
}

// Valida que a string não está vazia e não ultrapassa o limite máximo de caracteres
bool is_valid_string(const char *str, int max_len) {
    return str != NULL && strlen(str) > 0 && strlen(str) < max_len;
}

// Valida que o valor é maior ou igual a 0
bool is_valid_value(float value) {
    return value >= 0;
}

// Função que valida um `Finance`
bool is_valid_finance(const Finance *finance) {
    if (finance == NULL) {
        printf("❌ Erro: Estrutura Finance nula.\n");
        return false;
    }

    if (!is_valid_string(finance->description, 100)) {
        printf("⚠️  Descrição inválida! Ela não pode estar vazia e deve ter até 100 caracteres.\n");
        return false;
    }

    if (!is_valid_value(finance->value)) {
        printf("⚠️  Valor inválido! O valor deve ser maior ou igual a 0.\n");
        return false;
    }

    if (!validation_date(finance->date)) {
        printf("⚠️  Data inválida! Use o formato dd/mm/aaaa e insira uma data real.\n");
        return false;
    }

    if (!is_valid_string(finance->category, 20)) {
        printf("⚠️  Categoria inválida! Ela não pode estar vazia e deve ter até 20 caracteres.\n");
        return false;
    }

    if (finance->type != 'R' && finance->type != 'D' && finance->type != 'r' && finance->type != 'd') {
        printf("⚠️  Tipo inválido! Use 'R' (receita) ou 'D' (despesa).\n");
        return false;
    }

    return true;
}

// Função que valida uma `People`
bool is_valid_people(const People *person) {
    if (person == NULL) {
        printf("❌ Erro: Estrutura People nula.\n");
        return false;
    }

    if (!is_valid_string(person->name, 100)) {
        printf("⚠️  Nome inválido! Ele não pode estar vazio e deve ter até 100 caracteres.\n");
        return false;
    }

    if (!validation_date(person->birth_date)) {
        printf("⚠️  Data de nascimento inválida! Use o formato dd/mm/aaaa e insira uma data real.\n");
        return false;
    }

    if (!is_valid_email(person->email)) {
        printf("⚠️  Email inválido! Certifique-se de que contém '@' e '.' e está no formato correto.\n");
        return false;
    }

    if (!is_valid_phone(person->phone)) {
        printf("⚠️  Telefone inválido! Use apenas números, '+' e '-', com 10 a 20 caracteres.\n");
        return false;
    }

    return true;
}