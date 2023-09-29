/*
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
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <locale.h>

int main() 
{
	setlocale(LC_ALL, "rus");
	float zadst, bok, kr, door, polk;//масса деталей
	float h, w, d;//характеристические показатели
	float pldvp, pldsp, pld;//плотности материалов
	float kolpol, hvsp, i;//вспомогательные переменные для вычисления количества полок
	float masshk;//масса самого шкафа
	do
	{
		printf("Введите высоту\n");
		scanf("%f", &h);
		if (h < 180.0 || h > 220.0)
		{
			printf("Введите значение высоты от 180 до 220 см  \n");
		}
	} while (h < 180.0 || h > 220.0);
	do
	{
		printf("Введите ширину\n");
		scanf("%f", &w);
		if (w < 80 || w>120)
		{
			printf("Введите значение ширины от 80 до 120 см  \n");
		}
	} while (w < 80 || w>120);
	do
	{
		printf("Введите глубину\n");
		scanf("%f", &d);
		if (d < 50 || d>90)
		{
			printf("Введите значение глубины от 50 до 90 см  \n");
		}
	} while (d < 50 || d>90);
	hvsp = h;
	i = 0;
	do
	{
		i++;
		hvsp = hvsp - 41.5;
	} while (hvsp > 41.5);
	kolpol = i;
	pldvp = 0.82;
	pldsp = 0.55;
	pld = 0.7;
	zadst = h * w * 0.5*pldvp;
	bok = h * d * 1.5 * pldsp;
	kr = w * d * 1.5 * pldsp;
	door = h * w * 1 * pld;
	polk = d * (w - 1.5 * 2) * 1.5 * pldsp;//если принять толщину полки равной 15 мм, как и листы дсп до этого
	//также мною были учтены две боковые стенки по 1.5 см каждая
	masshk = (zadst + 2 * bok + 2 * kr + 2 * door + kolpol * polk)/1000;
	printf("Масса шкафа = %f", masshk);
	system("pause");
}