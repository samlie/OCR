#include <stdio.h>


//Print a matrix
void printMat(size_t nbrows, size_t nbcols, int mat[nbrows][nbcols]) {
	for (size_t rows=0; rows<nbrows; rows++)
	{
	    for(size_t cols=0; cols<nbcols; cols++)
	    {
	    	if (mat[rows][cols])
		        	printf("1");
		    	else
		    		printf("-");
	    }
	    printf("\n");
	}
	printf("\n");
}

// Prints a float matrix in ASCII Art (different characters with grayscale representing value)
void printMatfloatASCII(size_t nbrows, size_t nbcols, float mat[nbrows][nbcols]) {
	for (size_t rows=0; rows<nbrows; rows++)
	{
	    for(size_t cols=0; cols<nbcols; cols++)
	    {
	    	if (mat[rows][cols]>0.9f)
	    		printf("@");
	    	else if (mat[rows][cols]>0.8f)
	    		printf("%%");
	    	else if (mat[rows][cols]>0.7f)
	    		printf("#");
	    	else if (mat[rows][cols]>0.6f)
	    		printf("*");
	    	else if (mat[rows][cols]>0.5f)
	    		printf("+");
	    	else if (mat[rows][cols]>0.4f)
	    		printf("=");
	    	else if (mat[rows][cols]>0.2f)
	    		printf("-");
	    	else if (mat[rows][cols]>0)
	    		printf(".");
		    else
		   		printf(" ");
	    }
	    printf("\n");
	}
	printf("\n");
}

// Prints a float matrix with 0s and 1s
void printMatfloat(size_t nbrows, size_t nbcols, float mat[nbrows][nbcols]) {
	for (size_t rows=0; rows<nbrows; rows++)
	{
	    for(size_t cols=0; cols<nbcols; cols++)
	    {
	    	if (mat[rows][cols]>0.6f)
	    		printf("1");
		    else
		   		printf("-");
	    }
	    printf("\n");
	}
	printf("\n");
}

//Initialize a matrix filled with 0
void initialize(size_t nbrows, size_t nbcols, int mat[nbrows][nbcols]) {
	for (size_t rows=0; rows<nbrows; rows++)
	{
	    for(size_t cols=0; cols<nbcols; cols++)
	    {
	        mat[rows][cols] = 0;
	    }
	}
}

// Initializes a float matrix with 0s
void initializefloat(size_t nbrows, size_t nbcols, float mat[nbrows][nbcols]) {
	for (size_t rows=0; rows<nbrows; rows++)
	{
	    for(size_t cols=0; cols<nbcols; cols++)
	    {
	         mat[rows][cols] = 0;
	    }
	}
}


// A recursive flood fill algorithm that starts at the given point in the matrix and fills every
// connected pixel with the given number
void boundAndColor(size_t nbrows, size_t nbcols, int mat[nbrows][nbcols], size_t rows, size_t cols, int nb, size_t bounds[4])
{
	if (mat[rows][cols] == 1)
	{
		//Coloration of the pixel with his number
		mat[rows][cols] = nb;		

		//Update the rows and the bounds
		if (rows<bounds[0])
			bounds[0] = rows;
		if (rows>bounds[1])
			bounds[1] = rows;
		if (cols<bounds[2])
			bounds[2] = cols;
		if (cols>bounds[3])
			bounds[3] = cols;

		if (rows != nbrows)
		{
			//If the raw is different from the last row
			//Recursion on the next row
			boundAndColor(nbrows, nbcols, mat, rows+1, cols, nb, bounds);
		}
		if (rows != 0)
		{
			//if the row is different from the first row
			boundAndColor(nbrows, nbcols, mat, rows-1, cols, nb, bounds);
		}
		if (cols != 0)
		{
			boundAndColor(nbrows, nbcols, mat, rows, cols-1, nb, bounds);
		}
		if (cols != nbcols)
		{
			boundAndColor(nbrows, nbcols, mat, rows, cols+1, nb, bounds);
		}

	}
}


