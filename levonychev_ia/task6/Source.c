#define _CRT_SECURE_NO_WARNINGS

#include <math.h>
#include <stdio.h>  
#include <stdlib.h>
#include <memory.h>
#include <Windows.h>
#include <wincon.h>

#include "MyFunc.h"

void modes(int mode);
double temp(double x, double precision, int N, int* pcount);

int main()
{	
	char mode;
	printf("This is a calculator of functions that are calculated using Taylor series, please, select program mode:\n");
	printf("1 - One-time calculation of a function at a given point\n");
	printf("2 - Serial experiment\n");

	do
	{	
		printf("--> ");
		mode = getchar();
		getchar();
		if (mode != '1' && mode != '2')
			printf("Input error!\n");
	} while (mode != '1' && mode != '2');
	system("cls");

	if (mode == '1')
		modes(1);
	if (mode == '2')
		modes(2);
	system("pause");
	return 0;
}

void modes(int mode)
{	
	char func; // Selecting a function
	double x; // Argument
	double precision;
	int N; // Number of series elements (mode 1)
	int NMax; // number of experiments (mode 2)
	int count; // Number of terms that were calculated (mode 1)
	int* pcount = &count;
	*pcount = -1;
	char* name_func = "temp";

	double (*my_function) (double, double, int, int*);
	my_function = temp;

	double (*function) (double);
	function = sin;

	printf("Please, select the function:\n");
	printf("1 - e^x\n");
	printf("2 - sin(x)\n");
	printf("3 - cos(x)\n");
	printf("4 - asinh(x)\n");
	do
	{
		printf("--> ");
		func = getchar();
		getchar();
		if (func < '1' || func > '4')
			printf("Input error!\n");
	} while (func < '1' || func > '4');
	system("cls");

	if (func == '4')
	{	
		printf("Enter function argument (abs(x) < 1):\n");
		do
		{
			printf("--> ");
			scanf("%lf", &x);
			if (x <= -1 || x >= 1)
				printf("Input error!\n");
		} while (x <= -1 || x >= 1);
	}
	else
	{	
		printf("Enter function argument:\n");
		printf("--> ");
		scanf("%lf", &x);
	}
	system("cls");

	if (mode == 1)
	{
		printf("Enter calculation precision (>= 0.000001):\n");
		do
		{
			printf("--> ");
			scanf("%lf", &precision);
			if (precision < 0.000001)
				printf("Input error!\n");
		} while (precision < 0.000001);
		system("cls");
		printf("Enter the number of series elements to perform the calculation (N - from 1 to 1000):\n");
		do
		{
			printf("--> ");
			scanf("%d", &N);
			if (N < 1 || N > 1000)
				printf("Input error!\n");
		} while (N < 1 || N > 1000);
		system("cls");
	}
	if (mode == 2)
	{
		printf("Enter the number of experiments (NMax - from 1 to 25):\n");
		do
		{
			printf("--> ");
			scanf("%d", &NMax);
			if (NMax < 1 || NMax > 25)
				printf("Input error!\n");
		} while (NMax < 1 || NMax > 25);
		system("cls");
	}

	if (func == '1')
	{
		function = exp;
		my_function = my_exp;
		name_func = "e^";
	}
	if (func == '2')
	{	
		function = sin;
		my_function = my_sin;
		name_func = "sin";
	}
	if (func == '3')
	{	
		function = cos;
		my_function = my_cos;
		name_func = "cos";
	}
	if (func == '4')
	{
		function = asinh;
		my_function = my_asinh;
		name_func = "asinh";
	}

	if (mode == 1)
	{
		printf("%s(%g) = %lf (from math.h)\n", name_func, x, function(x));
		printf("my_%s(%g) = %lf (from MyFunc.h)\n\n", name_func, x, my_function(x, precision, N, pcount));
		printf("my_%s(%g) - %s(%g) = %lf\n", name_func, x, name_func, x, my_function(x, precision, N, pcount) - function(x));
		printf("Number of terms that were calculated = %d\n", *pcount);
	}
	if (mode == 2)
	{	
		printf("x = %lf\n", x);
		printf("f(x) = %s(x)\n", name_func);
		printf("my_f(x) = my_%s(x)\n", name_func);
		printf("+----+---------------------+--------------------------+\n");
		printf("|NMax|              my_f(x)|            my_f(x) - f(x)|\n");
		printf("+----+---------------------+--------------------------+\n");
		for (int i = 1; i <= NMax; i++)
			printf("|%4d| %20lf| %25lf|\n", i, my_function(x, 0, i, pcount), my_function(x, 0, i, pcount) - function(x));
		printf("+----+---------------------+--------------------------+\n");
		printf("%s(%lf) = %lf (from math.h)\n", name_func, x, function(x));
	}
}

double temp(double x, double precision, int N, int* pcount)
{
	return 0.;
}
