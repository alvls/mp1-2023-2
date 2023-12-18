#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

double f_sin(double x, double p, int k);
double f_cos(double x, double p, int k);
double f_exp(double x, double p, int k);
void factorial(int cnt);
void bernulli(int cnt);
double f_tan(double x, double p, int k);

typedef double (*MathFunc)(double, double, int);
extern MathFunc f[];

typedef double (*standart)(double);
extern standart funcs[];

extern int count;
extern double* res;
extern double* fact;
extern double* B;
