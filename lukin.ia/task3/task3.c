#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <locale.h>

int main()
{
	int n,c, d, i, chislo, vvod, chislo_pl, kor, buk, vsp1,vsp2, itog, vsp, vybor;
	int mass[5] = { 0 };
	int arr_bot[5] = { 0 };
	int arr_player[5] = { 0 };
	setlocale(LC_ALL, "rus");
	vvod = 0;
	i = 1;
	itog = 0;
	printf("����� ���������� � ���� *���� � ������*\n");
	printf("���� ���������� ��� ����� (2-5 ����, ������� �� �����������)\n");
	printf("�� �������� ������� ��� �����\n");
	printf("���� � ��� ������� ����� �� ���������� ������, �� ��� ����; �� ������ - ������\n");
	printf("������: �������� ����� 235, �� ����� 325\n");
	printf("�����:1  �����:2\n");
	do
	{
		printf("����� ����� ����� �� ������ ����������? (�� 2 �� 5)\n");
		scanf("%i", &n);
		if (n >= 2 && n <= 5)
		{
			vvod = 1;
		}
		else if (n < 2 || n > 5);
		{
			printf("������� ������, ����� ����� ���� �� 2 �� 5 ����\n");// ��� ��� ������ ��������� ������ ���, �� �������, ��� �������� ����� �����
		}
	} while (vvod != 1);
	srand(time(NULL));
	c =  1 + rand() % 9;
	mass[0] = c;//������ ����� ��������, ����� �������� �� ����
	do
	{
		d = 0;
		srand(time(NULL));
		d = rand() % 10;
		if (d == mass[0] || d == mass[1] || d == mass[2] || d == mass[3] || d == mass[4])
		{
			do
			{
				d = 0;
				srand(time(NULL));
				d = rand() % 10;
			} while (d == mass[0] || d == mass[1] || d == mass[2] || d == mass[3] || d == mass[4]);
		}
		mass[i] = d;
		i++;
	} while (i < n);
	chislo = mass[0] * 10000 + mass[1] * 1000 + mass[2] * 100 + mass[3] * 10 + mass[4];
	// ��� ���� ������� ������ ����
	if (n == 2)
	{
		chislo = chislo / 1000;
	}
	if (n == 3)
	{
		chislo = chislo / 100;
	}
	if (n == 4)
	{
		chislo = chislo / 10;
	}
	//���, �� �������� ���������� �����
	i = 1;
	vsp1 = chislo;
	do
	{
		vsp = vsp1 % 10;
		arr_bot[n - i] = vsp;
		vsp1 = vsp1/10;
		i++;
	} while (vsp1 != 0);
	do
	{
		i = 1;
		printf("���������� ������� ����� �� %i ������ ����\n", n);
		scanf("%i", &chislo_pl);
		vsp2 = chislo_pl;
		do
		{
			vsp = vsp2 % 10;
			arr_player[n - i] = vsp;
			vsp2 = vsp2 / 10;
			i++;
		} while (vsp2 != 0);
		i = 0;
		if (chislo == chislo_pl)
		{
			printf("�� ��������, �����������!!!\n");
			itog = 1;
			break;
		}
		else if (chislo != chislo_pl)
		{
			buk = kor = 0;
			do
			{
				if (arr_bot[i] == arr_player[i])
				{
					buk++;
				}
				else if (arr_player[i] != arr_bot[i] && (arr_player[i] == arr_bot[n-1] || arr_player[i] == arr_bot[n-2] || arr_player[i] == arr_bot[n-3] || arr_player[i] == arr_bot[n-4] || arr_player[i] == arr_bot[n-5]))
				{
					kor++;
				}
				i++;
			} while (i < n);
		}
		printf("�����:%i  �����:%i\n", buk, kor);
		printf("�� ������ �� �������? 0 - ���, 1 - ��\n");
		scanf("%i", &vybor);
		if (vybor == 0)
		{
			;
		}
		else if (vybor == 1)
		{
			itog = 1;
		}
	} while (itog != 1);
	system("pause");
}