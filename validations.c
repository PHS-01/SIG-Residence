#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>

#include "people.h"
#include "finance.h"
#include "residence.h"
#include "terminal_control.h"
#include "config.h"
#include "controllers.h"

// Valida se o nome é válido
bool is_valid_name(const char *name) {
    if (name == NULL || strlen(name) == 0) {
        return false;
    }
    
    int len = strlen(name);
    if (len < 2 || len > 100) {
        return false;
    }
    
    // Verificar se tem pelo menos um espaço (nome e sobrenome)
    bool has_space = false;
    for (int i = 0; i < len; i++) {
        if (name[i] == ' ') {
            has_space = true;
            break;
        }
    }
    
    if (!has_space) {
        return false;
    }
    
    // Verificar caracteres básicos
    int letter_count = 0;
    for (int i = 0; i < len; i++) {
        unsigned char c = name[i];
        
        // Contar letras
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
            letter_count++;
        }
        
        // Caracteres permitidos: letras, espaços, hífens, apóstrofos e caracteres acentuados
        if (!((c >= 'A' && c <= 'Z') || 
              (c >= 'a' && c <= 'z') ||
              c == ' ' || c == '-' || c == '\'' ||
              (c >= 128))) { // Permitir caracteres acentuados
            return false;
        }
    }
    
    // Deve ter pelo menos 2 letras
    if (letter_count < 2) {
        return false;
    }
    
    // Verificar espaços consecutivos
    for (int i = 0; i < len - 1; i++) {
        if (name[i] == ' ' && name[i + 1] == ' ') {
            return false;
        }
    }
    
    // Verificar se não começa ou termina com espaço
    if (name[0] == ' ' || name[len - 1] == ' ') {
        return false;
    }
    
    return true;
}

bool is_valid_people_id(const int people_id) {
    People people;

    set_search_id(people_id);

    if (read(&people, sizeof(People), FILE_NAME_PEOPLE, match_people_by_id)) {
        return true;
    } else {
        return false;
    }
    
}

