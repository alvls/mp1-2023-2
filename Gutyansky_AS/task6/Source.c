#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "taylor_math.h"

int main() {
	setlocale(LC_ALL, "rus");

	double x;
	scanf("%lf", &x);

	double ex = taylor_exp(x, 100);
	double si = taylor_sin(x, 100);
	double co = taylor_cos(x, 100);
	printf("%lf %lf %lf", ex, si, co);

	system("pause");
	return 0;
}