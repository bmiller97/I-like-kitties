#pragma once

void convolveImg(float** img, int rows, int cols, float** filter, int f_rows, int f_cols, float** outImg);
float getFilteredVal(float** img, int rows, int cols, float** filter, int f_rows, int f_cols, int x, int y);