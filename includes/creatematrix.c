#include <stdio.h>
#include <stdlib.h>
#include "image.h"

Matrix createMatrix(int width, int height) {
   // Allocate memory for rows
   Matrix matrix;
   matrix.width = width;
   matrix.height = height;
   matrix.data = (int **)malloc(height * sizeof(int*));
   if (!matrix.data) {
       printf("Memory error\n");
       exit(0);
   }

   // Allocate memory for columns
   for (int i = 0; i < height; ++i) {
       matrix.data[i] = (int *)malloc(width * sizeof(int));
       if (!matrix.data[i]) {
           printf("Memory error\n");
           exit(0);
       }
   }

   return matrix;
}