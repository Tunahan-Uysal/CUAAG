#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/ioctl.h>
#include <string.h>
#include <math.h>
#include "../includes/debug.h"
#include "../includes/image.h"
#include "../includes/constants.h"


int giveHelp(char* programName);

/**
 * Program entry point - handles command line argument parsing and program initialization
 *
 * @param argc Number of command line arguments
 * @param argv Array of command line argument strings
 * @return EXIT_SUCCESS on successful execution, EXIT_FAILURE on error
 */
int main( int argc, char *argv[] ) {

    struct winsize w;
    ioctl(0, TIOCGWINSZ, &w);
    if (argc < 2 || strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
        giveHelp(argv[0]);
    }

    char* filePath, *charset;
    int width, height;
    bool customPath = false, customSize = false, customCharset = false;

    for (size_t i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-p") == 0) {
            customPath = true;
            filePath = argv[i+1];
            if (filePath == NULL) {
                debug_error("Error! No filePath inserted!\n");
                exit(ERROR_NO_PATH);
            }

            if (!is_valid_image(filePath)) {
                debug_error("Error! Invalid image file!\n");
                exit(ERROR_LOAD_FAILED);
            }
            debug_success("Given Path: %s\n", filePath);
            i++;
        }
        if (strcmp(argv[i], "-s") == 0) {
            customSize = true;

            if (i+1 == argc) {
                debug_error("Width is not determined! Please input a width value.\n");
                exit(ERROR_NO_WIDTH);
            }
            else {
                width = atoi(argv[i+1]);
            }
            if (i+2 == argc) {
                debug_error("Height is not determined! Please input a height value.\n");
                exit(ERROR_NO_HEIGHT);
            }
            else {
                height = atoi(argv[i+2]);
            }
            debug_print("Dimensions: %d x %d\n", width, height);
            i+=2;
        }
        if (strcmp(argv[i], "-c") == 0){
            customCharset = true;
            charset = argv[i+1];
            debug_print("Used Chars: %s\n", charset);
            i++;
        }
        if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--verbose") == 0) {
            DEBUG_MODE = true;
            continue;
        }
    }

    if (customPath == false) {
        debug_error("Path is missing!\n");
        giveHelp(argv[0]);
    }
    if (customSize == false) {
        width = w.ws_col;
        height = w.ws_row;
        debug_print("Default Dimensions: %d x %d\n", width, height);
    }
    if (customCharset == false) {
        charset = DEFAULT_CHARSET;
        debug_print("Default Used Chars: %s\n", charset);
        for (size_t i = 0; i < strlen(charset); i++)
        {
            // wtf is this for
            debug_print("%s %ld\n", &charset[i], i);

        }

    }

    for (int num = 255; num > 0; num--) {
        // this too
        debug_print("%c\n", charset[(int)round(num/CHARSET_DIVIDER)] + 0);
    }
    Matrix* luminescence = getimage(filePath, width, height);
    ascii_generation(luminescence, filePath, charset);
    return 0;
}
/**
 * Displays help information about program usage and commands
 *
 * @param programName The name of the executable
 * @return Always returns EXIT_SUCCESS
 */
int giveHelp(char* programName) {
    printf("Usage: %s [options]\n", programName);
    printf("Options:\n"
    " -p <path>   Specify the path to the image file (Uses working directory)\n"
    " -s <width> <height>   Specify the size of the image\n"
    " -c '<charset>'   Specify the charset of the image inbetween quotes and with no gaps inbetween characters\n"
    " -h, --help   Display this help message\n");
    exit(EXIT_SUCCESS);
}
