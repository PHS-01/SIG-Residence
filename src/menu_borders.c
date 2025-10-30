#include "menu_borders.h"

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