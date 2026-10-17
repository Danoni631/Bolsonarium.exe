#pragma once

#include "Bolsonarium.h"

#define PI 3.141592653589793238462643383279

inline void Reflect2D(int* x, int* y, int w, int h)
{
	*x = abs(*x);
	*y = abs(*y);

	int rx = *x / w;
	int ry = *y / h;

	*x = (rx % 2 == 0) ? (*x % w) : (w - 1 - (*x % w));
	*y = (ry % 2 == 0) ? (*y % h) : (h - 1 - (*y % h));
}