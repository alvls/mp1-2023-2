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


// Factorial calculation function
double Factorial(int x, int order);

// Bernoulli number calculation function
double Bernoulli(int n, double* Bs);

// Calculates binominal coefficient
double Binominal(int n, int k);