#define _CRT_SECURE_NO_WARNINGS
#include "functions.h"

//area of acceptable values && periods
double intervals[SIZE][2] = {
		{-5, 5},
		{-pi / 2, pi / 2},
		{0, pi},
		{-1, 1}
};

//modes
void mode1(TfuncPart Tfunc, TfuncInpWork TMath, double x, int sgn) {
	printf("Enter precision (must be >= 0.000001): ");
	double precision = -1;
	while ( (scanf("%lf", &precision) < 1) || (precision < 0.000001) ) {
		printf("\nIncorrect precision. Try again: ");
		scanf("%*[^\n]");
		getchar();
	}

	printf("Enter number of elements in row (must be <= 1000): ");
	unsigned int elmNum = 1001;
	while ( (scanf("%ui", &elmNum) < 1) || (elmNum > 1000) || (elmNum < 1)) {
		printf("\nIncorrect  number of elements. Try again: ");
		scanf("%*[^\n]");
		getchar();
	}

	double res = 0, Mres = sgn*TMath(x);
	unsigned int elmInd = 0; unsigned long long fact = 1; double xpow = 1;
	while ((elmInd < elmNum) && (fabs(res - Mres) > precision)) {
		res += sgn * Tfunc(x, elmInd, &xpow, &fact);
		elmInd++;
	}
	printf("Exact value of the function value at this point: %.20lf\n", Mres);
	printf("Evalution of the function value at this point: %.20lf\n", res);
	double dif = fabs(res - Mres);
	printf("Difference: %.20lf\n", dif);
	printf("Amount of calculated elements: %u\n", elmInd);
}

void mode2(TfuncPart Tfunc, TfuncInpWork TMath, double x, int sgn) {
	printf("Enter number of experiments (must be <= 25): ");
	unsigned int nMax = 26;
	while ( (scanf("%ui", &nMax) < 1) || (nMax > 25) || (nMax < 1)) {
		printf("\nIncorrect  number of elements. Try again: ");
		scanf("%*[^\n]");
		getchar();
	}

	double res = 0, Mres = sgn*TMath(x);
	unsigned int expInd = 0; unsigned long long fact = 1; double xpow = 1;

	printf("Exact value of the function value at this point: %.20lf\n", Mres);
	printf("Exp %14c Evalution %19c Difference\n", ' ', ' ');
	while (expInd < nMax) {
		res += sgn * Tfunc(x, expInd, &xpow, &fact);
		printf("%-2u     %-35.20lf    %-35.20lf\n", expInd+1, res, fabs(res - Mres));
		expInd++;
	}
}

//inp work
int getMode() {
	printf("Select the mode type: \n");
	printf("1 stands for One-time calculation of the function at a given point \n");
	printf("2 stands for a serial experiment \n");
	int mode = 0;
	printf("Enter mode: ");
	scanf("%i", &mode);
	scanf("%*[^\n]");
	getchar();
	while ((mode != 1) && (mode != 2)) {
		printf("Incorrect mode type. Try again: ");
		scanf("%i", &mode);
		scanf("%*[^\n]");
		getchar();
		printf("\n");
	}
	return mode;
}

int getfNum() {
	int fNum;
	printf("Choose a function for calculation\n");
	printf("1 - exp(x), 2 - sin(x), 3 - cos(x)\n");
	printf("4 - arth(x)\n");
	printf("Enter a function number: ");
	scanf("%i", &fNum);
	scanf("%*[^\n]"); // delete all symbols till \n, not including \n
	getchar(); // delete \n
	while ((fNum < 1) || (fNum > 4)) {
		printf("Incorrect number. Try again\n");
		scanf("%i", &fNum);
		scanf("%*[^\n]");
		getchar();
	}
	return fNum;
}

double getArgument() {
	double x = 0.0;
	printf("Enter x: ");
	scanf("%lf", &x);
	scanf("%*[^\n]");
	getchar();
	return x;
};

//checking Argument
void simplArgument(double* x, int* sgn, double noPeriodZone[SIZE][2], int* index) {
	int tgTrue = ((*index == NULL) || (*index == NULL)) ? -1 : 1; // вместо NULL вписать номера tg и ctg
	while (*x > noPeriodZone[*index][1]) { *x -= pi; *sgn *= -1 * tgTrue; }
	while (*x < noPeriodZone[*index][0]) { *x += pi; *sgn *= -1 * tgTrue; }
	/* Обоснование
	sin(x - pi) == -sin(x)
	sin(x + pi) == -sin(x)
	cos(x - pi) == -cos(x)
	cos(x + pi) == -cos(x)

	tgTrue = -1, если у нас в руках tg или ctg
	тогда на 109 - 110 строках при +-pi знак выражения изменяться не будет, тк у tg/ctg период = pi
	*/
};

void checkArgumentSegment(double* x, int* sgn, double RoAV[SIZE][2], int* index) { //RoAV = the range of acceptable values
	while ((*x < RoAV[*index][0]) || (*x > RoAV[*index][1])) {
		printf("Incorrect number. \n");
		printf("Argument for this function must be from %f till %f\n",  RoAV[*index][0], RoAV[*index][1]);
		printf("otherwise you will have worse accuracy / this argument is out of the range of acceptable values for this function\n" );
		printf("Try again: ");
		scanf("%lf", &x);
		scanf("%*[^\n]");
		getchar();
		printf("\n");
	}
}

void checkArgumentIntervl(double* x, int* sgn, double RoAV[SIZE][2], int* index) {
	while ((*x <= RoAV[*index][0]) || (*x >= RoAV[*index][1])) {
		printf("Incorrect number. \n");
		printf("Argument for this function must be from %f till %f (not inclusive)\n", RoAV[*index][0], RoAV[*index][1]);
		printf("otherwise you will have worse accuracy / this argument is out of the range of acceptable values for this function\n");
		printf("Try again: ");
		scanf("%lf", &x);
		scanf("%*[^\n]");
		getchar();
		printf("\n");
	}
}

//Tfuncs
double expPart(double x, int n, double* preX, unsigned long long* preFac) { //preX first = 1, preFac = 1
	double res= 0.0;
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

double arthPart(double x, int n, double* preX, unsigned long long* placeHolder) {
	double res = 0.0;
	if (n == 0) {
		return 0;
	}

	if (n % 2 == 0) {
		*preX *= x;
		return 0;
	}

	res = (*preX * x) / (double)(n);
	*preX *= x;
	return res;
}