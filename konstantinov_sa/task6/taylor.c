#include "taylor.h"
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define pi 3.14159265358979323846
#define dopdigits 10

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

void tpCos(double x, unsigned n, double* t, double* ans) {
	if (n == 0) {
		*ans = 1.0;
		*t = 1.0;
	}
	else {
		*t *= -1 * x * x / ((2 * n - 1) * (2 * n));
		*ans += *t;
	}
}

void tpExp(double x, unsigned n, double* t, double* ans) {
	if (n == 0) {
		*ans = 1.0;
		*t = 1.0;
	}
	else {
		*t *= x / n;
		*ans += *t;
	}
}

void tpCh(double x, unsigned n, double* t, double* ans) {
	if (n == 0) {
		*ans = 1.0;
		*t = 1.0;
	}
	else {
		*t *= x * x / ((2 * n - 1) * (2 * n));
		*ans += *t;
	}
}

void tpSh(double x, unsigned n, double* t, double* ans) {
	if (n == 0) {
		*ans = x;
		*t = x;
	}
	else {
		*t *= x * x / ((2 * n) * (2 * n + 1));
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
		printf("Результат %26c Разница с эталоном\n", ' ');
		for (unsigned i = 0; i < n;i++) {
			func(x, i, &t, &ans);
			printf("%u) %.*lf %.*lf\n",i+1, e + dopdigits, ans, e + dopdigits, fabs(et - ans));
		}
	}
}