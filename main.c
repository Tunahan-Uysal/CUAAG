#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb/stb_image_resize2.h"

int  main(void) {
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

