#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <math.h>
#include "functions.h"
#define SIZE 3

//функция на первый член

// массив функций:
// чек ввода (корректность через возврат 1),мб можно какую то общую, типа, что не строка, а число
// пользовательские
// из math



int main()
{
	double out = 0;
	double x = 3.5;
	double xpow = 1;
	unsigned long long fact = 1;
	int fNum = 2;
	TfuncPart Tfuncs[SIZE] = { expPart, sinPart, cosPart };
	TfuncInpWork TMaths[SIZE] = { exp, sin, cos };
	//TfuncInpWork TfuncInp[] = {from_to, sin_halfpi, cos_pi};



	for (int i = 0; i < 25; i++) {
		out += Tfuncs[fNum](x, i, &xpow, &fact);
		printf("on %i step: %.20f\n", i, out);
	}

	printf("MATH: %.20f\n", TMaths[fNum](x));
	system("pause");
	return 0;
}

