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

// Taylor series approximation of Sqrt(1 + x)
double Sqrt_T(double x, int TargetAccuracy, int* N, int IgnoreAccuracy);

// Taylor series approximation of Ln(1 + x)
double Ln_T(double x, int TargetAccuracy, int* N, int IgnoreAccuracy);

// Taylor series approximation of Tan(x)
double Tan_T(double x, int TargetAccuracy, int* N, int IgnoreAccuracy);

// Taylor series approximation of Cotan(x)
double Cotan_T(double x, int TargetAccuracy, int* N, int IgnoreAccuracy);

// Taylor series approximation of Arcsin(x)
double Arcsin_T(double x, int TargetAccuracy, int* N, int IgnoreAccuracy);

// Taylor series approximation of Arccos(x)
double Arccos_T(double x, int TargetAccuracy, int* N, int IgnoreAccuracy);

// Taylor series approximation of Arctan(x)
double Arctan_T(double x, int TargetAccuracy, int* N, int IgnoreAccuracy);

// Taylor series approximation of Arccotan(x)
double Arccotan_T(double x, int TargetAccuracy, int* N, int IgnoreAccuracy);

// Taylor series approximation of Sh(x)
double Sh_T(double x, int TargetAccuracy, int* N, int IgnoreAccuracy);

// Taylor series approximation of Ch(x)
double Ch_T(double x, int TargetAccuracy, int* N, int IgnoreAccuracy);

// Taylor series approximation of Th(x)
double Th_T(double x, int TargetAccuracy, int* N, int IgnoreAccuracy);



// Factorial calculation function
double Factorial(int x, int order);

// Bernoulli number calculation function
double Bernoulli(int n, double* Bs);

// Calculates binominal coefficient
double Binominal(int n, int k);