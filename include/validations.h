#ifndef VALIDATIONS_H
#define VALIDATIONS_H

#include <stdbool.h>
#include "people.h"
#include "finance.h"
#include "residence.h"

// Valida se uma string é uma data válida no formato "dd/mm/yyyy"
bool validation_date(const char *date);

// Valida se um telefone é válido (com ou sem código de país)
bool is_valid_phone(const char *phone);

// Valida se um e-mail é válido (verificação básica)
bool is_valid_email(const char *email);

// Valida se uma string não está vazia e não ultrapassa o limite máximo de caracteres
bool is_valid_string(const char *str, size_t max_len);

// Valida se um valor numérico é maior ou igual a zero
bool is_valid_value(float value);

// Valida CEP
bool is_valid_cep(const char *cep);

// Valida número da residência
bool is_valid_residence_number(int number);

// Valida estado (sigla)
bool is_valid_state(const char *state);

// Valida uma struct Finance
bool is_valid_finance(const Finance *finance);

// Valida uma struct People
bool is_valid_people(const People *person);

// Valida uma struct Residence
bool is_valid_residence(const Residence *residence);

// Valida o ID de Pessoa
bool is_valid_people_id(const int);

#endif