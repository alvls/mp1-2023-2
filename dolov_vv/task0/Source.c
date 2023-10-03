#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <locale.h>

int main()
{
	float x1, y1, r1;
	float x2, y2, r2;
	float rasst;

	setlocale(LC_ALL, "rus");
	printf("Введите координаты центра первой окружности и ее радиус");
	scanf("%f %f %f", &x1, &y1, &r1);
	printf("Введите координаты центра второй окружности и ее радиус");
	scanf("%f %f %f", &x2, &y2, &r2);

	rasst = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
	if (rasst > r1 + r2)
		printf("Окружности не пересекаются  и не касаются друг друга");
	if (rasst > r1 - r2 && rasst > r2 - r1 && rasst < r1 + r2)
		printf("Окружности пересекаются \n");
	if (rasst == r1 + r2)
		printf("Окружности касаются друг друга внешним образом \n");
	if (rasst == r2 - r1 && rasst != 0)
		printf("Первая окружность вписана во вторую и касается ее, но они не совпадают  \n");
	if (rasst == r1 - r2 && rasst != 0)
		printf("Вторая окружность вписана в первую и касается ее, но они не совпадают  \n");
	if (rasst < r2 - r1)
		printf("Первая окружность вписана во вторую, но не касается ее \n");
	if (rasst < r1 - r2)
		printf("Вторая окружность вписана в первую, но не касается ее \n");
	if (rasst == 0 && r1 == r2)
		printf("Окружности вписаны друг в друга(совпадают) \n");

	system("pause");
}