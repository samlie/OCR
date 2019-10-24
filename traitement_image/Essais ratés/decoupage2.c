#include <stdio.h>

void printMat(size_t nbrows, size_t nbcols, short mat[nbrows*nbcols])
{
	for (size_t rows=0; rows<nbrows; rows++)
	{
	    for(size_t cols=0; cols<nbcols; cols++)
	    {
	         printf("%d ", mat[rows*nbrows + cols]);
	    }
	    printf("\n");
	}
	printf("\n");
}

void initialize(size_t nbrows, size_t nbcols, short mat[nbrows*nbcols])
{
	for (size_t rows=0; rows<nbrows; rows++)
	{
	    for(size_t cols=0; cols<nbcols; cols++)
	    {
	         mat[rows*nbrows + cols] = 0;
	    }
	}
}

void printTabMat(size_t nbmat, size_t nbrows, size_t nbcols, short tabMat[nbmat][nbrows*nbcols], short limit)
{
	size_t limit2 = (size_t) limit;
	for (size_t mat=0; mat<limit2; mat++)
	{
		for (size_t rows=0; rows<nbrows; rows++)
		{
		    for(size_t cols=0; cols<nbcols; cols++)
		    {
		    	if (tabMat[mat][rows*nbrows + cols])
		        	printf("%d ", tabMat[mat][rows*nbrows + cols]);
		    	else
		    		printf("  ");
		    }
		    printf("\n");
		}
		printf("\n");
	}
}


void _colorMat(size_t nbrows, size_t nbcols, short mat[nbrows*nbcols], size_t rows, size_t cols, short nb)
{
	if (mat[rows*nbrows + cols] == 1)
	{
		mat[rows*nbrows + cols] = nb;
		if (rows != nbrows) {
			_colorMat(nbrows, nbcols, mat, rows+1, cols, nb);
		}
		if (rows != 0) {
			_colorMat(nbrows, nbcols, mat, rows-1, cols, nb);
		}
		if (cols != 0) {
			_colorMat(nbrows, nbcols, mat, rows, cols-1, nb);
		}
		if (cols != nbcols) {
			_colorMat(nbrows, nbcols, mat, rows, cols+1, nb);
		}

	}
}

void colorMat(size_t nbrows, size_t nbcols, short mat[nbrows*nbcols])
{
	short nb = 2;
	for (size_t rows=0; rows<nbrows; rows++)
	{
	    for(size_t cols=0; cols<nbcols; cols++)
	    	{
	        if (mat[rows*nbrows + cols] == 1) {
	        	_colorMat(nbrows, nbcols, mat, rows, cols, nb);
	        	nb+=1;
	        }
	    }
	}
}

void addMat(size_t nbmats, size_t nbrows, size_t nbcols, short tabMat[nbmats][nbrows*nbcols], size_t pos, short mat[nbrows*nbcols])
{
	for (size_t rows=0; rows<nbrows; rows++)
	{
	    for(size_t cols=0; cols<nbcols; cols++)
	    {
	        tabMat[pos][rows*nbrows + cols] = mat[rows*nbrows + cols];
	    }
	}
}


void boundAndColor(size_t nbrows, size_t nbcols, short mat[nbrows*nbcols], size_t rows, size_t cols, short nb, size_t bounds[4])
{
	if (mat[rows*nbrows + cols] == 1)
	{
		mat[rows*nbrows + cols] = nb;

		if (rows<bounds[0])
			bounds[0] = rows;
		if (rows>bounds[1])
			bounds[1] = rows;
		if (cols<bounds[2])
			bounds[2] = cols;
		if (cols>bounds[3])
			bounds[3] = cols;

		if (rows != nbrows) {
			boundAndColor(nbrows, nbcols, mat, rows+1, cols, nb, bounds);
		}
		if (rows != 0) {
			boundAndColor(nbrows, nbcols, mat, rows-1, cols, nb, bounds);
		}
		if (cols != 0) {
			boundAndColor(nbrows, nbcols, mat, rows, cols-1, nb, bounds);
		}
		if (cols != nbcols) {
			boundAndColor(nbrows, nbcols, mat, rows, cols+1, nb, bounds);


		}

	}
}

void matrix(size_t nbrows,size_t nbcols, short mat[nbrows*nbcols], size_t bounds[4], short mat2[nbrows*nbcols], short key)
{
	for (size_t rows=bounds[0]; rows<=bounds[1]; rows++)
	{
		for(size_t cols=bounds[2]; cols<=bounds[3]; cols++)
		{
			if (mat[rows*nbrows + cols] == key)
				mat2[(rows-bounds[0])*nbrows + (cols-bounds[2])] = 1;
	    }
	}
}

short isoleTache(size_t nbmats, size_t nbrows, size_t nbcols, short tabMat[nbmats][nbrows*nbcols], short mat[nbrows*nbcols])
{
	short nb = 2;
	for (size_t rows=0; rows<nbrows; rows++)
	{
		for(size_t cols=0; cols<nbcols; cols++)
		{
			if (mat[rows*nbrows + cols] == 1)
			{
				size_t bounds[4] = {nbrows, 0, nbcols, 0};
				boundAndColor(nbrows, nbcols, mat, rows, cols, nb, bounds);
				short caractere[nbrows*nbcols];
				initialize(nbrows, nbcols, caractere);
				matrix(nbrows, nbcols, mat, bounds, caractere, nb);
				addMat(nbmats, nbrows, nbcols, tabMat, nb-2, caractere);
			 	nb+=1;
			 	prin
	        }
	    }
	}
	return nb;
}

int main() {

	short mat[10*20] = 
	{
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,1,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,
	0,0,1,1,1,1,0,0,0,1,1,1,1,1,0,0,0,1,0,0,
	0,0,0,0,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,1,0,0,0,0,
	0,0,0,0,1,1,1,1,1,1,1,0,0,0,1,1,1,0,0,0,
	0,0,0,1,1,1,0,0,1,1,0,0,0,0,1,1,1,0,0,0,
	0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,1,0,1,0,0,
	0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,1,0,0,0,
	};

	//printMat(10,20,mat);
	//colorMat(10,20,mat);
	//printMat(10,20,mat);

	//printf("\n\n\n");

	short tabMat[1000][10*20];

	//printTabMat(7,10,20, tabMat);
	//printf("\n\n\n");
	//addMat(7,10,20, tabMat, 0, mat);
	

	short limit = isoleTache(1000, 10, 20, tabMat, mat) -2;

	printTabMat(1000,10,20, tabMat, limit);
	printMat(10,20, mat);

	return 0;
}