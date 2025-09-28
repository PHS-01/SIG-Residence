#ifndef TERMINAL_CONTROL_H
#define TERMINAL_CONTROL_H

// Cores básicas ANSI
enum Color {
    COLOR_DEFAULT = 39,
    COLOR_BLACK = 30,
    COLOR_RED = 31,
    COLOR_GREEN = 32,
    COLOR_YELLOW = 33,
    COLOR_BLUE = 34,
    COLOR_MAGENTA = 35,
    COLOR_CYAN = 36,
    COLOR_LIGHT_GRAY = 37,
    COLOR_DARK_GRAY = 90,
    COLOR_LIGHT_RED = 91,
    COLOR_LIGHT_GREEN = 92,
    COLOR_LIGHT_YELLOW = 93,
    COLOR_LIGHT_BLUE = 94,
    COLOR_LIGHT_MAGENTA = 95,
    COLOR_LIGHT_CYAN = 96,
    COLOR_WHITE = 97
};

// ANSI Utils
void move_cursor(int, int);
void ansi_print(int, int, const char*);
void clear_screen(void);
void update_terminal_size(int*, int*);
void hide_cursor(void);
void show_cursor(void);
void enable_bold(void);
void disable_bold(void);
void set_text_color(enum Color);
void reset_text_color(void);

// Termios Utils
char get_keypress(void);
void disable_raw_mode(void);
void enable_raw_mode(void);
void restore_terminal(void);

#endif