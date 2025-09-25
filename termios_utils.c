#include <termios.h>
#include <unistd.h>

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