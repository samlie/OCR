#include "grayscale.h"
#include <stdio.h>
#include <err.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "pixel_operations.h"
#include "decoupage.h"

int main()
{

	init_sdl();
	//Create the sdl surface we'll use
	SDL_Surface* image_surface = load_image("pil_text.bmp");

	int width = getwidth(image_surface);
	int height = getheight(image_surface);
	printf("%d %d \n", width, height);


	int res[height][width];

	matrix(image_surface, width, height, res);

    print_matrix("matrix", width, height, res);
    isoleTache(height, width, res);


    SDL_FreeSurface(image_surface);
	return 0;
}