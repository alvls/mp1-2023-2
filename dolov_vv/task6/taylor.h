#pragma once
typedef double (*TaylorFunc)(double, double, int, int*);
double sinTaylor(double x, double acc, int N, int* el);
double cosTaylor(double x, double acc, int N, int* el);
double expTaylor(double x, double acc, int N, int* el);
double arctgTaylor(double x, double acc, int N, int* el);
