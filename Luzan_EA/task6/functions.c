#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

double expPart(double x, int n, double* preX, unsigned long long* preFac) { //preX first = 1, preFac = 1
	double res = 0.0;
	if (n == 0)
		return 1;
	res = (*preX * x) / (double)(n * *preFac);
	*preX *= x; *preFac *= n;
	return res;
}

double sinPart(double x, int n, double* preX, unsigned long long* preFac) {
	double res = 0.0;
	if (n == 0) {
		return 0;
	}

	if (n % 2 == 0) {
		*preX *= x; *preFac *= n;
		return 0;
	}
	double sign = 1.0;
	if (n % 4 == 3) {
		sign = -1.0;
	}
	res = (*preX * x) / (double)(n * *preFac) * sign;;
	*preX *= x; *preFac *= n;
	return res;
}

double cosPart(double x, int n, double* preX, unsigned long long* preFac) {
	double res = 0.0;
	if (n == 0) {
		return 1;
	}

	if (n % 2 == 1) {
		*preX *= x; *preFac *= n;
		return 0;
	}
	double sign = 1.0;
	if (n % 4 == 2) {
		sign = -1.0;
	}
	res = (*preX * x) / (double)(n * *preFac) * sign;;
	*preX *= x; *preFac *= n;
	return res;
}
