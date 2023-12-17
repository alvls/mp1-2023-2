#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <math.h>
#include "functions.h"

//функция на первый член

// !!!!!!!!!!!!!!!!!упрощение аргумента на tg практически чек

int getfNum() {
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
	double out = 0; double xpow = 1; unsigned long long fact = 1;
	double x = 0.0; int fNum = -10; //in
	TfuncPart Tfuncs[SIZE] = { expPart, sinPart, cosPart };
	TfuncInpWork TMaths[SIZE] = { exp, sin, cos };

	fNum = getfNum();
	fNum--;

	x = getArgument();
	int sgn = 1; 
	double xc = x;
	
	if ( (fNum == 1) || (fNum == 2) || (fNum == 3) || (fNum == 4) ) 
		sgn = simplArgument(&xc, intervals, fNum);  // &sgn
	else {
		xc = checkArgument(xc, intervals, fNum);
	}


	printf("\n-----------------------------------------------------------------\n");
	// output 
	for (int i = 0; i < 25; i++) {
		out += sgn * Tfuncs[fNum](xc, i, &xpow, &fact);          
		printf("on %i step: %.20f\n", i+1, out);
	}

	printf("MATH: %.20f\n", TMaths[fNum](x));
	system("pause");
	return 0;
}