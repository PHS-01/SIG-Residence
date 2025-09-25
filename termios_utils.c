#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

static struct termios original_termios;

// Configura terminal para modo raw (sem buffer e sem echo)
void enable_raw_mode(void) {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);         // Pega config atual
    original_termios = term;                // Salva config original

    term.c_lflag &= ~(ICANON | ECHO);       // Desativa buffer e echo
    tcsetattr(STDIN_FILENO, TCSANOW, &term); // Aplica config
}

// Restaura modo original do terminal
void disable_raw_mode(void) {
    tcsetattr(STDIN_FILENO, TCSANOW, &original_termios); // Restaura config original
}

// Função que espera uma tecla sem precisar de ENTER
char get_keypress(void) {
    char resp;
    enable_raw_mode();

    if (read(STDIN_FILENO, &resp, 1) != 1) {
        resp = '\0';  // Erro de leitura
    }

    disable_raw_mode();
    return resp;
}

// Função para restaurar o terminal ao estado original
void restore_terminal(void) {
    // Restabelece o modo normal do terminal (desativa cores, etc)
    printf("\033[0m");   // Reseta cores e atributos
    printf("\033[H");    // Restaura o cursor para a posição inicial
    fflush(stdout);
}