#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>
#include "functions.h"

void funct(double acrc, int mode, int count, double x, int choice)
{
	double* spr = (double *)malloc(count*sizeof(double));
	double value, et, tmp;
	int flag = 0, terms;
	switch (mode)
	{
	case 1:
		if (choice == 4)
		{
			et = 1/etalon[choice](x);
		}
		else
			et = etalon[choice](x);
		terms = 0;
		for (int i = 1; i <= count; i++)
		{
			terms++;
			value = function[choice](x, i);
			if (fabs(et - value) < acrc)
				break;
		}
		printf("\n���������� ������ ���������:\n");
		printf("��������� ��������: %lf\n", et);
		printf("����������� ��������: %lf\n", value);
		printf("����������� ����������: %lf\n", fabs(value - et));
		printf("��������� ������ � ���� �������: %i\n", terms);
		break;
	case 2:
		for (int i = 1; i <= count; i++)
		{
			spr[i - 1] = function[choice](x, i);
		}
		if(choice == 4)
			printf("��������� ��������: %lf\n", 1/etalon[choice](x));
		else
			printf("��������� ��������: %lf\n", etalon[choice](x));
		printf("���������        ��������                       �����������\n");
		for (int i = 0 ; i < count; i++)
		{
			if(choice == 4)
				printf("%i                %0.20lf         %0.20lf\n", i + 1, spr[i], fabs(spr[i] - 1/etalon[choice](x)));
			else
				printf("%i                %0.20lf         %0.20lf\n", i + 1, spr[i], fabs(spr[i] - etalon[choice](x)));
		}
		system("pause");
		break;
	}
	free(spr);
}

int main()
{
	func_arr();
	int func, flag, mode, count;
	double x, acrc, pi = 3.141592;
	setlocale(LC_ALL, "rus");
	printf("\n�������� �������:\n1.sin(x)\n2.cos(x)\n3.e^x\n4.csc(x) x �� ������ ���� ������ ����� '��'\n");
	do
	{
		flag = 0;
		scanf("%i", &func);
		while (getchar() != '\n');
		if (func != 1 && func != 2 && func != 3 && func != 4)
			printf("������������ ����! ���������� ���\n");
		else
			flag = 1;
	} while (flag == 0);
	printf("\n�������� ���� �� ���� �������:\n1.����������� ������ ������� � �������� �����\n2.�������� �����������\n");
	do
	{
		flag = 0;
		scanf("%i", &mode);
		while (getchar() != '\n');
		if (mode != 1 && mode != 2)
			printf("������������ ����! ���������� ���!\n");
		else
			flag = 1;
	} while (flag == 0);
	switch (mode)
	{
	case 1:
		printf("\n�� ������� ������ �����\n�������:\n1.�����, � ������� ����� �������������� ������ (��� ���� �������, ����� 3 ���� � ��������)\n2.�������� (�� 0,1 �� 0,000001)\n3.������� ������ ���� ������� ����� ���������\n");
		do
		{
			flag = 0;
			scanf("%lf %lf %i", &x, &acrc, &count);
			while (getchar() != '\n');
			if (count < 1 || count > 1000)
				printf("������������ ���-�� ������! ���������� ���!\n");
			else
				flag = 1;
			if ((func == 1) || (func == 2) || (func == 4))
			{
				while (x > (2 * pi))
					x = x - 2 * pi;
				if (func == 4)
				{
					if (sin(x) == 0)
					{
						flag = 0;
						printf("cosec �� ����� ��������� �������� pi*K. ������� ������!");
					}
				}
			}
		} while (flag == 0);
		funct(acrc, mode, count, x, func);
		break;
	case 2:
		do
		{
			printf("\n�� ������� ������ �����\n�������:\n1.�����, � ������� ����� �������������� ������ (��� ���������� �����: 0,15 - ���������� �����)\n    (��� ���� �������, ����� 3 ���� � ��������)\n2. ���������� ������������� (�� 1 �� 25)\n");
			flag = 0;
			scanf("%lf %i", &x, &count);
			while (getchar() != '\n');
			if (count > 25 || count < 1)
				printf("������������ ���-�� �������������! ���������� ���!\n");
			else
				flag = 1;
			if ((func == 1) || (func == 2) || (func == 4))
			{
				while (x > (2 * pi))
					x = x - 2 * pi;
				if (func == 4)
				{
					if (sin(x) == 0)
					{
						flag = 0;
						printf("cosec �� ����� ��������� �������� pi*K. ������� ������!");
					}	
				}
			}
		} while (flag == 0);
		funct(1, mode, count, x, func);
		break;
	default:
		;
	}
	system("pause");
}