// Função para verificar se um ano é bissexto
bool is_leap_year(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// Função para verificar se uma string é um número válido no formato dd/mm/yyyy
bool validation_date(const char *date) {
    // Verificar formato básico
    if (strlen(date) != 10) {
        return false;
    }
    
    for (int i = 0; i < 10; i++) {
        if (i == 2 || i == 5) {
            if (date[i] != '/') {
                return false;
            }
        } else if (!isdigit(date[i])) {
            return false;
        }
    }
    
    // Extrair dia, mês e ano
    int day, month, year;
    if (sscanf(date, "%d/%d/%d", &day, &month, &year) != 3) {
        return false;
    }

    // Validar mês
    if (month < 1 || month > 12) {
        return false;
    }

    // Validar ano (1900-2100)
    if (year < 1900 || year > 2100) {
        return false;
    }

    // Validar dia baseado no mês
    int days_in_month;
    switch (month) {
        case 2:
            days_in_month = is_leap_year(year) ? 29 : 28;
            break;
        case 4: case 6: case 9: case 11:
            days_in_month = 30;
            break;
        default:
            days_in_month = 31;
            break;
    }

    if (day < 1 || day > days_in_month) {
        return false;
    }

    return true;
}

// Valida o telefone (com ou sem código de país, apenas números e o formato correto)
bool is_valid_phone(const char *phone) {
    int len = strlen(phone);

    if (len < 9 || len > 20) {
        return false;
    }

    // Verificar caracteres permitidos
    for (int i = 0; i < len; i++) {
        if (!isdigit(phone[i]) &&
            phone[i] != '+' &&
            phone[i] != '-' &&
            phone[i] != ' ' &&
            phone[i] != '(' &&
            phone[i] != ')') 
        {
            return false;
        }
    }

    // "+" só pode ser o primeiro caractere
    for (int i = 1; i < len; i++) {
        if (phone[i] == '+') {
            return false;
        }
    }

    // Contar apenas os dígitos
    int digit_count = 0;
    for (int i = 0; i < len; i++) {
        if (isdigit(phone[i])) digit_count++;
    }

    // Validação geral de quantidade de dígitos (Brasil)
    // 10 dígitos → fixo (ex: 1134567890)
    // 11 dígitos → celular (ex: 11987654321)
    if (digit_count == 10) {
        return true;
    }
    if (digit_count == 11) {
        return true;
    }

    // Caso use formato internacional +55...
    if (phone[0] == '+') {
        // Aceitar de 12 a 13 dígitos (+55 + DDD + número)
        if (digit_count >= 12 && digit_count <= 13) {
            return true;
        }
    }

    return false;
}

// Valida o email (forma mais robusta)
bool is_valid_email(const char *email) {
    int len = strlen(email);
    
    if (len < 5 || len > 100) {
        return false;
    }
    
    bool at_found = false;
    bool dot_after_at = false;
    int at_position = -1;
    
    for (int i = 0; i < len; i++) {
        // Caracteres permitidos: letras, números, ., -, _, @
        if (!isalnum(email[i]) && email[i] != '.' && email[i] != '-' && email[i] != '_' && email[i] != '@') {
            return false;
        }
        
        if (email[i] == '@') {
            if (at_found) {
                return false;
            }
            at_found = true;
            at_position = i;
        }
        
        // Verificar se há um ponto após o @
        if (at_found && email[i] == '.' && i > at_position + 1) {
            dot_after_at = true;
        }
    }
    
    if (!at_found) {
        return false;
    }
    
    if (!dot_after_at) {
        return false;
    }
    
    // Verificar se não começa ou termina com ponto ou hífen
    if (email[0] == '.' || email[0] == '-' || email[0] == '@' ||
        email[len-1] == '.' || email[len-1] == '-' || email[len-1] == '@') {
        return false;
    }
    
    // Verificar se o @ não está no início ou fim
    if (at_position == 0 || at_position == len-1) {
        return false;
    }
    
    return true;
}

// Valida que a string não está vazia e não ultrapassa o limite máximo de caracteres
bool is_valid_string(const char *str, size_t max_len) {
    return str != NULL && strlen(str) > 0 && strlen(str) < max_len;
}

// Valida que o valor é maior ou igual a 0
bool is_valid_value(float value) {
    return value >= 0;
}

// Valida CEP no formato 12345-678 ou 12345678
bool is_valid_cep(const char *cep) {
    int len = strlen(cep);
    
    if (len != 8 && len != 9) {
        return false;
    }
    
    if (len == 9) {
        // Formato com hífen: 12345-678
        if (cep[5] != '-') {
            return false;
        }
        
        for (int i = 0; i < 9; i++) {
            if (i != 5 && !isdigit(cep[i])) {
                return false;
            }
        }
    } else {
        // Formato sem hífen: 12345678
        for (int i = 0; i < 8; i++) {
            if (!isdigit(cep[i])) {
                return false;
            }
        }
    }
    
    return true;
}

// Valida número de residência
bool is_valid_residence_number(int number) {
    return number > 0;
}

// Valida estado (sigla de 2 caracteres)
bool is_valid_state(const char *state) {
    if (strlen(state) != 2) {
        return false;
    }
    
    if (!isalpha(state[0]) || !isalpha(state[1])) {
        return false;
    }
    
    // Converter para maiúsculas para verificação
    char upper_state[3];
    upper_state[0] = toupper(state[0]);
    upper_state[1] = toupper(state[1]);
    upper_state[2] = '\0';
    
    // Lista de siglas válidas
    const char *valid_states[] = {"AC", "AL", "AP", "AM", "BA", "CE", "DF", "ES", "GO", 
                                 "MA", "MT", "MS", "MG", "PA", "PB", "PR", "PE", "PI", 
                                 "RJ", "RN", "RS", "RO", "RR", "SC", "SP", "SE", "TO", NULL};
    
    for (int i = 0; valid_states[i] != NULL; i++) {
        if (strcmp(upper_state, valid_states[i]) == 0) {
            return true;
        }
    }
    
    return false;
}

// Função que valida um `Finance`
bool is_valid_finance(const Finance *finance) {
    if (finance == NULL) {
        return false;
    }

    if (!is_valid_string(finance->description, 100)) {
        return false;
    }

    if (!is_valid_value(finance->value)) {
        return false;
    }

    if (!validation_date(finance->date)) {
        return false;
    }

    if (!is_valid_string(finance->category, 50)) {
        return false;
    }

    if (finance->type != 'R' && finance->type != 'D' && finance->type != 'r' && finance->type != 'd') {
        return false;
    }

    return true;
}

// Função que valida uma `People`
bool is_valid_people(const People *person) {
    if (person == NULL) {
        return false;
    }

    if (!is_valid_string(person->name, 100)) {
        return false;
    }

    if (!validation_date(person->birth_date)) {
        return false;
    }

    if (!is_valid_email(person->email)) {
        return false;
    }

    if (!is_valid_phone(person->phone)) {
        return false;
    }

    return true;
}

// Função que valida uma `Residence`
bool is_valid_residence(const Residence *residence) {
    if (residence == NULL) {
        return false;
    }

    if (!is_valid_string(residence->address, 100)) {
        return false;
    }

    if (!is_valid_residence_number(residence->number)) {
        return false;
    }

    // Complemento pode ser vazio, apenas verificar tamanho se preenchido
    if (strlen(residence->complement) > 0 && strlen(residence->complement) >= 50) {
        return false;
    }

    if (!is_valid_string(residence->neighborhood, 50)) {
        return false;
    }

    if (!is_valid_string(residence->city, 50)) {
        return false;
    }

    if (!is_valid_state(residence->state)) {
        return false;
    }

    if (!is_valid_cep(residence->cep)) {
        return false;
    }

    return true;
}