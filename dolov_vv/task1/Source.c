#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>

int main()
{
	int h, w, d;
	float densy_dvp =950;
	float densy_dsp =600;
	float densy_wood =720; //плотность дуба
	float weight;

	setlocale(LC_ALL, "rus");
	printf("введите высоту шкафа \n");
	scanf("%d", &h);
	printf("введите ширину шкафа \n");
	scanf("%d", &w);
	printf("введите глубину шкафа \n");
	scanf("%d", &d);
	
	if ((h < 180) || (h > 220) || (w < 80) || (w > 120) || (d < 50) || (d > 90))
	{
		printf("неправильно введены размеры ");
		system("pause");
		return 0;
	}
	float vol_dvp; //задн€€ стенка
	float vol_dsp; //2 боковины, верхн€€ и нижн€€ стенки
	float vol_wood; // 2 двери
	float vol_shelf; // полки

	vol_dvp = (h*0.01 * w*0.01) * 0.005;
	vol_dsp = (2 * h * 0.01 * d * 0.01 + 2 * w * 0.01 * d * 0.01) * 0.015; //без полок
	vol_wood = (h * 0.01 * w * 0.01) * 0.01;


	int i=415, shelf_count=0;
	while (h*10>i)
	{
		shelf_count++;
		i += 415;
	}
	vol_shelf = (shelf_count * (w-3)*0.01 * d*0.01) * 0.015;

	weight = vol_dvp * densy_dvp + densy_dsp * (vol_dsp + vol_shelf) + vol_wood * densy_wood;
	printf("масса шкафа %f кг ", weight);

	system("pause");
}
