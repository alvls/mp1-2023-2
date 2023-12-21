#define _CRT_SECURE_NO_WARNINGS
#include "functions.h"

int main() {
	int inp = 1;
	while (inp != 0) {
		double x = 0.0; int fNum = -10; 
		TfuncPart Tfuncs[SIZE] = { expPart, sinPart, cosPart, arthPart };
		TfuncInpWork TMaths[SIZE] = { exp, sin, cos, atanh};

		// selecting function number
		fNum = getfNum();
		fNum--;
		TfuncPart Tfunc = Tfuncs[fNum];
		TfuncInpWork TMath = TMaths[fNum];

		//argument
		x = getArgument();
		int sgn = 1; 
		if ((fNum == 0) || (fNum == 1)) {
			simplArgument(&x, &sgn, intervals, fNum);
		}
		else {
			checkArg(&x, intervals, fNum);
		}

		// mode
		int mode = getMode();
		if (mode == 1)
			mode1(Tfunc, TMath, x, sgn);
		else
			mode2(Tfunc, TMath, x, sgn);

		//end
		printf("If you want to exit, enter '0'\nIf you want to repeat, enter something else\n");
		scanf("%i", &inp);
		scanf("%*[^\n]"); 
		getchar();
	}

	system("pause");
	return 0;
}