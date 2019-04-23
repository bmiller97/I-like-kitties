

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "KernelFilter.h"


void Sobel(float** img, int rows, int cols, float** outImg) {

	//horizonal filter
	float x_filter[3][3] = { {-1,0,1},{-1,0,1},{-1,0,1} };
	float y_filter[3][3] = { {-1,-1,-1},{0,0,0},{1,1,1} };
	float** xImg = malloc(sizeof(float)*rows*cols);
	float** yImg = malloc(sizeof(float)*rows*cols);

	//find horizontal (x) filter
	convolveImg(img, rows, cols, x_filter, 3, 3, xImg);
	//find vertical (y) filter
	convolveImg(img, rows, cols, y_filter, 3, 3, yImg);


	//combine filters
	//for y = range(0 cols)
	//	for x = range(0,rows)
	//		outImg[y][x] = sqrt(xImg[y][x]^2 + yImg[y][x]^2);

}
