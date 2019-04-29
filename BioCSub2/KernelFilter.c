
#include <stdio.h>
#include <stdlib.h>
#include "KernelFilter.h"


void convolveImg(float** img, int rows, int cols, float* filter, int f_rows, int f_cols, float** outImg) 
{

	for (int y = 0; y < rows; y++) 
	{
		for (int x = 0; x < cols; x++) 
		{
			//find convolution filter value at location
			outImg[y][x] = getFilteredVal(img, rows, cols, filter, f_rows, f_cols, x, y);
		}
	}

}

float getFilteredVal(float** img, int rows, int cols, float* filter, int f_rows, int f_cols, int x,int y) {
	int center_y = (f_rows) / 2; //the center y value from the filter
	int center_x = f_cols / 2; //the center x value from the filter
	int real_x = 0; //the x location being tested from the img
	int real_y = 0; //the y location being tested from the img
	float out_val = 0; //total filtered value

	for (int i = 0; i < f_rows; i++) {
		for (int k = 0; k < f_cols; k++) {
			real_x = x + (center_x - k); //x value to test is offset from center of filter
			real_y = y + (center_y - i); //y value to test is offset from center of filter
			//out of bounds check
			if (real_x < 0 || real_x >= cols || real_y < 0 || real_y >= rows)
				continue;

			out_val += img[real_y][real_x] * filter[i*f_cols+k];
		}

	}
	return out_val;


}