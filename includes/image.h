#ifndef IMAGE_H
#define IMAGE_H

#include <stdbool.h>

typedef struct {
 int** data;
 int width;
 int height;
} Matrix;

Matrix createMatrix(int width, int height);

Matrix* getluminescence(unsigned char* image, int width, int height, int channels);
Matrix* getimage(char* path, int width, int height);
bool is_valid_image(const char* path);

void ascii_generation(Matrix* luminescence, char* path, char* charset);

#endif
