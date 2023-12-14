#pragma once
#define _CRT_SECURE_NO_WARNINGS

typedef double (*func_ptr_t)(double, double, int);
void getmode(int* mode);
double tey_sin(double x, double precision, int n);
double tey_cos(double x, double precision, int n);
double tey_exp(double x, double precision, int n);
double tey_sinh(double x, double precision, int n);
void mode1(func_ptr_t func);
void mode2(func_ptr_t func);