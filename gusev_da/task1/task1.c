#include <stdio.h>
#include <locale.h>

void main1()
{
	setlocale(LC_ALL, "Rus");
	int shelf; // ���������� �����
	float bokovini, polki, krishki, dveri, stenka, massa; // ����� ���� ������� ����� � ������ �����
	int dvp, dsp, wood; // ��������� ���, ���, ������
	double dvp_v, dsp_v, wood_v; // ������� ���, ��� � ������
	double h, w, d; // ����� �����, ������ � �������


	dvp = 500;
	dsp = 800;
	wood = 1500;
	dsp_v = 1.5;
	dvp_v = 0.5;
	wood_v = 1;

	printf("������! ��� ��������� ��������� ����� ����� ������ �� ��� ��������.\n"
		"������ ������ ������ ��������� ������ ������ � �������.\n"
		"������ ������ ������ ��������� ������ ������, ����� � �������.\n"
		"������� ������� ��������� ������� ������ � �����.\n\n");
	do
	{
		printf("������� ������ ������ ������ ����� �� 180 �� 220 ��: ");
		scanf_s("%lf", &h);
	} while ((h < 180) || (h > 220));
	do
	{
		printf("������� ������ ������ ������ ����� �� 80 �� 120 ��: ");
		scanf_s("%lf", &w);
	} while ((w < 80) || (w > 120));
	do
	{
		printf("������� ������� �������� ����� �� 50 �� 90 ��: ");
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

	printf("����� ����� ����� %.3f ��", massa);
	system("pause");
}