#ifndef GRAYSCALE_H
#define GRAYSCALE_H

#include <stdlib.h>
#include <SDL.h>
#include "pixel_operations.h"

void init_sdl();
SDL_Surface* load_image(char *path);
void print_matrix(char s[], int width, int height, int m[height][width]);
int getwidth(SDL_Surface* image_surface);
int getheight(SDL_Surface* image_surface);
void matrix(SDL_Surface* image_surface, int width, int height, int res[height][width]);

#endif