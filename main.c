#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

int  main(void) {
    int width, height, channels;
    stbi_set_flip_vertically_on_load(true);  
    unsigned char *img = stbi_load("proxy-image.png", &width, &height, &channels, 0);
    if(img != NULL) {
        unsigned char *new_img = malloc(width * height * channels);
        if(new_img == NULL) {
            printf("Error allocating memory for new image\n");
            stbi_image_free(img);
            return 1;
        }

        for(int i = 0; i < width; i++) {
            for(int k = 0; k < height; k++) {
                unsigned char r = img[k*width*channels + i*channels + 0];
                unsigned char g = img[k*width*channels + i*channels + 1];
                unsigned char b = img[k*width*channels + i*channels + 2];
                unsigned char a = img[k*width*channels + i*channels + 3];
                printf("RGB values of pixel %d %d: %d %d %d %d\n", i, k, r, g, b, a);
            
            

                // Fill the new image with the RGB values
                new_img[k*width*channels + i*channels + 0] = r;
                new_img[k*width*channels + i*channels + 1] = g;
                new_img[k*width*channels + i*channels + 2] = b;
                new_img[k*width*channels + i*channels + 3] = a;
            }
        }
        // Write the new image to a PNG file
        printf(new_img);
        stbi_write_png("new_image.png", width, height, channels, new_img, width * channels);

        // Free the memory used for the new image and the original image
        free(new_img);
        stbi_image_free(img);
    }

    return 0;
}   

