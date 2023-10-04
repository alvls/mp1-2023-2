//#define _CRT_SECURE_NO_WARNINGS
//
//#include <stdio.h>
//#include <math.h>
//#include <locale.h>
//#include <stdlib.h>
//
//void main()
//{
//	setlocale(LC_ALL, "rus");
//	float X1, Y1, R1;
//	float X2, Y2, R2;
//	float d;
//	printf("������� ���������� ������ X1 � Y1 � ������ R1 ������ ����������: ");
//	scanf("%f %f %f", &X1, &Y1, &R1);
//	printf("������� ���������� ������ X2 � Y2 � ������ R2 ������ ����������: ");
//	scanf("%f %f %f", &X2, &Y2, &R2);
//	d = sqrt(pow((X1 - X2), 2) + pow((Y1 - Y2), 2)); // ��������� ����� �������� �����������
//	if (R1 + R2 == d)
//		printf("���������� �������� ������� �������\n");
//	else if (d == 0)
//		if (R2 > R1)
//			printf("������ ����������� ��������� � ���������� 1 ����� ������ ���������� 2\n");
//		else if (R1 > R2)
//			printf("������ ����������� ��������� � ���������� 2 ����� ������ ���������� 1\n");
//		else
//			printf("���������� ���������\n");
//	else if (fabs(R1 - R2) == d)
//		if (R1 + d == R2)
//			printf("���������� �������� ���������� ������� � ���������� 1 ����� ������ ���������� 2\n");
//		else
//			printf("���������� �������� ���������� ������� � ���������� 2 ����� ������ ���������� 1\n");
//	else if (R1 + R2 < d)
//		printf("���������� ����������� ��� ���� �����, �� ������������ � �� ��������\n");
//	else if (fabs(R1 - R2) > d)
//		if (R1 + d < R2)
//			printf("���������� 1 ����������� ������ ���������� 2, ��� �� ��������, �� ������������ � �� ������ �� ���������\n");
//		else
//			printf("���������� 2 ����������� ������ ���������� 1, ��� �� ��������, �� ������������ � �� ������ �� ���������\n");
//	else if ((R1 + R2 > d) && (R1 + d > R2) && (R2 + d > R1))
//		printf("���������� ������������\n");
//	system("pause");
//}



#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <math.h>

void main()
{
	setlocale(LC_ALL, "rus");
	float density_DSP = 800;
	float density_DVP = 820;
	float density_wood = 600;
	float h;// ������
	float w;// ������
	float d;// �������
	float hh;
	int flag, count = 0, ch;
	float m_back_wall, m_sidewalls, m_covers, m_doors, m_shelves, m_closet;
	char restart;
	do
	{
		system("cls");
		do
		{
			printf("������� ������ h �� 180 �� 220 ��: ");
			scanf("%f", &h);
			while (ch = getchar() != '\n');
			flag = 1;
			if (h >= 180 && h <= 220)
				flag = 0;
		} while (flag);
		do
		{
			printf("������� ������ w �� 80 �� 120 ��: ");
			scanf("%f", &w);
			while (ch = getchar() != '\n');
			flag = 1;
			if (w >= 80 && w <= 120)
				flag = 0;
		} while (flag);
		do
		{
			printf("������� ������� d �� 50 �� 90 ��: ");
			scanf("%f", &d);
			while (ch = getchar() != '\n');
			flag = 1;
			if (d >= 50 && d <= 90)
				flag = 0;
		} while (flag);
		h /= 100;
		w /= 100;
		d /= 100;
		m_back_wall = density_DVP * h * w * 5 / 1000;// ����� ������ ��������� ������ �� ���
		m_sidewalls = density_DSP * h * d * 15 / 1000 * 2;// ����� ������� �� ���
		m_covers = density_DSP * w * d * 15 / 1000 * 2;// ����� ��������� ������� � ������ ������ �� ���
		m_doors = density_wood * h * w * 1 / 100;// ����� ���� ��������� ������ �� ������
		hh = h * 100;
		while (hh - 41.5 > 0)
		{
			count++;
			hh -= 41.5;
		}
		m_shelves = count * (density_DSP * 15 / 1000 * (w * 100 - 3) / 100 * d); // ����� ���������� �����
		m_closet = m_back_wall + m_sidewalls + m_covers + m_doors + m_shelves; // ����� �����
		printf("%f\n", m_closet);
		printf("������ ������������� ���������? Y = ��: ");
		scanf("%c", &restart);
	} while (restart == 'y' || restart == 'Y');
	system("pause");
}