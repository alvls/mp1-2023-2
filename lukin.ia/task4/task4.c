#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <locale.h>
#include <string.h>

int cena_tovara(int a)
{
	int cena;
	if (a == 0)
	{
		cena = 80;
	}
	else if (a == 1)
	{
		cena = 40;
	}
	else if (a == 2)
	{
		cena = 300;
	}
	else if (a == 3)
	{
		cena = 150;
	}
	else if (a == 4)
	{
		cena = 350;
	}
	else if (a == 5)
	{
		cena = 80;
	}
	return cena;
}
void tovar_name(int a)// a - ������������� ������ � ������� (������ ����� �������� ������������ ������ �������, � ������� ���� ��������� ���������� ��������������� ������� + ����� ���� �� ������� �������, ��������� ��� ������ �� ��� ��������������)
{
	if (a == 0)
	{
		printf("������(1�)");
	}
	else if (a == 1)
	{
		printf("����(�����)");
	}
	else if (a == 2)
	{
		printf("�������(500�)");
	}
	else if (a == 3)
	{
		printf("����� ���������(250�)");
	}
	else if (a == 4)
	{
		printf("������(1.5��)");
	}
	else if (a == 5)
	{
		printf("������ ��������(95�)");
	}
}
float skidka_cyfra()
{
	float skidka;
	int a;
	a = rand() % 15;
	if (a == 0 || a == 11 || a == 12 || a == 13 || a == 14)//����� �� ����������
	{
		skidka = 1;
	}
	if (a == 1)
	{
		skidka = 0.95;
	}
	else if (a == 2)
	{
		skidka = 0.9;
	}
	else if (a == 3)
	{
		skidka = 0.85;
	}
	else if (a == 4)
	{
		skidka = 0.8;
	}
	else if (a == 5)
	{
		skidka = 0.75;
	}
	else if (a == 6)
	{
		skidka = 0.7;
	}
	else if (a == 7)
	{
		skidka = 0.65;
	}
	else if (a == 8)
	{
		skidka = 0.6;
	}
	else if (a == 9)
	{
		skidka = 0.55;
	}
	else if (a == 10)
	{
		skidka = 0.5;
	}
	return skidka;
}
int skidka2(int real, float skidk, int kol)
{
	int sk;
	sk = 0.5 + (1 - (skidk / (real*kol))) * 100;
	return sk;
}
int main()
{
	int kod, vybor, itog = 1, i = 0, itogo = 0, real_cena = 0;
	float cena_ed, skidka;
	int arr[6] = { 0 };
	srand(time(NULL));
	setlocale(LC_ALL, "rus");
	char mol[] = "1234";
	char bread[] = "5678";
	char kolb[] = "1357";
	char butter[] = "2468";
	char chicken[] = "1122";
	char chok[] = "2233";
	char kode[] = "0000";
	printf("����� ���������� � ����������� �������!\n");
	printf("������ �������� �� ���������� ��� �����������!\n");
	printf("�������: ������ ����� ������ �� ������ - ��������. ������� ��� � ������������� ��������.\n");
	printf("1.������(1�): 80 ���. (1234)\n");
	printf("2.����(�����): 40 ���. (5678)\n");
	printf("3.�������(500�): 300 ���. (1357)\n");
	printf("4.����� ���������(250�): 150 ���. (2468)\n");
	printf("5.������(1.5��): 350 ���. (1122)\n");
	printf("6.������ ��������(95�): 80 ���. (2233)\n");
	printf("����� �� ������ ����� �������� ������ �� 5 �� 50 ���������\n");
	printf("*�������-������� �������* ������ ����� � �� ���� :(\n");
	do
	{
		printf("*���������� ��������*\n");
		scanf("%s", kode);
		if (strcmp(kode, mol) == 0)
		{
			arr[0]++;
		}
		else if (strcmp(kode, bread) == 0)
		{
			arr[1]++;
		}
		else if (strcmp(kode, kolb) == 0)
		{
			arr[2]++;
		}
		else if (strcmp(kode, butter) == 0)
		{
			arr[3]++;
		}
		else if (strcmp(kode, chicken) == 0)
		{
			arr[4]++;
		}
		else if (strcmp(kode, chok) == 0)
		{
			arr[5]++;
		}
		else
		{
			printf("�������� �������, ���������� ��� ���!");
		}
		printf("������ ���������� ������������?\n1 - ��, 0 - ���.\n");
		scanf("%i", &vybor);
		if (vybor == 1)
		{
			itog = 0;
		}
		else if (vybor == 0)
		{
			itog = 1;
		}
	} while (itog != 1);
	printf("*��� ���*\n");
	do
	{
		if (arr[i] != 0)
		{
			skidka = skidka_cyfra();
			cena_ed = arr[i] * cena_tovara(i) * skidka;
			tovar_name(i);
			printf(" � ���������� %i ", arr[i]);
			printf("�� ���� %i �� ������� ������, � � ������ ������: %.0f ������", cena_tovara(i), cena_ed);
			printf(", ���� ������ %i ���������\n", skidka2(cena_tovara(i), cena_ed, arr[i]));
			itogo = itogo + cena_ed;
			real_cena = real_cena + arr[i] * cena_tovara(i);
		}
		i++;
	} while (i < 6);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("��������� ������: %i\n", real_cena - itogo);
	printf("����� (� ������ ������): %i\n", itogo);
	printf("������� �� �������!\n��������� ���!\n");
	system("pause");
}