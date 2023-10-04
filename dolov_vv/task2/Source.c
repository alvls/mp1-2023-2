#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>

int main()
{
	int h, w, d;
	float densy_dvp = 950;
	float densy_dsp = 600;
	float densy_wood = 720; //��������� ����
	float weight;

	setlocale(LC_ALL, "rus");

	float vol_dvp; //������ ������
	float vol_dsp; //2 ��������, ������� � ������ ������
	float vol_wood; // 2 �����
	float vol_shelf; // �����

	int flag = 0;

	do
	{
		printf("������� ������ ����� (180-220 (��)) \n");
		scanf("%d", &h);
		if ((h < 180) || (h > 220))
		{
			printf("����������� ������� ����� �����");
			system("pause");
			flag = 1;
		}
		else
			flag = 0;
	} while (flag == 1);

	do
	{
		printf("������� ������ ����� (80-120 (��))\n");
		scanf("%d", &w);
		if ((w < 80) || (w > 120))
		{
			printf("����������� ������� ������ �����");
			system("pause");
			flag = 1;
		}
		else
			flag = 0;
	} while (flag == 1);

	do
	{
		printf("������� ������� ����� (50-90 (��))\n");
		scanf("%d", &d);
		if ((d < 50) || (d > 90))
		{
			printf("����������� ������� ������� �����");
			system("pause");
			flag = 1;
		}
		else
			flag = 0;
	} while (flag == 1);


	vol_dvp = (h * 0.01 * w * 0.01) * 0.005;
	vol_dsp = (2 * h * 0.01 * d * 0.01 + 2 * w * 0.01 * d * 0.01) * 0.015; //��� �����
	vol_wood = (h * 0.01 * w * 0.01) * 0.01;


	int i = 415, shelf_count = 0;
	while (h * 10 > i)
	{
		shelf_count++;
		i += 415;
	}
	vol_shelf = (shelf_count * (w - 3) * 0.01 * d * 0.01) * 0.015;

	weight = vol_dvp * densy_dvp + densy_dsp * (vol_dsp + vol_shelf) + vol_wood * densy_wood;
	printf("����� ����� %f �� ", weight);

	system("pause");
}
