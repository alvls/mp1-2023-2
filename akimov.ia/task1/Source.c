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
//	printf("Введите координаты центра X1 и Y1 и радиус R1 первой окружности: ");
//	scanf("%f %f %f", &X1, &Y1, &R1);
//	printf("Введите координаты центра X2 и Y2 и радиус R2 второй окружности: ");
//	scanf("%f %f %f", &X2, &Y2, &R2);
//	d = sqrt(pow((X1 - X2), 2) + pow((Y1 - Y2), 2)); // Растояние между центрами окружностей
//	if (R1 + R2 == d)
//		printf("Окружности касаются внешним образом\n");
//	else if (d == 0)
//		if (R2 > R1)
//			printf("Центры окружностей совпадают и окружность 1 лежит внутри окружности 2\n");
//		else if (R1 > R2)
//			printf("Центры окружностей совпадают и окружность 2 лежит внутри окружности 1\n");
//		else
//			printf("Окружности совпадают\n");
//	else if (fabs(R1 - R2) == d)
//		if (R1 + d == R2)
//			printf("Окружности касаются внутренним образом и окружность 1 лежит внутри окружности 2\n");
//		else
//			printf("Окружности касаются внутренним образом и окружность 2 лежит внутри окружности 1\n");
//	else if (R1 + R2 < d)
//		printf("Окружности расположены вне друг друга, не пересекаются и не касаются\n");
//	else if (fabs(R1 - R2) > d)
//		if (R1 + d < R2)
//			printf("Окружность 1 расположена внутри окружности 2, они не касаются, не пересекаются и их центры не совпадают\n");
//		else
//			printf("Окружность 2 расположена внутри окружности 1, они не касаются, не пересекаются и их центры не совпадают\n");
//	else if ((R1 + R2 > d) && (R1 + d > R2) && (R2 + d > R1))
//		printf("Окружности пересекаются\n");
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
	float h;// Высота
	float w;// Ширина
	float d;// Глубина
	float hh;
	int flag, count = 0, ch;
	float m_back_wall, m_sidewalls, m_covers, m_doors, m_shelves, m_closet;
	char restart;
	do
	{
		system("cls");
		do
		{
			printf("Введите высоту h от 180 до 220 см: ");
			scanf("%f", &h);
			while (ch = getchar() != '\n');
			flag = 1;
			if (h >= 180 && h <= 220)
				flag = 0;
		} while (flag);
		do
		{
			printf("Введите ширину w от 80 до 120 см: ");
			scanf("%f", &w);
			while (ch = getchar() != '\n');
			flag = 1;
			if (w >= 80 && w <= 120)
				flag = 0;
		} while (flag);
		do
		{
			printf("Введите глубину d от 50 до 90 см: ");
			scanf("%f", &d);
			while (ch = getchar() != '\n');
			flag = 1;
			if (d >= 50 && d <= 90)
				flag = 0;
		} while (flag);
		h /= 100;
		w /= 100;
		d /= 100;
		m_back_wall = density_DVP * h * w * 5 / 1000;// масса задней накладной стенки из ДВП
		m_sidewalls = density_DSP * h * d * 15 / 1000 * 2;// масса боковин из ДСП
		m_covers = density_DSP * w * d * 15 / 1000 * 2;// масса накладных верхней и нижней крышки из ДСП
		m_doors = density_wood * h * w * 1 / 100;// масса двух накладных дверей из дерева
		hh = h * 100;
		while (hh - 41.5 > 0)
		{
			count++;
			hh -= 41.5;
		}
		m_shelves = count * (density_DSP * 15 / 1000 * (w * 100 - 3) / 100 * d); // масса внутренних полок
		m_closet = m_back_wall + m_sidewalls + m_covers + m_doors + m_shelves; // масса шкафа
		printf("%f\n", m_closet);
		printf("Хотите перезапустить программу? Y = да: ");
		scanf("%c", &restart);
	} while (restart == 'y' || restart == 'Y');
	system("pause");
}