#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include "functions.h"

double intervals[SIZE][2] = {
		{-1000, 1000}, // почему подчёркивает?
		{-pi / 2, pi / 2},
		{0, pi}
};

int simplByPeriod(double* x, double noPeriodZone[SIZE][2], int i) { //noPeriodZone через **?
	int sgn = 1, tgTrue = ((i == 3) || (i == 4)) ? -1 : 1; // вместо 3 и 4 вписать номера tg и ctg
	while (*x > noPeriodZone[i][1]) { *x -= pi; sgn *= -1 * tgTrue; }
	while (*x < noPeriodZone[i][0]) { *x += pi; sgn *= -1 * tgTrue; }
	/* Обоснования вот этого вот всего
	sin(x - pi) == -sin(x)
	sin(x + pi) == -sin(x)
	cos(x - pi) == -cos(x)
	cos(x + pi) == -cos(x)

	tgTrue = -1, если у нас в руках тг или ктг
	тогда на 15 - 16 строках при +-pi знак выражения изменяться не будет, тк у tg/ctg период = pi
	*/
	return sgn;
};

int checkInput();

int checkArgument();

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

