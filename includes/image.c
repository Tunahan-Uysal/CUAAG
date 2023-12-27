#include <stdio.h>

int getimage(char* path, int width, int height) {
    int channels;
    // zero seems to be auto assignment? docs dont say shit, not that the docs are good
    // TODO: create a way to add your file in
    unsigned char *img = stbi_load(&path, &width, &height, &channels, 0);
    if(img != NULL) {
        printf("%d\n", channels);
        if(img == NULL) {
            printf("File could not be loaded.\n");
            stbi_image_free(img);
            return NULL;
        }
        

        //stbi_write_png("old_image.png", width, height, channels, img, width * channels);
        unsigned char *output_img = malloc(width * height * channels);
        // Why does this have two sections where it must be zero? why!!!!!!!
        stbir_resize_uint8_srgb(img, width, height, 0, output_img, width, height, 0, channels);
        if (output_img != NULL) {
            printf("Success!\n");
            stbi_write_png("new_image.png", width, height, channels, output_img, width * channels);
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