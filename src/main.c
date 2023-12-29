#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/ioctl.h>
#include <string.h>
#include <math.h>
#include "../includes/image.h"


int giveHelp(char* programName);

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
                printf("Error! No filePath inserted!\n");
                exit(EXIT_FAILURE);
            }
            printf("Given Path: %s\n", filePath);
            i++;
        } 
        if (strcmp(argv[i], "-s") == 0) {
            customSize = true;

            if (i+1 == argc) {
                printf("Width is not determined! Please input a width value.\n");
                exit(EXIT_FAILURE);
            }
            else {
                width = atoi(argv[i+1]);
            }
            if (i+2 == argc) {
                printf("Height is not determined! Please input a height value.\n");
                exit(EXIT_FAILURE);
            }
            else {
                height = atoi(argv[i+2]);
            }
            printf("Dimensions: %d x %d\n", width, height);
            i+=2;
        } 
        if (strcmp(argv[i], "-c") == 0){
            customCharset = true;
            charset = argv[i+1];
            printf("Used Chars: %s\n", charset);
            i++;
        }
    }

    if (customPath == false) {
        printf("Path is missing!\n");
        giveHelp(argv[0]);
    }
    if (customSize == false) {
        width = w.ws_row;
        height = w.ws_col;
        printf("Default Dimensions: %d x %d\n", width, height);
    }  
    if (customCharset == false) {
        charset = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'.";
        printf("Default Used Chars: %s\n", charset);
        for (size_t i = 0; i < strlen(charset); i++)
        {
            printf("%s %ld\n", &charset[i], i);

        }
        
    }

    for (int num = 255; num > 0; num--) { 
        printf("%c\n", charset[(int)round(num/3.75)] + 0);
    }
    Matrix* luminescence = getimage(filePath, width, height);
    ascii_generation(luminescence, filePath, charset);
    return 0;
}   

int giveHelp(char* programName) {
    printf("Usage: %s [options]\n", programName);
    printf("Options:\n");
    printf(" -p <path>   Specify the path to the image file (Uses working directory)\n");
    printf(" -s <width> <height>   Specify the size of the image\n");
    printf(" -c '<charset>'   Specify the charset of the image inbetween quotes and with no gaps inbetween characters\n");
    printf(" -h, --help   Display this help message\n");
    exit(EXIT_SUCCESS);
}


