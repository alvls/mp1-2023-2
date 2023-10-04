#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>

int main()
{
	int h, w, d;
	float densy_dvp = 950;
	float densy_dsp = 600;
	float densy_wood = 720; //плотность дуба
	float weight;

	setlocale(LC_ALL, "rus");

	float vol_dvp; //задн€€ стенка
	float vol_dsp; //2 боковины, верхн€€ и нижн€€ стенки
	float vol_wood; // 2 двери
	float vol_shelf; // полки

	int flag = 0;

	do
	{
		printf("введите высоту шкафа (180-220 (см)) \n");
		scanf("%d", &h);
		if ((h < 180) || (h > 220))
		{
			printf("неправильно введена длина шкафа");
			system("pause");
			flag = 1;
		}
		else
			flag = 0;
	} while (flag == 1);

	do
	{
		printf("введите ширину шкафа (80-120 (см))\n");
		scanf("%d", &w);
		if ((w < 80) || (w > 120))
		{
			printf("неправильно введена ширина шкафа");
			system("pause");
			flag = 1;
		}
		else
			flag = 0;
	} while (flag == 1);

	do
	{
		printf("введите глубину шкафа (50-90 (см))\n");
		scanf("%d", &d);
		if ((d < 50) || (d > 90))
		{
			printf("неправильно введена глубина шкафа");
			system("pause");
			flag = 1;
		}
		else
			flag = 0;
	} while (flag == 1);


	vol_dvp = (h * 0.01 * w * 0.01) * 0.005;
	vol_dsp = (2 * h * 0.01 * d * 0.01 + 2 * w * 0.01 * d * 0.01) * 0.015; //без полок
	vol_wood = (h * 0.01 * w * 0.01) * 0.01;


	int i = 415, shelf_count = 0;
	while (h * 10 > i)
	{
		shelf_count++;
		i += 415;
	}
	vol_shelf = (shelf_count * (w - 3) * 0.01 * d * 0.01) * 0.015;

	weight = vol_dvp * densy_dvp + densy_dsp * (vol_dsp + vol_shelf) + vol_wood * densy_wood;
	printf("масса шкафа %f кг ", weight);

	system("pause");
}
