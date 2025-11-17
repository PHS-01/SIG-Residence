#include "menu_borders.h"

// Função para calcular o comprimento real da string no terminal (considerando caracteres acentuados)
int string_display_length(const char *str) {
    int length = 0;
    unsigned char *p = (unsigned char *)str;
    
    while (*p) {
        // Caracteres acentuados em UTF-8 começam com 0xC3
        if (*p == 0xC3 && *(p+1)) {
            // Pula o caractere acentuado (conta como 1 caractere, não 2)
            length++;
            p += 2;
        } else {
            length++;
            p++;
        }
    }
    return length;
}

// Função para imprimir string com padding correto
void print_padded_string(const char *str, int width) {
    int actual_length = string_display_length(str);
    int padding = width - actual_length;
    
    if (padding > 0) {
        printf("%s%*s", str, padding, "");
    } else {
        // Se a string for muito longa, trunca
        printf("%.*s", width, str);
    }
}

// Função para imprimir uma linha formatada do detail
void print_detail_line(const char *label, const char *value, int label_width, int value_width) {
    int label_padding = label_width - string_display_length(label);
    int value_padding = value_width - string_display_length(value);
    
    printf("║ %s", label);
    if (label_padding > 0) printf("%*s", label_padding, "");
    
    printf(" %s", value);
    if (value_padding > 0) printf("%*s", value_padding, "");
    printf(" ║\n");
}

// Versão para valores inteiros
void print_detail_line_int(const char *label, int value, int label_width, int value_width) {
    char value_str[20];
    snprintf(value_str, sizeof(value_str), "%d", value);
    print_detail_line(label, value_str, label_width, value_width);
}

// Versão para valores float
void print_detail_line_float(const char *label, float value, int label_width, int value_width) {
    char value_str[20];
    snprintf(value_str, sizeof(value_str), "%.2f", value);
    print_detail_line(label, value_str, label_width, value_width);
}

void draw_top_border(int width) {
    printf("%s", BORDER_TOP_LEFT);
    for (int i = 0; i < width - 2; i++) {
        printf("%s", BORDER_HORIZONTAL);
    }
    printf("%s\n", BORDER_TOP_RIGHT);
}

void draw_bottom_border(int width) {
    printf("%s", BORDER_BOTTOM_LEFT);
    for (int i = 0; i < width - 2; i++) {
        printf("%s", BORDER_HORIZONTAL);
    }
    printf("%s\n", BORDER_BOTTOM_RIGHT);
}

void draw_middle_border(int width) {
    printf("%s", BORDER_LEFT_T);
    for (int i = 0; i < width - 2; i++) {
        printf("%s", BORDER_HORIZONTAL);
    }
    printf("%s\n", BORDER_RIGHT_T);
}

void draw_text_line(const char* text, int width) {
    printf("%s %-*s %s\n", BORDER_VERTICAL, width - 4, text, BORDER_VERTICAL);
}

void draw_menu_line(const char* text, int width) {
    printf("%s  %-*s  %s\n", BORDER_VERTICAL, width - 6, text, BORDER_VERTICAL);
}

void draw_centered_text_line(const char* text, int width) {
    int text_len = strlen(text);
    int padding = (width - 2 - text_len) / 2;
    int extra_padding = (width - 2 - text_len) % 2;
    
    printf("%s", BORDER_VERTICAL);
    for (int i = 0; i < padding; i++) printf(" ");
    printf("%s", text);
    for (int i = 0; i < padding + extra_padding; i++) printf(" ");
    printf("%s\n", BORDER_VERTICAL);
}

void draw_empty_line(int width) {
    printf("%s", BORDER_VERTICAL);
    for (int i = 0; i < width - 2; i++) printf(" ");
    printf("%s\n", BORDER_VERTICAL);
}

void draw_menu_header(const char* title, int width) {
    draw_top_border(width);
    draw_centered_text_line(title, width);
    draw_middle_border(width);
}

void draw_simple_header(const char* title, int width) {
    draw_top_border(width);
    draw_centered_text_line(title, width);
    draw_bottom_border(width);  // Agora usamos a borda inferior normal
}

void draw_menu_option(int number, const char* text, int width) {
    char option[100];
    if (number == 0) {
        snprintf(option, sizeof(option), "[0] %s", text);
    } else {
        snprintf(option, sizeof(option), "[%d] %s", number, text);
    }
    draw_menu_line(option, width);
}

void draw_menu_footer(int width) {
    draw_bottom_border(width);
}