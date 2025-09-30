#ifndef TERMINAL_CONTROL_H
#define TERMINAL_CONTROL_H

// Cores básicas ANSI
enum Color {
    MY_COLOR_BLACK = 30,
    MY_COLOR_RED = 31,
    MY_COLOR_GREEN = 32,
    MY_COLOR_YELLOW = 33,
    MY_COLOR_BLUE = 34,
    MY_COLOR_MAGENTA = 35,
    MY_COLOR_CYAN = 36,
    MY_COLOR_LIGHT_GRAY = 37,
    MY_COLOR_DARK_GRAY = 90,
    MY_COLOR_LIGHT_RED = 91,
    MY_COLOR_LIGHT_GREEN = 92,
    MY_COLOR_LIGHT_YELLOW = 93,
    MY_COLOR_LIGHT_BLUE = 94,
    MY_COLOR_LIGHT_MAGENTA = 95,
    MY_COLOR_LIGHT_CYAN = 96,
    MY_COLOR_WHITE = 97
};


// ANSI Utils
void move_cursor(int, int);
void ansi_print(int, int, const char*);
void clear_screen(void);
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
void set_terminal_size(int, int);
void update_terminal_size(int*, int*);

#endif