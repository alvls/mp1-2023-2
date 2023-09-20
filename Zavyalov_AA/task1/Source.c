#include <stdio.h>
#include <locale.h>
#include <math.h>

void main() {
	float x1, y1, r1, x2, y2, r2;
	setlocale(LC_ALL, "Rus");
	printf("Введите координаты и радиус первой окружности: ");
	scanf_s("%f %f %f", &x1, &y1, &r1);
	printf("Введите координаты и радиус второй окружности: ");
	scanf_s("%f %f %f", &x2, &y2, &r2);
	// касаются внутри, касаются снаружи, совпадают, не касаются, пересекаются
	float rasst = sqrt(fabs(x2 - x1) * fabs(x2 - x1) + fabs(y2 - y1) * fabs(y2 - y1));
	if (x1 == x2 & y1 == y2 & r1 == r2) {
		printf("Совпадают. ");
	}
	else if (rasst > (r1 + r2)) { // не касаются
		printf("Не касаются и не пересекаются, никакая из окружностей не находится внутри другой. ");
	}
	else if (rasst == (r1 + r2)) {
		printf("Касаются снаружи. ");
	}
	else if (rasst == fabs(r1 - r2)) {
		printf("Касаются внутри. ");
	}
	else if (x1 == x2 & y1 == y2 & r1 != r2) {
		printf("Центры окружностей совпадают, радиусы не совпадают. ");
	} 
	else if (rasst < (r1 + r2)) {
		printf("Пересекаются. ");
	}
	else {
		printf("Одна окружность внутри другой. ");
	}
	system("pause");

}