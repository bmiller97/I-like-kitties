#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "KernelFilter.h"

void S2_sobelFilter(float** img, int rows, int cols, float** outImg);
void S2_dilationFilter(float**img, int rows, int cols, float** outImg);


#define DISABLE_PRINTF
#ifdef DISABLE_PRINTF
    #define printf(fmt, ...) (0)
#endif







//DUMMY MAIN TO TEST
int main()
{
	printf("Start of Main\n");

	FILE *fp;
	int nRows, nColumns, i, ii;
	FILE *outfile;

	//INPUT FILE PROVIDED BY DR. GILAT-SCHMIDT
	char *fileName;	
	float **inputImage, **outputImage;			
	printf("Define Variables\n");


	//INPUT DIMENSIONS GIVEN BY DR. GILAT-SCHMIDT
	nRows=304;
	nColumns=304;
	//printf("I'M HERE 3\n");
	printf("Columns: %d	Rows: %d\n", nColumns, nRows);

	// LOAD FILE
	fp = fopen("test_image1.bin","rb");
	outfile = fopen("results.txt", "w");

	// CHECK IT EXISTS
	if (fp == NULL)
	{
		printf("File does not exist.\n");
		return 1;
	}
	else
	{
		printf("FILE EXISTS.\n");
	}

	// CREATE INPUT AND OUTPUT ARRAYS
	inputImage = (float**) malloc(nRows * sizeof(float*));
	outputImage = (float**) malloc(nRows * sizeof(float*));
	
	printf("Malloc image Rows\n");

	//unneeded for input, because buffer mallocs individual rows
	for (i = 0; i < nRows; i++)
	{
		outputImage[i] = (float*) malloc(nColumns * sizeof(float));
	}
	printf("Malloc image Columns\n");

	// GET INPUT ARRAY
	for (ii = 0; ii < nRows; ii++)
	{
		
		//read entire line of buffer instead of by individual float
		float* buffer = malloc(nColumns * sizeof(float));
		fread(buffer, sizeof(float), nColumns, fp);
		inputImage[ii] = buffer;
		
	}
	
	//CHECK INPUT ARRAY 
	int n, nn;
	fprintf(outfile,"Input array:\n");
	for (nn = 0; nn < nRows; nn++)
	{
		for (n = 0; n < nColumns; n++)
		{
			fprintf(outfile, "%.1f ", inputImage[n][nn]);
		}
		fprintf(outfile, "\n");
	}


	// SOBEL FILTER
	S2_sobelFilter(inputImage, nRows, nColumns, outputImage);

	//CHECK OUTPUT ARRAY 
//	fprintf(outfile,"\n\nOutput SOBEL array:\n");
//	for (nn = 0; nn < nColumns; nn++)
//	{
//		for (n = 0; n < nRows; n++)
//		{
//			fprintf(outfile, "%.1f ", &outputImage[n][nn]);
//		}
//		fprintf(outfile, "\n");
//	}


	//Dilation Filter
	S2_dilationFilter(outputImage, nRows, nColumns, inputImage);


	// EXIT
}


void S2_sobelFilter(float** img, int rows, int cols, float** outImg) 
{
	printf("SOBEL I'M HERE\n");

	FILE *SOBELoutfile;
	SOBELoutfile = fopen("SOBELresults.txt", "w");

	//horizontal and vertical filters
	float x_filter[3][3] = { {-1,0,1},{-1,0,1},{-1,0,1} };
	float y_filter[3][3] = { {-1,-1,-1},{0,0,0},{1,1,1} };

	//Initialize xImg and yImg
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
	printf("SOBEL I'M HERE 2");
	//CHECK X-IMAGE ARRAY
	int n, nn;
	fprintf(SOBELoutfile,"X-IMAGE:\n");
	for (nn = 0; nn < rows; nn++)
	{
		for (n = 0; n < cols; n++)
		{
			fprintf(SOBELoutfile, "%.1f ", xImg[nn][n]);
		}
		fprintf(SOBELoutfile, "\n");
	}

	printf("SOBEL I'M HERE 3");

	//find vertical (y) filter
	convolveImg(img, rows, cols, y_filter, 3, 3, yImg);
	
	//CHECK Y-IMAGE ARRAY
	fprintf(SOBELoutfile,"Y-IMAGE:\n");
	for (nn = 0; nn < rows; nn++)
	{
		for (n = 0; n < cols; n++)
		{
			fprintf(SOBELoutfile, "%.1f ", yImg[nn][n]);
		}
		fprintf(SOBELoutfile, "\n");
	}
//Was this supposed to have been completed??
	//combine filters
	//for y = range(0 cols)
	//	for x = range(0,rows)
	//		outImg[y][x] = sqrt(xImg[y][x]^2 + yImg[y][x]^2);
	for (ii = 0; ii < rows; ii++) {
		for (i = 0; i < cols; i++) {
			float xVal = xImg[ii][i];
			float yVal = yImg[ii][i];
			outImg[ii][i] = sqrtf(xVal * xVal + yVal * yVal);
		}
	}

	free(xImg);
	free(yImg);
	fclose(SOBELoutfile);

}

void S2_dilationFilter(float**img, int rows, int cols, float** outImg) 
{
	printf("DILATION I'M HERE\n");

	FILE *DILATIONoutfile;
	DILATIONoutfile = fopen("DILATIONresults.txt", "w");

	float blur_filter[3][3] = { {1,1,1},{1,1,1},{1,1,1} };
	
	//CHECK BLUR FILTER
	int i, ii;

	convolveImg(img, rows, cols, blur_filter, 3, 3, outImg);
	
	//CHECK Y-IMAGE ARRAY
	fprintf(DILATIONoutfile,"DILATION-IMAGE:\n");
	for (ii = 0; ii < rows; ii++)
	{
		for (i = 0; i < cols; i++)
		{
			fprintf(DILATIONoutfile, "%.1f ", outImg[ii][i]);
		}
		fprintf(DILATIONoutfile, "\n");
	}
	fclose(DILATIONoutfile);

	
}