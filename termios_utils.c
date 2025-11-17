#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <sys/ioctl.h>

// Funções para controle do terminal, e manipulação do texto
#include "terminal_control.h"

static struct termios original_termios;
static bool term_saved = false;
// Configura terminal para modo raw (sem buffer e sem echo)
void save_terminal_state() {
    if (!term_saved) {
        tcgetattr(STDIN_FILENO, &original_termios);
        term_saved = true;
    }
}
void enable_raw_mode(void) {
    save_terminal_state();
    struct termios raw = original_termios;
    raw.c_lflag &= ~(ICANON | ECHO);
    raw.c_cc[VMIN] = 1;
    raw.c_cc[VTIME] = 0;

    tcsetattr(STDIN_FILENO, TCSANOW, &raw);
}

// Restaura modo original do terminal
void disable_raw_mode(void) {
    tcsetattr(STDIN_FILENO, TCSANOW, &original_termios); // Restaura config original
}

// Entra em modo "sem ENTER"
void enable_getchar_raw_mode() {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~(ICANON | ECHO); // Sem buffer, sem echo
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

// Restaura modo normal
void disable_getchar_raw_mode() {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag |= (ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

// Função que espera uma tecla sem precisar de ENTER
char get_keypress(void) {
    enable_raw_mode();
    int ch = getchar();
    restore_terminal();
    return (char)ch;
}

// Função para restaurar o terminal ao estado original
void restore_terminal(void) {
    if (term_saved) {
        tcsetattr(STDIN_FILENO, TCSANOW, &original_termios);
    }

    printf("\033[?25h"); // mostra cursor
    printf("\033[0m");   // reseta estilo
    fflush(stdout);
}

// Função para verificar mudanças no tamanho do terminal
void update_terminal_size(int *last_rows, int *last_cols) {
    struct winsize w;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1) {
        return; // Falha ao pegar tamanho
    }

    // Se o tamanho do terminal mudou, atualiza as variáveis
    if (*last_rows != w.ws_row || *last_cols != w.ws_col) {
        *last_rows = w.ws_row;
        *last_cols = w.ws_col;
        // Redesenha a tela
        clear_screen();
    }
}

// Função para definir o tamanho do terminal
void set_terminal_size(int rows, int cols) {
    struct winsize size;
    size.ws_row = rows;   // Número de linhas
    size.ws_col = cols;   // Número de colunas
    ioctl(STDOUT_FILENO, TIOCSWINSZ, &size);
}