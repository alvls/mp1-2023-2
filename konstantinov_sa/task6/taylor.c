#include "taylor.h"
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define pi 3.14159265358979323846
#define dopdigits 10

//unsigned long long ullFactorial(unsigned a) {
//	unsigned long long r = 1;
//	for (unsigned i = 2; i <= a;i++)
//		r *= i;
//	return r;
//}
//
//int minusOnePow(unsigned a) {
//	return (a % 2) ? -1 : 1;
//}
//
//double partSin(double x, unsigned n) {
//	x = argWrap(x, 2 * pi);
//	int sig = (x < 0) ? -1 : 1;
//	x *= sig;
//	if (x > pi) {
//		x -= pi;
//		sig *= -1;
//	}
//	if (x > pi / 2) {
//		x = pi - x;
//	}
//	return sig * minusOnePow(n) * pow(x, 2 * n + 1) / ullFactorial(2 * n + 1);
//}

//double sinArg(double x, int* sig) {
//	x = argWrap(x, 2 * pi);
//	int s = (x < 0) ? -1 : 1;
//	x *= s;
//	if (x > pi) {
//		x -= pi;
//		s *= -1;
//	}
//	if (x > pi / 2) {
//		x = pi - x;
//	}
//	*sig = s;
//	return x;
//}

//double tSin(double x, unsigned n) {
//	x = argWrap(x, 2 * pi);
//	int sig = (x < 0) ? -1 : 1;
//	x *= sig;
//	if (x > pi) {
//		x -= pi;
//		sig *= -1;
//	}
//	if (x > pi / 2) {
//		x = pi - x;
//	}
//	double res = x;
//	double term = x;
//	for (int i = 1; i <= n; i++) {
//		term *= -1 * x * x / ((2 * i) * (2 * i + 1));
//		res += term;
//	}
//
//	return sig * res;
//}

double TrigArgWrap(double arg) {
	double period = 2 * pi;
	int sig = (arg < 0) ? -1 : 1;
	arg *= sig;
	int ps = arg / period;
	arg -= ps * period;
	if (arg > pi)
		arg -= 2 * pi;
	return arg * sig;
}

void tpSin(double x, unsigned n, double* t, double* ans) {
	if (n == 0) {
		*ans = x;
		*t = x;
	}
	else {
		*t *= -1 * x * x / ((2 * n) * (2 * n + 1));
		*ans += *t;
	}

}

void Taylor(void (*func)(double, unsigned, double*, double*), double (*etalon)(double), double x, unsigned n, unsigned e, int mode) {
	double ans = 1;
	double t = 1;
	double et = etalon(x);
	//double sx = TrigArgWrap(x);
	if (mode == 1) {
		double eps = pow(10, -(double)e);
		unsigned i = 0;
		while (i<n && fabs(t)>eps) {
			func(x, i, &t, &ans);
			//printf(" >%.*lf\n  %.*lf\n", e + dopdigits, fabs(t), e + dopdigits, eps);
			i++;
		}
		printf("Точность:  %.*lf\n", e + dopdigits, eps);
		printf("Эталон:    %.*lf\nВычислено: %.*lf\nРазница:   %.*lf\nСлагаемых: %u\n", e + dopdigits, et, e + dopdigits, ans, e + dopdigits, fabs(et - ans), i);
	}
	else {
		printf("Эталон: %.*lf\n", e + dopdigits, et);
		for (unsigned i = 0; i < n;i++) {
			func(x, i, &t, &ans);
			printf("%u) %.*lf %.*lf\n",i+1, e + dopdigits, ans, e + dopdigits, fabs(et - ans));
		}
	}
}