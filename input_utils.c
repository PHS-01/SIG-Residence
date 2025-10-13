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
        return 0;
    }
    
    return sscanf(input, "%d", value) == 1;
}

int read_string_input(const char* prompt, char* buffer, size_t size) {
    if (prompt != NULL) {
        printf("%s", prompt);
        fflush(stdout);
    }
    
    if (fgets(buffer, size, stdin) == NULL) {
        return 0;
    }
    
    // Remove o \n se existir
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len-1] == '\n') {
        buffer[len-1] = '\0';
    } else {
        // Se não tinha \n, limpa o buffer até encontrar um
        clear_input_buffer();
    }
    
    return 1;
}

void wait_for_enter(void) {
    printf("Pressione Enter para continuar...");
    fflush(stdout);
    
    // Limpa qualquer coisa que esteja no buffer ANTES de esperar
    clear_input_buffer();
    
    // Espera pelo Enter
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}