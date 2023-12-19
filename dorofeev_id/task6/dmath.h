#pragma once
#define MAX_ITERATIONS 1000
#define PI (3.14159265358979323846)
#include <math.h>

unsigned long long factorial(unsigned long long n);
double calculate_precision(int precision);

double exp_taylor(double x, int precision, int max_iterations, int* terms_count);

double sin_taylor(double x, int precision, int max_iterations, int* terms_count);
double cos_taylor(double x, int precision, int max_iterations, int* terms_count);
double tan_taylor(double x, int precision, int max_iterations, int* terms_count);
double cot_taylor(double x, int precision, int max_iterations, int* terms_count);

double arcsin_taylor(double x, int precision, int max_iterations, int* terms_count);
double arccos_taylor(double x, int precision, int max_iterations, int* terms_count);
double arctan_taylor(double x, int precision, int max_iterations, int* terms_count);
double arccot_taylor(double x, int precision, int max_iterations, int* terms_count);

double cot(double x);
double acot(double x);
