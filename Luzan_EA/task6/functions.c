#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include "functions.h"
#include <limits.h>

double intervals[SIZE][2] = {
		{-5, 5},
		{-pi / 2, pi / 2},
		{0, pi}
};

int simplArgument (double* x, double noPeriodZone[SIZE][2], int index) { //noPeriodZone через **?
	int sgn = 1, tgTrue = ((index == 3) || (index == 4)) ? -1 : 1; // вместо 3 и 4 вписать номера tg и ctg
	while (*x > noPeriodZone[index][1]) { *x -= pi; sgn *= -1 * tgTrue; }
	while (*x < noPeriodZone[index][0]) { *x += pi; sgn *= -1 * tgTrue; }
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

double getArgument() { 
	double x = 0.1;
	printf("Enter x: ");
	scanf("%lf", &x);
	scanf("%*[^\n]");
	getchar();

	return x;
};

double checkArgument(double x, double RoAV[SIZE][2], int index) { //RoAV = the range of acceptable values
	while ((x < RoAV[index][0]) || (x > RoAV[index][1])) {
		printf("Incorrect number. \n");
		printf("Argument for this function must be from %f till %f, else you will have worse accuracy.\n", RoAV[index][0], RoAV[index][1]);
		printf("Try again: ");
		scanf("%lf", &x);
		scanf("%*[^\n]");
		getchar();
		printf("\n");
	}
	return x;
}

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

