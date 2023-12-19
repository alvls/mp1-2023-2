#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include<math.h>
#include"taylor.h"

int main() {
	setlocale(LC_ALL, "");
	/*for (int i = 0; i <= 21;i++) {
		unsigned long long f = ullFactorial(i);
		printf("%llu %lf \n",f, (double)f );
	}*/

	/*for (double i = -8 * pi; i < 8 * pi; i++) {
		printf("%lf %lf\n", i, argWrap(i));
	}*/
	unsigned todigit = 10;
	double x = 12;
	x = TrigArgWrap(x);
	Taylor(tpSin, sin, x, 5, todigit, 2);
	system("pause");
	return 0;
}