#define _CRT_SECURE_NO_WARNINGS
#include <locale.h>
#include <stdlib.h> 
#include <stdio.h>
#include <math.h>
#define M_PI 3.14159265358979323846
#include "taylor.h"

int main() {
	setlocale(LC_ALL, "Russian");
	int mode, function_select;
	double x, precision, reference_value, estimated_value, difference;
	int N, NMax, el;
	int flag = 1;
	while (flag) 
	{
		printf("Выберите режим работы программы:\n");
		printf("1 - Однократный расчет\n");
		printf("2 - Серийный эксперимент\n");
		scanf("%d", &mode);
		if (mode >= 1 && mode <= 2)
			flag = 0;
		else
			printf("Выбран неверный режим. Пожалуйста, попробуйте еще раз.\n");
	}

	flag = 1;
	while (flag)
	{
		printf("Выберите функцию: 1 - sin(x), 2 - cos(x), 3 - exp(x), 4 - arctg(x)\n");
		scanf("%d", &function_select);
		if (function_select >= 1 && function_select <= 4)
			flag = 0;
		else
			printf("Введен неправильный номер функции. Пожалуйста, попробуйте еще раз.\n");
	}
	printf("Введите значение точки: \n");
	printf("(для функция sin и cos необходимо вводить значение точки в градусах)\n");
	printf("(для функция arctg необходимо вводить значение точки в итервале от -1 до 1)\n");
	scanf("%lf", &x);
	if (function_select == 1 || function_select == 2)
	{
		x = fmod(x, 360.0);
		x = x * M_PI / 180.0;
	}

	flag = 1;
	if (function_select == 4)
	{
		while (flag)
		{
			if ((x < -1) || (x > 1)) {
				printf("Неправильно введено значение точки для арктангенса. Пожалуйста, попробуйте еще раз.\n");
				printf("(для функция arctg необходимо вводить значение точки в итервале от -1 до 1)\n");
				printf("Введите значение точки: \n");
				scanf("%lf", &x);
			}
			else
				flag = 0;
		}
	}

	TaylorFunc taylorFunctions[] = { sinTaylor, cosTaylor, expTaylor, arctgTaylor };

	switch (function_select)
	{
	case 1: reference_value = sinl(x); break;
	case 2: reference_value = cosl(x); break;
	case 3: reference_value = expl(x); break;
	case 4: reference_value = atanl(x); break;
	}
	if (mode == 1) 
	{
		flag = 1;
		while (flag) {
			printf("Введите точность вычисления (>= 0,000001): \n");
			scanf("%lf", &precision);
			if (precision >= 0.000001)
				flag = 0;
			else
				printf("Слишком низкая точность. Пожалуйста, попробуйте еще раз.\n"); 
		}

		flag = 1;
		while (flag) {
			printf("Введите число элементов ряда для выполнения расчета (1 - 1000): \n");
			scanf("%d", &N);
			if (N < 1 || N > 1000)
				printf("Неверно введено количество элементов. Пожалуйста, попробуйте еще раз.\n");
			else
				flag = 0;
		}
		el = 1;
		estimated_value = taylorFunctions[function_select - 1](x, precision, N-1, &el);
		difference = fabs(reference_value - estimated_value);
		printf("Эталонное значение: %f\n", reference_value);
		printf("Вычисленная оценка значения функции: %f\n", estimated_value);
		printf("Разница: %f\n", difference);
		printf("Количество вычисленных слагаемых: %d\n", el);
	}
	else 
	{
		flag = 1;
		while (flag) {
			printf("Введите число экспериментов (1 - 25): \n");
			scanf("%d", &NMax);
			if (NMax < 1 || NMax > 25)
				printf("Неверное количество экспериментов. Пожалуйста, попробуйте еще раз.\n");
			else
				flag = 0;
		}

		printf("Эталонное значение: %f\n", reference_value);
		printf("Слагаемое | Оценочное значение | Разница\n");
		el = 1;
		estimated_value = taylorFunctions[function_select - 1](x, -1, NMax, &el);
	}
	system("pause");
}