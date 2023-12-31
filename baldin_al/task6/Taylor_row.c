#include "Taylor_row.h"

MathFunc f[] = { f_sin, f_cos, f_exp, f_tan };
standart funcs[] = { sin, cos, exp, tan };

int count = 0;
double* res;
double* B;
long double* fact;

double f_sin(double x, double p, int k)
{
	double st = funcs[0](x);
	while (fabs(x) >= 2 * M_PI)
	{
		x -= (x > 0 ? 1 : -1) * 2 * M_PI;
	}
	double result = x, term = x;
	int i = 3, n = 0;
	res[0] = result;
	while (n++ < k && fabs(st - result) > p)
	{
		term *= -x * x / (i * (i - 1));
		result += term;
		i += 2;
		res[n] = result;
	}
	count = n;
	return result;
}

double f_cos(double x, double p, int k)
{
	double st = funcs[1](x);
	while (fabs(x) >= 2 * M_PI)
	{
		x -= (x > 0 ? 1 : -1) * 2 * M_PI;
	}
	double result = 1, term = 1;
	int i = 2, n = 0;
	res[0] = result;
	while (n++ < k && fabs(st - result) > p)
	{
		term *= -x * x / (i * (i - 1));
		result += term;
		i += 2;
		res[n] = result;
	}
	count = n;
	return result;
}

double f_exp(double x, double p, int k)
{
	double st = funcs[2](x);
	double result = 1, term = 1;
	int i = 1, n = 0;
	res[0] = result;
	while (n++ < k && fabs(st - result) > p)
	{
		term *= x / i;
		result += term;
		i += 1;
		res[n] = result;
	}
	count = n;
	return result;
}

void bernulli(int cnt)
{
	memset(B, 0, cnt * sizeof(double));
	int n, k;
	long double C = 0, sum;
	B[0] = 1;
	B[1] = -0.5;
	for (n = 2; n < cnt; n += 2) {
		sum = 0;
		for (k = 1; k <= n; k++) {
			C = (fact[n + 1] / (fact[k + 1] * fact[n - k]));
			sum += C * B[n - k];
		}
		B[n] = sum * (-1.0) / (n + 1);
	}
}

void factorial(int cnt)
{
	memset(fact, 0, cnt * sizeof(long double));
	fact[0] = 1;
	fact[1] = 1;
	for (int i = 2; i <= cnt; i++)
		fact[i] = fact[i - 1] * i;
}

double f_tan(double x, double p, int k)
{
	double st = funcs[3](x);
	factorial(2 * k + 1);
	bernulli(2 * k + 1);
	while (fabs(x) >= M_PI / 2)
	{
		x -= (x > 0 ? 1 : -1) * M_PI;
	}
	double result = x, term = 0;
	int i = 2, n = 0;
	res[0] = result;
	double t = x, d = 0;
	while (n++ < k && fabs(st - result) > p)
	{
		d = pow(2, 2 * i) * (pow(2, 2 * i) - 1);
		t *= -x * x;
		term = (d * B[2 * i] * t) / fact[2 * i];
		result += term;
		i++;
		res[n] = result;
	}
	count = n;
	return result;
}