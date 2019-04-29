#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "KernelFilter.h"

//DUMMY MAIN TO TEST
int main()
{
	printf("I'M HERE\n");

	FILE *fp;
	int nRows, nColumns, i, ii;
	FILE *outfile;

	//INPUT FILE PROVIDED BY DR. GILAT-SCHMIDT
	char *fileName;	
	float **inputImage, **outputImage;			
	printf("I'M HERE 2\n");


	//INPUT DIMENSIONS GIVEN BY DR. GILAT-SCHMIDT
	nRows=304;
	nColumns=304;
	printf("I'M HERE 3\n");
	printf("Columns: %d	Rows: %d\n", nColumns, nRows);

	// LOAD FILE
	fp = fopen("test_image1.bin","r");
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
	
	printf("NEW I'M HERE\n");

	for (i = 0; i < nRows; i++)
	{
		inputImage = (float**) malloc(nColumns * sizeof(float));
		outputImage = (float**) malloc(nColumns * sizeof(float));
	}
	printf("NEW I'M HERE 2\n");

	// GET INPUT ARRAY
	for (ii = 0; ii < nColumns; ii++)
	{
		for (i = 0; i < nRows; i++)
		{
			fscanf(fp, "%f", &inputImage[i][ii]);
		}
	}
	
	//CHECK INPUT ARRAY 
	int n, nn;
	fprintf(outfile,"Input array:\n");
	for (nn = 0; nn < nColumns; nn++)
	{
		for (n = 0; n < nRows; n++)
		{
			fprintf(outfile, "%.1f ", &inputImage[n][nn]);
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
	S2_dilationFilter(inputImage, nRows, nColumns, outputImage);


	// EXIT
}


void S2_sobelFilter(float** img, int rows, int cols, float** outImg) 
{
	printf("SOBEL I'M HERE\n");

	FILE *SOBELoutfile;
	SOBELoutfile = fopen("SOBELresults.txt", "w");

	//horizonal filter
	float x_filter[3][3] = { {-1,0,1},{-1,0,1},{-1,0,1} };

	//CHECK X-FILTER ARRAY 
	int i, ii;
	printf("X-FILTER array:\n");
	for (ii = 0; ii < 3; ii++)
	{
		for (i = 0; i < 3; i++)
		{
			printf("%.1f ", x_filter[i][ii]);
		}
		printf( "\n");
	}
	float y_filter[3][3] = { {-1,-1,-1},{0,0,0},{1,1,1} };
	
	//CHECK Y-FILTER ARRAY
	printf("Y-FILTER array:\n");
	for (ii = 0; ii < 3; ii++)
	{
		for (i = 0; i < 3; i++)
		{
			printf("%.1f ", x_filter[i][ii]);
		}
		printf( "\n");
	}
	float** xImg = malloc(sizeof(float)*rows*cols);
	float** yImg = malloc(sizeof(float)*rows*cols);
	
	//find horizontal (x) filter
	convolveImg(img, rows, cols, x_filter, 3, 3, xImg);
	printf("SOBEL I'M HERE 2");
	//CHECK X-IMAGE ARRAY
	int n, nn;
	fprintf(SOBELoutfile,"X-IMAGE:\n");
	for (nn = 0; nn < cols; nn++)
	{
		for (n = 0; n < rows; n++)
		{
			fprintf(SOBELoutfile, "%.1f ", xImg[i][ii]);
		}
		fprintf(SOBELoutfile, "\n");
	}

	printf("SOBEL I'M HERE 3");

	//find vertical (y) filter
	convolveImg(img, rows, cols, y_filter, 3, 3, yImg);
	
	//CHECK Y-IMAGE ARRAY
	fprintf(SOBELoutfile,"Y-IMAGE:\n");
	for (nn = 0; nn < cols; nn++)
	{
		for (n = 0; n < rows; n++)
		{
			fprintf(SOBELoutfile, "%.1f ", yImg[i][ii]);
		}
		fprintf(SOBELoutfile, "\n");
	}
//Was this supposed to have been completed??
	//combine filters
	//for y = range(0 cols)
	//	for x = range(0,rows)
	//		outImg[y][x] = sqrt(xImg[y][x]^2 + yImg[y][x]^2);

	free(xImg);
	free(yImg);
	fclose("SOBELresults.txt");

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
	fprintf(DILATIONoutfile,"Y-IMAGE:\n");
	for (ii = 0; ii < cols; ii++)
	{
		for (i = 0; i < rows; i++)
		{
			fprintf(DILATIONoutfile, "%.1f ", outImg[i][ii]);
		}
		fprintf(DILATIONoutfile, "\n");
	}
	fclose("DILATIONresults.txt");

	
}