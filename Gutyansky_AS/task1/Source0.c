#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <locale.h>
#include <math.h>


// переименовать в main 
void main1() {
	setlocale(LC_ALL, "rus");

	float x1, y1, r1;
	float x2, y2, r2;
	float delta_x, delta_y;
	float radius_sum;
	float distance;

	printf("Введите через пробел две координаты и радиус первой окружности: ");
	scanf("%f %f %f", &x1, &y1, &r1);
	printf("Введите через пробел две координаты и радиус второй окружности: ");
	scanf("%f %f %f", &x2, &y2, &r2);

	delta_x = x2 - x1;
	delta_y = y2 - y1;
	radius_sum = r1 + r2;
	distance = sqrt(delta_x * delta_x + delta_y * delta_y);

	if (x1 > x2) {
		printf("Первая окружность расположена правее второй\n");
	}
	else if (x1 < x2) {
		printf("Первая окружность расположена левее второй\n");
	}
	else {
		printf("Окружности находятся на одной вертикальной оси (координаты по горизонтали совпадают)\n");
	}

	if (y1 > y2) {
		printf("Первая окружность расположена выше второй\n");
	}
	else if (y1 < y2) {
		printf("Первая окружность расположена ниже второй\n");
	}
	else {
		printf("Окружности находятся на одной горизонтальной оси (коодинаты по вертикали совпадают)\n");
	}

	if (distance > radius_sum) {
		printf("Окружности не пересекаются\n");
	}
	else if (distance == radius_sum) {
		printf("Окружности касаются друг друга внешним образом\n");
	}
	else {
		printf("Окружности пересекаются\n");
	}

	if (distance + r1 == r2) {
		printf("Первая окружность касается второй окружности изнутри\n");
	}
	else if (distance + r1 < r2) {
		printf("Первая окружность находится внутри второй\n");
	}

	if (distance + r2 == r1) {
		printf("Вторая окружность касается второй окружности изнутри\n");
	}
	else if (distance + r2 < r1) {
		printf("Вторая окружность находится внутри первой\n");
	}

	if (distance == 0 && r1 == r2) {
		printf("Окружности совпадают\n");
	}

	system("pause");
}