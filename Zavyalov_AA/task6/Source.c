#define _CRT_SECURE_NO_WARNINGS

#include "header.h"
#include <stdio.h>
int main() {
	int mode; getmode(&mode);
	printf("The mode is %i.\n", mode);
	double (*funcPtr)(double, double, int);
	funcPtr = tey_sinh;
	printf("Enter the argument: ");
	double arg;
	scanf("%lf", &arg);
	double fval = funcPtr(arg, 0.00001, 104);
	printf("The value is %g.\n", fval);
	if (mode == 1)
		mode1();
	else
		mode2();

	system("pause");
	return 0;
}