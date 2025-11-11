#include "terminal_control.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

void print_success(const char* message, ...) {
    char formatted_message[512];
    va_list args;
    
    va_start(args, message);
    vsnprintf(formatted_message, sizeof(formatted_message), message, args);
    va_end(args);
    
    printf(COLOR_GREEN "✓ %s" COLOR_RESET "\n", formatted_message);
}

void print_error(const char* message, ...) {
    char formatted_message[512];
    va_list args;
    
    va_start(args, message);
    vsnprintf(formatted_message, sizeof(formatted_message), message, args);
    va_end(args);
    
    printf(COLOR_RED "✗ %s" COLOR_RESET "\n", formatted_message);
}

void print_warning(const char* message, ...) {
    char formatted_message[512];
    va_list args;
    
    va_start(args, message);
    vsnprintf(formatted_message, sizeof(formatted_message), message, args);
    va_end(args);
    
    printf(COLOR_YELLOW "⚠ %s" COLOR_RESET "\n", formatted_message);
}

void print_info(const char* message, ...) {
    char formatted_message[512];
    va_list args;
    
    va_start(args, message);
    vsnprintf(formatted_message, sizeof(formatted_message), message, args);
    va_end(args);
    
    printf(COLOR_CYAN "%s" COLOR_RESET "\n", formatted_message);
}