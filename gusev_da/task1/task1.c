#include <stdio.h>
#include <locale.h>

void main1()
{
	setlocale(LC_ALL, "Rus");
	int shelf; // количество полок
	float bokovini, polki, krishki, dveri, stenka, massa; // масса всех деталей шкафа и самого шкафа
	int dvp, dsp, wood; // плотность двп, дсп, дерева
	double dvp_v, dsp_v, wood_v; // толщина двп, дсп и дерева
	double h, w, d; // общая длина, ширина и глубина


	dvp = 500;
	dsp = 800;
	wood = 1500;
	dsp_v = 1.5;
	dvp_v = 0.5;
	wood_v = 1;

	printf("Привет! Эта программа высчитает массу шкафа исходя из его размеров.\n"
		"Высота задней стенки равняется высоте дверей и боковин.\n"
		"Ширина задней стенки равняется ширине дверей, полок и боковин.\n"
		"Глубина боковин равняется глубине крышек и полок.\n\n");
	do
	{
		printf("Введите высоту задней стенки шкафа от 180 до 220 см: ");
		scanf_s("%lf", &h);
	} while ((h < 180) || (h > 220));
	do
	{
		printf("Введите ширину задней стенки шкафа от 80 до 120 см: ");
		scanf_s("%lf", &w);
	} while ((w < 80) || (w > 120));
	do
	{
		printf("Введите глубину боковины шкафа от 50 до 90 см: ");
		scanf_s("%lf", &d);
	} while ((d < 50) || (d > 90));
	
	if (h > 200.5)
	{
		shelf = 5;
	}
	else
	{
		shelf = 4;
	}

	stenka = dvp * dvp_v * h * w * 0.000001;
	bokovini = dsp * dsp_v * d * h * 2 * 0.000001;
	krishki = dsp * dsp_v * d * w * 2 * 0.000001;
	dveri = wood * wood_v * w * h * 0.000001;
	polki = dsp * dsp_v * d * w * shelf * 0.000001;
	massa = stenka + bokovini + krishki + dveri + polki;

	printf("Масса шкафа равна %.3f кг", massa);
	system("pause");
}