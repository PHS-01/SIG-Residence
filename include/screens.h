#ifndef SCREENS_H
#define SCREENS_H

/*
Declaração das funções
*/

// Telas
bool home(int, int);
// void credits(int y, int x);
// void about(int y, int x);
// int confirm_exit(int y, int x);

// // Telas do modulo pessoas
// void dashboard_people(int y, int x);
// void create_people(int y, int x);
// void read_people(int y, int x, char people[4][50]);
// void update_people(int y, int x, char people[4][50]);
// void delete_people(int y, int x, char people[4][50]);

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

// // Animações de tela
// void fade_animation(char *type, int delay);
// void animation_building_border(char style, int border_margin_left_right, int border_margin_top_bottom, int delay);
// void animation_logo_staircase(int y, int x, int delay);

// Elementos de Interface
void draw_border(int, int);
void draw_menu_options(int, int, char *[], int);
void draw_logo(int, int);
// char draw_alert(const char *msg[], const int length_msg, int width, bool space);
// void input_box(int width, const char *prompt, char *buffer, int max_len);

#endif