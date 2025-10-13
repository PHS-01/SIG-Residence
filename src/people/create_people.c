#include <stdio.h>
#include <string.h>
#include "people.h"
#include "config.h"

void create_people_ui() {
    People new_person;

    printf("=== CADASTRO DE PESSOA ===\n");
    
    // ID será gerado automaticamente
    new_person.id = 0; // Será substituído pela função generate_people_id()
    
    printf("Nome: ");
    fgets(new_person.name, sizeof(new_person.name), stdin);
    new_person.name[strcspn(new_person.name, "\n")] = '\0';

    printf("Data de nascimento (dd/mm/aaaa): ");
    fgets(new_person.birth_date, sizeof(new_person.birth_date), stdin);
    new_person.birth_date[strcspn(new_person.birth_date, "\n")] = '\0';

    printf("Email: ");
    fgets(new_person.email, sizeof(new_person.email), stdin);
    new_person.email[strcspn(new_person.email, "\n")] = '\0';

    printf("Telefone: ");
    fgets(new_person.phone, sizeof(new_person.phone), stdin);
    new_person.phone[strcspn(new_person.phone, "\n")] = '\0';

    new_person.status = true; // Sempre ativo ao criar

    create_people(new_person);
}