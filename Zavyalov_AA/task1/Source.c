#include <stdio.h>
#include <locale.h>
#include <math.h>


float max(float x, float y) {
	if (x > y) {
		return x;
	}
	else {
		return y;
	}
}

float min(float x, float y) {
	if (x > y) {
		return y;
	}
	else {
		return x;
	}
}

void main() {
	float x1, y1, r1, x2, y2, r2;
	setlocale(LC_ALL, "Rus");
	printf("Введите координаты и радиус первой окружности: ");
	scanf_s("%f %f %f", &x1, &y1, &r1);
	printf("Введите координаты и радиус второй окружности: ");
	scanf_s("%f %f %f", &x2, &y2, &r2);
	// касаются внутри, касаются снаружи, совпадают, не касаются, пересекаются
	double rasst = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
	if (x1 == x2 && y1 == y2 && r1 == r2) {
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
	else if (x1 == x2 && y1 == y2 && r1 != r2) {
		printf("Центры окружностей совпадают, радиусы не совпадают. ");
	} 
	else if ((rasst < max(r1, r2)) && (max(r1, r2) > rasst + min(r1, r2))) {
		printf("Одна окружность внутри другой. ");
	}
	else {
		printf("Пересекаются. ");
	}
	system("pause");

}