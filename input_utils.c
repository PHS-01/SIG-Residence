#include <stdio.h>
#include <string.h>
#include "terminal_control.h"

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int read_int_input(const char* prompt, int* value) {
    char input[20];
    
    if (prompt != NULL) {
        printf("%s", prompt);
        fflush(stdout);
    }
    
    if (fgets(input, sizeof(input), stdin) == NULL) {
        // Se fgets falhar, limpar buffer e retornar erro
        clear_input_buffer();
        return 0;
    }
    
    // Verificar se leu uma linha completa
    if (strchr(input, '\n') == NULL) {
        // Linha muito longa, limpar o resto do buffer
        clear_input_buffer();
    }
    
    return sscanf(input, "%d", value) == 1;
}

int read_string_input(const char* prompt, char* buffer, size_t size) {
    if (prompt != NULL) {
        printf("%s", prompt);
        fflush(stdout);
    }
    
    if (fgets(buffer, size, stdin) == NULL) {
        clear_input_buffer();
        return 0;
    }
    
    // Remove o \n se existir
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len-1] == '\n') {
        buffer[len-1] = '\0';
        return 1;
    } else {
        // Se não tinha \n, a linha era muito longa - limpar buffer
        clear_input_buffer();
        return 1; // Ainda retorna sucesso, mas com string truncada
    }
}

void wait_for_enter(void) {
    printf("Pressione Enter para continuar...");
    fflush(stdout);
    
    // Limpa qualquer caractere residual no buffer
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}