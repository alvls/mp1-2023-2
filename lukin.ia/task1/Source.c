#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <locale.h>

int main(){
	float r1, r2, x1, x2, y1, y2, D;
	setlocale(LC_ALL, "rus");
	printf("Введите радиусы окружностей 1 и 2\n");
	scanf("%f %f", &r1, &r2);
	printf("Введите координаты центра первой окружности\n");
	scanf("%f %f", &x1, &y1);
	printf("Введите координаты центра второй окружности\n");
	scanf("%f %f", &x2, &y2);
	D = sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
	if (D > r2 + r1){
		printf("Окружности не касаются  ");
	}
	else if (D == r1 + r2){
		printf("Окружности касаются снаружи  ");
	}
	else if ((D < r1 + r2) && (D > fabs(r1 - r2))){
		printf("Окружности пересекаются в двух точках  ");
	}
	else if (x1 == x2 && y1 == y2 && r1 == r2){
		printf("Окружности совпадают  ");
	}
	else if ((D == fabs(r1 - r2))){
		printf("Окружности касаются изнутри  ");
	}
	else if ((D < fabs(r1 - r2))){
		printf("Окружности не касаются, причем одна лежит внутри другой  ");
	}
	
	system("pause");

}