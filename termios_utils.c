#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>

// Funções para controle do terminal, e manipulação do texto
#include "terminal_control.h"

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