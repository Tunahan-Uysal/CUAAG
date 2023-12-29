#include <stdio.h>
#include <stdlib.h>
#include "image.h"

#define arraylen(a) (sizeof(a) / sizeof(a[0]))

void ascii_generation(Matrix* luminescence, char* path, char* charset) {
   int height = luminescence->height;
   int width = luminescence->width;

   // Free each row of the 2D array
   for (int i = 0; i < height; ++i) {
       free(luminescence->data[i]);
   }
   
   // Then free the array itself
   free(luminescence->data);

   free(luminescence);
}
