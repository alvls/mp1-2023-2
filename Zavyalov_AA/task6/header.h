#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <math.h>

typedef double (*func_ptr_t)(double, double, int, int* elemcount);
typedef double (*standart_func_ptr_t)(double);
void getmode(int* mode);
double tey_sin(double x, double precision, int n, int* elemcount);
double tey_cos(double x, double precision, int n, int* elemcount);
double tey_exp(double x, double precision, int n, int* elemcount);
double tey_sinh(double x, double precision, int n, int* elemcount);
double tey_cosh(double x, double precision, int n, int* elemcount);
void mode1(func_ptr_t func);
void mode2(func_ptr_t func);