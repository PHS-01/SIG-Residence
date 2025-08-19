#ifndef SCREENS_H
#define SCREENS_H

// Declaração das funções
void home();
void credits();
void about();
int sair();

void fade_animation(char *type);
void draw_building_border(char style, int border_margin_left_right, int border_margin_top_bottom);

#endif