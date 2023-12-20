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
		printf("�������� ����� ������ ���������:\n");
		printf("1 - ����������� ������\n");
		printf("2 - �������� �����������\n");
		scanf("%d", &mode);
		if (mode >= 1 && mode <= 2)
			flag = 0;
		else
			printf("������ �������� �����. ����������, ���������� ��� ���.\n");
	}

	flag = 1;
	while (flag)
	{
		printf("�������� �������: 1 - sin(x), 2 - cos(x), 3 - exp(x), 4 - arctg(x)\n");
		scanf("%d", &function_select);
		if (function_select >= 1 && function_select <= 4)
			flag = 0;
		else
			printf("������ ������������ ����� �������. ����������, ���������� ��� ���.\n");
	}
	printf("������� �������� �����: \n");
	printf("(��� ������� sin � cos ���������� ������� �������� ����� � ��������)\n");
	printf("(��� ������� arctg ���������� ������� �������� ����� � �������� �� -1 �� 1)\n");
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
				printf("����������� ������� �������� ����� ��� �����������. ����������, ���������� ��� ���.\n");
				printf("(��� ������� arctg ���������� ������� �������� ����� � �������� �� -1 �� 1)\n");
				printf("������� �������� �����: \n");
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
			printf("������� �������� ���������� (>= 0,000001): \n");
			scanf("%lf", &precision);
			if (precision >= 0.000001)
				flag = 0;
			else
				printf("������� ������ ��������. ����������, ���������� ��� ���.\n"); 
		}

		flag = 1;
		while (flag) {
			printf("������� ����� ��������� ���� ��� ���������� ������� (1 - 1000): \n");
			scanf("%d", &N);
			if (N < 1 || N > 1000)
				printf("������� ������� ���������� ���������. ����������, ���������� ��� ���.\n");
			else
				flag = 0;
		}
		el = 1;
		estimated_value = taylorFunctions[function_select - 1](x, precision, N-1, &el);
		difference = fabs(reference_value - estimated_value);
		printf("��������� ��������: %f\n", reference_value);
		printf("����������� ������ �������� �������: %f\n", estimated_value);
		printf("�������: %f\n", difference);
		printf("���������� ����������� ���������: %d\n", el);
	}
	else 
	{
		flag = 1;
		while (flag) {
			printf("������� ����� ������������� (1 - 25): \n");
			scanf("%d", &NMax);
			if (NMax < 1 || NMax > 25)
				printf("�������� ���������� �������������. ����������, ���������� ��� ���.\n");
			else
				flag = 0;
		}

		printf("��������� ��������: %f\n", reference_value);
		printf("��������� | ��������� �������� | �������\n");
		el = 1;
		estimated_value = taylorFunctions[function_select - 1](x, -1, NMax, &el);
	}
	system("pause");
}