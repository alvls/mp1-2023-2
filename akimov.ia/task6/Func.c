#include "Func.h"
#include <stdio.h>
#include <math.h>

void sinus(double x, double accuracy, int N)
{
	double res = x, current = x, etalon = sin(x);
	int count = 1, n, temp;
	if (accuracy == -1)
	{
		temp = N;
		n = 1;
	}
	else
	{
		temp = 1;
		n = N;
	}
	for (int i = 1; i <= temp; i++)
	{
		while ((fabs(etalon - res) > accuracy) && (count < n))
		{
			current *= (-1) * pow(x, 2) / ((2 * count + 1) * 2 * count);
			res += current;
			count++;
		}
		printf("��������� ��������: %lf\n", etalon);
		printf("����������� ������ �������� �������: %lf\n", res);
		printf("������� ����� ������� � ��������� ���������: %lf\n", fabs(res - etalon));
		printf("���������� ���������: %d\n\n", count);
		n++;
	}
}

void cosinus(double x, double accuracy, int N)
{
	double res = 1, current = 1, etalon = cos(x);
	int count = 1, n, temp;
	if (accuracy == -1)
	{
		temp = N;
		n = 1;
	}
	else
	{
		temp = 1;
		n = N;
	}
	for (int i = 1; i <= temp; i++)
	{
		while ((fabs(etalon - res) > accuracy) && (count < n))
		{
			current *= (-1) * pow(x, 2) / ((2 * count - 1) * 2 * count);
			res += current;
			count++;
		}
		printf("��������� ��������: %lf\n", etalon);
		printf("����������� ������ �������� �������: %lf\n", res);
		printf("������� ����� ������� � ��������� ���������: %lf\n", fabs(res - etalon));
		printf("���������� ���������: %d\n\n", count);
		n++;
	}
}

void exponent(double x, double accuracy, int N)
{
	double res = 1, current = 1, etalon = exp(x);
	int count = 1, n, temp;
	if (accuracy == -1)
	{
		temp = N;
		n = 1;
	}
	else
	{
		temp = 1;
		n = N;
	}
	for (int i = 1; i <= temp; i++)
	{
		while ((fabs(etalon - res) > accuracy) && (count < n))
		{
			current *= x / count;
			res += current;
			count++;
		}
		printf("��������� ��������: %lf\n", etalon);
		printf("����������� ������ �������� �������: %lf\n", res);
		printf("������� ����� ������� � ��������� ���������: %lf\n", fabs(res - etalon));
		printf("���������� ���������: %d\n\n", count);
		n++;
	}
}

void sqrt_1plusx(double x, double accuracy, int N)
{
	double res = 1, current = 1, etalon = sqrt(1 + x);
	int count = 1, n, temp;
	if (accuracy == -1)
	{
		temp = N;
		n = 1;
	}
	else
	{
		temp = 1;
		n = N;
	}
	for (int i = 1; i <= temp; i++)
	{
		while ((fabs(etalon - res) > accuracy) && (count < n))
		{
			current *= x * (1.5 - count) / count;
			res += current;
			count++;
		}
		printf("��������� ��������: %lf\n", etalon);
		printf("����������� ������ �������� �������: %lf\n", res);
		printf("������� ����� ������� � ��������� ���������: %lf\n", fabs(res - etalon));
		printf("���������� ���������: %d\n\n", count);
		n++;
	}
}