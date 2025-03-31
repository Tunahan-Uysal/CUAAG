#ifndef DEBUG_H
#define DEBUG_H

#include <stdbool.h>

extern bool DEBUG_MODE;

void debug_print(const char* format, ...);
void debug_error(const char* format, ...);
void debug_success(const char* format, ...);

#endif
