#include "debug.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdarg.h>

bool DEBUG_MODE = false;

void debug_print(const char* format, ...) {
    if (!DEBUG_MODE) return;

    va_list args;
    va_start(args, format);
    printf("[DEBUG] ");
    vprintf(format, args);
    printf("\n");
    va_end(args);
}

void debug_error(const char* format, ...) {
    va_list args;
    va_start(args, format);
    printf("\033[0;31m[ERROR] "); // Red text
    vprintf(format, args);
    printf("\033[0m\n"); // Reset color
    va_end(args);
}

void debug_success(const char* format, ...) {
    va_list args;
    va_start(args, format);
    printf("\033[0;32m[SUCCESS] "); // Green text
    vprintf(format, args);
    printf("\033[0m\n"); // Reset color
    va_end(args);
}
