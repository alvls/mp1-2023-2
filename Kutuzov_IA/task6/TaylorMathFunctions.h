#pragma once

#define PI 3.141592

// Taylor series approximation of Sin(x)
double Sin_T(double x, int TargetAccuracy, int* N, int IgnoreAccuracy);

// Taylor series approximation of Cos(x)
double Cos_T(double x, int TargetAccuracy, int* N, int IgnoreAccuracy);

// Taylor series approximation of Exp(x)
double Exp_T(double x, int TargetAccuracy, int* N, int IgnoreAccuracy);

// Taylor series approximation of Cth(x)
double Cth_T(double x, int TargetAccuracy, int* N, int IgnoreAccuracy);


double Sqrt_T(double x, int TargetAccuracy, int* N, int IgnoreAccuracy);

double Ln_T(double x, int TargetAccuracy, int* N, int IgnoreAccuracy);

double Tan_T(double x, int TargetAccuracy, int* N, int IgnoreAccuracy);

double Cotan_T(double x, int TargetAccuracy, int* N, int IgnoreAccuracy);

double Arcsin_T(double x, int TargetAccuracy, int* N, int IgnoreAccuracy);

double Arccos_T(double x, int TargetAccuracy, int* N, int IgnoreAccuracy);

double Arctan_T(double x, int TargetAccuracy, int* N, int IgnoreAccuracy);

double Arccotan_T(double x, int TargetAccuracy, int* N, int IgnoreAccuracy);

double Sh_T(double x, int TargetAccuracy, int* N, int IgnoreAccuracy);

double Ch_T(double x, int TargetAccuracy, int* N, int IgnoreAccuracy);

double Th_T(double x, int TargetAccuracy, int* N, int IgnoreAccuracy);

// Factorial calculation function
double Factorial(int x, int order);

// Bernoulli number calculation function
double Bernoulli(int n, double* Bs);

// Calculates binominal coefficient
double Binominal(int n, int k);