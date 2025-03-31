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
// I have no fucking clue what charset_divider is
// I just made it up
// It crashes if its lower than who knows what, i dont even really know what it changes
// 3.2 crashes
// 3.5 crashes
// 3.6 doesnt crash
// anything above it works
// 3.55 crashes
// 3.58 doesnt crash
// 3.56 crashes
// 3.57 doesnt crash
// 3.565 doesnt crash
// 3.5625 doesnt crash
// 3.561 doesnt crash
// 3.5601 doesnt crash
// 3.56 doesnt crash (???)
// 3.555 didnt crash
// 3.5 crashed
// what even is the pattern

#define DEFAULT_CHARSET "@%&QWNM0gB#$DR8mHXAKUObPd9h6PkqwSE2iF7JvtL?szy*cr!+><;=^,_':.-`";

#define ERROR_NO_PATH 1
#define ERROR_NO_WIDTH 2
#define ERROR_NO_HEIGHT 3
#define ERROR_LOAD_FAILED 4

#endif
