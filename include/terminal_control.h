#ifndef TERMINAL_CONTROL_H
#define TERMINAL_CONTROL_H

#include <stddef.h> // Para size_t
#include <stdarg.h> // Para va_list

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

// Cores ANSI
#define COLOR_RESET   "\033[0m"
#define COLOR_RED     "\033[31m"
#define COLOR_GREEN   "\033[32m"
#define COLOR_YELLOW  "\033[33m"
#define COLOR_BLUE    "\033[34m"
#define COLOR_MAGENTA "\033[35m"
#define COLOR_CYAN    "\033[36m"
#define COLOR_WHITE   "\033[37m"

// Funções de output (agora variádicas)
void print_success(const char* message, ...);
void print_error(const char* message, ...);
void print_warning(const char* message, ...);
void print_info(const char* message, ...);

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

// Input Utils
void clear_input_buffer(void);
int read_int_input(const char* prompt, int* value);
int read_string_input(const char* prompt, char* buffer, size_t size);
int read_float_input(const char* prompt, float* value);
void wait_for_enter(void);

#endif