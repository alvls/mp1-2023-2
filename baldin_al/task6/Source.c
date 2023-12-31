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
		printf("1. ����������� ������ ������� � �������� �����\n");
		printf("2. �������� ����������� \n");
		do {
			printf("������� ����� ������: ");
			scanf_s("%d", &choice);
			if (choice != 1 && choice != 2)
				printf("������� ������ �� ����������. ������� ����� ������ �� ������������.\n\n");
		} while (choice != 1 && choice != 2);

		int y;
		double x;
		double p = 0;
		int k;
		system("cls");
		printf("1) sin(x) \n2) cos(x) \n3) exp(x) \n4) tan(x) \n");
		do {
			printf("������� ����� ��������� �������: ");
			scanf_s("%d", &y);
			if (y < 1 || y > 4)
				printf("������ ������� �� ����������. ������� ����� ����� �� ������������. \n\n");
		} while (y < 1 || y > 4);

		system("cls");
		printf("������� ����� x, � ������� ���������� ��������� ��������: ");
		scanf_s("%lf", &x);

		system("cls");
		if (choice == 1)
		{
			do {
				printf("������� �������� ���������� (>= 0.000001): ");
				scanf_s("%lf", &p);
				if (p < 0.000001)
					printf("������ �������� ������ ����������. \n\n");
			} while (p < 0.000001);
			system("cls");
		}
		if (choice == 1)
		{
			do {
				printf("������� ����� ��������� ���� ��� ���������� ������� (N - �� 1 �� 1000): ");
				scanf_s("%d", &k);
				if (k < 1 || k > 1000)
					printf("����� ������������� ������ ���� � ��������� �� 1 �� 1000. \n\n");
			} while (k < 1 || k > 1000);
			system("cls");
		}
		if (choice == 2)
		{
			do {
				printf("������� ����� ������������� (NMax - �� 1 �� 25): ");
				scanf_s("%d", &k);
				if (k < 1 || k > 25)
					printf("����� ������������� ������ ���� � ��������� �� 1 �� 25. \n\n");
			} while (k < 1 || k > 25);
			system("cls");
		}
		fact = (long double*)malloc((2 * k + 1) * sizeof(long double));
		B = (double*)malloc((2 * k + 1) * sizeof(double));
		double a = funcs[y - 1](x);
		double b = f[y - 1](x, p, k);

		if (choice == 1)
		{
			printf("��������� ��������: %.7lf \n", a);
			printf("����������� ������ �������� �������: %.7lf \n", b);
			printf("������� ����� ������� � ��������� ���������: %.7lf \n", fabs(a - b));
			printf("���������� ���������, ������� ���� ���������: %d \n", count - 1);
		}
		else
		{
			printf("��������� ��������: %.16lf \n", a);
			printf("======================================= \n");
			printf("\n       ����������� ������ �������� �������  |  ������� ����� ������� � ��������� ��������� \n");
			for (int i = 0; i < count - 1; i++)
			{
				printf("%3.d  |  %-32.16lf    |  %.16lf\n", i + 1, res[i], fabs(res[i] - a));
			}
		}
		printf("\n���� �� ������ �������� ��� ���� ������, �� ������� 1\n");
		printf("���� �� ������ ��������� ���������, �� ������� 2\n");
		scanf_s("%d", &ch);
		free(res);
		system("cls");
	} while (ch != 2);
	free(B);
}
