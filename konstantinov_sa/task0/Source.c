#include <stdio.h>
#include <math.h>
#include <locale.h>

int main() {
	setlocale(LC_ALL, "");
	float x1, y1, r1, x2, y2, r2 = -1.0f;
	printf("Введите координаты центра первой окружности (x, y), а затем её радиус через пробелы\n");
	scanf_s("%f %f %f", &x1, &y1, &r1);
	printf("Введите координаты центра второй окружности (x, y), а затем её радиус через пробелы\n");
	scanf_s("%f %f %f", &x2, &y2, &r2);

	if (r1 < 0 || r2 < 0) { //также срабатывает когда scanf не смог присвоить неверно введённое значение и значения r1, r2 остались отрицательными с инициализации
		printf("Неверный ввод!\n"); 
		system("pause");
		return -1;
	}

	float vx = x1 - x2;
	float vy = y1 - y2;
	float dist = sqrt(vx * vx + vy * vy);

	if (dist > r1 + r2) {
		printf("Окружности не пересекаются");
	}
	else if (dist == 0 && r1 != r2) {
		printf("Центры окружностей совпадают, одна находится внутри другой");

	}
	else if (dist == 0 && r1 == r2) {
		printf("Окружности совпадают");

	}
	else if (dist == r1 + r2) {
		printf("Окружности касаются в одной точке снаружи");
	}
	else if (dist == fabs(r1 - r2)) {
		
		printf("Одна окружность находится внутри другой, касается в одной точке");
	}
	else if (dist < fabs(r1 - r2)) {
		printf("Одна окружность находится внутри другой, они не касаются");
	}
	else {
		printf("Окружности пересекаются в двух точках");
	}

	printf("\n");
	system("pause");
	return 0;
	
}