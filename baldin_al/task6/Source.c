#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include "Taylor_row.h"

int main()
{
	setlocale(LC_ALL, "rus");
	int ch = 0;
	do {
		res = (double*)malloc(26 * sizeof(double));
		int choice;
		printf("1. Однократный расчёт функции в заданной точке\n");
		printf("2. Серийный эксперимент \n");
		do {
			printf("Введите номер режима: ");
			scanf_s("%d", &choice);
			if (choice != 1 && choice != 2)
				printf("Данного режима не существует. Введите номер одного из предложенных.\n\n");
		} while (choice != 1 && choice != 2);

		int y;
		double x;
		double p = 0;
		int k;
		system("cls");
		printf("1) sin(x) \n2) cos(x) \n3) exp(x) \n4) tan(x) \n");
		do {
			printf("Введите номер доступной функции: ");
			scanf_s("%d", &y);
			if (y < 1 || y > 4)
				printf("Данной функции не существует. Введите номер одной из предложенных. \n\n");
		} while (y < 1 || y > 4);

		system("cls");
		printf("Задайте точку x, в которой необходимо вычислить значение: ");
		scanf_s("%lf", &x);

		system("cls");
		if (choice == 1)
		{
			do {
				printf("Задайте точность вычисления (>= 0.000001): ");
				scanf_s("%lf", &p);
				if (p < 0.000001)
					printf("Данную точность задать невозможно. \n\n");
			} while (p < 0.000001);
			system("cls");
		}
		if (choice == 1)
		{
			do {
				printf("Задайте число элементов ряда для выполнения расчёта (N - от 1 до 1000): ");
				scanf_s("%d", &k);
				if (k < 1 || k > 1000)
					printf("Число экспериментов должно быть в диапазоне от 1 до 1000. \n\n");
			} while (k < 1 || k > 1000);
			system("cls");
		}
		if (choice == 2)
		{
			do {
				printf("Задайте число экспериментов (NMax - от 1 до 25): ");
				scanf_s("%d", &k);
				if (k < 1 || k > 25)
					printf("Число экспериментов должно быть в диапазоне от 1 до 25. \n\n");
			} while (k < 1 || k > 25);
			system("cls");
		}
		fact = (long double*)malloc((2 * k + 1) * sizeof(long double));
		B = (double*)malloc((2 * k + 1) * sizeof(double));
		double a = funcs[y - 1](x);
		double b = f[y - 1](x, p, k);

		if (choice == 1)
		{
			printf("Эталонное значение: %.7lf \n", a);
			printf("Вычисленная оценка значения функции: %.7lf \n", b);
			printf("Разница между оценкой и эталонным значением: %.7lf \n", fabs(a - b));
			printf("Количество слагаемых, которое было высчитано: %d \n", count - 1);
		}
		else
		{
			printf("Эталонное значение: %.16lf \n", a);
			printf("======================================= \n");
			printf("\n       Вычисленная оценка значения функции  |  Разница между оценкой и эталонным значением \n");
			for (int i = 0; i < count - 1; i++)
			{
				printf("%3.d  |  %-32.16lf    |  %.16lf\n", i + 1, res[i], fabs(res[i] - a));
			}
		}
		printf("\nЕсли вы хотите провести ещё один расчёт, то введите 1\n");
		printf("Если вы хотите завершить программу, то введите 2\n");
		scanf_s("%d", &ch);
		free(res);
		system("cls");
	} while (ch != 2);
	free(B);
}
