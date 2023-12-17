#define _CRT_SECURE_NO_WARNINGS
#include "functions.h"
#include <time.h>

//функция на первый член
// !!!!!!!!!!!!!!!!!упрощение аргумента на tg практически чек

int main() {
	double x = 0.0; int fNum = -10; //in
	TfuncPart Tfuncs[SIZE] = { expPart, sinPart, cosPart };
	TfuncInpWork TMaths[SIZE] = { exp, sin, cos };

	fNum = getfNum();
	fNum--;
	TfuncPart Tfunc = Tfuncs[fNum];
	TfuncInpWork TMath = TMaths[fNum];

	x = getArgument();
	int sgn = 1; 
	double xc = x;
	if ((fNum == 1) || (fNum == 2) || (fNum == 3) || (fNum == 4)) 
		sgn = simplArgument(&xc, intervals, fNum);  // &sgn
	else 
		xc = checkArgument(xc, intervals, fNum);
	
	int mode = getMode();
	if (mode == 1)
		mode1(Tfunc, TMath, xc, sgn);
	else
		mode2(Tfunc, TMath, xc, sgn);

	system("pause");
	return 0;
}