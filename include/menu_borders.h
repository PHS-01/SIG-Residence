#ifndef MENU_BORDERS_H
#define MENU_BORDERS_H

#include <stdio.h>
#include <string.h>

// Caracteres de borda
#define BORDER_TOP_LEFT "╔"
#define BORDER_TOP_RIGHT "╗"
#define BORDER_BOTTOM_LEFT "╚"
#define BORDER_BOTTOM_RIGHT "╝"
#define BORDER_HORIZONTAL "═"
#define BORDER_VERTICAL "║"
#define BORDER_LEFT_T "╠"
#define BORDER_RIGHT_T "╣"

// Largura padrão dos menus
#define MENU_WIDTH 70

// Funções para desenhar bordas
void draw_top_border(int width);
void draw_bottom_border(int width);
void draw_middle_border(int width);
void draw_text_line(const char* text, int width);
void draw_menu_line(const char* text, int width);
void draw_centered_text_line(const char* text, int width);
void draw_empty_line(int width);

// Cabeçalho simples (sem borda do meio em T)
void draw_simple_header(const char* title, int width);

// Menus completos
void draw_menu_header(const char* title, int width);
void draw_menu_option(int number, const char* text, int width);
void draw_menu_footer(int width);

#endif