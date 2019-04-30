#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "KernelFilter.h"

void S2_sobelFilter(float** img, int rows, int cols, float** outImg);
void S2_dilationFilter(float**img, int rows, int cols, float** outImg);


//#define DISABLE_PRINTF
//#ifdef DISABLE_PRINTF
//    #define printf(fmt, ...) (0)
//#endif


//DUMMY MAIN TO TEST
int main()
{
	// LOAD FILES
	FILE *fp;
	FILE *DILATIONoutfile;
	FILE *SOBELoutfile;
	FILE *INPUT;
	fp = fopen("test_image2.bin","rb");
	DILATIONoutfile = fopen("DILATIONresults.bin", "wb");
	SOBELoutfile = fopen("SOBELresults.bin", "wb");
	INPUT= fopen("INPUTimage.bin", "wb");

	//INITIALIZE VARIABLES
	int nRows, nColumns, i, ii, n, nn;
	float **inputImage, **outputImage;			

	//INPUT IMAGE DIMENSIONS
	nRows=304;
	nColumns=304;

	// CHECK INPUT FILE EXISTS
	if (fp == NULL)
	{
		printf("File does not exist.\n");
		return 1;
	}
	else
	{
		//printf("INPUT FILE EXISTS.\n");
	}
	
	// CREATE INPUT AND OUTPUT ARRAYS
	inputImage = (float**) malloc(nRows * sizeof(float*));
	outputImage = (float**) malloc(nRows * sizeof(float*));
	
	//unneeded for input, because buffer mallocs individual rows
	for (i = 0; i < nRows; i++)
	{
		outputImage[i] = (float*) malloc(nColumns * sizeof(float));
	}

	// GET INPUT ARRAY
	for (ii = 0; ii < nRows; ii++)
	{
		float* buffer = malloc(nColumns * sizeof(float));
		fread(buffer, sizeof(float), nColumns, fp);
		inputImage[ii] = buffer;	
	}

	
	//CHECK INPUT ARRAY 
	for (nn = 0; nn < nRows; nn++)
	{		
		fwrite(inputImage[nn], sizeof(float), nColumns, INPUT);
		
		//fprintf(INPUT, "\n");
	}

	// SOBEL FILTER
	S2_sobelFilter(inputImage, nRows, nColumns, outputImage);

	//CHECK SOBEL OUTPUT ARRAY 
	for (nn = 0; nn < nColumns; nn++)
	{
		fwrite(outputImage[nn], sizeof(float), nColumns, SOBELoutfile);

	}


	//Dilation Filter
	S2_dilationFilter(outputImage, nRows, nColumns, inputImage);
	
	//CHECK DILATION OUTPUT
	for (ii = 0; ii < nRows; ii++)
	{
		fwrite(inputImage[ii], sizeof(float), nColumns, DILATIONoutfile);

	}
	fclose(DILATIONoutfile);
	fclose(SOBELoutfile);
	fclose(INPUT);
	fclose(fp);


	// EXIT
}


void S2_sobelFilter(float** img, int rows, int cols, float** outImg) 
{

	//make horizontal and vertical filters
	float x_filter[3][3] = { {-1,0,1},{-1,0,1},{-1,0,1} };
	float y_filter[3][3] = { {-1,-1,-1},{0,0,0},{1,1,1} };

	//initialize xImg and yImg
	int i =0, ii = 0;
	int r_size = sizeof(float*)*rows;
	float** xImg = malloc(r_size);
	float** yImg = malloc(r_size);
	int c_size = sizeof(float)*cols;
	for (i = 0; i < rows; i++) {
		xImg[i] = malloc(c_size);
		yImg[i] = malloc(c_size);
	}

	//find horizontal (x) filter
	convolveImg(img, rows, cols, x_filter, 3, 3, xImg);


	//find vertical (y) filter
	convolveImg(img, rows, cols, y_filter, 3, 3, yImg);
	
	//COMBINE X AND Y FILTERS
	for (ii = 0; ii < rows; ii++) {
		for (i = 0; i < cols; i++) {
			float xVal = xImg[ii][i];
			float yVal = yImg[ii][i];
			outImg[ii][i] = sqrtf(xVal * xVal + yVal * yVal);
		}
	}

	free(xImg);
	free(yImg);

}

void S2_dilationFilter(float**img, int rows, int cols, float** outImg) 
{

	//make blur filter
	float blur_filter[3][3] = { {1,1,1},{1,1,1},{1,1,1} };

	//apply blur filter
	convolveImg(img, rows, cols, blur_filter, 3, 3, outImg);

	
}