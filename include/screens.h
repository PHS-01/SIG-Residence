#ifndef SCREENS_H
#define SCREENS_H

/*
Declaração das funções
*/

// Telas
void home(int y, int x);
void credits(int y, int x);
void about(int y, int x);
int confirm_exit(int y, int x);

// Animações de tela
void fade_animation(char *type, int delay);
void animation_building_border(char style, int border_margin_left_right, int border_margin_top_bottom, int delay);
void animation_logo_staircase(int y, int x, int delay);

// Elementos de Interface
void draw_border(char style, int border_margin_left_right, int border_margin_top_bottom);
char draw_alert(const char *msg[], const int length_msg, int width, bool space);

#endif