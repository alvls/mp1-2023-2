#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include<math.h>
#include"taylor.h"

void rinput(unsigned* v, unsigned l, unsigned r) {
	int k = 0;
	while (k != 1 || (*v < l) || (*v > r))
		k = scanf("%u", v);
}

int main() {
	setlocale(LC_ALL, "");
	while (1) {
		void (*func)(double, unsigned, double*, double*);
		double (*et)(double);
		unsigned todigit = 20;
		double x = 5;
		unsigned choose = 0;
		int mode = 1;
		unsigned n = 1;
		printf("Выберите функцию:\n0) exp - экспонента\n1) sin - синус\n2) cos - косинус\n3) sinh - гиперболический синус\n4) cosh - гиперболический косинус\n");
		rinput(&choose, 0, 4);
		printf("Выберите режим: 1 - однократный расчёт 2 - серийный эксперимент\n");
		rinput(&mode, 1, 2);
		printf("Значение функции в какой точке вычислять\n");

		while (!scanf("%lf", &x)) {
			int i = 0;
			while (getchar() != '\n' && i < 20) {
				i++;
				printf("?");
			}

			printf("!");
		}
		while (getchar() != '\n');


		if (mode == 1) {
			printf("С точностью до какой цифры после запятой требуется вычислить\n");
			rinput(&todigit, 6, UINT_MAX - 10);
			printf("Максимальное число членов\n");
			rinput(&n, 1, 1000);
		}
		else {
			printf("Сколько членов вычислять\n");
			rinput(&n, 1, 25);

		}

		switch (choose) {
		default:
			func = tpExp;
			et = exp;
			break;
		case 1:
			func = tpSin;
			et = sin;
			break;
		case 2:
			func = tpCos;
			et = cos;
			break;
		case 3:
			func = tpSh;
			et = sinh;
			break;
		case 4:
			func = tpCh;
			et = cosh;
		}
		if (choose == 1 || choose == 2)
			x = TrigArgWrap(x);
		Taylor(tpSh, sinh, x, n, todigit, mode);
	}
	//system("pause");
	return 0;
}