// Fills a smaller matrix with portion of a bigger matrix
void matrixdec(size_t nbrows,size_t nbcols, int mat[nbrows][nbcols], size_t bounds[4], int mat2[bounds[1]-bounds[0]+1][bounds[3]-bounds[2]+1], int key) {
	for (size_t rows=bounds[0]; rows<=bounds[1]; rows++)
	{
		for(size_t cols=bounds[2]; cols<=bounds[3]; cols++)
		{
			//Copy the part of the matrix filled with the character
			//Thanks to its coordonates
			if (mat[rows][cols] == key)
			{
				mat2[rows-bounds[0]][cols-bounds[2]] = 1;
			}
	    }
	}
}


// Resizes a matrix of 0s and 1s to a smaller matrix (smaller matrix only !)
// The given matrix becomes a float matrix
void resize(size_t nbrows, size_t nbcols, int caractere[nbrows][nbcols], size_t n, float res[n][n])
{
	float factor;
	float alignvertical;
	float alignhorizontal;

	// Choose the right resizing factor based on matrix proportions
	if (nbrows>nbcols)
	{
		factor = n/(nbrows/1.0f);
		alignvertical = 0;
		alignhorizontal = (n-(nbcols*factor))/2.0f;
	}
	else
	{
		factor = n/(nbcols/1.0f);
		alignvertical = (n-(nbrows*factor))/2.0f;
		alignhorizontal = 0;
	}

	// For each old pixel, compute the new positions and color it
	for (size_t row=0; row<nbrows; row++)
	{
		for(size_t col=0; col<nbcols; col++)
		{
			if (caractere[row][col]==1) {
				// New positions (float)
				float newrow = row*factor + alignvertical;
				float newcol = col*factor + alignhorizontal;

				// New positions (rounded up to the floor and ceil integers)
				unsigned int newrowup = (int)newrow;
				unsigned int newcolleft = (int)newcol;
				unsigned int newrowdown = newrowup+1;
				unsigned int newcolright = newcolleft+1;

				// Coefficients for the new positions
				float coeffup = (newrow-newrowup)*factor;
				float coeffleft = (newcol-newcolleft)*factor;
				float coeffdown = (newrowdown-newrow)*factor;
				float coeffright = (newcolright-newcol)*factor;

				// Edit the values of the pixels in the new matrix
				res[newrowup][newcolleft] += coeffup*coeffleft;
				if (newcolright<nbcols) {res[newrowup][newcolright] += coeffup*coeffright;}
				if (newrowdown<nbrows) {res[newrowdown][newcolleft] += coeffdown*coeffleft;}
				if (newcolright<nbcols&&newrowdown<nbrows){res[newrowdown][newcolright] += coeffdown*coeffright;}
			}
		}
	}
}

int poww(int x, int n) 
{
	if (n <= 0) 
	{
		return 1;
	}
	else 
	{
		return (int)x*poww(x,n-1);
	}
}

void save(int n, float minicar[n][n])
{
	FILE * fp;

    /* open the file for writing*/
	fp = fopen("sortie.txt","a");
    for (int rows=0; rows<n; rows++)
	{
	    for(int cols=0; cols<n; cols++)
	    {
	    	int value = (int)(minicar[rows][cols]*255);
	    	for (int i = 7; i >=0; i--)
	    	{
	    		int div = poww(2, i);
		    	if (value>=div) 
		    	{
		    		value -= div;
		    		fprintf(fp, "%d", 1);
		    	}
		    	else 
		    	{
		    		fprintf(fp, "%d", 0);
		    	}
		    }
	    	/*
	    	if (minicar[rows][cols])
		        	fprintf(fp, "%d", 1);
		    	else
		    		fprintf(fp, "%d", 0);*/
	    }
	}
	fprintf(fp, "\n");
	fclose (fp);
}


