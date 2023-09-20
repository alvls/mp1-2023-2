#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <locale.h>

int main(){
	setlocale(LC_ALL, "rus");
	
	float x1,x2,y1,y2,r1,r2, L;
	
	printf("Введите координаты Х и У первой окружности: ");
	scanf("%f %f", &x1, &y1);
	
	printf("Введите координаты Х и У второй окружности: ");
	scanf("%f %f", &x2, &y2);
	
	printf("Введите радусы окружностей: ");
	scanf("%f %f", &r1, &r2);

	L = sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
	
	if (L == (r1 + r2)) {
		printf("Внешнее касание ");
	}

	else if ((L == abs(r1 - r2)) && ((x1 != x2) || (y1 !=y2))) {
		printf("Внутреннее касание ");
	}

	else if (L > abs(r1 - r2)) {
		printf("Одна окружность находится внутри другой и центры не совпадают ");
	}

	else if (L > (r1 + r2)) {
		printf("Одна окружность не касается другой ");
	}

	else if ((L == 0) && (r1 == r2)) {
		printf("Одна окружность совпадает с другой ");
	}

	else if ((L == 0) && (r1 != r2)) {
		printf("Одна окружность находится внутри другой и центры совпадают ");
	}
	
	else if ((L < (r1 + r2)) && (L > abs(r1 - r2))) {
		printf("Одна окружность пересекает другую в 2 точках ");
	}

	system("pause");
}