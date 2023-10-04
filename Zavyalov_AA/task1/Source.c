/*
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
		printf("Окружности совпадают. ");
	}
	else if (rasst > (r1 + r2)) { // не касаются
		printf("Окружности не касаются и не пересекаются, никакая из окружностей не находится внутри другой. ");
	}
	else if (rasst == (r1 + r2)) {
		printf("Окружности касаются снаружи. ");
	}
	else if (rasst == fabs(r1 - r2)) {
		printf("Окружности касаются внутри. ");
	}
	else if (x1 == x2 && y1 == y2 && r1 != r2) {
		printf("Центры окружностей совпадают, радиусы не совпадают. ");
	}
	else if ((rasst < max(r1, r2)) && (max(r1, r2) > rasst + min(r1, r2))) {
		printf("Одна окружность внутри другой. ");
	}
	else {
		printf("Окружности пересекаются. ");
	}
	system("pause");

}
*/

#include <stdio.h>
#include <locale.h>

int main() {
	int h, w, d;
	float zad_t = 0.5, bok_t = 1.5, krish_t = 1.5, dv_t = 1;
	float dsp_den = 0.75, dvp_den = 0.95, der_den = .7;
	setlocale(LC_ALL, "rus");
	printf("Введите высоту и ширину задней стенки: "); // Enter the height and width of the back wall: 
	scanf_s("%d %d", &h, &w); // 1.h and 1.w
	printf("Введите глубину боковин: "); // Enter the depth of the sidewalls: 
	scanf_s("%d", &d);
	while (!(180 <= h && h <= 220)) {
		printf("Введите высоту от 180 см 220 см: "); // Enter the height from 180 cm 220 cm:
		scanf_s("%d", &h);
	}
	while (!(80 <= w && w <= 120)) {
		printf("Введите ширину от 80 см 120 см: "); // Enter a width from 80 cm to 120 cm:
		scanf_s("%d", &w);
	}
	while (!(50 <= d && d <= 90)) {
		printf("Введите глубину от 50 см до 90 см: "); // Enter a depth of 50 cm to 90 cm:
		scanf_s("%d", &d);
	}
	int kol_p = h / (41.5);
	float ans = 0;
	int zad_stenka = h * w * zad_t * dvp_den; // 1
	int dve_bokovini =  h * d * bok_t * dsp_den * 2; // 2
	int krishki = w * d * krish_t * dsp_den * 2; // 3
	int dveri = h * w * dv_t * der_den; // 4
	int polki = d * (w - bok_t * 2) * 1.5 * kol_p * dsp_den; // 5
	ans = zad_stenka + dve_bokovini + krishki + dveri + polki;
	ans /= 1000;
	printf("Вес шкафа: %g кг\n", ans); // cabinet weight: ans kg
	system("pause");
	return 0;
}