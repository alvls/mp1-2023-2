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

	printf("Введите координаты первой окружности (x1,y1): ");
	scanf("%f %f", &x1, &y1);
	printf("Введите радиус первой окружности (r1): ");
	scanf("%f", &r1);

	printf("Введите координаты второй окружности (x2,y2):");
	scanf("%f %f", &x2, &y2);
	printf("Введите радиус второй окружности (r2): ");
	scanf("%f", &r2);

	S = sqrtf(powf(fabs(x2 - x1), 2) + powf(fabs(y2 - y1), 2));

	if (S > r1 + r2)
	{
		printf("Окружности не пересекаются");
	}

	if (S < fabs(r1 - r2))
	{
		printf("Одна из окружностей содержится внутри другой");
	}

	if (S == r1 + r2)
	{
		printf("Окружности касаются друг друга в одной точке (внешнее касание)");
	}

	if (S == fabs(r1 - r2) && !(x1 == x2 && y1 == y2 && r1 == r2))
	{
		printf("Окружности касаются друг друга в одной точке (внутреннее касание)");
	}

	if (fabs(r1 - r2) < S && S < r1 + r2)
	{
		printf("Окружности пересекаются в двух точках");
	}

	if (x1 == x2 && y1 == y2 && r1 == r2)
	{
		printf("Окружности совпадают");
	}

	system("pause");
}