#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <math.h>

typedef double (*func_ptr_t)(double, double, int, int*);
typedef double (*standart_func_ptr_t)(double);
void getmode(int* mode);
void getfunc(func_ptr_t* target, standart_func_ptr_t* standart);
double tey_sin(double x, double precision, int n, int* elemcount);
double tey_cos(double x, double precision, int n, int* elemcount);
double tey_exp(double x, double precision, int n, int* elemcount);
double tey_sinh(double x, double precision, int n, int* elemcount);
double tey_cosh(double x, double precision, int n, int* elemcount);
void mode1(func_ptr_t func, standart_func_ptr_t standartfunc);
void mode2(func_ptr_t func, standart_func_ptr_t standartfunc);