void isoleTache(size_t nbrows, size_t nbcols, int mat[nbrows][nbcols])
{
	FILE * fp;

    /* open the file for writing*/
	fp = fopen("sortie.txt","w");
	fclose (fp);

	//Represents the color of the character
	int nb = 2;
	for (size_t rows=0; rows<nbrows; rows++)
	{
		for(size_t cols=0; cols<nbcols; cols++)
		{
			//Meet a "1"
			if (mat[rows][cols]==1){
				//Create a list
				//Bounds[0] = Minimal row
				//Bounds[1] = Maximal row
				//Bounds[2] = Minimal col
				//Bounds[3] = Maximal col
				size_t bounds[4] = {nbrows, 0, nbcols, 0};
				boundAndColor(nbrows, nbcols, mat, rows, cols, nb, bounds);
				size_t nbrowschar = bounds[1]-bounds[0]+1;
				size_t nbcolschar = bounds[3]-bounds[2]+1;
				int caractere[nbrowschar][nbcolschar];
				initialize(nbrowschar, nbcolschar, caractere);
				//printMat(nbrowschar, nbcolschar, caractere);
				matrixdec(nbrows, nbcols, mat, bounds, caractere, nb);
				int n = 16;
				float minicar[n][n];
				initializefloat(n, n, minicar);
				resize(nbrowschar, nbcolschar, caractere, n, minicar);
				save(n, minicar);
				printMatfloatASCII(n, n, minicar);
				nb++;
	        }
	    }
	}
}


/*

void isoleTacheFromLine(size_t nbrows, size_t nbcols, int mat[nbrows][nbcols], int bounds[4])
{
	FILE * fp;

    // open the file for writing
	fp = fopen("sortie.txt","w");
	fclose (fp);
	//Represents the color of the character
	int nb = 2;
	for (int cols=bounds[0]; cols<bounds[2]; cols++)
	{
		for(int rows=bounds[1]; rows<bounds[3]; rows++)
		{
			//Meet a "1"
			if (mat[rows][cols]==1){
				//Create a list
				//Bounds[0] = Minimal row
				//Bounds[1] = Maximal row
				//Bounds[2] = Minimal col
				//Bounds[3] = Maximal col
				size_t bounds[4] = {nbrows, 0, nbcols, 0};
				boundAndColor(nbrows, nbcols, mat, rows, cols, nb, bounds);
				size_t nbrowschar = bounds[1]-bounds[0]+1;
				size_t nbcolschar = bounds[3]-bounds[2]+1;
				int caractere[nbrowschar][nbcolschar];
				initialize(nbrowschar, nbcolschar, caractere);
				//printMat(nbrowschar, nbcolschar, caractere);
				matrixdec(nbrows, nbcols, mat, bounds, caractere, nb);
				int n = 16;
				float minicar[n][n];
				initializefloat(n, n, minicar);
				//So that it's not too big
				resize(nbrowschar, nbcolschar, caractere, n, minicar);
				//Save the char in the file
				save(n, minicar);
				printMatfloatASCII(n, n, minicar);
				nb++;
	        }
	    }
	}
} */



void isoleTacheFromLine(size_t nbrows, size_t nbcols, int mat[nbrows][nbcols], int bounds[4])
{
	
	//Represents the color of the character
	int nb = 2;
	size_t innerbounds[4] = {nbrows, 0, nbcols, 0};
	int scanningcharacter = 0;


	for (int cols=bounds[0]; cols<bounds[2]+1; cols++)
	{
		int nbtrouve = 0;
		for(int rows=bounds[1]; rows<bounds[3]+1; rows++)
		{
			if (mat[rows][cols]==nb) 
			{
				nbtrouve=1;
			}

			//Meet a "1"
			if (mat[rows][cols]==1)
			{
				nbtrouve = 1;
				scanningcharacter = 1;
				//Create a list
				//Bounds[0] = Minimal row
				//Bounds[1] = Maximal row
				//Bounds[2] = Minimal col
				//Bounds[3] = Maximal col


				size_t newbounds[4] = {nbrows, 0, nbcols, 0};
				boundAndColor(nbrows, nbcols, mat, rows, cols, nb, newbounds);
				if (innerbounds[0] > newbounds[0]) 
				{
					innerbounds[0] = newbounds[0];
				}
				if (innerbounds[1] < newbounds[1]) 
				{
					innerbounds[1] = newbounds[1];
				}
				if (innerbounds[2] > newbounds[2]) 
				{
					innerbounds[2] = newbounds[2];
				}
				if (innerbounds[3] < newbounds[3]) 
				{
					innerbounds[3] = newbounds[3];
				}
				
	        }
	    }

	    if (cols==bounds[2] || (nbtrouve == 0 && scanningcharacter))
	    {
	    	scanningcharacter = 0;
			size_t nbrowschar = innerbounds[1]-innerbounds[0]+1;
			size_t nbcolschar = innerbounds[3]-innerbounds[2]+1;
			int caractere[nbrowschar][nbcolschar];
			initialize(nbrowschar, nbcolschar, caractere);
			//printMat(nbrowschar, nbcolschar, caractere);

			matrixdec(nbrows, nbcols, mat, innerbounds, caractere, nb);

			int n = 16;
			float minicar[n][n];
			initializefloat(n, n, minicar);
			//So that it's not too big
			resize(nbrowschar, nbcolschar, caractere, n, minicar);
			//Save the char in the file
			innerbounds[0] = nbrows;
			innerbounds[1] = 0;
			innerbounds[2] = nbcols;
			innerbounds[3] = 0;
			save(n, minicar);
			printMatfloatASCII(n, n, minicar);
			nb++;
	    }
	}
}







