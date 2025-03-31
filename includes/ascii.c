#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "debug.h"
#include "image.h"
#include "constants.h"

#define arraylen(a) (sizeof(a) / sizeof(a[0]))

void ascii_generation(Matrix* luminescence, char* path, char* charset) {
   int height = luminescence->height;
   int width = luminescence->width;

    for (size_t y = 0; y < height; y++)
    {

        for (size_t x = 0; x < width; x++)
        {
            int luminescenceChar = charset[(int)round(luminescence->data[y][x]/CHARSET_DIVIDER)] + 0;
            printf("%c",luminescenceChar);
        }
        printf("\n");
    }


   for (int i = 0; i < height; ++i) {
       free(luminescence->data[i]);
   }

   free(luminescence->data);

   free(luminescence);
}
