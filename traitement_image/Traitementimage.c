#include <stdio.h>
#include <stdint.h>

/*#define MAXCHAR 1000

void readimage(){
	FILE *fp;
    char str[MAXCHAR];
    char* filename = "/home/samantha/OCR/pil_text.bmp";

    fp = fopen(filename, "rb");
    if (fp == NULL){
        printf("Could not open file %s",filename);
    }
    while (fgets(str, MAXCHAR, fp) != NULL)
        printf("%s", str);
    fclose(fp);
}*/

header()
{
    //read the file
    FILE* img = fopen("/home/samantha/OCR/pil_text.bmp", "rb");
    unsigned char header[54];


    // read the 54-byte header
    size_t a = fread(header, sizeof(unsigned char), 54, img); 

    // extract image information from header
    int width = *(int*)&header[18];     //width of the image
    int height = *(int*)&header[22];    //height of the image
    int bpp = *(int*)&header[28];       //number of bits per pixels
    int bpc = bpp/3;                    //number of bits per colors
    int matrix[width*height];           //output matrix

    int paddingsize = 4-(bpp/8*width%4)%4;
    int r, g, b;
    unsigned char padding[paddingsize];
    uint16_t greyscale;
    uint16_t red;
    uint16_t blue;
    uint16_t green;
    size_t inutile;


    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            inutile = fread(&blue, 16, 1, img);
            inutile = fread(&green, 16, 1, img);
            inutile = fread(&red, 16, 1, img);
            printf("%d  ", red);/*
            r = (int)red[0]<<8+(int)red[1];
            g = (int)green[0]<<8+(int)green[1]; 
            b = (int)blue[0]<<8+(int)blue[1];
            printf("%d  ", b);
            greyscale = 0.212671f*r + 0.715160f*g + 0.072169f*b;
            matrix[i*width + j] = greyscale;
            //printf("%d ",matrix[i*width + j]);
            */
        }
        inutile = fread(padding, sizeof(unsigned char), paddingsize, img);
        printf("\n");
    }
    printf("%zu\n", inutile);*/
                            
    fclose(img); //close the file 
}