// Extracts the lines of text from the matrix
void getLineBlocks(size_t nbrows, size_t nbcols, int mat[nbrows][nbcols], int nboftextrows, int allbounds[nboftextrows][4])
{
	// Bounds for vertical cropping of the next ocurring text line
	int upperbound = 0;
	int lowerbound = 0;

	// Bounds for horizontal cropping of the next occurring line
	int min_leftbound = nbcols;
	int max_rightbound = 0;

	// 1 if we're currently between two lines, 0 if we're currently on a text line
	int interligne = 0;
	
	int i = 0;

	for (unsigned int row = 0; row < nbrows; row++) {
		int emptyline = 1;
		int leftbound = 0;
		int rightbound = 0;

		for (unsigned int col = 0; col < nbcols; col++) {
			if (mat[row][col]==1) {
				if (emptyline==1) {
					leftbound=col;
					emptyline=0;
				}
				rightbound=col;
			}
		}

		if (emptyline==0) {
			// If the line wasn't empty, ajust the min and max bounds
			if (leftbound < min_leftbound) min_leftbound = leftbound;
			if (rightbound > max_rightbound) max_rightbound = rightbound;			
		}

		if (emptyline==0 && interligne==1) {
			// This means the beginning of a new line, so keep in memory the current row
			upperbound = row;
			interligne = 0;
		}

		else if (emptyline==1 && interligne==0) {
			if (row == 0) {interligne = 1;}
			else {
				// This means the end of a text line
				interligne = 1;
				lowerbound = row - 1;

				// Dimensions of the text line
				size_t lineheight = lowerbound - upperbound + 1;
				size_t linewidth = max_rightbound - min_leftbound + 1;

				// Copy values into a matrix of the corresponding size
				int textline[lineheight][linewidth];
				initialize(lineheight, linewidth, textline);
				size_t bounds[4] = {upperbound, lowerbound, min_leftbound, max_rightbound};
				matrixdec(nbrows, nbcols, mat, bounds, textline, 1);
				printMat(lineheight, linewidth, textline);

				// Keep the bounds in memory so we can draw rectangles around text later
				allbounds[i][0] = min_leftbound;
				allbounds[i][1] = upperbound;
				allbounds[i][2] = max_rightbound;
				allbounds[i][3] = lowerbound;
				
				i++;

				// Reset the min and max horizontal bounds
				min_leftbound = nbcols;
				max_rightbound = 0;
			}
		}
	}
}

/*
int main2(int width, int height, int mat[height][width])
{

	//printMat(10,20,mat);
	//colorMat(10,20,mat);
	//printMat(10,20,mat);

	//printf("\n\n\n");

	//printTabMat(7,10,20, tabMat);
	//printf("\n\n\n");
	//addMat(7,10,20, tabMat, 0, mat);
	

	int limit = isoleTache(1000, width, height, mat) -2;

	return 0;
}*/