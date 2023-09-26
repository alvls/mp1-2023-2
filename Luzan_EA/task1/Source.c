#include <stdio.h>
#include <math.h>
#include <locale.h>


void main() {

	setlocale(LC_ALL, "rus");
	float r, R, dist; // first radius, second radius, distance
	float x1, x2, y1, y2; // coordinates
	float e = 0.0001; // to check the equality float == float


	scanf_s("%f %f %f", &x1, &y1, &R);
	scanf_s("%f %f %f", &x2, &y2, &r);


	// determining the maximum radius, dist is used to avoid creating new variables
	if (r > R) {
		dist = R;
		R = r;
		r = dist;
	}


	dist = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));

	
	if ((R + r > dist) && (R < dist)) { printf_s("окружности перескаются \n the circles intersect \n"); }
	if (dist > r + R ) { printf_s("никакая из окружностей не лежит внутри другой, не касаются, не пересекаются \n none of the circles lies inside the other, do not touch, do not intersect \n"); }
	if (R == dist + r) { printf_s("внутреннее касание \n inner touch \n"); }
	if (R + r - dist < e) { printf_s("внешнее касание \n external touch \n"); }
	if ((dist + r < R) && (R > dist)) { printf_s("одна окружность лежит в другой \n one circle lies in the other \n"); }
	

	system("pause");
}
