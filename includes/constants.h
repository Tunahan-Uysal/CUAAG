#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <string.h>

// Processing Image Values -> Chars
#define LUMINESCENCE_R 0.2126
#define LUMINESCENCE_G 0.7152
#define LUMINESCENCE_B 0.0722

static inline float calculate_charset_divider(const char* charset) {
    return 255.0 / (strlen(charset) - 0.999);
}

#define CHARSET_DIVIDER calculate_charset_divider(charset)
#define DEFAULT_CHARSET "@%&QWNM0gB#$DR8mHXAKUObPd9h6PkqwSE2iF7JvtL?szy*cr!+><;=^,_':.-`";

#define ERROR_NO_PATH 1
#define ERROR_NO_WIDTH 2
#define ERROR_NO_HEIGHT 3
#define ERROR_LOAD_FAILED 4

#endif
