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

// Função para calcular o comprimento real da string no terminal (considerando caracteres acentuados)
int string_display_length(const char* str);
void print_padded_string(const char* str, int width);

// Funções para imprimir linhas detalhadas
void print_detail_line(const char* label, const char* value, int label_width, int value_width);
void print_detail_line_int(const char* label, int value, int label_width, int value_width);
void print_detail_line_float(const char* label, float value, int label_width, int value_width);

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