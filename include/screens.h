#ifndef SCREENS_H
#define SCREENS_H

/*
Declaração das funções
*/
#include <stdbool.h>

// Telas
bool home(void);
void credits(void);
void about(void);
bool confirm_exit(void);

// Telas do modulo pessoas
void dashboard_people(void);

// // Telas do módulo residência
// void dashboard_residence(int y, int x);
// void create_residence(int y, int x);
// void read_residence(int y, int x, char residences[2][50]);
// void update_residence(int y, int x, char residences[2][50]);
// void delete_residence(int y, int x, char residences[2][50]);

// // Telas do módulo Receita/Despesa
// void dashboard_finance(int y, int x);
// void create_finance(int y, int x, char type);
// void read_finance(int y, int x, char transaction[4][50], char type);
// void update_finance(int y, int x, char transaction[4][50], char type);
// void delete_finance(int y, int x, char transaction[4][50], char type);

// Animações de tela
void fade_animation(const char*);
void draw_rainbow_logo(int, int);

// Elementos de Interface
void draw_box(int, int, int, int);
void draw_menu_options(int, int, char *[], int);
void draw_logo(int, int);
char draw_alert(const char*[], const int, int);
// void input_box(int width, const char *prompt, char *buffer, int max_len);

#endif