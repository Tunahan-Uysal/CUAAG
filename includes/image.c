#include <stdio.h>
#include "image.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../lib/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../lib/stb_image_write.h"
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "../lib/stb_image_resize2.h"

Matrix* getluminescence(unsigned char* image, int width, int height, int channels) {
    printf("Before the createMatrix\n with values: %d and %d\n", width, height);
    Matrix* luminescence = malloc(sizeof(Matrix));
    *luminescence = createMatrix(width, height);
    printf("Before the ForLoop\n with values: %d and %d\n", width, height);
    for (size_t y = 0; y < height; y++)
    {
        
        for (size_t x = 0; x < width; x++)
        {        
            printf("Before the RGB\n with values: %ld and %ld\n", x, y);   
            unsigned char R = image[y*width*channels + x*channels + 0];
            unsigned char G = image[y*width*channels + x*channels + 1];
            unsigned char B = image[y*width*channels + x*channels + 2];
            (luminescence)->data[y][x] = 0.2126 * R + 0.7152 * G + 0.0722 * B;
            
            printf("%ld, %ld, %dx%d\n", x, y, width, height);
        }
        printf("\n");
    }
    printf("After the ForLoop\n");
    printf("end");
    free(image);
    return luminescence;
}
Matrix* getimage(char* path, int _width, int _height) {
    int width, height, channels;
    // zero seems to be auto assignment? docs dont say shit, not that the docs are good
    // TODO: create a way to add your file in
    unsigned char *img = stbi_load(path, &width, &height, &channels, 0);
    if(img != NULL) {
        printf("%d\n", channels);
        if(img == NULL) {
            printf("File could not be loaded.\n");
            stbi_image_free(img);
            return NULL;
        }
        
        //stbi_write_png("old_image.png", width, height, channels, img, width * channels);
        unsigned char *output_img = malloc(_width * _height * channels);
        // Why does this have two sections where it must be zero? why!!!!!!!
        stbir_resize_uint8_srgb(img, width, height, 0, output_img, _height, _width, 0, channels);
        if (output_img != NULL) {
            printf("Success!\n");
            stbi_write_png("new_image.png", _height, _width, channels, output_img, _height * channels);
            stbi_image_free(img);
            return getluminescence(output_img, _width, _height, channels);
        }
        else {
            printf("sorry\n");
        }
        // Free the memory used for the new image and the original image
        // have to keep it allocated as ill be using it next
    }
    else {
        printf("failure case %s", path);
        EXIT_FAILURE;
    }
    return NULL;
}