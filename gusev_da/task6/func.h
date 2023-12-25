#pragma once

#define Max_Iter 1000
#define PI (3.14159265358979323846)

#include <math.h>

unsigned long long factorial(unsigned long long n);
double calc_acc(int accuracy);
double taylor_exp(double x, int accuracy, int N, int* count);
double taylor_sin(double x, int accuracy, int N, int* count);
double taylor_cos(double x, int accuracy, int N, int* count);
double taylor_arcsin(double x, int accuracy, int N, int* count);