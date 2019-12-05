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

	FILE * fp;

    /* open the file for writing*/
	fp = fopen("sortie.txt","w");
	fclose (fp);

	int width = getwidth(image_surface);
	int height = getheight(image_surface);
	printf("%d %d \n", width, height);

	// Create a matrix of the corresponding size
	int res[height][width];

	// Fill the matrix with the 
	matrix(image_surface, width, height, res);

	// Print the matrix on screen
    //print_matrix("matrix", width, height, res);

	// Displays the color image in a window and 
	SDL_Surface* screen_surface = display_image(image_surface);
    wait_for_keypressed();
    // We know that we have three lines of text, but otherwise the function is 
    // able to determine the number of lines 
    //int x = getNbOfLines(width, height, res);
    int a[5][4];
    getLineBlocks(height, width, res, 5, a);

	for (int i = 0; i<5; i++) {
		// Draws a red rectangle around the detected text line
		isoleTacheFromLine(height, width, res, a[i]);
    	encadre(image_surface, a[i][0], a[i][1], a[i][2], a[i][3]);
    }

    // Update the surface on screen
	update_surface(screen_surface, image_surface);
	wait_for_keypressed();

    // Release the surface in memory
    SDL_FreeSurface(image_surface);

	// Isolates, resizes and prints every connex region of pixels (supposedly a character)
    //isoleTache(height, width, res);

	return 0;
}