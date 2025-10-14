#ifndef CONTROLLERS_H
#define CONTROLLERS_H
    #include <stdbool.h>

    // Definindo a estrutura People
    typedef struct {
        int type_id;             // Indentificador de type de dado
        int id;                  // Identificador único
        char name[100];          // Nome da pessoa
        char birth_date[11];     // Data de nascimento (formato: dd/mm/yyyy)
        char email[100];         // Email
        char phone[20];          // Telefone
        bool status;
        // char role[50];           // Papel ou função (ex: chefe de família, responsável pelas finanças)
        // float participation;     // Percentual de participação nas despesas compartilhadas (0.0 a 1.0)
        // int expense_type;        // Tipo de despesa (Pessoal ou Compartilhada)
    } People;

    void create(const void*, size_t);
    int read(void*, size_t, int (*match)(const void *));
    int update(const void*, size_t, int (*match)(const void *));

#endif