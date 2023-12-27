#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/ioctl.h>
#include <string.h>
#define STB_IMAGE_IMPLEMENTATION
#include "../includes/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../includes/stb_image_write.h"
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "../includes/stb_image_resize2.h"
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

    getimage(filePath, width, height);

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

int getImage(void) {

    int width, height, channels;
    // zero seems to be auto assignment? docs dont say shit, not that the docs are good
    // TODO: create a way to add your file in
    unsigned char *img = stbi_load("temp.png", &width, &height, &channels, 0);
    if(img != NULL) {
        printf("%d\n", channels);
        if(img == NULL) {
            printf("File could not be loaded.\n");
            stbi_image_free(img);
            exit(EXIT_FAILURE);
        }
        

        //stbi_write_png("old_image.png", width, height, channels, img, width * channels);
        unsigned char *output_img = malloc(80 * 80 * channels);
        // Why does this have two sections where it must be zero? why!!!!!!!
        stbir_resize_uint8_srgb(img, width, height, 0, output_img, 80, 80, 0, channels);
        if (output_img != NULL) {
            printf("Success!\n");
            stbi_write_png("new_image.png", 80, 80, channels, output_img, 80 * channels);
        }
        else {
            printf("sorry\n");
        }
        // Free the memory used for the new image and the original image
        stbi_image_free(img);
        free(output_img);
    }

    return 0;
}


