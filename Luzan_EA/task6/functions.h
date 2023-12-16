#pragma once
#include <stdio.h>
#include <math.h>

#define SIZE 3

#define pi 3.1415926535897

// ������ ������������?
double interval[SIZE][2] = {
		{-INFINITY, INFINITY},
		{-pi / 2, pi / 2},
		{0, pi}
};

typedef double (*TfuncPart) (double, int, double*, unsigned long long*);

typedef double (*TfuncInpWork) (double);      //������� �� �������� ���������� �������� ���������� 
									    	  //��� ����� ������������� ������ �������


double expPart(double x, int n, double* preX, unsigned long long* preFac);

double sinPart(double x, int n, double* preX, unsigned long long* preFac);

double cosPart(double x, int n, double* preX, unsigned long long* preFac);

