#pragma once
#include <stdio.h>
#include <math.h>

#define SIZE 3
#define pi 3.1415926535897

double intervals[SIZE][2];

typedef double (*TfuncPart) (double, int, double*, unsigned long long*);

typedef double (*TfuncInpWork) (double);      //хорошая ли рпактика передавать аргумент указателем 
									    	  //или лучше присваиаваить возват функции

double checkArgument(double x, double RoAV[SIZE][2], int index);

double getArgument();

int simplArgument(double* x, double noPeriodZone[SIZE][2], int i);

double expPart(double x, int n, double* preX, unsigned long long* preFac);

double sinPart(double x, int n, double* preX, unsigned long long* preFac);

double cosPart(double x, int n, double* preX, unsigned long long* preFac);

