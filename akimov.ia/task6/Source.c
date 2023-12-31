#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <locale.h>
#include "Func.h"

void main()
{
	setlocale(LC_ALL, "rus");
	typedef double (*functions)(double, double, int);
	functions func;
	int n, num_func, mode, flag;
	double x, accuracy;
	void (*f[4])(double, double, int) = { sinus, cosinus, exponent, sqrt_1plusx };
	do
	{
		printf("Функции:\n1. sin(x)\n2. cos(x)\n3. exp(x)\n4. sqrt(1 + x), |x| <= 1\nВведите номер функции: ");
		scanf("%d", &num_func);
		system("cls");
		flag = 0;
		while (getchar() != '\n');
		if (num_func != 1 && num_func != 2 && num_func != 3 && num_func != 4)
		{
			printf("Указанной функции не существует!\n");
			flag = 1;
		}
	} while (flag);		
	func = f[num_func - 1];
	do
	{
		printf("Задайте точку x, в которой необходимо вычислисть значение: ");
		scanf("%lf", &x);
		system("cls");
		flag = 0;
		while (getchar() != '\n');
		if (num_func == 4 && (x < -1 || x > 1))
		{
			printf("Для sqrt(1 + x) |x| <= 1\n");
			flag = 1;
		}
	} while (flag);
	do
	{
		printf("Режимы:\n1. Однократный расчет функции в заданной точке.\n2. Серийный эксперимент.\nВведите номер режима: ");
		scanf("%d", &mode);
		system("cls");
		flag = 0;
		while (getchar() != '\n');
		if (mode != 1 && mode != 2)
		{
			printf("Указанного режима не существует!\n");
			flag = 1;
		}
	} while (flag);
	switch (mode)
	{
	case 1:
		do
		{
			printf("Задайте точность вычисления (>= 0,000001): ");
			scanf("%lf", &accuracy);
			system("cls");
			flag = 0;
			while (getchar() != '\n');
			if (accuracy < 0.000001)
			{
				printf("Неверная точность вычисления!\n");
				flag = 1;
			}
		} while (flag);
		do
		{
			printf("Задайте число элементов ряда для выполнения расчета (от 1 до 1000): ");
			scanf("%d", &n);
			system("cls");
			flag = 0;
			while (getchar() != '\n');
			if (n < 1 || n > 1000)
			{
				printf("Неверное число элементов ряда для выполнения расчета!\n");
				flag = 1;
			}
		} while (flag);
		func(x, accuracy, n);
		break;
	case 2:
		do
		{
			printf("Задайте число экспериментов (от 1 до 25): ");
			scanf("%d", &n);
			system("cls");
			flag = 0;
			while (getchar() != '\n');
			if (n < 1 || n > 25)
			{
				printf("Неверное число экспериментов!\n");
				flag = 1;
			}
		} while (flag);
		func(x, -1, n);
		break;
	}
	system("pause");
}