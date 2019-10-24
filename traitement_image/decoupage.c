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


void initializefloat(size_t nbrows, size_t nbcols, float mat[nbrows][nbcols]) {
	for (size_t rows=0; rows<nbrows; rows++)
	{
	    for(size_t cols=0; cols<nbcols; cols++)
	    {
	         mat[rows][cols] = 0;
	    }
	}
}

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


void resize(size_t nbrows, size_t nbcols, int caractere[nbrows][nbcols], size_t n, float res[n][n])
{
	float factor;
	float alignvertical;
	float alignhorizontal;

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
	for (size_t row=0; row<nbrows; row++)
	{
		for(size_t col=0; col<nbcols; col++)
		{
			if (caractere[row][col]==1) {
				float newrow = row*factor + alignvertical;
				float newcol = col*factor + alignhorizontal;

				unsigned int newrowup = (int)newrow;
				unsigned int newcolleft = (int)newcol;
				unsigned int newrowdown = newrowup+1;
				unsigned int newcolright = newcolleft+1;

				float coeffup = (newrow-newrowup)*factor;
				float coeffleft = (newcol-newcolleft)*factor;
				float coeffdown = (newrowdown-newrow)*factor;
				float coeffright = (newcolright-newcol)*factor;

				res[newrowup][newcolleft] += coeffup*coeffleft;
				if (newcolright<nbcols) {res[newrowup][newcolright] += coeffup*coeffright;}
				if (newrowdown<nbrows) {res[newrowdown][newcolleft] += coeffdown*coeffleft;}
				if (newcolright<nbcols&&newrowdown<nbrows){res[newrowdown][newcolright] += coeffdown*coeffright;}
			}
		}
	}
}


void isoleTache(size_t nbrows, size_t nbcols, int mat[nbrows][nbcols])
{
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
				printMatfloatASCII(n, n, minicar);
				nb++;
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