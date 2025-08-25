#include <ncurses.h>
#include <string.h>

void draw_border(char style, int border_margin_left_right, int border_margin_top_bottom)
{
    // Desenha borda superior e inferior
    for (int x = border_margin_left_right; x < (COLS - border_margin_left_right); x++) {
        mvaddch(border_margin_top_bottom, x, style);                              // borda cima
        mvaddch(LINES - 1 - border_margin_top_bottom, x, style);                  // borda baixo
    }

    // Desenha borda esquerda e direita
    for (int y = border_margin_top_bottom; y < (LINES - border_margin_top_bottom); y++) {
        mvaddch(y, border_margin_left_right, style);               // borda esquerda
        mvaddch(y, COLS - 1 - border_margin_left_right, style);   // borda direita
    }
}

char draw_alert(const char *msg[], const int length_msg, int width, bool space) 
{
    int h = length_msg + 5;
    int y = (LINES - h) / 2;
    int x = (COLS - width) / 2;  
            
    char resp;

    WINDOW *alert = newwin(h, width, y, x);
    box(alert, 0, 0);

    h = 2;

    // escreve a mensagem centralizada
    for (int i = 0; i < length_msg; i++)
    {
        mvwprintw(alert, h, (width - (int)strlen(msg[i])) / 2, "%s", msg[i]);

        if (space)
        {
            h += 2;
        } else
        {
            h += 1;
        }
    }

    wrefresh(alert);

    // Espera uma até tecla ser digitada
    resp = wgetch(alert);

    // apaga a janela
    werase(alert);
    wrefresh(alert);
    delwin(alert);

    return resp;
}

// Função genérica para entrada de texto em caixa (window)
void input_box(int width, const char *prompt, char *buffer, int max_len)
{
    int h = 5;
    int y = (LINES - h) / 2;
    int x = (COLS - width) / 2;

    // Cria a janela
    WINDOW *win = newwin(h, width, y, x);
    box(win, 0, 0);
    mvwprintw(win, h/2, 2, "%s ", prompt);
    wrefresh(win);

    // Habilita eco e lê entrada
    echo();
    wgetnstr(win, buffer, max_len - 1);
    noecho();

    // Remove a janela
    delwin(win);
}