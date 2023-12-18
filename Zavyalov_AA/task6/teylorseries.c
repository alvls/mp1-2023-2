#include <math.h>

double tey_sin(double x, double precision, int n, int* elemcount) {
	int i = 0, sign = 1, nextmult = 2; // current step, sign, next multiplier for factorial
	unsigned long long fact = 1; // current factorial value
	double res = 0, value = sin(x), tek = x; // result, exact value of sin(x), current multiplier for res
	while (fabs(res - value) > precision && i++ < n)
	{
		res += sign * tek / fact;
		tek *= x * x;
		fact *= nextmult++;
		fact *= nextmult++;
		sign = -sign;
	}
	if (i == n)
		i--;
	*elemcount = i;
	return res;
}

double tey_cos(double x, double precision, int n, int* elemcount) {
	int i = 1, sign = 1, nextmult = 1;
	unsigned long long fact = 1;
	double res = 1, value = cos(x), tek = 1;
	while (fabs(res - value) > precision && i++ < n)
	{
		tek *= x * x;
		fact *= nextmult++;
		fact *= nextmult++;
		sign = -sign;
		res += sign * tek / fact;
	}
	if (i == n)
		i--;
	*elemcount = i;
	return res;
}

double tey_exp(double x, double precision, int n, int* elemcount) {
	int i = 1, nextmult = 2;
	unsigned long long fact = 1;
	double res = 1, value = exp(x), tek = x;
	while (fabs(res - value) > precision && i++ < n) {
		res += tek / fact;
		tek *= x;
		fact *= nextmult++;
	}
	if (i > 1)
		i--;
	*elemcount = i;
	return res;
}

double tey_sinh(double x, double precision, int n, int* elemcount) {
	int i = 0, nextmult = 2;
	unsigned long long fact = 1;
	double res = 0, value = sinh(x), tek = x;
	while (fabs(res - value) > precision && i++ < n) {
		res += tek / fact;
		tek *= x * x;
		fact *= nextmult++;
		fact *= nextmult++;
	}
	if (i == n)
		i--;
	*elemcount = i;
	return res;
}

double tey_cosh(double x, double precision, int n, int* elemcount) {
	int i = 1, nextmult = 1;
	unsigned long long fact = 1;
	double res = 1, value = cosh(x), tek = 1;
	while (fabs(res - value) > precision && i++ < n)
	{
		tek *= x * x;
		fact *= nextmult++;
		fact *= nextmult++;
		res += tek / fact;
	}
	if (i == n)
		i--;
	*elemcount = i;
	return res;
}