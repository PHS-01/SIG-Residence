#ifndef TERMINAL_CONTROL_H
#define TERMINAL_CONTROL_H

// ANSI Utils
void move_cursor(int, int);
void ansi_print(int, int, const char*);
void clear_screen(void);
void update_terminal_size(int*, int*);
void hide_cursor(void);
void show_cursor(void);

// Termios Utils
char get_keypress(void);
void disable_raw_mode(void);
void enable_raw_mode(void);
void restore_terminal(void);

#endif