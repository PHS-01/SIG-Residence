#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

// Move o cursor para a posição (linha, coluna)
void move_cursor(int row, int col) {
    printf("\033[%d;%dH", row, col);
    fflush(stdout);
}

// Esconde o cursor
void hide_cursor(void) {
    printf("\033[?25l");
    fflush(stdout);
}

// Mostra o cursor
void show_cursor(void) {
    printf("\033[?25h");
    fflush(stdout);
}

// Limpa a tela e move o cursor para o canto superior esquerdo (1,1)
void clear_screen(void) {
    printf("\033[2J");  // Limpa a tela
    printf("\033[H");   // Move o cursor para (1,1)
    fflush(stdout);
}

// Imprime texto em uma posição específica
void ansi_print(int row, int col, const char *text) {
    move_cursor(row, col);
    printf("%s", text);
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
        system("clear");
    }
}