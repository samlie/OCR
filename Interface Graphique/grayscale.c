#include <err.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "pixel_operations.h"
#include <stdio.h>

void init_sdl()
{
    // Init only the video part.
    // If it fails, die with an error message.
    if(SDL_Init(SDL_INIT_VIDEO) == -1)
        errx(1,"Could not initialize SDL: %s.\n", SDL_GetError());
}

SDL_Surface* load_image(char *path)
{
    SDL_Surface *img;

    // Load an image using SDL_image with format detection.
    // If it fails, die with an error message.
    img = IMG_Load(path);
    if (!img)
        errx(3, "can't load %s: %s", path, IMG_GetError());

    return img;
}

void print_matrix(char s[], int width, int height, int m[height][width])
{
    printf("%s =\n", s);
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            if (m[i][j])
                printf("%d", m[i][j]);
            else
                printf(" ");
        }
        printf("\n");
    }
}

void encadre(SDL_Surface* image_surface, int x1, int y1, int x2, int y2) {

    Uint32 color = 16711680;
    for (int x = x1; x <= x2; x++) {
        put_pixel(image_surface, x, y1, color);
        put_pixel(image_surface, x, y2, color);
    }

    for (int y = y1+1; y < y2; y++) {
        put_pixel(image_surface, x1, y, color);
        put_pixel(image_surface, x2, y, color);
    }
}

int getwidth(SDL_Surface* image_surface)
{
    int width = image_surface->w;       //width of the image
    return width;
}

int getheight(SDL_Surface* image_surface)
{
    int height = image_surface->h;      //height of the image
    return height;
}



void matrix(SDL_Surface* image_surface, int width, int height, int res[height][width])
{
    /*//output matrix
    int matrix[width*height];  */         

    //Initiate the values we'll need
    Uint32 pixel;
    Uint8 r, g, b, gray;

    //Will put the color in the output matrix
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            //load the pixel
            pixel = get_pixel(image_surface, j, i);

            //take the rgb values of the pixel
            SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);

            //change the rgb values in greyscale
            gray = 0.212671f*r + 0.715160f*g + 0.072169f*b;

            //Thresholding and filling the output matrix
            if (gray > 127)
            {
                res[i][j] = 0;
            }
            else
            {
                res[i][j] = 1;
            }
        }
    }
}

