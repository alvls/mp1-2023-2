#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <math.h>
#include "functions.h"

//функция на первый член

// !!!!!!!!!!!!!!!!!упрощение аргумента на tg практически чек


// массив функций:
// чек ввода (корректность через возврат 1),мб можно какую то общую, типа, что не строка, а число
// пользовательские
// из math
int getInp() {
	int fNum;
	printf("Enter function number for calculation\n");
	printf("1 - exp, 2 - sin, 3 - cos\n");
	scanf("%i", &fNum);
	scanf("%*[^\n]"); // delete all symbols till \n, not including \n
	getchar(); // delete \n
	while ((fNum < 1) || (fNum > 3)) {
		printf("Incorrect number. Try again\n");
		scanf("%i", &fNum);
		scanf("%*[^\n]");
		getchar();
	}
	return fNum;
}


int main()
{
	printf("%i\n", SIZE);
	double out = 0; double xpow = 1; unsigned long long fact = 1;
	double x = 3.5; int fNum = -10; //in
	TfuncPart Tfuncs[SIZE] = { expPart, sinPart, cosPart };
	TfuncInpWork TMaths[SIZE] = { exp, sin, cos };

	fNum = getInp();
	fNum--;

	int sgn = 1; 
	double xc = x;
	if ( (fNum == 1) || (fNum == 2) ) { sgn = simplByPeriod(&xc, intervals, fNum); }
	for (int i = 0; i < 25; i++) {
		out += sgn * Tfuncs[fNum](xc, i, &xpow, &fact);          
		printf("on %i step: %.20f\n", i, out);
	}

	printf("MATH: %.20f\n", TMaths[fNum](x));
	system("pause");
	return 0;
}

/*
void mainii() {
	simplByPeriod(300.0, intervals, 2);
	printf("\n\n\n");
	/*for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < 2; j++)
			printf("%f  ", intervals[i][j]);
		printf("\n");
	} //
	system("pause");
}*/