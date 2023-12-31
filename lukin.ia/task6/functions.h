#pragma once
#include <math.h>

double (*function[4])(double, int);
double (*etalon[4])(double);

double sin_x(double x, int count)
{
	double e = x, tmp;
	int flag, k=3, j=5, f_k, f_j;
	if (count == 1)
		return x;
	flag = 1;//механизм чередования
	for (int i = 2; i <= count; i++)
	{
		tmp = 1;
		if (flag == 1)//отриц
		{
			for (f_k = 1; f_k <= k; f_k++)
			{
				tmp = tmp * x/f_k;
			}
			e = e - tmp;
			k = k + 4;
			flag = 2;
		}
		else if (flag == 2)//полож
		{
			for (f_j = 1; f_j <= j; f_j++)
			{
				tmp = tmp * x / f_j;
			}
			e = e + tmp;
			j = j + 4;
			flag = 1;
		}
	}
	return e;
}

double cos_x(double x, int count)
{
	double e = 1, tmp;
	int flag, k = 2, j = 4, f_k, f_j;
	if (count == 1)
		return 1;
	flag = 1;//механизм чередования знаков
	for (int i = 2; i <= count; i++)
	{
		tmp = 1;
		if (flag == 1)//отриц
		{
			for (f_k = 1; f_k <= k; f_k++)
			{
				tmp = tmp * x / f_k;
			}
			e = e - tmp;
			k = k + 4;
			flag = 2;
		}
		else if (flag == 2)//полож
		{
			for (f_j = 1; f_j <= j; f_j++)
			{
				tmp = tmp * x / f_j;
			}
			e = e + tmp;
			j = j + 4;
			flag = 1;
		}
	}
	return e;
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

double cosec(double x, int count)
{
	double e = x, tmp;
	int flag, k = 3, j = 5, f_k, f_j;
	if (count == 1)
		return x;
	flag = 1;//механизм чередования
	for (int i = 2; i <= count; i++)
	{
		tmp = 1;
		if (flag == 1)//отриц
		{
			for (f_k = 1; f_k <= k; f_k++)
			{
				tmp = tmp * x / f_k;
			}
			e = e - tmp;
			k = k + 4;
			flag = 2;
		}
		else if (flag == 2)//полож
		{
			for (f_j = 1; f_j <= j; f_j++)
			{
				tmp = tmp * x / f_j;
			}
			e = e + tmp;
			j = j + 4;
			flag = 1;
		}
	}
	return 1/e;
}

void func_arr()
{
	function[3] = expan;
	etalon[3] = exp;
	function[1] = sin_x;
	etalon[1] = sin;
	function[2] = cos_x;
	etalon[2] = cos;
	function[4] = cosec;
	etalon[4] = sin;
}