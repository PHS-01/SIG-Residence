#include "terminal_control.h"
#include <stdio.h> 

void print_success(const char* message) {
    printf(COLOR_GREEN "✓ %s" COLOR_RESET "\n", message);
}

void print_error(const char* message) {
    printf(COLOR_RED "✗ %s" COLOR_RESET "\n", message);
}

void print_warning(const char* message) {
    printf(COLOR_YELLOW "⚠ %s" COLOR_RESET "\n", message);
}

void print_info(const char* message) {
    printf(COLOR_CYAN "ℹ %s" COLOR_RESET "\n", message);
}