#ifndef SCREENS_H
#define SCREENS_H

/*
Declaração das funções
*/

// Telas
void home();
void credits();
void about();
int sair();

// Animações de tela
void fade_animation(char *type, int delay);
void animation_building_border(char style, int border_margin_left_right, int border_margin_top_bottom, int delay);
void animation_logo_staircase(int y, int x, int delay);

// Elementos de Interface
void draw_border(char style, int border_margin_left_right, int border_margin_top_bottom);

#endif