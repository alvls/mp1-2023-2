/*
#define _CRT_SECURE_NO_WARNINGS


#include <stdio.h>
#include <locale.h>
#include <math.h>

void main()
{
	float x1, y1;
	float x2, y2;
	float r1, r2;
	float S;

	setlocale(LC_ALL, "rus");

	printf("������� ���������� ������ ���������� (x1,y1): ");
	scanf("%f %f", &x1, &y1);
	printf("������� ������ ������ ���������� (r1): ");
	scanf("%f", &r1);

	printf("������� ���������� ������ ���������� (x2,y2):");
	scanf("%f %f", &x2, &y2);
	printf("������� ������ ������ ���������� (r2): ");
	scanf("%f", &r2);

	S = sqrtf(powf(fabs(x2 - x1), 2) + powf(fabs(y2 - y1), 2));

	if (S > r1 + r2)
	{
		printf("���������� �� ������������");
	}

	if (S < fabs(r1 - r2))
	{
		printf("���� �� ����������� ���������� ������ ������");
	}

	if (S == r1 + r2)
	{
		printf("���������� �������� ���� ����� � ����� ����� (������� �������)");
	}

	if (S == fabs(r1 - r2) && !(x1 == x2 && y1 == y2 && r1 == r2))
	{
		printf("���������� �������� ���� ����� � ����� ����� (���������� �������)");
	}

	if (fabs(r1 - r2) < S && S < r1 + r2)
	{
		printf("���������� ������������ � ���� ������");
	}

	if (x1 == x2 && y1 == y2 && r1 == r2)
	{
		printf("���������� ���������");
	}

	system("pause");
}
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <locale.h>
#include <math.h>

void main()
{
	float h, w, d, M;
	float back_wall, side_walls, covers, doors, shelves; 
	float dvp = 0.85, dsp = 0.8, derevo = 0.5; 
	int count;

	setlocale(LC_ALL, "rus");

	do
	{
		printf("������� ������ ����� (180 - 220 ��): ");
		scanf("%f", &h);
		if (h < 180 || h > 220)
			printf("�������� ��������. \n");
	} while (h < 180 || h > 220);

	do
	{
		printf("������� ������ ����� (80 - 120 ��): ");
		scanf("%f", &w);
		if (w < 80 || w > 120)
			printf("�������� ��������. \n");
	} while (w < 80 || w > 120);

	do
	{
		printf("������� ������� ����� (50 - 90 ��): ");
		scanf("%f", &d);
		if (d < 50 || d > 90)
			printf("�������� ��������. \n");
	} while (d < 50 || d > 90);

	back_wall = h * w * 0.5 * dvp;
	side_walls = 2 * h * d * 1.5 * dsp;
	covers = 2 * w * d * 1.5 * dsp;
	doors = h * w * 1 * derevo;
	count = (h - 40) / (40 + 1.5);
	shelves = count * (w - 3) * d * 1.5 * dsp;

	M = back_wall + side_walls + covers + doors + shelves;
	M = M / 1000;

	printf("����� �����: %.3f �� \n", M);

	system("pause");
}