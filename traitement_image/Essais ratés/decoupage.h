#ifndef GRAYSCALE_H
#define GRAYSCALE_H

#include <stdlib.h>
#include <SDL.h>
#include "pixel_operations.h"

void initialize(int height, int width, int mat[height][width]);
void printTabMat(int height, int width, int tabMat[1000][height*width], int limit);
void _colorMat(int height, int width, int mat[height*width], int i, int j, int nb);
void colorMat(int height, int width, int mat[height][width]);
void addMat(int nbmats, int height, int width, int tabMat[nbmats][height*width], int pos, int mat[height*width]);
void boundAndColor(int height, int width, int mat[height*width], int i, int j, int nb, int bounds[4]);
void matrix2(int height,int width, int mat[height*width], int bounds[4], int mat2[height*width], int key);
int isoleTache(int nbmats, int height, int width, int tabMat[nbmats][height*width], int mat[height*width]);




#endif