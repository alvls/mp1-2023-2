#include <stdio.h>
#include <math.h>
#include <locale.h>
// не дописана

void main() {
	setlocale(LC_ALL, "rus");
	float r, R, p; // малый радиус, большой радиус, расстояние
	float x1, x2, y1, y2;

	scanf_s("%f %f %f", &x1, &y1, &R);
	scanf_s("%f %f %f", &x2, &y2, &r);

	//определение максимального радиуса

	if (r > R) {
		p = R;
		R = r;
		r = p;
	}

	p = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
	//printf_s("%f", p);
	


	
	if ((R + r > p) && (R < p)) { printf_s("Окружности перескаются \n"); }
	if (p > r + R) { printf_s("Никакая из окружностей не лежит внутри другой, не касаются, не пересекаются \n"); }
	if (R == p + r) { printf_s("внутреннее касание \n"); }
	if (R + r == p) { printf_s("внешнее касание \n"); }
	if ((p + r < R) && (R > p)) { printf_s("одна окружность лежит в другой \n"); }
	if ((p == 0) && (r != R)) { printf_s("совпали центры и не совпали радиусы \n"); }
	if ((p == 0)&&(r == R)) { printf_s("полное совпадение \n"); }
	


	system("pause");
}
