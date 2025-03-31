#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "image.h"
#include "debug.h"
#include "constants.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../lib/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../lib/stb_image_write.h"
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "../lib/stb_image_resize2.h"

/*
 * This function takes in an image and returns a matrix of the luminescence
 * of the image.
 *
 * @param image The image to be processed.
 * @param width The width of the image.
 * @param height The height of the image.
 * @param channels The number of channels in the image.
 * @return A matrix of the luminescence of the image.
 */
Matrix* getluminescence(unsigned char* image, int width, int height, int channels) {
    //printf("Before the createMatrix\n with values: %d and %d\n", width, height);
    Matrix* luminescence = malloc(sizeof(Matrix));
    *luminescence = createMatrix(width, height);
    //printf("Before the ForLoop\n with values: %d and %d\n", width, height);
    for (size_t y = 0; y < height; y++)
    {

        for (size_t x = 0; x < width; x++)
        {
            //printf("Before the RGB\n with values: %ld and %ld\n", x, y);
            unsigned char R = image[y*width*channels + x*channels + 0];
            unsigned char G = image[y*width*channels + x*channels + 1];
            unsigned char B = image[y*width*channels + x*channels + 2];
            (luminescence)->data[y][x] = LUMINESCENCE_R * R +
                                         LUMINESCENCE_G * G +
                                         LUMINESCENCE_B * B;

            //printf("%ld, %ld, %dx%d\n", x, y, width, height);
        }
        //printf("\n");
    }
    free(image);
    return luminescence;
}
/*
 * This function takes in a path to an image and returns true if the image
 * is valid.
 *
 * @param path The path to the image.
 * @return True if the image is valid, false otherwise.
 */
bool is_valid_image(const char* path) {
    int _width, _height, _channels;
    if (!stbi_info(path, &_width, &_height, &_channels)) {
        debug_error("Invalid or inaccessible image: %s", path);
        debug_error("STB Error: %s", stbi_failure_reason());
        return false;
    }
    debug_success("Valid image found: %dx%d, %d channels", _width, _height, _channels);
    return true;
}

/*
 * This function takes in a path to an image and returns a matrix of the
 * luminescence of the image.
 *
 * @param path The path to the image.
 * @param _width The width of the image.
 * @param _height The height of the image.
 * @return A matrix of the luminescence of the image.
 */
Matrix* getimage(char* path, int _width, int _height) {
    int width, height, channels;
    // zero seems to be auto assignment? docs dont say shit, not that the docs are good
    // TODO: create a way to add your file in
    unsigned char *img = stbi_load(path, &width, &height, &channels, 0);
    if(img != NULL) {
        debug_print("%d\n", channels);
        if(img == NULL) {
            debug_error("File could not be loaded.\n");
            stbi_image_free(img);
            return NULL;
        }

        //stbi_write_png("old_image.png", width, height, channels, img, width * channels);
        unsigned char *output_img = malloc(_width * _height * channels);
        // Why does this have two sections where it must be zero? why!!!!!!!
        stbir_resize_uint8_srgb(img, width, height, 0, output_img, _width, _height, 0, channels);
        if (output_img != NULL) {
            debug_success("Success!\n");
            stbi_write_png("new_image.png", _width, _height, channels, output_img, _width * channels);
            stbi_image_free(img);
            return getluminescence(output_img, _width, _height, channels);
        }
        else {
            debug_error("Failed to resize image to %dx%d", _width, _height);
        }
        // Free the memory used for the new image and the original image
        // have to keep it allocated as ill be using it next
    }
    else {
        debug_error("failure case %s", path);
        EXIT_FAILURE;
    }
    return NULL;
}
