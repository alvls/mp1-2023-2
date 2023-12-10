#pragma once
#include <math.h>

double (*function[4])(double, int);
double (*etalon[4])(double);

double sin_x(int x)
{

}

double cos_x(int x)
{

}

double expan(double x, int count)
{
	double e = 1, tmp = 1;
	for (int i = 1; i < count; i++)
	{
		tmp = tmp * (x / i);
		e = e + tmp;
	}
	return e;
}

double cosec(int x)
{

}

void func_arr()
{
	function[3] = expan;
	etalon[3] = exp;
}